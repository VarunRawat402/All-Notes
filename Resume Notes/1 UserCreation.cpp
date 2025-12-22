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

1: User Creation DTO:
Used to receive user creation data from client.
Used for validation 

Code:

public class CreateUserRequest {
    private String email;
    private String name;
}

------------------------------------------------------------------------------------------------------------------------------------------------

2: User Entity:
Used to map user data to the DB 

Code:

@Entity
@Table(
    name = "users",
    uniqueConstraints = @UniqueConstraint(columnNames = "email")
)
public class User {

    @Id
    private UUID id;

    private String email;
    private String name;
}

------------------------------------------------------------------------------------------------------------------------------------------------

3: User Kafka Entity:
Used to store user data to send to kafka topics

public class UserCreatedEvent {

    private UUID eventId;
    private UUID userId;
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

4: OutBox Entity:
Used to store user data to send to kafka topics later

@Entity
@Table(name = "outbox_event")
public class OutboxEvent {

    @Id
    private UUID id; // SAME as eventId

    private String topic;

    @Lob
    private String payload;

    @Enumerated(EnumType.STRING)
    private Status status; // NEW, SENT

    private int retryCount;
}

------------------------------------------------------------------------------------------------------------------------------------------------

5: Service Layer:
Create and save User in DB + Outbox entity

@Service
public class UserService {

    @Transactional
    public void createUser(CreateUserRequest dto) throws Exception {

        User user = new User(
            UUID.randomUUID(),
            dto.getEmail(),
            dto.getName()
        );

        userRepository.save(user); // business data

        UserCreatedEvent event = UserCreatedEvent.from(user);

        outboxRepository.save(
            new OutboxEvent(
                event.getEventId(),
                "user_created",
                objectMapper.writeValueAsString(event),
                Status.NEW,
                0
            )
        );
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

6: OutBox Repository:
Used to make row locking so multiple pods cannot use single row together
Prevents multiple pods publishing the same event

public interface OutboxRepository extends JpaRepository<OutboxEvent, UUID> {

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

------------------------------------------------------------------------------------------------------------------------------------------------

7: Kafka Scheduler:
Used to send user information to kafka topics using outbox Entity

@Component
public class OutboxScheduler {

    @Scheduled(fixedDelay = 5000)
    @Transactional
    public void publish() {

        List<OutboxEvent> events = outboxRepository.fetchForPublishing();

        for (OutboxEvent event : events) {
            try {
                kafkaTemplate.send(event.getTopic(), event.getPayload());
                event.setStatus(Status.SENT);
            } catch (Exception e) {
                event.incrementRetry();
            }
        }
    }
}


------------------------------------------------------------------------------------------------------------------------------------------------
Consumer:
------------------------------------------------------------------------------------------------------------------------------------------------

Wallet Consumer Code:
// No Redis or DB is used to perform idempotency
// idempotency is checked using DB operation using unique key { user Id }

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
// Stores eventId in redis or DB 
// If eventId is present skip the operation
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
Retry and Backoff :

When your @KafkaListener method or consumer throws an exception
Spring Kafkas error handler catches it
After the configured backoff delay
The same @KafkaListener method is invoked again
With the same record (same partition, same offset) so it can process the same message again

Flow:

@KafkaListener method runs
↓
Exception thrown
↓
ErrorHandler waits (backoff)
↓
@KafkaListener method runs AGAIN (same message)
↓
Success → offset committed
OR
Retries exhausted → send to DLT → offset committed

------------------------------------------------------------------------------------------------------------------------------------------------
Monitoring:

When work is done asynchronously (Kafka, queues, background jobs), failures are not visible to the user immediately.
So the system must actively track and surface failures.

1: Business-level failures (most important):
Email not sent + Wallet not created + Notification not delivered
These are business failures, not infra failures.

2: Technical signals:
Kafka consumer lag + Retry count + DLT growth rate + Processing latency

------------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

1: Structured logging:
log.error("Wallet creation failed for userId={}", userId, ex);

2: Metrics:
Wallet creation failed counter
Email not sent failed counter

3: Dead Letter Topic monitoring:
Alert if DLT count > threshold
Alert if growth rate spikes

Example:
If more than 10 wallet-creation events go to DLT in 5 minutes → alert

------------------------------------------------------------------------------------------------------------------------------------------------
Prioritization:

Not all async work is equally important.
    Wallet creation → critical
    Welcome email → non-critical
    Marketing email → lowest priority

------------------------------------------------------------------------------------------------------------------------------------------------

How prioritization is done in real systems:

1. Separate Kafka topics / queues:
wallet_create_topic     (high priority)
email_notification_topic (low priority)

2. Separate consumer groups / resources:
Wallet Consumer: 6 instances
Email Consumer: 2 instances

------------------------------------------------------------------------------------------------------------------------------------------------

In async systems, we actively monitor business-level failures like wallet creation or email delivery using logs, metrics, and DLT alerts. 
We also prioritize critical async tasks by isolating them into separate topics and consumer groups with higher resources and stricter retry policies, while non-critical tasks like marketing emails run with lower priority.

------------------------------------------------------------------------------------------------------------------------------------------------

https://chatgpt.com/c/69481aea-c948-8323-9f4d-2ddafd2624fb
+

------------------------------------------------------------------------------------------------------------------------------------------------\
Ordering of Keys in Kafka:
------------------------------------------------------------------------------------------------------------------------------------------------

Why ordering matters:

USER_CREATED  → USER_UPDATED → USER_DELETED

USER_UPDATED → USER_CREATED
What breaks:
    Consumer receives UPDATE before CREATE
    User does not exist → error / inconsistent state

Messages with the same key go to the same partition, therefore are ordered.

------------------------------------------------------------------------------------------------------------------------------------------------

You must choose a business entity identifier as key:

Good keys
    userId
    orderId
    accountId

Bad keys
    random UUID
    timestamp
    null key

------------------------------------------------------------------------------------------------------------------------------------------------

Example:

kafkaTemplate.send(
    "user.created.v1",
    userId.toString(),   // key
    eventPayload         // value
);

All events for userId=101:

partition-2:
    USER_CREATED
    USER_UPDATED
    USER_DELETED

What happens if you dont use key:
kafkaTemplate.send("user.created.v1", payload);

partition-1 → USER_CREATED
partition-3 → USER_UPDATED
Order broken ❌

------------------------------------------------------------------------------------------------------------------------------------------------