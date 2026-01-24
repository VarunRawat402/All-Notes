------------------------------------------------------------------------------------------------------------------------------
Api Gateway:
------------------------------------------------------------------------------------------------------------------------------

→ Single entry point for all client requests
→ Clients never call microservices directly.
→ Gateway forwards requests to the correct service

------------------------------------------------------------------------------------------------------------------------------

Core Responsibilities:

1. Request Routing:
    Routes requests to the correct service.

2. Authentication & Authorization:
    JWT / OAuth2 validation
    Role-based access
    Done once at gateway

3. Rate Limiting
    Prevent abuse of requests
    Example: 100 requests/min per user

4. Load Balancing
    Routes traffic across multiple service instances
    Uses service discovery (Eureka / Kubernetes)

5. Request / Response Transformation
    Modify headers
    Convert payloads
    Add user 
    
6. Caching:
    Cache frequent responses
    Reduce backend load

7. Logging & Monitoring
    Central request logging
    Tracing IDs
    
------------------------------------------------------------------------------------------------------------------------------

How to add API Gateway ( Service ):

1: Add Dependecies:

// <!-- API Gateway -->
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-gateway</artifactId>
</dependency>

// <!-- Eureka Client -->
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
</dependency>


2: Application.properties:

server.port=9765
spring.application.name=api-gateway
eureka.client.service-url.defaultZone=http://localhost:8761/eureka/             //To connect to the Eureka Server
spring.cloud.gateway.discovery.locator.enabled=true                             //To automatically re-route the request to the microservice
spring.cloud.gateway.discovery.locator.lowerCaseServiceId=true                  //make everything lowercase to tackle case sensitivity

------------------------------------------------------------------------------------------------------------------------------

Re-Routing in API GATEWAY:
    You can manually specify routes using RouteLocator.
    Similar path will re-route the request to correct service in a load balanced way

Load Balancing : 
    Automatic when multiple service instances exist
    Uses Spring Cloud LoadBalancer

------------------------------------------------------------------------------------------------------------------------------

With Java Code:

@Configuration
public class ApiConfiguration {

    @Bean
    public RouteLocator getRouteLocator(RouteLocatorBuilder builder) {
        return builder.routes()
                .route(p -> p.path("/currency/exchange/**").uri("lb://CurrencyExchange"))
                .route(p -> p.path("/currency/conversion/**").uri("lb://CurrencyConversion"))
                .build();
    }
}

------------------------------------------------------------------------------------------------------------------------------

Custom URL Rewriting:

Incoming Request:
    http://localhost:9765/fx/USD/INR

Gateway Rewrites To:
    /currency/exchange/USD/INR
    Forwards to CurrencyExchange Service

Code:

@Configuration
public class ApiConfiguration {

    //fx/ → matches prefix
    // (?<segment>.*) → captures everything after /fx/
    // ${segment} → inserts captured value into new path
    @Bean
    public RouteLocator customRoute(RouteLocatorBuilder builder) {
        return builder.routes()
                .route(p -> p.path("/fx/**").filters(f -> f.rewritePath("/fx/(?<segment>.*)","/currency/exchange/${segment}"))
                    .uri("lb://CURRENCY-EXCHANGE"))
                    .build();
    }
}

------------------------------------------------------------------------------------------------------------------------------

Authentication and Authorization via GateWay:

Authentication (API Gateway)
    JWT validation
    Reject invalid tokens
    Prevents unnecessary service calls

Authorization (Microservices)
    Extract roles from JWT
    Allow / deny access based on roles
    Optional re-validation for sensitive APIs

------------------------------------------------------------------------------------------------------------------------------
