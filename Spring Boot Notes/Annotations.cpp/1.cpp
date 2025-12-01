----------------------------------------------------------------------------------------------------------------------
Annotations In Spring Boot
----------------------------------------------------------------------------------------------------------------------

@Component: 	
Marks a class as a Spring-managed component.
Spring automatically detects it during component scanning and creates a bean in IOC Container

----------------------------------------------------------------------------------------------------------------------

@Configuration:
Used to mark a class where we need to create beans manually 

Example: 
@Bean
public RestTemplate restTemplate(){

}
----------------------------------------------------------------------------------------------------------------------

@ComponentScan:
Used to tell spring to create bean of all the classes marked as @Controller, @Service, @Respository, @Component

----------------------------------------------------------------------------------------------------------------------

@EnableConfiguration:
Used to automatically set the environments based on dependencies

Example:
spring-boot-starter-web -> Tomcat and Spring MVC
spring-boot-starter-data-jpa -> I will set up DataSource, EntityManager, etc

----------------------------------------------------------------------------------------------------------------------

@JsonIgnore: 	
Used to exclude a field from JSON serialization and deserialization.
Spring will skip this field in API responses and in request-body mapping.

----------------------------------------------------------------------------------------------------------------------

@Transient: 	
Used on entity fields that should not be persisted in the database.
Hibernate ignores this field completely (no column generated).

----------------------------------------------------------------------------------------------------------------------

HikaryPool: 	
The default connection pool used by Spring Boot + Hibernate to efficiently manage database connections.

----------------------------------------------------------------------------------------------------------------------

@Table: 	
Customize table name.

@Column:	
Customize column name.

----------------------------------------------------------------------------------------------------------------------

GenerationType: 	
AUTO: Hibernate chooses the best strategy based on the database.
IDENTITY: Uses identity columns (auto-increment in MySQL).

----------------------------------------------------------------------------------------------------------------------

@CreationTimestamp:	
Automatically sets the field value to the current timestamp when the record is first inserted.

@UpdateTimestamp:	
Automatically updates the field value to the current timestamp whenever the entity is updated.

----------------------------------------------------------------------------------------------------------------------

@PostConstruct:	
Runs a method automatically after the bean is created and dependencies are injected.
Useful for initialization tasks.

@PreDestroy:	
Runs a method just before the bean is destroyed.
Used to close resources like database connections or threads.

----------------------------------------------------------------------------------------------------------------------

DispatcherServlet:	
The front controller of Spring MVC.
Receives every HTTP request, maps it to the correct controller, processes the response, and sends it back to the client.

----------------------------------------------------------------------------------------------------------------------

Jackson:	
A JSON serialization/deserialization library used by Spring Boot to convert Java objects to JSON and vice versa.

----------------------------------------------------------------------------------------------------------------------

@Slf4j:
Lombok annotation that automatically generates a Logger for the class.

----------------------------------------------------------------------------------------------------------------------
