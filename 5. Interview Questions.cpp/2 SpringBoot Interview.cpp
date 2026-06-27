-----------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component, @Service, @Repository, @Controller.

1. @Component:
    → Generic bean 
    → use when class doesn't fit any layer
    → No extra behavior

2. @Service
    → Business logic layer
    → No extra behavior but clarifies intent
    → AOP + transactions work cleanly here

3. @Repository
    → Data access layer
    → Auto converts DB exceptions → Spring DataAccessException

4. @RestController
    → Presentation layer → handles HTTP requests
    → @Controller + @ResponseBody combined
    → Without it → GET/POST mappings won't work

-----------------------------------------------------------------------------------------------------------------------------------------------------

@SpringBootApplication Annotation:
    → Combination of 3 annotations:

1: @EnableAutoConfiguration
    → Automatically configures beans based on dependencies
    → Example: spring-boot-starter-web, spring-boot-starter-security

2: @ComponentScan
    → Scans package/sub-packages
    → registers @Component, @Service, @Repository etc as beans

3: @Configuration
    → marks class as bean definition source
    → allows @Bean methods inside
        
-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference between @Component and @Configuration:

@Component:
    → Marks a class as Spring-managed bean
    → Bean created automatically in Spring IOC container

@Configuration:
    → Marks class as configuration class
    → Used to define @Bean methods manually
    → Enforces SINGLETON → same instance returned every time

Note:
    → @Bean inside @Configuration    → singleton enforced
    → @Bean outside @Configuration   → new instance created every injection 

-----------------------------------------------------------------------------------------------------------------------------------------------------

hasRole vs hasAuthority:

→ Both check permissions, just different naming conventions
→ So you can add roles and authorties togethere for a user

hasRole:
    → Automatically adds ROLE_ prefix when checking
    → hasRole("ADMIN") → looks for "ROLE_ADMIN" in authorities
    → Must store as "ROLE_ADMIN" in DB

hasAuthority:
    → Checks EXACT string, no prefix added
    → hasAuthority("ADMIN") → looks for "ADMIN"
    → Must store as "ADMIN" in DB

Example:

.requestMatchers("/users/read")
    .hasRole("USER")                            // checks for "ROLE_USER"
    .hasAuthority("AUTHORITY_READ_PRIVILEGE")   // checks for exact "AUTHORITY_READ_PRIVILEGE"

-----------------------------------------------------------------------------------------------------------------------------------------------------

Method level security:
    → Add @EnableMethodSecurity on main class to activate
    → Used on @RestController and @Service methods

-----------------------------------------------------------------------------------------------------------------------------------------------------

Preauthorize():
    → Checks BEFORE method executes
    → Use to validate: caller's role / method parameters
    → Method never runs if check fails

@PreAuthorize("hasRole('ADMIN')")
public List<User> getAllUsers() { }                 // only ADMIN can call

@PreAuthorize("#id == authentication.principal.id or hasRole('ADMIN')")
public User getUser(@PathVariable Long id)          // user can only get their own data OR admin can get anyone's

-----------------------------------------------------------------------------------------------------------------------------------------------------

Postauthorize:
    → Checks AFTER method executes
    → Use to validate the RETURN value
    → Method runs but result blocked if check fails


@PostAuthorize("returnObject.userId == authentication.principal.id")
public Order getOrder(Long id) { }          // can only return YOUR order

-----------------------------------------------------------------------------------------------------------------------------------------------------

API Versioning:
    → Update APIs without breaking existing clients

Why:
    → Backward compatibility  → old clients keep working
    → Safe evolution          → add/remove fields without breaking everyone
    → Independent upgrades    → mobile/web/partners upgrade at their own pace

-----------------------------------------------------------------------------------------------------------------------------------------------------

1. URI Versioning (most common):
    → Version in URL → easy to read, debug, cache
    → /api/v1/users | /api/v2/users

@RequestMapping("/api/v1/users")
public UserV1 getUser() { return new UserV1("Varun"); }

@RequestMapping("/api/v2/users")
public UserV2 getUser() { return new UserV2("Varun", "Rawat"); }

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. Header Versioning:
    → URL stays same → version sent in request header
    → X-API-VERSION: 2

@GetMapping(headers = "X-API-VERSION=1")
public UserV1 getUserV1() { return new UserV1("Varun"); }

@GetMapping(headers = "X-API-VERSION=2")
public UserV2 getUserV2() { return new UserV2("Varun", "Rawat"); }

-----------------------------------------------------------------------------------------------------------------------------------------------------

When to use:
    URI versioning    → public APIs, easy to test, most common
    Header versioning → cleaner URLs, internal/partner APIs

-----------------------------------------------------------------------------------------------------------------------------------------------------