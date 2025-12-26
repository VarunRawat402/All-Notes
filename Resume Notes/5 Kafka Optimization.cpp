------------------------------------------------------------------------------------------------------------------------------------------------
How to Optimise your Application
------------------------------------------------------------------------------------------------------------------------------------------------

1: spring.kafka.listener.concurrency=4
By Default kafka reads message synchronusly one by one

This creates 4 threads for 1 kafka consumer

If topic has 4 partition, then 4 threads can read each partition
If consumer takes 1 sec to read 1 message, then it would take 4 sec to read 4 messages
With concurrency 4, it can read 4 messages in 1 sec

Note:
Threads should not be greater than the partition, otherwise they would stay idle

------------------------------------------------------------------------------------------------------------------------------------------------

2: Multiple Kafka Listeners in 1 Application:
This creates 4 consumers in same consumer group, doing same task
So, If topic has 4 partition, each consumer gets 1 partition

@KafkaListener(topics = "user_created", groupId = "grp123")
public void c1(String msg){}

@KafkaListener(topics = "user_created", groupId = "grp123")
public void c2(String msg){}

@KafkaListener(topics = "user_created", groupId = "grp123")
public void c3(String msg){}

@KafkaListener(topics = "user_created", groupId = "grp123")
public void c4(String msg){}

Note:
Comapnies mostly used Horizontal scaling and launch multiple instances of same application
Concurrency method is also

------------------------------------------------------------------------------------------------------------------------------------------------
Consumer Group:

1 partition can be read by only 1 consumer in the consumer group
1 consumer can read multiple partition 
Main focus is Load Balancing  and parallel processing for consumer groups so, If any consumer broke then other consumers
will still be there to read messages.

If you have 2 kafka Listeneres who are listening to same topic 'order' and perfroming different things
Their GroupId should be different otherwise only 1 of them can read messages

To create 2 consumer with same group id to load balance we need to run another instance of the application basically

------------------------------------------------------------------------------------------------------------------------------------------------

Disadvantages of Using Spring Kafka concurrency:

1: Concurrency is limited by the JVM and core size, It takes a load on CPU
2: If you set high concurrency and use single intannce, this means single point of failure, if consumer broke, all message will stop
3: In modern systems, kubernetes scale Horizontally

------------------------------------------------------------------------------------------------------------------------------------------------
Backoff and Retry in Kafka:
------------------------------------------------------------------------------------------------------------------------------------------------

What happens when processing fails:

Exception thrown (no retry configured):
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

Other partitions/threads:
Continue normally

------------------------------------------------------------------------------------------------------------------------------------------------

WHY THIS IS DANGEROUS (real production impact)

CPU goes to 100%
Logs explode
DB gets hammered
Other messages in that partition never get processed
Looks like Kafka is “stuck”

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

Metrics you see:
    CPU usage (%)
    CPU cores used
    CPU usage per container / pod

How to explain:
    CPU usage shows how much processing power the application is using. 
    High CPU usage can indicate heavy load or inefficient processing.
    Safe example line:
    “We monitored CPU usage to ensure the service was not over-consuming processor resources.”

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