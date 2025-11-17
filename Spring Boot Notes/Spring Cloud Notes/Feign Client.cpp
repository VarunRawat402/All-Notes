------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Feign Client Practical:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

There are 3 Mircoservice:
    Address Service
    Employee Service
    Discovery Service

Address Service gives the addrress of the Employee
Employee Service gives the personal info of the Employee
Discovery Service is used to connect to and remeber the ports and IP of the Mircoservice

In order to get the address from the Address service we need to make a call to the address service from Employee service
We will do that using Feign Client 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------\

Application Properties code:

Discovery Service Properties code:
    spring.application.name=discovery
    server.port = 8761

    eureka.client.fetch-registry = false            //Now this will not fetch the details of other microservices from Discovery Service
    eureka.client.register-with-eureka=false        //It will not resigter itself with Discovery Service

Address Service Properties code:
    spring.application.name=address
    spring.datasource.url=jdbc:mysql://localhost:3306/address?createDatabaseIfNotExist=true
    spring.datasource.username=root
    spring.datasource.password=root402
    server.port=4000
    spring.jpa.hibernate.ddl-auto=update

    management.endpoints.web.exposure.include=*
    management.info.env.enabled=true
    info.app.name = Address-Service
    info.app.version = 1.0.0
    info.app.description = Address-Service which gives the address of the employee 

Employee Service Properties code:
    spring.application.name=employee
    spring.datasource.url=jdbc:mysql://localhost:3306/employee?createDatabaseIfNotExist=true
    spring.datasource.username=root
    spring.datasource.password=root402
    server.port=5000
    spring.jpa.hibernate.ddl-auto=create

    management.endpoints.web.exposure.include=*
    management.info.env.enabled=true
    info.app.name = Employee-Service
    info.app.version = 1.0.0
    info.app.description = Employee-Service which gives the info of the Employee

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Feign Client:

AddressClient is an interface for the address Mircoservice
Whenever getAddress method will run it will make a call to the IP and gets the data

Code:
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
It is automatically included in the netflix eureka dependency but you can add manually the dependency too
If you have multiple instances of 1 Mircoservice the load Balancer will use default technique ( Round Robin )
We can change the technique of Load balancing too in the Load Balancer

------------------------------------------------------------------------------------------------------------------------------------------------------------------------