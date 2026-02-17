----------------------------------------------------------------------------------------------------------------------
Annotations In Spring Boot
----------------------------------------------------------------------------------------------------------------------

@JsonIgnore: 	
    → Used on Entity feilds
    Excludes attributes from serialization and ignore the attribute in response
    → Spring will skip this field in API responses and in request-body mapping.

----------------------------------------------------------------------------------------------------------------------

@Transient: 	
    → Used on attributes that should not be saved in the database.
    → Hibernate ignores this field completely (no column generated).

----------------------------------------------------------------------------------------------------------------------

HikaryPool: 	
    → The default connection pool used by Spring Boot + Hibernate to efficiently manage database connections.

----------------------------------------------------------------------------------------------------------------------

@Table: 	
    → Customize table name.

@Column:	
    → Customize column name.

----------------------------------------------------------------------------------------------------------------------

GenerationType: 	
    → AUTO: Hibernate chooses the best strategy based on the database.
    → IDENTITY: Uses identity columns (auto-increment in MySQL).

----------------------------------------------------------------------------------------------------------------------

@CreationTimestamp:	
    → Automatically sets the field value to the current timestamp when the record is first inserted.

@UpdateTimestamp:	
    → Automatically updates the field value to the current timestamp whenever the entity is updated.

----------------------------------------------------------------------------------------------------------------------

DispatcherServlet:	
    → The front controller of Spring MVC.
    → Receives every HTTP request, maps it to the correct controller, processes the response, and sends it back to the client.

----------------------------------------------------------------------------------------------------------------------

@Slf4j:
    → Lombok annotation that automatically generates a Logger for the class.

----------------------------------------------------------------------------------------------------------------------
