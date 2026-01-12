----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Framework:
    Requires a lot of manual configuration
    You have to set up the application server, dependencies, and configurations yourself.

SpringBoot:
    Automatically configures beans using dependencies based on pom.xml
    Comes with embedded Tomcat/Jetty server
    Pre-Defined Dependency like springboot starter Web

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Explain Spring Boot Starters. Can you give examples:
    Spring Boot Starters are pre-defined dependency that group related dependencies together.

    spring-boot-starter-web
    spring-boot-starter-data-jpa
    spring-boot-starter-security
    spring-boot-starter-actuator

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component, @Service, @Repository, @Controller.

1. @Component:
    General-purpose bean.
    Use it when your class doesnt fit service, DAO, or controller.
    No special behavior.

2. @Service
    Business logic layer (services).
    Mostly for clarity: tells other developers, “this class does business work.”
    Can be used for AOP / transactions.

3. @Repository
    Data access layer (DAO classes).
    Special feature: converts database exceptions to Spring exceptions automatically.
    Otherwise works like @Component.

4. @RestController
    Presentation layer (handles HTTP requests).
    Works with Spring MVC.
    @RestController is a special version for REST APIs.
    If @Component is used, get and post will not work

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between CrudRepository, JpaRepository, and PagingAndSortingRepository.

CrudRepository:
    CRUD Methods
    save(), findById(), findAll(), delete(), count(), etc.

PagingAndSortingRepository:
    Extends CrudRepository with pagination and sorting support.
    CURD methods + Pagination and Sorting
    findAll(Sort sort)
    findAll(Pageable pageable)

JpaRepository:
    Extends PagingAndSortingRepository and adds JPA-specific methods.
    CURD methods + Pagination and Sorting + extra methods
    flush()
    saveAndFlush()
    deleteInBatch()
    getOne() (lazy fetch)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

API Versioning:
It is used to make changes to existing APIs without breaking existing clients and users 

Why API versioning is used
Backward compatibility      : Old clients continue to work while new clients use updated APIs.
Safe evolution              : You can add/remove fields or change behavior without impacting everyone.
Independent client upgrades : Mobile apps, partners, and third-party consumers upgrade at different times.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: URI-based versioning (most common and simple):
Easy to understand and debug
Works well with caching and gateways
URI Changes every version

@RestController
@RequestMapping("/api/v1/users")
public class UserControllerV1 {
    public UserV1 getUser() {return new UserV1("Varun");}
}

@RestController
@RequestMapping("/api/v2/users")
public class UserControllerV2 {
    public UserV2 getUser() {return new UserV2("Varun", "Rawat");}
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Header-based versioning:
Client sends:
    X-API-VERSION: 2


@RestController
@RequestMapping("/api/users")
public class UserController {

    @GetMapping(headers = "X-API-VERSION=1")
    public UserV1 getUserV1() {return new UserV1("Varun");}

    @GetMapping(headers = "X-API-VERSION=2")
    public UserV2 getUserV2() {return new UserV2("Varun", "Rawat");}
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@SpringBootApplication Annotation:
    It consist of 3 annotations

1: @EnableAutoConfiguration:
Automatically configures beans based on:
    Dependencies in pom.xml
    Properties in application.properties / application.yml

Example:
If spring-boot-starter-web is present → configures DispatcherServlet, Tomcat, etc.

2: ComponentScan:
Scans the package and subpackage to create bean who has annotatins like @Component, @Service etc etc 

3: Configuration:
Marks the class as a source of bean definitions
Allows use of @Bean methods

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constructor vs Setter Dependency Injection:

Constructor Injection:
    The object cannot be created without required dependencies.
    Once the object is created, dependencies are immutable
    Easy to pass mocks through the constructor.
    Works well with @RequiredArgsConstructor in Lombok.

Setter Injection:
    Dependencies are injected after object creation
    Dependencies are mutable
    Dependencies can be changed or reconfigured at runtime.
    Object may be used before dependencies are set → NullPointerException.
    Must remember to call setter before test; mocks not forced.

Autowired:
    Used by Spring to inject dependencies
    Uses reflection internally

Note:
When you have 1 constructor of the class dependencies will automatically gets injected using constructor Injection
When you have 2 constructors, we need to specify which constructor should be used to inject dependencies

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component and @Configuration.

@Component:
Marks a class as a simple Spring-managed bean.
Automatically creates the bean of the class in Spring IOC container

@Configuration:
Defines a class Configuration class to create beans
Used on classes in which we define @bean

Note:
We can create @Bean like this in any class but it wont enforces the singleton rule and we will get new instance everytime its injected
In Configuration class it enforces it to be singleton

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
