------------------------------------------------------------------------------------------------------------------------------
Api Gateway:
------------------------------------------------------------------------------------------------------------------------------

An API Gateway is the single entry point for all client requests in a microservices architecture.
It helps avoid writing common logic in every microservice by centralizing shared features.

------------------------------------------------------------------------------------------------------------------------------

Uses of API GATEWAY:

Routing: Clients call one endpoint instead of multiple services.
Service Discovery: Works with Eureka for dynamic service lookup.
Load Balancing: Distributes traffic across service instances.
Security & Authentication: Handles JWT, OAuth, API keys.
Rate Limiting & Throttling: Controls request spikes.
Logging & Monitoring: Central place to track and log requests.

------------------------------------------------------------------------------------------------------------------------------

How to add API Gateway ( Service ):

1: Dependecies:

//Gateway 
    <dependency>
        <groupId>org.springframework.cloud</groupId>
        <artifactId>spring-cloud-starter-gateway</artifactId>
    </dependency>

//Eureka Client
    <dependency>
        <groupId>org.springframework.cloud</groupId>
        <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
    </dependency>

2: Application.properties:

server.port=9765
spring.application.name=api-gateway
eureka.client.service-url.defaultZone=http://localhost:8761/eureka/     //To connect to the Eureka Server
spring.cloud.gateway.discovery.locator.enabled=true                     //To automatically re-route the request to the microservice
spring.cloud.gateway.discovery.locator.lowerCaseServiceId=true          //make everything lowercase to tackle case sensitivity

------------------------------------------------------------------------------------------------------------------------------

3. Using Automatic Routing:
Since routes are not defined manually, the URL must include the microservice name.

Before Gateway:
localhost:7000/student/{id}

After Gateway (auto-route):
localhost:7000/userservice/student/{id}

------------------------------------------------------------------------------------------------------------------------------

Manual Routing:
1: You can manually specify routes using RouteLocator.
2: Here, the service name is defined inside the route, so URL does NOT need the service name.

------------------------------------------------------------------------------------------------------------------------------

With Java Code:

@Configuration
public class ApiConfiguration {

    @Bean
    public RouteLocator getRouteLocator(RouteLocatorBuilder builder) {

        return builder.routes()
                .route(p -> p.path("/currency/exchange/**")
                        .uri("lb://CurrencyExchange"))
                .route(p -> p.path("/currency/conversion/**")
                        .uri("lb://CurrencyConversion"))
                .build();
    }
}


------------------------------------------------------------------------------------------------------------------------------

Custom URL:
 
@Configuration
public class ApiConfiguration {

    @Bean
    public RouteLocator getRouteLocator(RouteLocatorBuilder builder){

        //Any request starting with /chummalele/** is rewritten to /currency/exchange/** and forwarded to the CurrencyExchange service.
        //http://localhost:9765/chummalele/from/AUD/to/INR      ----> This will be re written as ---->
        //http://CurrencyExchange/currency/exchange/from/AUD/to/INR
        return builder.routes()
                .route(p->p.path("/chummalele/**")
                        .filters(r->r.rewritePath("/chummalele/(?<segment>.*)","/currency/exchange/${segment}"))
                        .uri("lb://CurrencyExchange"))
                .route(p->p.path("/currency/conversion/**")
                        .uri("lb://CurrencyConversion"))
                .build();
    }
}

------------------------------------------------------------------------------------------------------------------------------

Load Balancing : 
Gateway automatically load-balances requests when multiple service instances are registered in Eureka.
Uses Spring Cloud LoadBalancer (Ribbon is deprecated).
Custom algorithms like round-robin, random, etc. can be configured.

------------------------------------------------------------------------------------------------------------------------------

Authentication and Authorization via GateWay:

1: Authentication is done at the API Gateway.
    Validates JWT before forwarding the request.

2: Routing happens only after token validation.

3: Microservices extract roles from the token and allow/deny access.
    They may re-validate JWT for highly sensitive endpoints.

------------------------------------------------------------------------------------------------------------------------------

Centralized JWT Authentication Across Multiple Microservices:

Problem:
    Multiple microservices have protected endpoints.
    You want centralized authentication using JWT via an API Gateway.

Architecture Breakdown:

1. Auth-Service
Contains User entity + User DB.
User logs in through Auth-Service.
Auth-Service:
    Verifies username/password
    Generates JWT token
    Returns token to client

2: API Gateway:

All client requests come through the gateway.
Gateway validates the incoming JWT:
    If invalid → reject request
    If valid → forward to the appropriate service using path routing

3. Microservices

    Extract roles/claims from JWT
    Authorize based on roles
    Optionally validate token again for high-security endpoints

------------------------------------------------------------------------------------------------------------------------------

