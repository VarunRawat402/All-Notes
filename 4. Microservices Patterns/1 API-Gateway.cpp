------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Api Gateway:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Single entry point for all requests
→ Gateway forwards requests to the correct service

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Core Responsibilities:

1. Request Routing:
    → Send requests to the correct service.

2. Authentication & Authorization:
    → JWT validation
    → Role-based access

3. Rate Limiting
    → Prevent abuse of requests
    → Fail request after limit reached

4. Load Balancing
    → Send requests to service instances in a load balanced way
    
5. Caching:
    → Cache frequent responses
    → Reduce backend load

6. Logging & Monitoring
    → Central request logging
    → Tracing IDs
    
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
spring.cloud.gateway.discovery.locator.enabled=true                             //Auto-create routes using service names from Eureka
spring.cloud.gateway.discovery.locator.lowerCaseServiceId=true                  //Make service IDs lowercase to avoid case mismatch

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Re-Routing in API GATEWAY:
    → Create the routes using RouteLocatorBuilder
    → re-routes the requests based on URL to correct service

Load Balancing : 
    → Automatic when multiple service instances exist
    → Uses Spring Cloud LoadBalancer

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Custom URL Rewriting:

Incoming Request:
    → http://localhost:9765/fx/USD/INR

Gateway Rewrites To:
    → /currency/exchange/USD/INR
    → Forwards to CurrencyExchange Service

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

------------------------------------------------------------------------------------------------------------------------------------------------------------------------