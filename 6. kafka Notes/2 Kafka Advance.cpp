-----------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Producer Acknowledgments:
    → Controls how many confirmations producer waits for before marking message as sent

spring.kafka.producer.acks:
    acks=0   → no confirmation, fastest + data loss possible 
    acks=1   → leader confirms only, leader crash = data loss 
    acks=all → leader + all ISR confirm

-----------------------------------------------------------------------------------------------------------------------------------------------------

min.insync.replicas:
    → Minimum number of ISR replicas required to accept a write
    → Works WITH acks=all for guaranteed durability

Example:
3 brokers, RF=3, min.insync.replicas=2 :
    → Write accepted only if ≥2 replicas in sync
    → 1 broker down → still works (2 remaining) ✅
    → 2 brokers down → write fails → better than silent data loss ✅

-----------------------------------------------------------------------------------------------------------------------------------------------------
At-most-once vs At-least-once vs Exactly-once;
-----------------------------------------------------------------------------------------------------------------------------------------------------

At-most-once:
    → Producer sends message → Offset committed BEFORE processing
    → If app crashes after commit → message is lost.
    → offsets are autocomitted
    → No duplicates but data loss possible

spring.kafka.consumer.enable-auto-commit=true
spring.kafka.consumer.auto-commit-interval=100

@KafkaListener(topics = "email-topic")
public void sendEmail(String msg) {
    // offset already committed
    process(msg);           // crash here → message lost
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

At-least-once
    → Producer sends message → Offset committed AFTER processing
    → If processing fails → offset not commited → message re-delivered.
    → No data loss but duplicates possible

@KafkaListener(...)
public void consume(OrderEvent event, Acknowledgment ack) {
    process(msg);
    ack.acknowledge();      // commit AFTER processing
}   

-----------------------------------------------------------------------------------------------------------------------------------------------------

Exactly-once
    → Kafka transaction + DB transaction atomic together
    → Idempotent producer → same message sent twice → stored once
    → If anything fails   → entire transaction rolls back
    → No duplicates + no data loss

spring.kafka.producer.transaction-id-prefix=tx-
spring.kafka.producer.properties.enable.idempotence=true

@KafkaListener(topics = "payment-topic")
@Transactional
public void handlePayment(String msg) {
    updateDatabase(msg);
    sendAnotherKafkaEvent(msg);     // both succeed or both rollback → atomic

}

-----------------------------------------------------------------------------------------------------------------------------------------------------

DLT:
→ A Dead Letter Topic is a separate Kafka topic where messages are sent after all retry attempts fail and the message still cannot be processed successfully.

→ DLT Created manually when using DefaultErrorHandler
→ DLT Created automatically when using @RetryableTopic

→ Failed messages stored here for later reprocessing

-----------------------------------------------------------------------------------------------------------------------------------------------------

Retries:
    → When a message processing fails, we can retry it a few times before giving up and sending it to DLT.

1: Default retry:

→ Exception → offset not committed → Kafka re-sends same message
→ When retry happens kafka blocks that partition so other messages are also waiting to get processes
→ This can cause infinite retry if message is failing again and again and infinite block of partition

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: DefaultErrorHandler + DLT (Most Used):
    → Exception → Retries X times with backoff → exhausted 
    → sends to DLT → commits offset → moves on
    → Blocks the partition when retrying but unblocks after retries exhausted

Implementation:

1: DeadLetterPublishingRecoverer:
    → publishes failed message to topic-dlt

2: DefaultErrorHandler:
    → controls retries + backoff

3: Attach ErrorHandler to Listener Factory

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: @RetryableTopic - Non-blocking:
    → Retries WITHOUT blocking main partition
    → Retry topics + DLT created automatically
    → Offset committed immediately → main partition keeps moving

@RetryableTopic( attempts = 4, backoff = @Backoff(delay = 2000, multiplier = 2), dltTopicSuffix = "-dlt" )
@KafkaListener(topics = "order_create", groupId = "order-group")
public void consume(String message) {
    throw new RuntimeException("temporary failure");
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Listener Concurrency:
    → By default, a Kafka listener processes messages synchronously, one message at a time
    → Concurrency creates multiple consumer threads inside a single application instance.

→ spring.kafka.listener.concurrency=4
    concurrency=1 → 1 thread reads 4 partitions one by one → slow
    concurrency=4 → 4 threads read 4 partitions in parallel → 4x faster

Example:
    1 message takes 1s to process
    Without concurrency → 4 messages = 4s
    With concurrency=4  → 4 messages = 1s 

Concurrency cannot exceed number of partitions
   → 4 partition + concurrency=8
   → only 4 threads active, 4 idle → no performance gain

-----------------------------------------------------------------------------------------------------------------------------------------------------

Disadvantages of Using Spring Kafka Concurrency:

1: CPU heavy → limited by JVM + core size
2: Single point of failure → one instance down → all threads stop
3: Kubernetes pod scaling is better than increasing threads in one JVM

-----------------------------------------------------------------------------------------------------------------------------------------------------

KafkaListener:
    → @KafkaListener is used to consume messages from Kafka topics.
    → Method is triggered automatically
    → Message is converted to DTO before method execution

@KafkaListener(topics = "user-create", groupId = "user-consumer")
public void updateWallet(UserCreatedEvent event) {
    // Runs automatically when message arrives to user-create topic
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Type Headers:
    → Tell the consumer which Java class the JSON should be converted into.
    → Enables automatic Deserialization of JSON → DTO conversion.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Scenario 1: 
    → 1 topic → 1 DTO
    → user topic  → UserDTO object
    → order topic → OrderDTO object
    → No header needed
    → kafka Listener will automatically convert the json to UserDTO object based on the function parameter

@KafkaListener(topics = "user-create")
public void userCreate(UserDto userDto) {
    // Json message automatically converted to UserDto object
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Scenario 2: 
    → 1 topic → Multiple DTOs
    → user topic → UserCreateDTO + UserUpdateDTO + UserDeleteDTO
    → Header required

Code:
configProps.put(JsonDeserializer.TYPE_MAPPINGS, 
    "userCreation:com.example.dto.UserCreationEvent," +     //message with userCreation typeId will be mapped to userCreatedEvent DTO
    "userUpdate:com.example.dto.UserUpdateEvent,"     +     //message with userUpdate typeId will be mapped to UserUpdateEvent DTO     
    "userDelete:com.example.dto.UserDeleteEvent"            //message with userDelete typeId will be mapped to UserDeleteEvent DTO
);         

-----------------------------------------------------------------------------------------------------------------------------------------------------

How to consume mesasges using kafka listener for multiple DTOs in one topic:

→ 1 Topic → UserCreatedEvent + OrderCreatedEvent
→ Based on header value it will call the respective method

@Service
@KafkaListener(topics = "business-events-topic")
public class BusinessEventsConsumer {

    @KafkaHandler
    public void handleUser(UserCreatedEvent event) {
        userService.save(event);
    }

    @KafkaHandler
    public void handleOrder(OrderCreatedEvent event) {
        orderService.save(event);
    }

    @KafkaHandler(isDefault = true)
    public void unknown(Object event) {
        System.out.println("Unknown event type");
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------



