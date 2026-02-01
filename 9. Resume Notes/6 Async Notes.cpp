------------------------------------------------------------------------------------------------------------------------------------------------
ASYNC Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

@Async: 
It is used to run a method asynchronously

Implementation:
1: Create a Async Class with @Configuration and @EnableAsync Annotation
2: Use @Async on methods you want to run asynchronously
3: You have to call the method with another service, You cannot call from where its defined
4: Async function return void or CompletableFuture nothing else.

------------------------------------------------------------------------------------------------------------------------------------------------

1: Async Class:

@EnableAsync
@Configuration
public class AsyncConfig {
    
    @Bean(name = "taskExecutor")
    public Executor taskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(5);        // Threads always kept alive
        executor.setMaxPoolSize(10);        // Max threads allowed
        executor.setQueueCapacity(20);      // Tasks queued before creating extra threads
        executor.setThreadNamePrefix("AsyncThread-");
        executor.initialize();
        return executor;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

2: Service Class:

@Service
public class BackgroundService {

    @Async("taskExecutor")
    public void sendOtp(String phone) {
        //Send OTP
    }

    @Async("taskExecutor")
    public void logUserActivity(String userId) {
        //Log Data
    }

    @Async("taskExecutor")
    public CompletableFuture<String> processData() throws InterruptedException {
        Thread.sleep(2000); // heavy work
        return CompletableFuture.completedFuture("done");
    }

    String result = service.processData().get();  // waits
}


------------------------------------------------------------------------------------------------------------------------------------------------\

We moved from sequential message processing to parallel consumption
By processing messages faster, consumer lag reduced, which directly lowered end-to-end event latency.

Kafka assigns 1 thread per partition in a consumer group.
That consumer thread processes messages sequentially to maintain ordering.

If the @KafkaListener performs heavy operations (DB calls, external API calls, long computations):
The consumer thread becomes busy and blocked.

While the thread is busy:
    New messages for that partition cannot be processed
    Messages start waiting in Kafka

This leads to:
    Consumer lag increase
    Higher end-to-end latency
    Slower system throughput

------------------------------------------------------------------------------------------------------------------------------------------------
