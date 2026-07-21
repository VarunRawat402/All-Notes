------------------------------------------------------------------------------------------------------------------------------------------------
Async — Spring Boot
------------------------------------------------------------------------------------------------------------------------------------------------

@Async: 
    → It is used to run a method asynchronously
    → Runs a method in a separate thread — caller does not wait for it to finish.
    → Used to offload non-blocking work (emails, logs, OTPs, heavy processing).

Implementation:
1: Create a Async Class, Add @Configuration and @EnableAsync Annotation
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

Thread lifecycle:
    → Incoming task → assign to core thread (up to 5)
    → Core threads full → queue the task (up to 20)
    → Queue full → create extra threads (up to max 10)
    → Max threads + queue full → task rejected

------------------------------------------------------------------------------------------------------------------------------------------------

2: Service Class:

@Service
public class BackgroundService {

    // Fire-and-forget — caller doesn't wait for result
    @Async("taskExecutor")
    public void sendOtp(String phone) {
        // send OTP logic
    }

    @Async("taskExecutor")
    public void logUserActivity(String userId) {
        // logging logic
    }

    // Returns a future — caller can wait for result if needed
    @Async("taskExecutor")
    public CompletableFuture<String> processData() throws InterruptedException {
        Thread.sleep(2000); // simulate heavy work
        return CompletableFuture.completedFuture("done");
    }
}


------------------------------------------------------------------------------------------------------------------------------------------------\

ASYNC + KAFKA (Consumer Lag Problem)

Problem — Blocking Kafka Consumer Thread:
    → Each @KafkaListener runs on a consumer thread assigned to a partition.
    → If the listener does heavy work (DB calls, API calls, long computation),
      that thread is blocked for the duration.

While the thread is blocked:
    → New messages on that partition cannot be consumed.
    → Messages pile up in Kafka.
    → Consumer lag increases → end-to-end latency spikes → throughput drops.

Fix — Offload heavy work to async:
    → @KafkaListener receives the message (fast, non-blocking).
    → Hands off the heavy processing to @Async method immediately.
    → Consumer thread is freed to pick up the next message right away.

------------------------------------------------------------------------------------------------------------------------------------------------
