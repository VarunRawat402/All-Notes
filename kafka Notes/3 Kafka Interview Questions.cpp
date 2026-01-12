------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Interview Questions:
------------------------------------------------------------------------------------------------------------------------------------------------

Producer acknowledgments:
    spring.kafka.producer.acks:
    It defines how many Kafka brokers must confirm a message is written before the producer considers it successfully sent.

When a producer sends a message to Kafka:
The message is written to the leader partition
leader replicate the mesasge to other brokers
Kafka waits for acknowledgments based on the acks value.
after confirmations, Kafka replies success to the producer.

spring.kafka.producer.acks: 0/1/all
    0   -> No acknowledgment
    1   -> Leader acknowledgment only
    all -> Leader + all in-sync replicas

------------------------------------------------------------------------------------------------------------------------------------------------

min.insync.replicas:
It is the minimum number of replicas that must be alive and in-sync for Kafka to accept a write.
min.insync.replicas and acks work together 

3 brokers, 3 replication factor, ISR count - 3
min.insync.replicas:2
It means do not accept write from producer until 2 replicas are in sync or throw exception

------------------------------------------------------------------------------------------------------------------------------------------------

What happens if a consumer crashes:
If a Kafka consumer crashes, Kafka reassigns its partitions to another consumer in the same consumer group and continues message consumption.

Kafka periodically receives heartbeats from consumers
Consumer stops sending heartbeats
Broker waits for session.timeout.ms
Consumer is marked dead
Rebalance is triggered
Partitions of crashed consumer are assigned to other consumers

What Happens to Messages:

Case 1: Offsets Were Committed:
Consumer processed message, Offset committed
No reprocessing

Case 2: Offsets NOT Committed
    Consumer crashes mid-processing, Offset not committed
    Message is reprocessed by another consumer

------------------------------------------------------------------------------------------------------------------------------------------------

What is idempotent producer:
When producer sends message to broker and it ack back
if ack fails, then kafka retry sending the message automatically and with that duplicate message can be produced
It prevents this duplication of mesasges by checking producerID + Sequence number

------------------------------------------------------------------------------------------------------------------------------------------------

Does Kafka guarantee ordering:
It orders the messages in a single partition with same key, but not across multiple partitions.
If key is provided, it will send messagese with same key in same partition and in same order they are sent

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
    offsets are not auto commited

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

Consumer cannot keep up with producer rate
Business logic is slow
External API calls
Heavy Database operations

Fix:
Optimize processing
Increase spring.kafka.listener.concurrency
Use retry topics instead of blocking retries
Increase Partitions
Scale Kafka

------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle duplicate messages:
    Kafka allows duplicate messages due to at-least-once delivery, 
    so duplicates are handled by making consumers idempotent, typically using a unique business key with database or cache-based deduplication.

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