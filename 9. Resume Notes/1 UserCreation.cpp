------------------------------------------------------------------------------------------------------------------------------------------------
Customer Creation Service Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

1: Customer Service:

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
    → Cannot use @Retryable and @Recover here as its asynchronous way of sending messages

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

1: Wallet Consumer Code:
    → Idempotency is checked using DB Operation
    → Due to unique key constraint duplicate operation wont happen

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