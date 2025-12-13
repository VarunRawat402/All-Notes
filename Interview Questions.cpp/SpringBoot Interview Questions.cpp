-------------------------------------------------------------------------------------------------------------------------------
SpringBoot Interview Questions:
https://chatgpt.com/c/693a5d7f-7ae4-8322-bca2-a21f435eeb05
-------------------------------------------------------------------------------------------------------------------------------

Spring Framework:
Requires a lot of manual configuration
Bean creation, Web configuration, Dependency Injection
You have to set up the application server, dependencies, and configurations yourself.

SpringBoot:
Automatically configures beans based on the dependencies in your projec
Comes with embedded Tomcat/Jetty
Pre-Defined Dependency like springboot starter Web

-------------------------------------------------------------------------------------------------------------------------------

Explain Spring Boot Starters. Can you give examples:
Instead of adding multiple dependencies individually, you just include a single starter which includes related dependencies

spring-boot-starter-web
spring-boot-starter-data-jpa
spring-boot-starter-security
spring-boot-starter-actuator

-------------------------------------------------------------------------------------------------------------------------------

What is application.properties vs application.yml? Which one do you prefer:

1. application.properties:
Key-value pairs, simple and straightforward.
spring.datasource.url=jdbc:mysql://localhost:3306/mydb
spring.datasource.username=root
spring.datasource.password=root

2. application.yml (YAML):
Hierarchical, uses indentation for nesting.

spring:
  datasource:
    url: jdbc:mysql://localhost:3306/mydb
    username: root
    password: root

or small projects or simple settings → application.properties is fine.
For larger projects with hierarchical configurations → application.yml is preferred.

-------------------------------------------------------------------------------------------------------------------------------

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

-------------------------------------------------------------------------------------------------------------------------------

Conditional beans:
    Conditional Beans in Spring Boot are beans that are created only if certain conditions are met

1: @ConditionalOnProperty
Create a bean only if a property is set in application.properties or application.yml.

@Bean
@ConditionalOnProperty(name = "feature.enabled", havingValue = "true")
public MyService myService() {
    return new MyService();
}

feature.enabled=true
If feature.enabled=false, myService bean wont be created.

2: @ConditionalOnMissingBean:
Create a bean only if another bean of the same type is NOT already present.

@Bean
@ConditionalOnMissingBean
public MyService defaultService() {
    return new MyService();
}


3: @ConditionalOnClass:
Create a bean only if a specific class is present on the classpath.

@Bean
@ConditionalOnClass(name = "com.example.SomeLibrary")
public MyService someService() {
    return new MyService();
}


4: @ConditionalOnBean
Create a bean only if another specific bean exists.

@Bean
@ConditionalOnBean(MyOtherService.class)
public MyService myService() {
    return new MyService();
}

-------------------------------------------------------------------------------------------------------------------------------

What is @Value:
Annotation for injecting configuration values into fields

app.name=MyApp
app.port=8081


@Value("${app.name}")
private String appName;

@Value("${app.port}")
private int appPort;

@Value("${app.port:9000}")
private int appPort;

-------------------------------------------------------------------------------------------------------------------------------

@ConfigurationProperties:
Bind a group of related properties to a Class attributes automatically.
Used for binding multipe properties at once

app:
  name: MyApp
  port: 8080
  features:
    enabled: true

@Component
@ConfigurationProperties(prefix = "app")
public class AppProperties {
    private String name;
    private int port;
    private Features features;

    // getters and setters

    public static class Features {
        private boolean enabled;
        // getter & setter
    }
}

-------------------------------------------------------------------------------------------------------------------------------

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

-------------------------------------------------------------------------------------------------------------------------------

What is the N+1 query problem and how to solve it in Spring Boot?:

1: Use JOIN FETCH in JPQL
2: Use @EntityGraph
3: Batch Fetching (Hibernate-specific)

@Query("SELECT d FROM Department d JOIN FETCH d.employees")
List<Department> findAllWithEmployees();

@EntityGraph(attributePaths = "employees")
List<Department> findAll();

@OneToMany(mappedBy = "department")
@BatchSize(size = 10)
private List<Employee> employees;

-------------------------------------------------------------------------------------------------------------------------------
