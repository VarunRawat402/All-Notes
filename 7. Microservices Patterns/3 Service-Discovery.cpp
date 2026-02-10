------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Service Discovery:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

It allows services to connect and communicate with each other without hardcoding the IPs and addresses.

Client-Side Discovery:
    → Client calls service discovery to get service instance list
    → Client calls the instance directly
    → Client performs load balancing
    → Netflix Eureka + Spring Cloud LoadBalancer

Server-Side Discovery:
    → Client calls API gateway / load balancer
    → Gateway/load balancer calls service discovery and routes to instance
    → Client does not know service locations
    → Kubernetes (Kube-DNS, CoreDNS)
    → AWS ALB + ECS

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Server:
    → Acts as a Service Registry
    → All microservices register themselves here
    → Registry is queried using service name

Eureka Server Stores:
    → Service Name
    → IP Address
    → Port
    → Health Status

1: Add Eureka Server Dependency:
    → spring-cloud-starter-netflix-eureka-server

2: Add Annotation:
    → @EnableEurekaServer

3: Add configuration:
    server.port: 8761
    eureka.client.register-with-eureka: false           //Eureka Server does not register itself
    eureka.client.fetch-registry: false                 //It does not fetch registry from others

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Client:
    → Registers itself on Eureka server automatically on startup
    → Sends heartbeat every 30 seconds
    → Gets registry of other services (important addition)
    → Deregisters automatically if it goes down (or lease expires)
        
1: Add Eureka client Dependency:
    → spring-cloud-starter-netflix-eureka-client

2: Add configuration:

spring.application.name: user-service
eureka.client.service-url.defaultZone: http://localhost:8761/eureka

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Heartbeat:

→ A small periodic HTTP request sent by Eureka Client
→ Tells Eureka Server that the service is still alive

Default Behavior:
    → Heartbeat interval: 30 seconds
    → If heartbeats stop, Eureka marks service as DOWN and removes it

eureka.instance.lease-renewal-interval-in-seconds: 10           //Send heartbeat every 10 sec
eureka.instance.lease-expiration-duration-in-seconds: 30        //Remove service if no heartbeat in 30 seconds

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Notes:
    → Eureka is mostly used in Spring Cloud ecosystems
    → Kubernetes environments usually use built-in service discovery instead of Eureka
    → API Gateway + Discovery + LoadBalancer usually work together
    → Service name must match exactly when calling via lb://SERVICE-NAME

------------------------------------------------------------------------------------------------------------------------------------------------------------------------