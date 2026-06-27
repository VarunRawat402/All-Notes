-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot Basics:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Framework:
    → A framework to build Java enterprise applications
    → You dont create beans manually, Spring automatically creates and manages them for you
    → Problem: configuring Spring itself was complex (XML, boilerplate)

SpringBoot:
    → Built ON TOP of Spring Framework
    → Solves Springs configuration complexity
    → Automatic configuration using dependencies in pom.xml
    → Embedded Tomcat/Jetty server included
    → Pre-defined dependencies like spring-boot-starter-web

-----------------------------------------------------------------------------------------------------------------------------------------------------

Inversion Of Control:
    → Instead of YOU creating beans manually, Spring automatically creates and manages them for you
    → All auto-created beans are stored inside the IoC Container.
    → Objects created manually using new are not stored in the IoC Container, so Spring cannot inject them.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Dependency Injection:
    → DI allow us to use beans created by spring anywhere in the application

3 ways to inject:
    → Constructor Injection
    → Setter Injection
    → Field Injection
    
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
    → Comes after ? in the URL
    → Used when filtering, sorting, pagination etc etc is required
    → It is optional if required = false
    → /users?status=active&sort=name&page=2

@GetMapping("/users")
public List<User> getUsers(@RequestParam String status, @RequestParam int page) {
    return service.find(status, page);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

@PathVariable:
    → Part of the URL path itself
    → Used to identify a specific resource
    → It is not optional, Value needs to be passed or URL will fail
    → /orders/456/items/9 

@GetMapping("/users/{id}")
public User getUser(@PathVariable Long id) {
    return service.getUser(id);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why Main() is static:
    → When JVM starts, no objects exist yet
    → JVM needs to call main method to start the program
    → To call a method without an object → it must be static

If main() is not static:
    → JVM would need to create an object first
    → But which constructor to call?
    → What if constructor needs arguments?
    → JVM has no way to know → so it would fail

-----------------------------------------------------------------------------------------------------------------------------------------------------

Command line runner :
    → Interface
    → Runs code after spring context is fully started
    → @Override the run() method

Main():
    → Runs BEFORE Spring creates beans, loads configs, autowires dependencies
    → Cannot use @Autowired fields, beans, repos, services here

-----------------------------------------------------------------------------------------------------------------------------------------------------

Logging:

SLF4J:
    → Just an API (wrapper)
    → You write logs using SLF4J → actual logging done by framework underneath
    → Benefit: switch logging framework without changing code

Log4j:
    → Actual logging framework → does the real work

How to use:

Option 1: Manual logger
    private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    logger.info("This is an info message");

Option 2: Lombok (cleaner)
    @Slf4j  → on top of class
    log.info("message");  → use directly

Log levels (low → high):
    TRACE → DEBUG → INFO → WARN → ERROR

-----------------------------------------------------------------------------------------------------------------------------------------------------
