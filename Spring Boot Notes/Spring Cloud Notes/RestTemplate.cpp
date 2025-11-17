------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Rest Template and Feign Client in Microservices
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REST TEMPLATE:
    RestTemplate is a synchronous HTTP client used to perform REST calls.

1: Synchronous Operations: 
        The executing thread waits (blocks) until the response is received. One request occupies one thread until completion.

2: Template Methods: 
        Provides built-in methods like getForObject, postForObject, exchange, etc., reducing boilerplate code for common HTTP operations.

3: Error Handling: 
        Comes with a default error handler, which can be customized for specific client or server error handling.

4: Data Conversion: 
        Automatically converts request/response bodies to and from Java objects using message converters.
        Supports multiple formats and can be extended for custom types.

5: Interceptors: 
        Allows adding ClientHttpRequestInterceptor for modifying requests (headers, tokens) or logging request/response details.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:
RestTemplate restTemplate = new RestTemplate();

// getForObject performs GET and converts the response to the given type
String result = restTemplate.getForObject(
        "http://example.com/api/resource",
        String.class
);
System.out.println(result);

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

While RestTemplate was widely used, it does not support non-blocking I/O, which is a limitation for reactive or high-scale systems.
It is deprecated in favor of WebClient, which supports both synchronous and asynchronous non-blocking operations.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Thread Concept:

When a client sends a request, the server assigns one thread to handle it.
That thread performs all operations (DB calls, remote service calls) and stays blocked until the response is ready.
After the response is sent, the thread becomes free.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RestTemplate → Blocking
Spring WebFlux (WebClient) → Non-Blocking
Feign Client is blocking by defualt but we can make it non blocking with customization

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FEIGN CLIENT:
    Feign is a declarative HTTP client that simplifies calling REST services by defining interfaces.

Steps to implement it:

1: Add the spring cloud starter openfeign Dependency

2: Create a FeignClient interface for a specific microservice where you define the remote REST API calls.
3: Define methods inside the interface. Each method represents a remote REST call.
        The url is the base URL used for all endpoints in that Feign client.
4: Autowire the Feign client in the required service class (similar to RestTemplate usage).
        @Autowired
        AddressClient addressClient;
5: Add @EnableFeignClients Annotation in the main Class.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:
@FeignClient(name="abc", url = "http://localhost:8081/api/")
public interface AddressClient {

    @GetMapping("/address/{id}")
    public AddressResponse getAddressByEmployeeId(@PathVariable("id") int id);
} 

You can define multiple REST API functions inside a single Feign client if they belong to the same microservice.
In this example, the Feign client communicates with the Address Service, so all address-related endpoints can be added here.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Load Balancer:
It used to distribute the load and not let any server overload.
Spring provides Spring Cloud LoadBalancer, and older systems used Netflix Ribbon.

Scenario:
If multiple instances of the Address Service are running due to high traffic, the Employee Service must call them in a load-balanced manner.
The load balancer is applied on the client side, meaning the Employee Service decides which Address Service instance to call.e.

Code:
@FeignClient(name = "abc")
@RibbonClient(name = "address-service")
public interface AddressClient {

    @GetMapping("/address/{id}")
    public AddressResponse getAddressByEmployeeId(@PathVariable("id") int id);
}

application.properties:
//The first things is name of the ribbon client { address-service } should be same 
address-service.ribbon.listOfServers = http://localhost:8081,http://localhost:8082

Why Dynamic Discovery Is Needed

When deploying multiple instances, you do not know the exact IP/port beforehand.
If instances are added or removed (e.g., scaling from 4 to 2), manually changing IPs and ports is not feasible.
To solve this, systems use Service Discovery (Eureka, Consul, etc.) where microservices register themselves, and Feign + LoadBalancer fetches instance details dynamically.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Why Hardcoding URLs Is a Bad Practice

In microservices, servers are frequently scaled up or down. Because of this, their IP addresses and ports keep changing.
If URLs are hardcoded, you must manually update every service each time scaling happens.
This makes hardcoding URLs unreliable and not practical in real microservices environments.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Server-Side Load Balancing / Front Load Balancer:

Service A → Load Balancer → Service B (LB distributes requests across B instances)

Disadvantages of this:

Two remote call : 
    Client → Load Balancer
    Load Balancer → Server instance

Single point of failure : If the LB goes down, no requests reach the backend services.
Maintenance cost : Requires separate configuration, monitoring, and a dedicated team.
Manual configuration : You must manually configure IPs and ports of server instances on the LB.
Does not support Scalability

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Discovery service:
A Discovery Service stores the list of all active service instances along with their IP and port.
Load balancers or clients use this registry to know which servers are available.

Server Side Discovery:

Client A sends a request to the Load Balancer.
Load Balancer queries the Discovery Service.
Discovery Service returns available server instances.
Load Balancer picks one instance and forwards the request.

Client A never talks directly to the Discovery Service.
Ex: NGNIX, AWS ELB

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client Side Load Balancing:

Client A queries the Discovery Service.
Discovery Service returns all available instances of Service B.
Client A stores (caches) this instance list.
Client A performs load balancing locally, without any external LB.
    This removes the need for a dedicated load balancer server.
    The cached instance data prevents frequent calls to the Discovery Service.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

