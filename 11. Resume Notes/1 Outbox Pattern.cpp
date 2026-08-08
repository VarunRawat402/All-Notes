------------------------------------------------------------------------------------------------------------------------------------------------
Outbox Pattern:
------------------------------------------------------------------------------------------------------------------------------------------------

→ Saving something in DB and seding kafka event, These are two separate operations.
→ If the DB save succeeds but the Kafka send fails (network issue, broker down)
→ You end up with data saved but no event sent — other services never find out. Thats an inconsistency.
→ The Outbox Pattern fixes this by never doing a "direct" Kafka send inside the business logic at all. 

Instead:
→ Save your actual entity AND outbox record both in the same DB transaction.
→ A separate background a scheduler later reads these saved "pending events" and actually publishes them to Kafka.
→ Since both writes (entity + outbox event) happen in one transaction, either both succeed or both fail — no in-between broken state. 

------------------------------------------------------------------------------------------------------------------------------------------------

1: Customer Service:
→ Save Customer + Kafka Payload + Customer Outbox Record
→ Because of @Transactional, if any of these three steps fail, the entire transaction rolls back and nothing is saved.

@Service
public class CustomerService {

    @Transactional
    public void createCustomer(CreateCustomerRequest dto) throws Exception {

        //Customer is created and saved
        Customer Customer = new Customer( dto.getEmail(), dto.getName());
        CustomerRepository.save(Customer);

        //kafka payload is created
        CustomerCreatedEvent event = CustomerCreatedEvent.from(Customer);

        //Outbox is created and saved 
        CustomerOutbox outbox = new CustomerOutbox( event.getEventId(), "Customer_created", event, Status.NEW);
        outboxRepository.save(outbox);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

2: Kafka Scheduler:
→ Every 10 sec, it fetches batch of 50 pending outbox events
→ Marks each as processing so other schedulers dont pick it up
→ Sends to kafka and handle success/failure in callback

→ Cannot use @Retryable and @Recover here as its asynchronous way of sending messages
→ Retryable only works by intercepting an exception thrown from a method and retrying the same method call.
→ But with async kafka the failure comes back in a callback, not as an exception thrown from the method. So @Retryable cannot intercept it.

public class OutboxPublisher {

    private static final int MAX_RETRIES = 5;

    @Scheduled(fixedDelay = 2000)
    @Transactional
    public void publish() {

        List<CustomerOutbox> events = repository.fetchBatch(PageRequest.of(0, 50));

        for (CustomerOutbox event : events) {

            event.setStatus(EventOutbox.Status.PROCESSING);
            repository.save(event);

            kafkaTemplate.send("Customer_create", event.getAggregateId(), event.getPayload()).addCallback(
                result -> handleSuccess(event),
                ex -> handleFailure(event, ex)
            );
        }
    }

    private void handleSuccess(EventOutbox event) {
        event.setStatus(EventOutbox.Status.SENT);
        repository.save(event);
    }

    private void handleFailure(EventOutbox event, Throwable ex) {

        int retries = event.getRetryCount() + 1;
        event.setRetryCount(retries);

        if (retries >= MAX_RETRIES) {
            event.setStatus(EventOutbox.Status.FAILED);
        } else {
            event.setStatus(EventOutbox.Status.PENDING);
            event.setNextRetryAt(Instant.now().plusSeconds(backoff(retries)));
        }

        repository.save(event);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

3: OutBox Repository:

→ pending or processing 
→ Retry count < 3 or null
→ Asc so that older events are sent first
→ For update skip locked → so that multiple schedulers can run in parallel without picking same events
→ Limit 10 → so that we dont pick too many events at once and overload kafka


@Query(value = """
        SELECT * FROM outbox_event
        WHERE e.status IN ('PENDING', 'PROCESSING')
        AND (retry_count < 3 OR retry_count IS NULL)
        AND (next_retry_at IS NULL OR next_retry_at <= NOW())
        ORDER BY created_at ASC
        FOR UPDATE SKIP LOCKED
        LIMIT 10
        """, nativeQuery = true)
List<OutboxEvent> fetchForPublishing();

------------------------------------------------------------------------------------------------------------------------------------------------

Synchronous Alternative (Optional):
→ Kafka messages can also be sent synchronously using kafka.send().get():
→ Allows retry with @Retryable and @Recover methods.
→ Disadvantage: .get() is blocking → slows down processing for large batches.

@Component
public class OutboxScheduler {

    @Retryable(
    retryFor = KafkaException.class,
    maxAttempts = 3,
    backoff = @Backoff(delay = 2000)
    )
    public void publish(OutboxEvent event) {
        kafkaTemplate.send(event.getTopic(), event.getId(), event.getPayload()).get();      //blocking
    }

    @Recover
    public void recover(KafkaException ex, OutboxEvent event) {
        event.markFailed();
        outboxRepository.save(event);
    }

    @Scheduled(fixedDelay = 5000)
    @Transactional
    public void publish() {

        List<OutboxEvent> events = outboxRepository.fetchForPublishing();

        for (OutboxEvent event : events) {
            try {
                publish(event);
                event.setStatus(Status.SENT);
                outboxRepository.save(event);
            } catch (Exception e) {
            }
        }
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Idempotency Checking:
    → Kafka can send duplicate messages due to retries, network issues, or consumer restarts.
    → Consumers must check for duplicates before processing to avoid double-processing.

------------------------------------------------------------------------------------------------------------------------------------------------

1: Wallet Consumer Code:
    First time the event arrives → wallet gets created fine.
    If the same event arrives again (duplicate delivery) → trying to insert another wallet with the same customerId violates the unique constraint 
    → throws DataIntegrityViolationException → you just catch it and do nothing. 
    No duplicate wallet gets created.

@KafkaListener(topics = "Customer_created", groupId = "wallet-service")
@Transactional
public void consume(CustomerCreatedEvent event) {

    try {
        walletRepository.save(
            new Wallet(
                UUID.randomUUID(),
                event.getCustomerId(),
                BigDecimal.ZERO
            )
        );
    } catch (DataIntegrityViolationException e) {
        // duplicate event → wallet already exists
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

2: Email Consumer Code:
    → No DB operation so we need to use redis for idempotency check
    → If CustomerId is not present in cache, add in cache and perform the operation
    → If CustomerId is present, skip the operation

public boolean markIfFirst(UUID eventId) {
    return Boolean.TRUE.equals(
        redisTemplate.opsForValue()
          .setIfAbsent(eventId.toString(), "1", Duration.ofDays(1))
    );
}

@KafkaListener(topics = "Customer_created", groupId = "email-service")
public void consume(CustomerCreatedEvent event) {

    if (!redisService.markIfFirst(event.getEventId())) {
        return; // duplicate
    }

    emailService.sendWelcomeMail(event.getEmail());
}

------------------------------------------------------------------------------------------------------------------------------------------------

Testing:

→ I tested the CustomerService by creating unit tests that mock the CustomerRepository and OutboxRepository.
→ I verified that when createCustomer() is called, the Customer and outbox record are saved together, and if any exception occurs, the transaction rolls back.

→ My friend tested the OutboxPublisher by mocking the KafkaTemplate and OutboxRepository.
→ Mock KafkaTemplate
Simulate:
    → Success callback → status becomes SENT
    → Failure callback → retryCount increments, status becomes PENDING or FAILED

------------------------------------------------------------------------------------------------------------------------------------------------