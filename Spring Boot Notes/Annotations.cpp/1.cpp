Annotations In Spring Boot

@Component: 	
It is used to mark a class as a Spring-managed component.
Spring automatically detects and registers it as a bean in the application context.

@jsonIgnore: 	
It is used to skip the fields from serialization and deserialization and fetching from the DB
Spring Boot skips this feild in response

@Transient: 	
It is used on top of the attribute which we dont want as a column in our DB.
In Java, the field is ignored and not serialized.

HikaryPool: 	
It is a pool used by Hibernate to communicate with the internal DB.

@Table: 	
Customize table name.

@Column:	
Customize column name.

GenerationType: 	
Auto: Let Hibernate decide the best strategy for id generation and auto increment based on DB type.
Identity: Use MySQL identity.

@CreationTimestamp:	
This annotation is used to automatically set the value to current time when data is inserted first.

@UpdateTimestamp:	
This annotation is used to automatically update the value of the annotated field to the current time whenever the entity is updated and inserted.

@PostConstruct:	
Used on methods. Runs method automatically after bean is initialized and injected. Used for database connections.

@PreDestroy:	
Used on methods. Runs method before the bean is destroyed. Used for closing connections.

DispatcherServlet:	
It is a front controller. Receives request, finds the correct controller based on the URL, gets the response, renders it, and sends back to client.

Jackson:	
It is a library used for serializing and deserializing Java objects.

