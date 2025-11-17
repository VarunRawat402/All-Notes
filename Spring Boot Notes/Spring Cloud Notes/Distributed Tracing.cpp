--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Distributed Tracing:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Distributed Tracing tracks a request as it flows across multiple microservices.
It helps identify performance issues, latency, and bottlenecks in a distributed system.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin:
Zipkin is a distributed tracing tool used to visualize and monitor how requests travel through microservices.

Zipkin Run Command:
docker run -p 9411:9411 openzipkin/zipkin:2.23

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin URL ( UI ):
http://localhost:9411/zipkin/

Steps to Implement:
1: Add tracing dependencies to all microservices.
2: Add tracing properties to each service so that trace IDs and span IDs are generated and exported to Zipkin.  

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

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application.Properties File:
    management.tracing.sampling.probability=1.0
    logging.pattern.level=%5p [${spring.application.name:},%X{traceId:-},%X{spanId:-}]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------