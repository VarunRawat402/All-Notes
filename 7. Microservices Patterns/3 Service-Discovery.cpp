------------------------------------------------------------------------------------------------------------------------------
Service Discovery:
------------------------------------------------------------------------------------------------------------------------------

It allows services to connect and communicate with each other without hardcoding the IPs and addresses.

Client-Side Discovery:
    → Client calls service discovery to get service instance list.
    → Client calls the instance directly.
    → Netflix Eureka

Server-Side Discovery:
    → Client calls API gateway.
    → Gateway calls service discovery and calls instance
    → Kubernetes (Kube-DNS, CoreDNS)
    → AWS ALB + ECS

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Server:
    → Acts as a Service Registry
    → All microservices register themselves here

Eureka Server Stores:
    → Service Name
    → IP Address
    → Port
    → Health Status

1: Add Eureka Server Dependency:
2: Add Annotation:
3: Add configuration:

server.port: 8761
eureka.client.register-with-eureka: false           //Eureka Server does not need to register itself
eureka.client.fetch-registry: false                 //It does not need to fetch registry from anyone

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Client:
    → Registers itself on Eureka server automatically on startup
    → Sends heartbeat every 30 seconds
    → Deregisters automatically if it goes down
     
1: Add Eureka client Dependency:
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
