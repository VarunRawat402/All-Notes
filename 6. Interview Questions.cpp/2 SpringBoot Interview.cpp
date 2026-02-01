----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Framework:
    → Requires a lot of manual configuration
    → Manually set up application server, dependencies, and configurations manually

SpringBoot:
    → Automatically configures beans using dependencies in pom.xml
    → Embedded Tomcat/Jetty server included
    → Pre-defined dependencies like spring-boot-starter-web

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Explain Spring Boot Starters. Can you give examples:
    → Pre-defined dependencies that group related libraries together

Examples:
→ spring-boot-starter-web           → REST API / Web apps
→ spring-boot-starter-data-jpa      → JPA / Hibernate
→ spring-boot-starter-security      → Security features
→ spring-boot-starter-actuator      → Monitoring and metrics

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between CrudRepository, JpaRepository, and PagingAndSortingRepository.

CrudRepository:
    → Basic CRUD methods
    → save(), findById(), findAll(), delete(), count()

PagingAndSortingRepository:
    → Extends CrudRepository
    → Adds pagination and sorting
    → findAll(Sort sort), findAll(Pageable pageable)

JpaRepository:
    → Extends PagingAndSortingRepository
    → Adds JPA-specific methods
    → flush(), saveAndFlush(), deleteInBatch(), getOne() (lazy fetch)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

API Versioning:
    → Used to update APIs without breaking existing clients

Why API versioning is used
1: Backward compatibility → old clients continue to work
2: Safe evolution → add/remove fields without impacting everyone
3: Independent client upgrades → mobile apps, partners upgrade at different times

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. URI-based Versioning (most common):
    → Easy to understand and debug
    → Works well with caching & gateways
    → URI changes every version

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

2. Header-based Versioning:
    → Client sends header → X-API-VERSION: 2

@RestController
@RequestMapping("/api/users")
public class UserController {

    @GetMapping(headers = "X-API-VERSION=1")
    public UserV1 getUserV1() {return new UserV1("Varun");}

    @GetMapping(headers = "X-API-VERSION=2")
    public UserV2 getUserV2() {return new UserV2("Varun", "Rawat");}
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component, @Service, @Repository, @Controller.

1. @Component:
    → General-purpose bean
    → Use if class doesnt fit service, DAO, or controller
    → No special behavior

2. @Service
    → Business logic layer
    → Clarifies purpose to developers
    → Can be used for AOP / transactions

3. @Repository
    → Data access layer (DAO classes)
    → Converts database exceptions to Spring exceptions automatically
    → Otherwise behaves like @Component

4. @RestController
    → Presentation layer, handles HTTP requests
    → Works with Spring MVC
    → Special version for REST APIs
    → If only @Component is used → GET/POST wont work

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@SpringBootApplication Annotation:
    It consist of 3 annotations

1: @EnableAutoConfiguration
    → Automatically configures beans based on dependencies & properties
    → Example: spring-boot-starter-web → DispatcherServlet, Tomcat, etc.

2: @ComponentScan
    → Scans package/sub-packages
    → Creates beans for @Component, @Service, @Repository, etc.

3: @Configuration
    → Marks class as a source of bean definitions
    → Allows use of @Bean methods
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component and @Configuration:

@Component:
    → Marks a class as Spring-managed bean
    → Bean created automatically in Spring IOC container

@Configuration:
    → Marks class as configuration class
    → Used to define @Bean methods
    → Enforces singleton rule (Spring container manages single instance)

Note:
    → @Bean outside @Configuration class → new instance created each injection

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constructor vs Setter Dependency Injection:

Constructor Injection:
    → Object cannot be created without required dependencies
    → Dependencies are immutable once object is created
    → Works well with Lombok @RequiredArgsConstructor
    → Easy to pass mocks for testing

Setter Injection:
    → Dependencies injected after object creation
    → Mutable → can be changed at runtime
    → Object may be used before dependencies are set → NullPointerException possible
    → Must call setter before tests

@Autowired:
    → Used by Spring to inject dependencies
    → Uses reflection internally
    → Single constructor → auto-injected
    → Multiple constructors → specify which one to use

Note:
When you have 1 constructor of the class dependencies will automatically gets injected using constructor Injection
When you have 2 constructors, we need to specify which constructor should be used to inject dependencies

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

hasRole vs hasAuthority:

Role and authorities are just authorities strings 
They are same but with different naming conventions
So you can add roles and authorties togethere for a user
Example - user should have ROLE_USER and AUTHORITY_READ_PRIVILEGE to read something
    http.authorizeHttpRequests()
        .requestMatchers("/users/read")
            .hasRole("USER")                                // Must have ROLE_ADMIN
            .hasAuthority("AUTHORITY_READ_PRIVILEGE")       // Must have AUTHORITY_READ_PRIVILEGE


hasRole:
    → Checks for roles with prefix ROLE_
    → Have to manually add ROLE_ prefix when doing new SimpleGrantedAuthority
    → Example: hasRole("ADMIN") checks for "ROLE_ADMIN"

hasAuthority:
    → Checks for exact role without any prefix
    → No need for manually adding ROLE_ prefix
    → Example: hasAuthority("ADMIN") checks for "ADMIN"


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Preauthorize vs postauthorize:
    → Add this @EnableMethodSecurity
    → Can be used on both RestController and Service methods
    → Used for fine grained access
    → Can check method parameters and return values

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Preauthorize:
    Check BEFORE the method executes
    Used to validate method parameters or caller roles.

@GetMapping("/admin/users")
@PreAuthorize("hasRole('ADMIN')")
public List<User> getAllUsers() {
    return userService.findAll();
}

@GetMapping("/users/{id}")
@PreAuthorize("#id == authentication.principal.id or hasRole('ADMIN')")
public User getUser(@PathVariable Long id) {
    return userService.findById(id);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Postauthorize:
    Check AFTER the method executes
    Used to validate the returned object.

@PostAuthorize("returnObject.userId == authentication.principal.id")
public Order getOrder(Long id) {
    return orderRepo.findById(id).orElseThrow();
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
