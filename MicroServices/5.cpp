------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Cloud Eureka: localhost:8761
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Lets say there are 2 services A & B
Service A has 200 instances which have different ports and IPs
So to connect to service A we need to know all the ports and IP which is very hectic 
to get to know.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: First we will make a Discovery service with eureka server as a dependency
"spring cloud starter netflix eureka server"

2: Add @EnableEurekaServer annotation on the main class of the Discovery service
All Mircoservices will connect to eureka during the start up and fetch the 
eureka registry info of all the registered services and then use these to fetch the infos

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

When you start the discovery service what it will do is it will search for the other 
discover service to fetch the data of servers but we dont have any so it will give u the error

eureka.client.fetch-registry=false
It will make Discovery service stop to look for other Discovery service

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application Properties ( Discovery Service ):

server.port = 8761
spring.application.name = discover-service
eureka.client.fetch-registry = false
eureka.client.registry-with-eureka = false

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

We will add the "eureka discovery client dependency" in the address Mircoservice
By doing this we are making the address service a client to discover service

So,
Lets say we have 2 Mircoservice addressService and EmployeeService
When we start the addressService it will automatically make the call to the default discovery service url
to register itself
When it will register itself in the discovery service
You can see all the instances of all the Mircoservice registered in the discovery service in the eureka server
localhost:8761

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How Eureka client and Discovery Connects Internally:

1: When Mircoservice starts they know where eureka usually runs which is default 8761
2: So they use the default localhost:8761/eureka to connect and register themselves with eureka

What if we changed the port of the eureka:

1: Now we need to let these services know where the eureka is running otherwise they will try to
connect the eureka in default port which is wrong

To let the service know the path of the Discovery service
    eureka.client.service-url = localhost:5000/eureka/  

This url can take a map so we can add multiple ports of discover service here
    eureka.client.service-url.z1 = localhost:5000/eureka/  
    eureka.client.service-url.z2 = localhost:5001/eureka/ 
    eureka.client.service-url.z3 = localhost:5002/eureka/  

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Note:
We need to add these urls in both Discovery service and Mircoservices

Note:
Every Eureka client / Mircoservice sends heartbeat to the Discovery Service every 30 sec which 
tells discovery service to not remove that client from the registry
If it does not send the heartbeat the discovery service will remove that instances
You can change the interval of heartbeats of client

------------------------------------------------------------------------------------------------------------------------------------------------------------------------


