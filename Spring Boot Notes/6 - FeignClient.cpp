------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Rest Template:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Used to make HTTP calls from one microservice to another
RestTemplate is blocking (synchronous).
Deprecated for new projects
Use WebClient instead for modern apps

Example:

RestTemplate restTemplate = new RestTemplate();
String result = restTemplate.getForObject("http://example.com/api/resource",String.class);      //get the resource and convert it to string
System.out.println(result);

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FEIGN CLIENT:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Feign is used to call other microservices just by writing an interface.
No manual RestTemplate code, Clean and readable code
Works very well with Eureka, Built-in load balancing support


Steps to implement it:

1: Add OpenFeign dependency
2: Create an interface of microservice you need to communicate with
3: Annotate with @FeignClient
4: Define methods using Spring MVC annotations
5: Enable Feign in main class

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example:

Interface:
    @FeignClient(name = "address-service")
    public interface AddressClient {

        @GetMapping("/address/{id}")
        Address getAddress(@PathVariable("id") int id);
    }

Service:
    public Employee getEmployee(int id) {

        Employee employee = repository.findById(id);

        Address address = addressClient.getAddress(id);
        employee.setAddress(address);

        return employee;
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Load Balancer:
    Distributes requests across multiple service instances
    old -> Netflix Ribbon
    New -> Spring cloud load balancer

Code:
@FeignClient(name = "address-service")
@RibbonClient(name = "address-service")
public interface AddressClient {
}

application.properties: 
address-service.ribbon.listOfServers = http://localhost:8081,http://localhost:8082          //The first things is name of the ribbon client { address-service } should be same

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client-Side Load Balancing ( Uses Spring Cloud Load Balancer ):
The client itself finds service instances and balances requests.

Flow:
    Client → Eureka (gets all instance IPs)
    Client → Caches instance list
    Chooses one instance
    Sends request directly

Examples: Feign + Eureka + Spring Cloud LoadBalancer

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Server-Side Load Balancing ( Uses External Load Balancer):
    Load balancer sits between client and services
    Client never knows service instances

Examples: NGINX, AWS ELB, F5

Flow:
Client → Load Balancer
Load Balancer → Eureka (gets instance list)
Load Balancer → Service

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Web Client:
    Replacement for RestTemplate
    Modern HTTP client
    Non-Blocking & Reactive

CREATE WEB CLIENT:

WebClient webClient = WebClient.create();
or 
WebClient webClient = WebClient.builder()
        .baseUrl("https://api.example.com")
        .defaultHeader(HttpHeaders.CONTENT_TYPE,
                       MediaType.APPLICATION_JSON_VALUE)
        .build();

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Mono:

Returns 0 or 1 value
Similar to:
    Optional
    CompletableFuture

Flux:

Returns 0 to N values
Similar to:
    List
    Stream

------------------------------------------------------------------------------------------------------------------------------------------------------------------------