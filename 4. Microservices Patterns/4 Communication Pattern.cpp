------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Communication Pattern:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: Synchronous Communication:
    → Service A  →  Service B  →  Waits untill response
    → Failure or delay impacts Service A
    → Tight runtime coupling between services
    → used when immediately respone needed
    → Example: RestTemplate, Feignclient

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
2. Asynchronous Communication:
    → Service publishes event  →  other services consumes events independently
    → No direct dependency
    → Producer does not wait for consumer
    → Example : Kafka, RabbitMQ

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: Hybrid Communication:

Real systems use both:
    → REST → queries / validations
    → Kafka → state changes / workflows

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Rest Template:
    → Used to make HTTP calls from one microservice to another
    → RestTemplate is blocking (synchronous).
    → Deprecated for new projects
    → Use WebClient instead for modern apps

Example:

RestTemplate restTemplate = new RestTemplate();
String result = restTemplate.getForObject("http://example.com/api/resource",String.class);

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FEIGN CLIENT:
    → Used to call other microservices just by writing an interface.
    → No manual RestTemplate code, Clean and readable code
    → Works very well with Eureka
    → Built-in load balancing via Spring Cloud LoadBalancer

Steps to implement it:

1: Add OpenFeign dependency
2: Create an interface of microservice you need to communicate with
3: Annotate with @FeignClient
4: Define methods
5: Enable Feign in main class

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example:

@FeignClient(name = "address-service")
public interface AddressClient {

    @GetMapping("/address/{id}")
    Address getAddress(@PathVariable("id") int id);
}

public Employee getEmployee(int id) {

    Employee employee = repository.findById(id);
    Address address = addressClient.getAddress(id);

    employee.setAddress(address);
    return employee;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------