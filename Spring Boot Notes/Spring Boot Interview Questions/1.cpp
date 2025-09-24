-----------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot Interview Topics:
-----------------------------------------------------------------------------------------------------------------------------------------------------------

CommandLineRunner: It is a functional Interface which helps us to run non-static functions in the main as main is static

-----------------------------------------------------------------------------------------------------------------------------------------------------------

JDBC: 	
It is an api that allows applications to connect to the database, usually Relational DB, 
Provides methods to connect, send SQL queries and process result	
It gives you direct control over sql execution

JDBC Template: 
It is used to map your java objects to DB

-----------------------------------------------------------------------------------------------------------------------------------------------------------

JPA: 	
It is a specification or interface that defines how java objects can be stored, retrieved and managed in relational DB
Its a set of rules, Does not provide implementation

Hibernate : 	
It is ORM, object relational mapping which implements the JPA Interface
Converts java objects to tables automatically, removes JDBC boiler plate code	

-----------------------------------------------------------------------------------------------------------------------------------------------------------

FetchType: 	
Lazy: 	Entity data is loaded only, related data is loaded only when its accessed	
Eager: 	Both Entity data and related data are loaded at first

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade:	It tells what to do with child entities when u perform some action in parent entity
CascadeType.ALL	    :   Applies all operations (Persist, Merge, Remove, Refresh, Detach).
CascadeType.PERSIST	:   Saves child entities when the parent is saved.
CascadeType.MERGE	:   Updates child entities when parent is updated.
CascadeType.REMOVE	:   Deletes child entities when parent is deleted.

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Pagination: 	
It is used to limit the number of records which needs to be shown, split large numbr of data into chunks
Helps performance and user Experience, You dont need to show 1 million users at once
limit 10, offset = limit * pageNumber

Sorting: 	It makes the data meaningful, like cheapest products, latest articles

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Dialect:	It is syntax of each DB, mysql , postgreSQL has different dialects from each other

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Transient: 	feild is not serialized, ignored during serialization

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Transactional: 	
It is used where either everything executes or nothing executes
With this if 1 step fails, everything rollbacks
Can be used at class level, method level and both level
Method level overrides the class level configurations

Propogation:	
It defines how transaction behaves when one transactional method calls another transactional method
if service A() calls another service B(), should they share same transaction or create new one

Types:		
1: If transaction exist, join it but If does not exist then creates a new one
2: Always start a new transaction, suspend existing one until this finishes
3: Must run inside a existing transaction, if not exist, Throw exception
4: If transaction exists join it, if not run without one

Isolation:	How isolated is my data from other running transactions

-----------------------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity:	
It is a class which is used to create HTTP response
new ResponseEntity<>(body, header, httpstatus)
It has already defined static methods to make it ease

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Content Negotiation:	
It is used to server responses in different formats like Json, XML HTML
Add the dependency only
It checks the requests headers:
Accept: application/json → Server returns JSON
Accept: application/xml → Server returns XML

-----------------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot Actuator:	
It provides production-ready features to monitor and manage your application.
It exposes built-in endpoints that give insights into your apps health, metrics, environment, and more.
Monitor Application health (DB up or down)
Gather metrics (memory, CPU, HTTP requests, GC)
Check logs and thread dumps
Integrate with monitoring tools (Prometheus, Grafana, ELK, etc.)

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Sheduled:		
It is used on methods to execute them at intervals or at specific time using cron expressions
@EnableScheduling annotation needs to add to Main method

Cron:			
It is an expression which tells sheduled to run at given time
Syntax: @Sheduled( sec, min, hour, day, month, day of week(sat,sun)
* means every time, 0 means skip
			
-----------------------------------------------------------------------------------------------------------------------------------------------------------
	
Primary:		
When you have bean of same type, spring wont know which one to inject 
So, @Primary annotation is used to tell spring which one to inject by default

Qualifier:		
@Qualifer is used to specify which bean to inject when there are multiple beans of same type
It overrides the primary one

@Primary			
@Bean
public RestTemplate restTemplate1(){
	return new RestTemplate();
}

@Bean
public RestTemplate restTemplate2(){
	return new RestTemplate();
}

@Qualifer("restTemplate2")

-----------------------------------------------------------------------------------------------------------------------------------------------------------

AOP:	
It is used to define logic which is same in every service 
Insted of duplicating the same logic in every class use AOP
Like logging, SecurityChecks, Performance Monitoring

Annotations:
	Before:		Runs before the method
	After: 		Runs after the method, does not matter if it fails or executes
	AfterReturning	Runs only after method returns some value
	AfterThrowing	Runs only after method throws an exception

Aspect: Aspect class in which all the things will get initialized, @Aspect is used on that class 

Advice: Logic Method that needs to be run

PointCut: Expression to tell which service or methods needs to be intercepted

JoinPoint:	When pointcut is true and advice is executed, A specific instance of advice is called joinPoint. 
            JoinPoint helps get method details inside an aspect.

Around Annotation:
	@Around advice runs before and after the method execution.
	Unlike @Before and @After, it can control when the target method executes at all.
	It can also modify arguments, change return values, or handle exceptions.

In this you have ProceedingJoinPoint, which represents the method being called
In this you have to call the actual method like proceedingJoinPoint.proceed()

You can handles exception by calling the actual method in the try catch and catching the exception
You can do anything before the method and after the method
proceed() returns the actual result of the method and you can modify it and return it

-----------------------------------------------------------------------------------------------------------------------------------------------------------
	




























