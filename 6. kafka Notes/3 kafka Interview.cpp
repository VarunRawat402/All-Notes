-----------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Interview Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Question 1: What happens if a consumer crashes:

→ If a Kafka consumer crashes, Kafka reassigns its partitions to another consumer in the same consumer group and continues message consumption.

→ Kafka expects periodic heartbeats from consumers
→ Heartbeat stops → timeout → consumer marked dead
→ Rebalance triggered → partitions reassigned

-----------------------------------------------------------------------------------------------------------------------------------------------------

Question 2: What is idempotent producer:
    → Kafka auto retries if ack fails → can cause duplicate messages
    → Idempotent producer prevents duplicates using:
        → ProducerId + Sequence Number → broker detects duplicate → ignores it

-----------------------------------------------------------------------------------------------------------------------------------------------------

Question 3: What causes consumer lag:
    → Producer faster than consumer
    → Slow business logic
    → Heavy DB operations

Fix:
    → Optimize processing logic
    → Increase listener concurrency
    → Increase partitions → more parallel consumers
    → Scale consumer instances (Kubernetes)
    → Use @RetryableTopic → non-blocking retries

-----------------------------------------------------------------------------------------------------------------------------------------------------

Question 4: How to reprocess old messages:

→ Kafka stores messages by offset → reset offset → Kafka resends them

1. Reset offset to specific time:
    --to-datetime 2026-01-10T10:00:00.000
    → reprocesses all messages from that timestamp

2. Reset offset by N messages back:
    --shift-by -100
    → reprocesses last 100 messages

3. Reprocess from DLT (Best Practice):
    → Only failed messages reprocessed → safer than full replay

@KafkaListener(topics = "order-create-dlt", groupId = "dlt-grp")
public void reprocess(String message) {
    kafkaTemplate.send("order-create", message);
}

Important:
    → Consumer group must be STOPPED before resetting offsets
    → Affects ALL consumers in the group
    → Can cause duplicate processing → ensure idempotent processing

-----------------------------------------------------------------------------------------------------------------------------------------------------

Common Interview Clarifications:

Does Spring Boot always create topics:
    → No, Only if KafkaAdmin is enabled and broker allows it

Is topic creation done by producers/consumers:
    → No, Done by KafkaAdmin during application startup

Should topics be created in production apps:
    → Usually NO, 
    Topics created via:
        → Terraform
        → Kafka CLI
        → Platform team
        → Application does not own infra

-----------------------------------------------------------------------------------------------------------------------------------------------------