------------------------------------------------------------------------------------------------------------------------------
Api Gateway:
------------------------------------------------------------------------------------------------------------------------------

Single entry point for all client requests in a microservices system.
Clients never call microservices directly.
Gateway forwards requests to the correct service

------------------------------------------------------------------------------------------------------------------------------

Uses of API GATEWAY:

Routing: Client calls one URL, Gateway routes request to the correct service

Service Discovery: Integrates with Eureka, Finds service IP + port dynamically

Load Balancing: Distributes requests across service instances, Uses Spring Cloud LoadBalancer

Security & Authentication: JWT / OAuth / API Key validation, Rejects invalid requests early

Rate Limiting & Throttling: Controls traffic spikes, Protects backend services

Logging & Monitoring: Central place to log incoming requests

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

Regex Explained:



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

Centralized JWT Authentication Across Multiple Microservices:

1. Auth-Service
    Contains User entity + User DB.
    Handles login
    Verifies username & password
    Generates JWT

2: API Gateway:
    Gateway validates the incoming request using JWT token:
        If invalid → reject request
        If valid → forward to the appropriate service using path routing

3. Microservices
    Extract roles/claims from JWT
    Authorize based on roles
    Optionally validate token again for high-security endpoints

------------------------------------------------------------------------------------------------------------------------------

