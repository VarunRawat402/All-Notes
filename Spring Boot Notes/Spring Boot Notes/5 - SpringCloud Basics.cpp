------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Monolithic:

Disadvantages:
1: Scaling : Cannot scale individual components need to scale whole application 
2: Adding Features is hard because everything is tightly coupled 
3: As application grows, codebase becomes large and complex, Difficult to understand and maintain
4: Deployment is challenging because even a small change requires redeploying the entire application.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MicroServices:

Application is divided into multiple small, independent services
Services communicate with each other over the network (HTTP/REST, messaging)

Developed independently, Deployed independently, Scaled independently
Different services can use different technologies (Java, Node, DB, etc.)
Failure of one service does not bring down the entire system

Disadvantages:
    Network Overhead
    Latency, security, monitoring, and debugging become harder

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Cloud:
A framework that provides tools and libraries to build cloud-native microservices

Solves common microservice problems like::
    Service discovery
    Load balancing
    Fault tolerance
    Configuration management


Eureka (Service Discovery):
Part of Netflix OSS
Keeps a dynamic registry of all running microservices
Helps services find and communicate with each other without hardcoding URLs

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Server:
    Acts as a Service Registry
    All microservices register themselves here

Eureka Server Stores:
    Service Name
    IP Address
    Port
    Health Status

1: Add Eureka Server Dependency:
2: Add Annotation:
3: Add configuration:

server.port: 8761
eureka.client.register-with-eureka: false           //Eureka Server does not need to register itself
eureka.client.fetch-registry: false                 //It does not need to fetch registry from anyone

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Client:
    Registers itself on Eureka server automatically on startup
    Sends heartbeat every 30 seconds
    Deregisters automatically if it goes down
     
1: Add Eureka client Dependency:
2: Add configuration:

spring.application.name: user-service
eureka.client.service-url.defaultZone: http://localhost:8761/eureka

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eureka Heartbeat:

A small periodic HTTP request sent by Eureka Client
Tells Eureka Server that the service is still alive

Default Behavior:
    Heartbeat interval: 30 seconds
    If heartbeats stop, Eureka marks service as DOWN and removes it

eureka.instance.lease-renewal-interval-in-seconds: 10           //Send heartbeat every 10 sec
eureka.instance.lease-expiration-duration-in-seconds: 30        //Remove service if no heartbeat in 30 seconds

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
