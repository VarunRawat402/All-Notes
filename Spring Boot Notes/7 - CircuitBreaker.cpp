------------------------------------------------------------------------------------------------------------------------------
Circuit Breaker in Microservices (Resilience4j):
------------------------------------------------------------------------------------------------------------------------------

Prevents cascading failures in microservices
Stops calling a service that is slow or failing
Improves resilience and fault tolerance

------------------------------------------------------------------------------------------------------------------------------
How Circuit Breaker Works
------------------------------------------------------------------------------------------------------------------------------

Closed State (Normal)
    Requests go to the service normally
    Failures are counted
    If failure rate crosses threshold → Open state

Open State (Fail Fast Mode)
    No request goes to the service
    Calls fail immediately
    Protects the failing service from overload

Half-Open State (Testing the Waters)
    After a wait time, few requests are allowed
    If they succeed → back to Closed
    If they fail → back to Open

------------------------------------------------------------------------------------------------------------------------------

@CircuitBreaker:
    Automatically tracks failures
    Opens circuit when threshold is reached
    Calls fallback method instead of actual service

Application.properties:
    resilience4j.circuitbreaker.instances.myCB.failure-rate-threshold=50
    resilience4j.circuitbreaker.instances.myCB.wait-duration-in-open-state=5000ms
    resilience4j.circuitbreaker.instances.myCB.sliding-window-size=10
    resilience4j.circuitbreaker.instances.myCB.permitted-number-of-calls-in-half-open-state=2

Code:
    @CircuitBreaker(name = "myCB", fallbackMethod = "fallbackResponse")
    public String getHello() {
        String ans = restTemplate.getForObject("http://www.dsdsdsss.com", String.class);
        return ans;
    }

    public String fallbackResponse(Exception ex) {
        return "Service is currently unavailable. Please try again later.";
    }

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation Retry ( @Retry ):
    Retries a failed request before giving up
    Useful when service fails temporarily
    If all retries fail → fallback is executed


Application.properties:
    resilience4j.retry.instances.myRetry.max-attempts=3             
    resilience4j.retry.instances.myRetry.wait-duration=2000ms

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation RateLimiter ( @RateLimiter )
    Limits number of requests per time window
    Extra requests are rejected
    Protects service from traffic spikes

Application.properties:
resilience4j.ratelimiter.instances.myRateLimiter.limit-for-period=2
resilience4j.ratelimiter.instances.myRateLimiter.limit-refresh-period=8s

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Annotation BulkHead ( @BulkHead )
    Limits concurrent requests, Rejects extra calls
    Prevents thread pool exhaustion
    Isolates failures

Application.properties:
resilience4j.bulkhead.instances.myBulkhead.max-concurrent-calls=5
resilience4j.bulkhead.instances.myBulkhead.max-wait-duration=0ms

----------------------------------------------------------------------------------------------------------------------------------------------------------------