-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot Basics:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Framework:
    → Requires a lot of manual configuration
    → Manually set up application server, dependencies, and configurations manually

SpringBoot:
    → Automatically configures beans using dependencies in pom.xml
    → Embedded Tomcat/Jetty server included
    → Pre-defined dependencies like spring-boot-starter-web

-----------------------------------------------------------------------------------------------------------------------------------------------------

Inversion Of Control:

→ Instead of you managing the lifecycle of beans, Spring creates and manages them.
→ @Component → Spring automatically creates a bean of that class.
→ All auto-created beans are stored inside the IoC Container.
→ Objects created manually using new are not stored in the IoC Container, so Spring cannot inject them.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Dependency Injection:

→ DI allows us to use beans created by Spring anywhere in the application.
→ If Spring did not create an object, then that object is not available for injection.

-----------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot Starters Dependency:
    → Pre-defined dependencies that group related libraries together

Examples:
→ spring-boot-starter-web           → REST API / Web apps
→ spring-boot-starter-data-jpa      → JPA / Hibernate
→ spring-boot-starter-security      → Security features
→ spring-boot-starter-actuator      → Monitoring and metrics

-----------------------------------------------------------------------------------------------------------------------------------------------------

@RequestParam:
    → Takes query parameters from URL
    → It is used when single param does not define a signle entity
    → Used when filtering, sorting, pagination etc etc
    → It can be optional when required=false
    → /users?status=active&sort=name&page=2

@GetMapping("/users")
public List<User> getUsers(@RequestParam String status, @RequestParam int page) {
    return service.find(status, page);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

@PathVariable:
    → Takes params from URL path
    → It is used when param defines a single entity
    → It is not optional even with required=false
    → Need to use multiple mappings to make it optional
    → /orders/456/items/9 

@GetMapping("/users/{id}")
public User getUser(@PathVariable Long id) {
    return service.getUser(id);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why Main() is static:
    → main() is static so JVM can call main() immediately, without creating any object.
    → If it were not static:
    → JVM would need to create an object, but it would not know which constructor to call.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Command line runner :
    → Interface
    → Runs code after spring context is fully started
    → @Override the run() method

Main():
    → You cannot use autowired fields + access beans + repo, service, controller etc
    → It is static and runs before spring creates beans, load configs, autowire dependency

-----------------------------------------------------------------------------------------------------------------------------------------------------

How to use Logger:

Sl4j:
    It is a wrapper API which is wrapped around logging framework
    It is used to everyone can write logs using sl4j common even if implementation inside is different

Log4j:
    It is a logging framework which implements logging and logs to actual file

Option 1:
    → private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    → logger.info("This is an info message");
    → Controller is the class name.

Option 2:
    → Use @Slf4j on top of the class
    → log.info("message");


-----------------------------------------------------------------------------------------------------------------------------------------------------
