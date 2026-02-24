------------------------------------------------------------------------------------------------------------------------------
Distributed Tracing:
------------------------------------------------------------------------------------------------------------------------------

→ Distributed Tracing tracks a single request across multiple microservices.

→ A single user action can trigger multiple services
→ Failures or slowdowns may happen anywhere along the chain
→ Logs alone arent enough to correlate events

User → API Gateway → Order Service → Payment Service → Inventory Service

------------------------------------------------------------------------------------------------------------------------------

Core Concepts:

Trace
    → A complete request journey
    → Identified by traceId
    → Same traceId is shared across all services

Span
    → A single operation inside a service
    → Each service call creates its own span
    → Identified by spanId    

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin:
→ Zipkin is a distributed tracing tool used to visualize and monitor how requests travel through microservices.

→ Run Zipkin (Docker):
→ docker run -p 9411:9411 openzipkin/zipkin:2.23

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Zipkin ( UI ):
http://localhost:9411/zipkin/

From the UI you can:
    → Search traces by service name
    → See request latency
    → Visualize call dependency graph


Steps to Implement:
1: Add tracing dependencies to all microservices.
2: Add tracing properties to each service so that trace IDs and span IDs are generated and exported to Zipkin.  

// <!-- Core observation API -->
<dependency>
    <groupId>io.micrometer</groupId>
    <artifactId>micrometer-observation</artifactId>
</dependency>

// <!-- Tracing bridge (OpenTelemetry / Brave) -->
<dependency>
    <groupId>io.micrometer</groupId>
    <artifactId>micrometer-tracing-bridge-brave</artifactId>
</dependency>

// <!-- Tracing bridge (OpenTelemetry / Brave) -->
<dependency>
    <groupId>io.micrometer</groupId>
    <artifactId>micrometer-tracing-bridge-otel</artifactId>
</dependency>

// <!-- Zipkin exporter -->
<dependency>
    <groupId>io.opentelemetry</groupId>
    <artifactId>opentelemetry-exporter-zipkin</artifactId>
</dependency>

// <!-- Feign tracing support -->
<dependency>
    <groupId>io.github.openfeign</groupId>
    <artifactId>feign-micrometer</artifactId>
</dependency>


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application.Properties File:

// # Always sample traces (for learning / dev)
management.tracing.sampling.probability=1.0

// # Add traceId and spanId to logs
logging.pattern.level=%5p [${spring.application.name:},%X{traceId:-},%X{spanId:-}]

------------------------------------------------------------------------------------------------------------------------------------------------------------------------