------------------------------------------------------------------------------------------------------------------------------------------------
How to Optimise your Application
------------------------------------------------------------------------------------------------------------------------------------------------

1: spring.kafka.listener.concurrency=4
By default, a Kafka listener processes messages synchronously, one message at a time

Concurrency creates multiple consumer threads inside a single application instance.

With concurrency 1  → 1 thread reads partitions sequentially
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
Backoff and Retry in Kafka:
------------------------------------------------------------------------------------------------------------------------------------------------

What happens when processing fails:

public void consume(UserEvent event) {
    // error here
    throw new RuntimeException("DB down");
}

What happens on failure:
    Message read (offset 10)
    Exception thrown
    Offset NOT committed
    Consumer polls again
    Same message (offset 10) read immediately
    Infinite loop

❌ No delay
❌ No retry limit
❌ Partition blocked forever

------------------------------------------------------------------------------------------------------------------------------------------------

WHY THIS IS DANGEROUS (real production impact)

CPU spikes to 100%
Logs grow rapidly
Database / external services get hammered
Messages behind that offset never get processed

------------------------------------------------------------------------------------------------------------------------------------------------

Retry behavior (Spring Kafka):

For message at offset 10:
    Consumer reads message
    Processing fails

ErrorHandler:
    pauses the partition
    waits 3 seconds
    Retry #1
    Retry #2 (after 3 sec)
    Retry #3 (after 3 sec)
    Still fails → handler gives up

At this point:
    Offset is committed
    Message is skipped or sent to DLT
    Consumer moves to offset 11

Concurrency impact:
    Only that consumer thread is blocked
    Other threads keep running

------------------------------------------------------------------------------------------------------------------------------------------------

DEAD LETTER TOPIC:

Message fails 3 times
Sent to: user_create.DLT
Original offset committed
Consumer continues normally

Now you can:
    Inspect bad messages
    Replay them later


WHEN RETRY SHOULD NOT HAPPEN:
    Not all errors are retryable.

Example:
    Invalid email
    JSON schema error
    Business validation failure

Flow:
    No retry
    Directly sent to DLT
    Offset committed immediately

------------------------------------------------------------------------------------------------------------------------------------------------

PROM AND GRAFANA:

1. CPU Metrics
    CPU usage (%)
    CPU cores used
    CPU usage per container / pod

How to explain:
    CPU metrics indicate how much processing application consumes.
    High CPU usage can signal heavy load or inefficient processing.

Safe example line:
    We monitored CPU usage to ensure the service was not over-consuming processor resources.

2. Memory Metrics
Metrics you see:
    Memory usage (MB/GB)
    Memory limit vs used memory
    JVM heap usage (for Spring Boot)
How to explain:
    Memory metrics show how much RAM the application consumes. Monitoring this helps detect memory leaks or applications nearing their memory limits.
    Safe example line:
    “Memory usage was tracked to ensure the application stayed within allocated limits.”


3. Application (Basic) Metrics

These come from the application itself.
Common ones you can say:
    Request count
    Response time / latency
    Error count (4xx / 5xx)
    Application uptime
How to explain:
    Application metrics help understand how the service behaves under load, such as how many requests it handles and how quickly it responds.

------------------------------------------------------------------------------------------------------------------------------------------------

//Consumer Service Configuration of Kafka:
//This is used to map the kafka json event to java class automatically
//Json data coming with typeId = txncreation will be mapped to TxnCreation class
//Json data coming with typeId = usercreation will be mapped to UserCreation class
spring.kafka.consumer.properties.spring.json.type.mapping = txncreation:com.example.wallet.wallet.kafkaUtil.TxnCreation,usercreation:com.example.wallet.wallet.kafkaUtil.UserCreation


//Producer Service Configuration of Kafka:
//This is used to set the typeId while sending json data to kafka topic
//This will automatically add typeId = txnupdate in the json data
spring.kafka.producer.properties.spring.json.type.mapping=txnupdate:com.example.wallet.wallet.kafkaUtil.TxnUpdate

------------------------------------------------------------------------------------------------------------------------------------------------