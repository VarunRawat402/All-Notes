-----------------------------------------------------------------------------------------------------------------------------------------------------------
Resume Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------------

Improved API performance by optimizing Spring Boot backend processes and data handling:

1: I worked with my friend and I improved service method logic removed some of the unnecessary computations and DB calls

2: Used asynchronous processing for non-blocking tasks.
    @Async in Spring Boot allows a method to run in a separate thread.
    The main thread can return the response immediately while the async task runs in the background.
    Improves API responsiveness → user gets faster responses
    Frees main threads → system can handle more requests simultaneously.
    Configure Threadpool for async Data using ThreadPoolTaskExecutor

3: Cached frequently accessed data (like DB results) using Redis
    Reduced DB load and latency for repeated requests
    Used @Cacheable annotation on service methods to cache results in Redis

4: Optimized database queries and indexing to speed up data retrieval.
6: Used pagination for endpoints returning large datasets to limit response size.
7: Monitored API performance using tools like Spring Boot Actuator and New Relic to identify bottlenecks and optimize them.
8: Used connection pooling for database connections to reduce overhead of creating new connections.
9: Minimized data serialization/deserialization overhead by using efficient formats like JSON and avoiding unnecessary data
10: Used load balancing and horizontal scaling to distribute traffic across multiple instances of the API server.
11: Reviewed and optimized Spring Boot configurations for better performance (e.g. thread pool sizes, timeouts).
13: Implemented rate limiting to prevent abuse and ensure fair usage of the API.
14: Used efficient data structures and algorithms in the code to reduce time complexity.
16: Used lazy loading for entities to avoid fetching unnecessary data from the database.

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Reduced processing latency by 30% by improving Kafka thread management and message handling in Spring Boot:

In Spring Boot, Kafka listeners use threads to process messages. 
The number of threads affects how fast messages are consumed.
Configured Kafka consumer thread pool to have an optimal number of threads based on expected load.
Used ConcurrentKafkaListenerContainerFactory to set concurrency level.

spring:kafka:listener:concurrency: 4  
It Allows 4 threads to process messages simultaneously instead of just 1.

Using ConcurrentKafkaListenerContainerFactory and ThreadPoolTastExecutor you can customize the min, max thread size
@KafkaListener(topics = "my-topic", containerFactory = "kafkaListenerContainerFactory")

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Automated API docs with Swagger, cutting integration time by 25%:

I automated API documentation using Swagger, so all REST endpoints were documented and testable directly via a web UI. 
This made it much easier for other teams to understand and integrate with our APIs, cutting integration time by 25%.

-----------------------------------------------------------------------------------------------------------------------------------------------------------