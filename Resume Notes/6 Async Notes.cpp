------------------------------------------------------------------------------------------------------------------------------------------------
ASYNC Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------------------------\

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
