------------------------------------------------------------------------------------------------------------------------------
Api Gateway:
------------------------------------------------------------------------------------------------------------------------------

An API Gateway is a entry point for Client for all the microservices present.
It is used for adding those features to Microservices which are common so we dont have to add them separately on each one.

------------------------------------------------------------------------------------------------------------------------------

Uses of API GATEWAY:

Routing : Clients interact with one endpoint instead of multiple microservices
Service Discovery --> Works with Eureka to find services dynamically
Load Balancing 
Security & Authentication --> Handles JWT, OAuth, API keys, etc.
Rate Limiting & Throttling --> Prevents abuse by limiting requests per client.
Logging & Monitoring

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

3: Since we did not re-route the path manually and are using the automatic re-routing property we need to add the microservice name
in the path to tell which microservice this path belongs to

Ex: localhost:7000/student/{id} ---> localhost:7000/userservice/student/{id}

------------------------------------------------------------------------------------------------------------------------------

Manual Routing:
1: Use RouteLocator object to reroute the request 
2: In this we are specifying service here so no need to give in the url

------------------------------------------------------------------------------------------------------------------------------

With Java Code:

Code:
    @Configuration
    public class ApiConfiguration {

        @Bean
        public RouteLocator getRouteLocator(RouteLocatorBuilder builder){

            //Any url after currency/exchnange//----> will go to the currencyExchnage service
            return builder.routes()
                    .route(p->p.path("/currency/exchange/**")
                            .uri("lb://CurrencyExchange"))
                    .route(p->p.path("/currency/conversion/**")
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
Spring Cloud Gateway automatically load balances requests when multiple instances are registered in Eureka.
Uses Spring Cloud LoadBalancer (replaces Netflix Ribbon).
Can customize load balancing algorithm (e.g., random, round-robin).

------------------------------------------------------------------------------------------------------------------------------

Authentication and Authorization via GateWay:

Authentication is done in Gateway, Then request is re-routed based on the path
Microservices extracts the roles and authorize based on the roles
Microservices can re-validate the JWT if the API is super secret

------------------------------------------------------------------------------------------------------------------------------

PROBLEM STATEMENT:

There are multiple microservices with protected endpoints with user roles
You want to add JWT Authentication using API Gateway how will you add centralized 
Authentication in Multiple Microservices:

Auth-Service: 
Auth-service will have User Database and User Entity
User will login through Auth-Service 
It will Verify user credentials
After Verifying user credentials it will generate JWT token 
and return the token to user.

API Gateway: 
JWT Validation Before Forwarding Requests
Whenever we make a request to any microservice it will go to gateway with token
and gateway will validate that token before routing the request to the microservice based on the path

Microservices: 
Each microservice will extract roles and grant the access on the basis of roles.

------------------------------------------------------------------------------------------------------------------------------

