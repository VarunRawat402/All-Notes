------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Interview Questions:
------------------------------------------------------------------------------------------------------------------------------------------------

Producer Acknowledgments (spring.kafka.producer.acks):
→ Defines how many brokers must confirm a write before producer marks it successful
Producer → Leader → Replicas → Ack → Producer
Producer waits for the ack from the leader and the in-sync replicas to return the message as sent

spring.kafka.producer.acks:
    acks=0      → No confirmation (fast, unsafe)
    acks=1      → Leader confirms only
    acks=all    → Leader + all in-sync replicas (safest)

------------------------------------------------------------------------------------------------------------------------------------------------

min.insync.replicas:
→ Minimum number of in-sync replicas required to accept a write
→ Works together with acks

3 brokers, RF=3, min.insync.replicas=2
→ Write allowed only if ≥2 replicas are alive & in sync
→ Else → write fails

------------------------------------------------------------------------------------------------------------------------------------------------

What happens if a consumer crashes:

If a Kafka consumer crashes, Kafka reassigns its partitions to another consumer in the same consumer group and continues message consumption.

→ Kafka expects periodic heartbeats from consumers
→ Heartbeat stops → timeout → consumer marked dead
→ Rebalance triggered → partitions reassigned

What Happens to Messages:
    Offset committed        → no reprocessing
    Offset not committed    → message reprocessed by another consumer

------------------------------------------------------------------------------------------------------------------------------------------------

What is idempotent producer:
    → Kafka retries automatically if ack fails
    → Retries may cause duplicate messages
    → Kafka avoids duplicates using:
    → ProducerId + Sequence Number

------------------------------------------------------------------------------------------------------------------------------------------------
At-most-once vs At-least-once vs Exactly-once;
------------------------------------------------------------------------------------------------------------------------------------------------

At-most-once:
    Producer sends message
    Offset committed before processing
    Message lost if crash happens
    offsets are autocomitted

------------------------------------------------------------------------------------------------------------------------------------------------

At-least-once
    Producer sends message
    Offset committed after processing
    Duplicates possible if retry happens

@KafkaListener(...)
public void consume(OrderEvent event, Acknowledgment ack) {
    // process message
    ack.acknowledge(); // commit AFTER processing
}

------------------------------------------------------------------------------------------------------------------------------------------------

Exactly-once
    Kafka transactions used
    Producer + consumer coordinated
    No duplicates, no loss, atomic across topics/partitions

spring:
  kafka:
    producer:
      enable-idempotence: true
      transaction-id-prefix: tx-

kafkaTemplate.executeInTransaction(kafkaTemplate -> {
    kafkaTemplate.send("order_topic", orderId, event);
});


Exactly Once Working:
It helps us only when kafka retries internally not when application sends same message again
Consumer reads from read-commited message but if processing is done and consumer crashses when offsets are commited
message can be re-assign to different consumer and same message can be processes again

So idempotency is needed even with this

------------------------------------------------------------------------------------------------------------------------------------------------

DLT:
A Dead Letter Topic (DLT) is a separate Kafka topic where messages are sent after all retry attempts fail and the message still cannot be processed successfully.

DLT Created manually when using with DefaultErrorHandler
DLT Created automatically when using with @Retryable 

Later, failed message can be logged, re-publish from DLT

------------------------------------------------------------------------------------------------------------------------------------------------

Retry in Kafka:
Re-processing the failed messages automatically or manually

When consumer fails:
    The offset is not commited
    kafka will re-assign the same message

------------------------------------------------------------------------------------------------------------------------------------------------

Approach 1: Default retry (offset not committed)

@KafkaListener(topics = "order_create", groupId = "grp1")
public void consume(String message) {
    // if exception occurs, offset not committed
}

Exception → offset not committed
Kafka re-sends the same message
When retry happens kafka blocks that partition so other messages are also waiting to get processes
This can cause infinite retry if message is failing again and again and infinite block of partition

------------------------------------------------------------------------------------------------------------------------------------------------

Approach 2: Retry with DefaultErrorHandler (MOST USED):

Consumer receives message   →   Processing fails
DefaultErrorHandler retries the same record
Retries exhausted
DeadLetterPublishingRecoverer publishes message to  →   original-topic-dlt
Offset is committed   →   Consumer moves on

Implementation:

1: DeadLetterPublishingRecoverer:
    This component publishes the failed message to a DLT.

@Bean
public DeadLetterPublishingRecoverer deadLetterPublishingRecoverer(
        KafkaTemplate<Object, Object> kafkaTemplate) {

    return new DeadLetterPublishingRecoverer(
        kafkaTemplate,
        (record, ex) ->
            new TopicPartition(record.topic() + "-dlt", record.partition())
    );
}

2: DefaultErrorHandler:
    Control retries, backoff

@Bean
public DefaultErrorHandler errorHandler(
        DeadLetterPublishingRecoverer recoverer) {

    return new DefaultErrorHandler(
            recoverer,
            new FixedBackOff(2000L, 3) // 3 retries, 2 sec delay
    );
}

3: Attach ErrorHandler to Listener Factory

@Bean
public ConcurrentKafkaListenerContainerFactory<String, String>
kafkaListenerFactory(
        ConsumerFactory<String, String> consumerFactory,
        DefaultErrorHandler errorHandler) {

    ConcurrentKafkaListenerContainerFactory<String, String> factory =
            new ConcurrentKafkaListenerContainerFactory<>();

    factory.setConsumerFactory(consumerFactory);
    factory.setCommonErrorHandler(errorHandler);
    return factory;
}

------------------------------------------------------------------------------------------------------------------------------------------------

Approach 3: Non-blocking retry using Retry Topics (BEST PRACTICE):
    It retry the messages without blocking the main consumer
    DefaultErrorHandler, ConsumerFactory, DeadLetterPublishingRecoverer are configured automatically

Consumer receives message   →   Processing fails
Retry topics & DLT are automatically created
Offset is committed
Messages are passed to Retry topics 1 by 1 
Retries exhausted
Message is passed to DLT 

@RetryableTopic(
    attempts = 4,
    backoff = @Backoff(delay = 2000, multiplier = 2),
    dltTopicSuffix = "-dlt"
)
@KafkaListener(topics = "order_create", groupId = "order-group")
public void consume(String message) {
    throw new RuntimeException("temporary failure");
}

------------------------------------------------------------------------------------------------------------------------------------------------

What causes consumer lag:
    → Producer faster than consumer
    → Slow business logic
    → External API calls
    → Heavy DB operations

Fix:
    → Optimize processing
    → Increase listener concurrency
    → Use retry topics
    → Increase partitions
    → Scale Kafka

------------------------------------------------------------------------------------------------------------------------------------------------

How to reprocess old messages:
Reprocessing means consuming messages again that were already processed. 
This is done by moving the consumer offset backward or republishing messages.

Kafka stores messages by offset, not by status. 
Resetting offsets makes Kafka resend them.

Reprocess from a specific time:
    --to-datetime 2026-01-10T10:00:00.000

Reprocess last N messages:
    --shift-by -100

Important notes:
    Consumer group must be stopped
    Affects all consumers in the group
    Can cause duplicate processing

Reprocess Messages from DLT (Best Practice):
    Only failed messages need reprocessing
    Safer than full replay

@KafkaListener(topics = "order-create-dlt", groupId = "dlt-grp")
public void reprocess(String message) {
    kafkaTemplate.send("order-create", message);
}

Old Kafka messages are reprocessed by resetting consumer offsets, 
replaying from a DLT, or using a new consumer group, depending on whether full or selective reprocessing is needed

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Listener Concurrency:

spring.kafka.listener.concurrency=4
By default, a Kafka listener processes messages synchronously, one message at a time

Concurrency creates multiple consumer threads inside a single application instance.

With concurrency 1  → 1 thread reads 4 partitions one by one
With concurrency 4  → 4 threads read 4 partitions in parallel

If consumer takes 1 sec to process 1 message
Without concurrency     → 4 messages take ~4 sec
With concurrency 4      → 4 messages take ~1 sec

------------------------------------------------------------------------------------------------------------------------------------------------

Disadvantages of Using Spring Kafka Concurrency:

1: Concurrency is limited by the JVM and core size, It takes a load on CPU
2: If one instance goes down, all threads stop → single point of failure
3: Kubernetes scales pods better than increasing threads in one JVM

------------------------------------------------------------------------------------------------------------------------------------------------