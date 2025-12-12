------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Rest Template:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RestTemplate is used to make HTTP calls from one microservice to another microservice
RestTemplate is blocking (synchronous).
Use WebClient for New Projects

1: Synchronous Operations: 
Each request waits for the response. One request = one thread until its done.

2: Template Methods: 
Provides built-in methods like getForObject, postForObject, exchange, etc.. reducing boilerplate code.

3: Error Handling: 
Has a default error handler and lets you plug in custom handlers for 4xx/5xx responses.
        
4: Data Conversion: 
Converts JSON/XML ↔ Java objects using message converters. Supports custom converters too.

5: Interceptors: 
Lets you add interceptors to modify requests (headers, tokens) or log request/response.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Example:

RestTemplate restTemplate = new RestTemplate();

// getForObject performs GET and converts the response to the given type
String result = restTemplate.getForObject("http://example.com/api/resource",String.class);
System.out.println(result);

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RestTemplate → Blocking
Spring WebFlux (WebClient) → Non-Blocking
Feign Client is blocking by defualt but we can make it non blocking with customization

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FEIGN CLIENT:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Feign is used to call other microservices just by writing an interface.
Works great with Eureka because it can call services by service name.

Steps to implement it:

1: Add the spring cloud starter openfeign Dependency

2: You create an interface of the microservice you need to communicate with.
3: Add @FeignClient(name = "SERVICE-NAME").
4: Add methods with request mappings.
5: Feign automatically makes the HTTP call.
5: Add @EnableFeignClients Annotation in the main Class.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Example:

@FeignClient(name = "ADDRESS")
public interface AddressClient {
        @GetMapping("/address/{id}")
        public Address getAddress(@PathVariable("id") int id);
}

Controller class code:

@GetMapping(/employee/{id})

        public EmployeeResponse getEmployee(@PathVariable("id") int id) {
        emp employee = repository.findById(id).orElse(null);

        EmployeeResponse employeeResponse = modelMapper.map(employee, EmployeeResponse.class);
        Address address = addressClient.getAddress(id);
        employeeResponse.setAddress(address);

        return employeeResponse;
}

Main code:
    @SpringBootApplication
    @EnableDiscoveryClient
    @EnableFeignClients
    public class EmployeeApplication {

        public static void main(String[] args) {
            SpringApplication.run(EmployeeApplication.class, args);
            System.out.println("Employee Service is started");
        }

        
    }
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Load Balancer:
It is used to distribute the load between multiple microservice so not any server gets overloaded
old -> Netflix Ribbon
New -> Spring cloud load balancer

Code:
@FeignClient(name = "address-service")
@RibbonClient(name = "address-service")
public interface AddressClient {

    @GetMapping("/address/{id}")
    public AddressResponse getAddressByEmployeeId(@PathVariable("id") int id);
}

application.properties:
//The first things is name of the ribbon client { address-service } should be same 
address-service.ribbon.listOfServers = http://localhost:8081,http://localhost:8082

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Server-Side Load Balancing + Load Balancing:
A load balancer sits between the client and the service.
Examples: NGINX, AWS ELB, F5

Flow:
Client → Load Balancer
Load Balancer → Discovery Service (gets instance list)
Load Balancer → Picks an instance
Load Balancer → Forwards request to that instance
Client never sees service instances.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client-Side Discovery + Load Balancing:
The client itself finds service instances and balances requests.


Flow:
Client → Discovery Service (gets all instance IPs)
Client → Caches instance list
Client → Picks instance
Client → Sends request directly to that service
Examples: Ribbon, Spring Cloud LoadBalancer, Feign with Eur

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

