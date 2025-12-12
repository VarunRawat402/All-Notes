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