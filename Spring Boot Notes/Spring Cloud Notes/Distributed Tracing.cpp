--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Distributed Tracing:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Distributed Tracing is a way to track requests as they move through different services in a microservices architecture.
It helps in debugging performance issues and finding bottlenecks in a distributed system.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin:
Zipkin is used to track request across multiple microservices

Zipkin Run Command:
docker run -p 9411:9411 openzipkin/zipkin:2.23

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin URL ( UI ):
http://localhost:9411/zipkin/

Steps to Implement:
1: Add Dependency in the all the microservices
2: Add properties in all the microservices

Dependency:
    <dependency>
        <groupId>io.micrometer</groupId>
        <artifactId>micrometer-observation</artifactId>
    </dependency>

    <dependency>
        <groupId>io.micrometer</groupId>
        <artifactId>micrometer-tracing-bridge-otel</artifactId>
    </dependency>

    <dependency>
        <groupId>io.opentelemetry</groupId>
        <artifactId>opentelemetry-exporter-zipkin</artifactId>
    </dependency>
    <dependency>
        <groupId>io.github.openfeign</groupId>
        <artifactId>feign-micrometer</artifactId>
    </dependency>
    <dependency>
        <groupId>io.micrometer</groupId>
        <artifactId>micrometer-tracing-bridge-brave</artifactId>
    </dependency>

Application.Properties File:
    management.tracing.sampling.probability=1.0
    logging.pattern.level=%5p [${spring.application.name:},%X{traceId:-},%X{spanId:-}]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------