------------------------------------------------------------------------------------------------------------------------------------------------
How to Optimise your Application
------------------------------------------------------------------------------------------------------------------------------------------------

How to optimize Kafka Listener / Consumer:

1: spring.kafka.listener.concurrency=4

This is used when there is only single consumer and we want to make that consumer multi-threaded

This creates 4 threads for 1 kafka consumer
By Default it sets to 1 thread

If topic has 4 partition, then 4 threads can read each partition

If consumer takes 1 sec to read 1 msg, then it would take 4 sec to read 4 messages
With this, 4 threads works together and read 4 messages in 1 sec 

Note:
Threads should not be greater than the partition, otherwise they would stay idle

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

1 partition can be read by only 1 consumer in consumer group1 partition can be read by only 1 consumer in the consumer group
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

ASYNC Methods:

@Async : It is used to run a method in a background thread.

Helps offload non-critical, time-consuming tasks like:
	Email Send, Logging, Generating Report

Implementation:
1: Create a Async Class with @Configuration and @EnableAsync Annotation
2: Use @Async Annotation on top of the method
3: You have to call the method with another service, You cannot call from where its defined
4: Async function should be void or CompletableFuture nothing else.

@EnableAsync
@Configuration
public class AsyncConfig {
    
    @Bean(name = "taskExecutor")
    public Executor taskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();		
        executor.setCorePoolSize(5);						//4 threads will always be available for operations
        executor.setMaxPoolSize(10);						//Max threads can be created upto 10 not more than that
        executor.setQueueCapacity(20);						//Tasks can be in queue for upto 500 tasks after that reject
        executor.setThreadNamePrefix("AsyncThread-");
        executor.initialize();							//Initialize the properties 
        return executor;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Service Code:

@Service
public class BackgroundService {

    @Async("taskExecutor")
    public void sendOtp(String phone) {
        // call SMS API
    }

    @Async("taskExecutor")
    public void logUserActivity(String userId) {
        // log to database
    }
}

CompletableFuture :

@Async("taskExecutor")
public CompletableFuture<String> processData() throws InterruptedException {
    Thread.sleep(2000); // heavy work
    return CompletableFuture.completedFuture("done");
}

String result = service.processData().get();  // waits

------------------------------------------------------------------------------------------------------------------------------------------------

We improved thread management by configuring Kafka consumers to process messages in parallel using partitions and listener concurrency instead of sequential processing.
We increased partitions so Kafka could distribute load across multiple consumer threads
Earlier, messages were processed sequentially. After enabling parallel consumption using multiple partitions and consumer concurrency, messages waited less time in the queue, which reduced end-to-end processing latency by around 30%.
We compared average message processing time and lag before and after enabling parallel consumption using application logs and Kafka consumer lag metrics.


We moved from sequential message processing to parallel consumption using Kafka partitions and listener concurrency
By processing messages faster, consumer lag reduced, which directly lowered end-to-end event latency.
We ensured all consumers were in the same consumer group so partitions were evenly distributed and no instance stayed idle.

We avoided blocking operations inside the Kafka listener and moved heavy processing to async/service layers, using Async functions
    Kafka assigns one thread per partition
    That thread is now busy
    New messages for that partition wait
    Consumer lag increases
    Latency increases

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