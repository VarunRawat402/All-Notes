------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Monolithic:

Disadvantages:
1: Scaling : Cannot scale individual components need to scale whole application 
2: Adding Features is hard because everything is tightly coupled 
3: As the application becomes large, understanding and maintaining the code becomes complex.
4: Deployment is challenging because even a small change requires redeploying the entire application.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MicroServices:

Application is divided into multiple small microservices which communicate through network
Each services handles one functionality, can be developed, deployed and scaled independently
Different services can use different technologies based on requirements.
Failure in one service does not significantly impact the entire system.

Disadvantages:
Network calls between services can affect performance.
Distributed nature introduces latency, security concerns, and debugging complexity.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Cloud:
A framework that provides tools and libraries for building distributed systems and cloud-native microservice architectures.
Spring Cloud Eureka: localhost:8761

Every service runs on different ports/instances, and instances may scale up/down dynamically.
Clients needs to find port & address to communicate without hardcoding it
Service Discovery solves this by keeping a dynamic registry of all the running services

Eureka Server:
It is a Service registry from Netflix OSS
All microservices register themeselves on Eureka
Microservices uses Eureka to connect and communicate with each other

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eureka Server:

It contains :
    Service Name, IP address, Port, Health status

1: Add Dependency:

<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-eureka-server</artifactId>
</dependency>

2: Add Annotation:

@SpringBootApplication
@EnableEurekaServer
public class DiscoveryServerApplication { }

3: Add configuration:

server.port: 8761
eureka.client.register-with-eureka: false
eureka.client.fetch-registry: false

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eureka Client:
    Registers itself with Eureka
    Sends heartbeat every 30 seconds
    Deregisters automatically if it goes down
     
1: Add Dependency:
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
</dependency>

2: Add configuration:
spring.application.name: user-service
eureka.client.service-url.defaultZone: http://localhost:8761/eureka

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eureka Heartbeat:

When a microservice registers with Eureka Server, 
it must periodically send a heartbeat (a tiny HTTP request) so Eureka knows the service is still healthy.
Default : 30 seconds

If a heartbeat is missed for too long, the service is removed from the registry.

eureka.instance.lease-renewal-interval-in-seconds: 10           //Send heartbeat every 10 sec
eureka.instance.lease-expiration-duration-in-seconds: 30        //Remove service if no heartbeat in 30 seconds

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
