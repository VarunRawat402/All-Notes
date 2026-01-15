------------------------------------------------------------------------------------------------------------------------------------------------
User Creation Service Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

1: User Creation DTO:
2: User Entity:
3: User Kafka Entity:
4: OutBox Entity:
5: Service Layer:
6: OutBox Repository:
7: Kafka Scheduler:

------------------------------------------------------------------------------------------------------------------------------------------------

1. User Creation:

Client sends a UserRequestDTO.
DTO is validated and converted into a User entity.
A UserCreatedEvent is created from the User.
A UserOutboxEntity is created to store the event for Kafka publishing.
User and UserOutboxEntity are saved in the same database transaction → ensures atomicity (either both are saved or none).
The UserCreatedEvent is stored in the UserOutboxEntity to be published to Kafka.

------------------------------------------------------------------------------------------------------------------------------------------------

2. Outbox Scheduler (Asynchronous Kafka Publishing):

Scheduler periodically fetches UserOutboxEntity rows with PENDING or PROCESSING status from the repository.
Row-level locking is used with skip locked rows to prevent multiple pods from processing the same event.
Fetched entities are marked as PROCESSING and saved back to the database.
Events are sent to Kafka asynchronously using addCallback():
On success → status marked as SENT
On failure → retry count incremented and status marked as PENDING
If retry count exceeds MAX_RETRIES → status marked as FAILED
FAILED events can be retried manually or by the scheduler at a later time.

------------------------------------------------------------------------------------------------------------------------------------------------

3. Synchronous Alternative (Optional):

Kafka messages can be sent synchronously using kafka.send().get():
Allows retry with backoff and recover methods.
Disadvantage: .get() is blocking → slows down processing for large batches.

------------------------------------------------------------------------------------------------------------------------------------------------

Key Points / Highlights

Atomicity: User and Outbox entity saved in the same transaction.
Reliable delivery: Outbox pattern ensures events are not lost if service crashes.
Concurrency safe: Row locking + skip locked rows prevent multiple pods from publishing the same event.
Retry mechanism: Handles temporary Kafka failures with retry count and backoff.
Idempotency: Consumer ensures duplicate events are not processed.


------------------------------------------------------------------------------------------------------------------------------------------------

1: UserCreatedEvent:
    kafka Event which will be sent to kafka

public class UserCreatedEvent {

    private UUID eventId;
    private Long userId;
    private String email;
    private Instant createdAt;

    public static UserCreatedEvent from(User user) {
        return new UserCreatedEvent(
            UUID.randomUUID(),
            user.getId(),
            user.getEmail(),
            Instant.now()
        );
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

2: OutBox Entity:
    Processed by scheduler to send kafka event

public class EventOutbox{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String userId;
    private String eventType;

    @Lob
    private String payload;

    @Enumerated(EnumType.STRING)
    private Status status;

    private int retryCount;
    private Instant nextRetryAt;

    public enum Status {
        PENDING,
        PROCESSING,
        SENT,
        FAILED
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

3: Service Layer:
    Save User and UserOutboxEntity

@Service
public class UserService {

    @Transactional
    public void createUser(CreateUserRequest dto) throws Exception {

        User user = new User(
            dto.getEmail(),
            dto.getName()
        );

        userRepository.save(user); // business data

        UserCreatedEvent event = UserCreatedEvent.from(user);

        outboxRepository.save(
            new OutboxEvent(
                event.getEventId(),
                "user_created",
                event,
                Status.NEW,
            )
        );
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

4: OutBox Repository:
    Used to make row locking so multiple pods cannot use single row together
    Prevents multiple pods publishing the same event

public interface OutboxRepository extends JpaRepository<OutboxEvent, UUID> {
//This fetch rows and locks the fetched rows and skips the locked rows 
    @Query(
      value = """
        SELECT * FROM outbox_event
        WHERE status = 'NEW'
        FOR UPDATE SKIP LOCKED
        LIMIT 10
      """,
      nativeQuery = true
    )
    List<OutboxEvent> fetchForPublishing();
}

or 

public interface EventOutboxRepository extends JpaRepository<EventOutbox, Long> {
//This locks the fetched rows only not skips the locked rows
    @Lock(LockModeType.PESSIMISTIC_WRITE)                   //locks the row 
    @Query("""
        SELECT e FROM EventOutbox e
        WHERE e.status IN ('PENDING', 'PROCESSING')
          AND (e.nextRetryAt IS NULL OR e.nextRetryAt <= CURRENT_TIMESTAMP)
        ORDER BY e.createdAt
    """)
    List<EventOutbox> fetchBatch(Pageable pageable);
}

------------------------------------------------------------------------------------------------------------------------------------------------

5: Kafka Scheduler:
    Send Kafak Events to kafka topic, runs every 2 seconds
    Kafka Events will be sent asynchronously with callBack mechanism to handle success and failure
    Cannot use @Retryable and @Recover here as its asynchronous way of sending messages
    Failed message will be manually retried after fixing the issue


@Component
@RequiredArgsConstructor
@Slf4j
public class OutboxPublisher {

    private static final int MAX_RETRIES = 10;

    @Scheduled(fixedDelay = 2000)
    @Transactional
    public void publish() {

        List<EventOutbox> events =
                repository.fetchBatch(PageRequest.of(0, 50));

        for (EventOutbox event : events) {

            event.setStatus(EventOutbox.Status.PROCESSING);
            repository.save(event);

            kafkaTemplate
                .send("user_create", event.getAggregateId(), event.getPayload())
                .addCallback(
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

        log.error("Kafka publish failed for outbox id {}", event.getId(), ex);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------
Consumer:
------------------------------------------------------------------------------------------------------------------------------------------------

Wallet Consumer Code:
// idempotency is checked with save() DB operation using unique key { user Id }
// If user is saved, we get error then continue dont process the message

@KafkaListener(topics = "user_created", groupId = "wallet-service")
@Transactional
public void consume(UserCreatedEvent event) {

    try {
        walletRepository.save(
            new Wallet(
                UUID.randomUUID(),
                event.getUserId(),
                BigDecimal.ZERO
            )
        );
    } catch (DataIntegrityViolationException e) {
        // duplicate event → wallet already exists
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Email Consumer Code:
// Stores userId / eventId in redis
// If userId is present skip the operation
// If not perform the operation

public boolean markIfFirst(UUID eventId) {
    return Boolean.TRUE.equals(
        redisTemplate.opsForValue()
          .setIfAbsent(eventId.toString(), "1", Duration.ofDays(1))
    );
}

@KafkaListener(topics = "user_created", groupId = "email-service")
public void consume(UserCreatedEvent event) {

    if (!redisService.markIfFirst(event.getEventId())) {
        return; // duplicate
    }

    emailService.sendWelcomeMail(event.getEmail());
}

------------------------------------------------------------------------------------------------------------------------------------------------

Synchronous way of sending mesasges to kafka with Retry and Recover mechanism:

@Component
public class OutboxScheduler {

//Synchronous blocking way of sending message to kafka
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