------------------------------------------------------------------------------------------------------------------------------
Circuit Breaker in Microservices (Resilience4j):
------------------------------------------------------------------------------------------------------------------------------

A Circuit Breaker is used to prevent system failures from cascading when a service is unavailable or slow.
It helps improve the resilience and fault tolerance of microservices.

------------------------------------------------------------------------------------------------------------------------------
How Circuit Breaker Works
------------------------------------------------------------------------------------------------------------------------------

Closed State (Normal Operation)
Requests flow normally to the service.
If the failure rate crosses the defined threshold, the circuit moves to Open.

Open State (Fail Fast Mode)
All calls fail immediately without hitting the actual service.
Prevents overloading an already failing service.

Half-Open State (Testing the Waters)
After a cooldown period, only a small number of requests are allowed.
If they succeed → circuit goes back to Closed.
If they fail → circuit returns to Open.

------------------------------------------------------------------------------------------------------------------------------

@CircuitBreaker:
The @CircuitBreaker annotation helps prevent cascading failures in microservices by stopping calls to a failing service after a certain threshold.

Application.properties:
    resilience4j.circuitbreaker.instances.CB.failure-rate-threshold=50
    resilience4j.circuitbreaker.instances.CB.wait-duration-in-open-state=5000ms
    resilience4j.circuitbreaker.instances.CB.sliding-window-size=10
    resilience4j.circuitbreaker.instances.CB.permitted-number-of-calls-in-half-open-state=2

Code:
    @CircuitBreaker(name = "CB", fallbackMethod = "fallbackResponse")
    public String getHello() {
        logger.info("Request received. Attempting external call...");
        String ans = restTemplate.getForObject("http://www.dsdsdsss.com", String.class);
        return "This is the hello world, Welcome Home";
    }

    public String fallbackResponse(Exception ex) {
        logger.error("Circuit breaker triggered: {}", ex.getMessage());
        return "Service is currently unavailable. Please try again later.";
    }

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation Retry ( @Retry ):
    It is used to automatically retry failed requests before giving up. 
    This is useful when calling unstable services that might temporarily fail.
    If a call fails, it will retry a certain number of times.
    If it still fails, it will execute a fallback method.


Application.properties:
    resilience4j.retry.instances.myRetry.max-attempts=3             //myRetry is the name of the retry annotation
    resilience4j.retry.instances.myRetry.wait-duration=2000ms

Code:

@RestController
public class RetryController {

    RestTemplate restTemplate = new RestTemplate();
    private Logger logger = LoggerFactory.getLogger(RetryController.class);

    @GetMapping("/hello")
    @Retry(name = "myRetry", fallbackMethod = "fallbackResponse")
    public String getHello() {
        logger.info("This is fetched");
        String ans = restTemplate.getForObject("http://www.dsdsdsss.com", String.class);
        return "This is the hello world, Welcome Home";
    }

    public String fallbackResponse(Exception ex) {
        return "Service is currently unavailable. Please try again later.";
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation RateLimiter ( @RateLimiter )
RateLimiter controls how many requests are allowed in a fixed time window. 
Extra requests are blocked and routed to a fallback method.

How @RateLimiter Works
    Limits the number of requests in a given time period.
    Rejects excess requests with a fallback response.
    Automatically resets after the defined period.

Application.properties:
resilience4j.ratelimiter.instances.myRateLimiter.limit-for-period=2
resilience4j.ratelimiter.instances.myRateLimiter.limit-refresh-period=8s

Code:
@RestController
public class RetryController {

    @GetMapping("/hello")
    @RateLimiter(name = "myRateLimiter",fallbackMethod = "fallbackResponse")
    public String getHello() {
        return "This is the hello world, Welcome Home";
    }

    public String fallbackResponse(Exception ex) {
        return "Service is currently unavailable. Please try again later.";
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation BulkHead ( @BulkHead )
A Bulkhead limits the number of concurrent calls to prevent system resources (threads) from being overwhelmed.

How @Bulkhead Works
Limits the number of concurrent requests to a method.
Rejects excess requests when the limit is reached.
Optionally queues requests if a semaphore-based bulkhead is used.

Application.properties:
resilience4j.bulkhead.instances.myBulkhead.max-concurrent-calls=5
resilience4j.bulkhead.instances.myBulkhead.max-wait-duration=0ms

----------------------------------------------------------------------------------------------------------------------------------------------------------------