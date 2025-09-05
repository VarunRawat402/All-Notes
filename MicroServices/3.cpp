------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Open Feign / Feign client:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Steps to implement it:

1: Add the spring cloud starter openfeign Dependency

2: Make a Microservice specific FeignClient Interface in which we can implement rest API call functions
3: Creating the function which we will call and that function will hit the given url and get the data. 
    url = it is a base url which can be used in multiple feign clients 
4: Autowired the feign client in the Class you want to use like restTemplate
    code: 
    @Autowired
    AddressClient addressClient
5: Add @EnableFeignClients Annotation in the main Class.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:
@FeignClient(name="abc", url = "http://localhost:8081/api/")
public interface AddressClient {

    @GetMapping("/address/{id}")
    public AddressResponse getAddressByEmployeeId(@PathVariable("id") int id);
} 

You can make as many rest API calls in one feignclient for example:
This code is FeignClient for Address Service and can have multiple rest API calls for Address Service.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Load Balancer:
It used to distribute the load in equal manner and not let any server overload.
We are using Spring cloud Load Balancer and Netflix Ribbon LB
Lets say there are multiple address servers due to high traffic so how will the load Balancer
be implemented.

Load Balancer will be on to the client so the client will call the server in a load balanced way.
Employee service making call to address service so Load Balancer will be attached to the Employee service.

Code:
@FeignClient(name="abc")
@RibbonClient(name="address-service")
public interface AddressClient {

    @GetMapping("/address/{id}")
    public AddressResponse getAddressByEmployeeId(@PathVariable("id") int id);
} 

In xml file:
//The first things is name of the ribbon client { address-service } should be same 
address-service.ribbon.listOfServers = http://localhost:8081,http://localhost:8082;

When we deploy multiple servers of microservices we dont know the IP and port of the server and if 
lets say we deployed 4 servers and I removed 2 servers then i need to hardcore change the port and ip 
So we need to change these things dynamically

------------------------------------------------------------------------------------------------------------------------------------------------------------------------



