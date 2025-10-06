------------------------------------------------------------------------------------------------------------------------------------------------
How to Optimise your Application
------------------------------------------------------------------------------------------------------------------------------------------------

spring.kafka.listener.concurrency=4
    This is basically used when there is a single consumer and we want to make it multi-threaded

This creates 4 threads for single kafka consumer
These 4 threads will consume messages from different kafka topic partitions

If topic has 4 partition and 4 threads are used then 1 thread can read from 1 partition
Threads should not be greater than partition otherwise they will stay idle

By Default it sets to 1
Meaning if consumer takes 1 sec to read the message then it will read 4 messages in 4 sec
while if we use 4 threads it will read 4 message in 1 sec

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Group:

1 partition can be read by only 1 consumer in consumer group
Main focus is Load Balancing  and parallel processing for consumer groups so, If any consumer broke then other consumers
will still be there to read messages.

If you have 2 kafka Listeneres who are listening to same topic 'order' and perfroming different things
Their GroupId should be different otherwise only 1 of them can read messages

To create 2 consumer with same group id to load balance we need to run another instance of the application basically

------------------------------------------------------------------------------------------------------------------------------------------------

Disadvantages of Using Spring Kafka concurrency:

1. Concurrency is limited by the JVM and system resources
All concurrent threads in a single instance share the same JVM, memory, and CPU.
This means you are limited by vertical scalability (one machine's capacity).

2: High Availability / Fault Tolerance:
If you only run one instance, and it crashes, your consumer group goes offline.
With multiple app instances, even if one crashes, others keep consuming.

3: Microservices / Kubernetes / Docker
In modern distributed systems, apps are deployed in containers or pods, which naturally lend themselves to multi-instance deployments.
Scaling is often managed at the orchestration level, not just via threading.

------------------------------------------------------------------------------------------------------------------------------------------------

@Async : It is used to run a method in a background thread.

Helps offload non-critical, time-consuming tasks like:
	Email Send, Logging, Generating Report

Implementation:
1: Create a Async Class with @Configuration and @EnableAsync Annotation
2: Use @Async Annotation on top of the method
3: You have to call the method with another service, You cannot call from where its defined

This sets how the asynchro nus task should be executing 
Learn how they are helping and what will hapenn if we dont use it

@EnableAsync
@Configuration
public class AsyncConfig {
    
    @Bean
    public Executor taskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();		//Creating the object to initialize property
        executor.setCorePoolSize(4);						//4 threads will always be available for operations
        executor.setMaxPoolSize(10);						//Max threads can be created upto 10 not more than that
        executor.setQueueCapacity(500);						//Tasks can be in queue for upto 500 tasks after that reject
        executor.initialize();							//Initialize the properties 
        return executor;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------
