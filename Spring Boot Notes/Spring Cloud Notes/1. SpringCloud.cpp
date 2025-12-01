------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Monolithic:

Advantages:
1: Entire application is built as a single unit.
2: All components are tightly coupled and reside in one codebase.
3: Easier to debug since everything is in one place.
4: Easier to test because all modules are available within the same application.

Disadvantages:
1: Scaling is difficult because you must scale the whole application instead of individual components.
2: Adding or modifying features becomes harder as the system grows since everything is tightly coupled.
3: As the application becomes large, understanding and maintaining the code becomes complex.
4: Deployment is challenging because even a small change requires redeploying the entire application.


------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MicroServices:

An architecture where an application is divided into independent services that communicate over the network.
Each service handles a specific functionality, and services can be developed, deployed, and scaled independently.
Different services can use different technologies based on requirements.
Failure in one service does not significantly impact the entire system.

Disadvantages:
Network calls between services can affect performance.
Distributed nature introduces latency, security concerns, and debugging complexity.


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Cloud:

A framework that provides tools and libraries for building distributed systems and cloud-native microservice architectures.
It offers components that help solve common challenges like service discovery, configuration management, load balancing, resilience, and API gateways.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Cloud Eureka: localhost:8761
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Lets say there are 2 services A & B
Service A has 200 instances which have different ports and IPs
So to connect to service A we need to know all the ports and IP which is very hectic 
Eureka solves this by maintaining a centralized registry of all instances.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: Creating the Discovery Service (Eureka Server):
    Add dependency:
    spring-cloud-starter-netflix-eureka-server

2: Enable Eureka Server:
    @EnableEurekaServer on the main class.

All microservices will connect to this server during startup.
They will pull the registry and use that to know where other services are running.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Prevent Eureka Server from Looking for Other Eureka Servers:

When the Discovery Service starts, it tries to find other Eureka servers.
If none exist, errors appear.

eureka.client.fetch-registry=false
eureka.client.register-with-eureka=false
This ensures the Discovery Service acts only as a server, not a client.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Discovery Service Application Properties:

server.port = 8761
spring.application.name = discover-service
eureka.client.fetch-registry = false
eureka.client.registry-with-eureka = false

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Registering Microservices with Eureka:

Add dependency in each microservice:
    spring-cloud-starter-netflix-eureka-client

When the microservice starts:

It knows Eureka normally runs at http://localhost:8761/eureka
It automatically attempts to register itself using this default URL.
The service appears on the Eureka dashboard at localhost:8761.

If multiple instances exist, all will appear separately in the registry.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How Eureka client and Discovery Connects Internally:

1: When Mircoservice starts they know where eureka usually runs which is default 8761
2: So they use the default localhost:8761/eureka to connect and register themselves with eureka

If Eureka is not running on the default port, microservices must be told where Eureka is.

To let the service know the path of the Discovery service
    eureka.client.service-url.defaultZone=http://localhost:5000/eureka/  

Eureka supports multiple discovery server URLs:
    eureka.client.service-url.z1 = localhost:5000/eureka/  
    eureka.client.service-url.z2 = localhost:5001/eureka/ 
    eureka.client.service-url.z3 = localhost:5002/eureka/  

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Note:
We need to add these urls in both Discovery service and Mircoservices

Eureka Heartbeat Mechanism:
Every Eureka client (every microservice) sends a heartbeat to Eureka every 30 seconds.
This tells Eureka that the instance is still alive.
If a service stops sending heartbeats:
    Eureka marks that instance as DOWN
    Eventually, Eureka removes it from the registry
    The heartbeat interval is configurable.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
