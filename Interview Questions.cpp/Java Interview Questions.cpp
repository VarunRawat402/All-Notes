----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What are the main features of Java?

Platform Independent:
Compiles java code to byte code which is platform independent
Follows OOP principles
Automatic garbage collection reduces memory leaks.
Supports MultiThreading, build in libraries 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is exception propagation?
When an exception does not get caught it travels all the way back from where it gets propogated untill it gets caught or program crashes

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STACK:
method calls + local variables +  Refernce of objects + Primitive values

HEAP:
objects + arrays + Instance variable

Metaspace:
Class info ( class name, class structure ) + static variables

Examples:

int a = 10;                         //a and 10 both in stack
String s = "Varun"                  //s in stack, Varun in heap
Student s = new Student()           //s in stack, Object in heap

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How hashCode() and equals() work in collections:

hashCode() - decides bucket location
equals() - decides duplicate or not

Explanation:

You have 2 objects you want to save in hashmMap:
hashcode() creates hashcode of both the objects using key

If hashcode is different then both will be added
if hashcode is same, it will check if value is same or not using equals()
if value is same, then duplicates not added, if value is not same added

If key is same of 2 objects then hashcode will always be same too

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Garbage Collection:
It is a process by which JVM automatically frees memory occupied by objects that have no reference point
Prevent memory leaks
Manage heap memory automatically

How GC Works (High-level)

JVM identifies objects that are not reachable from any live thread or static reference.
Removes them from heap memory.
Frees memory for future object allocation.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Finalize vs Try with resource:

Finalize:

It is a method we override in the class to close the resources
GC calls finalize() automatically when object points to no reference
Depricated now, because it can take hours, or GC may never call finalize() and resource will never gets closed.

Try with resource:

It is used to automatically close the resource after the try catch ends.
In this you dont need to manually close the resource in the Finally
Your class must implements Closeable or AutoCloseable interface and overrides the close() method
Most classes already implement close() method

Example:
//Need to pass the resource in the () after try and it will close automatically
try (Resource res = new Resource()) {
    res.use();  // Auto-closes after this block
}  // c

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Synchronized

Keyword in Java.
Used to achieve implicit locking.
When a thread enters a synchronized block/method, it acquires the lock automatically, and releases it when the block/method ends.
Works at method level or block level.

Lock 
Interface introduced in Java 5 (ReentrantLock, ReadWriteLock, etc.).
Provides explicit locking — the programmer must manually acquire and release the lock.
More flexible than synchronized.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is starvation?

Starvation happens when a thread is ready to run but is continuously ignored because other higher-priority threads keep taking resources.
Thread scheduling policies.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW:
    Thread is created but not start yet
    Thread t1 = new Thread((){

    });

RUNNABLE:
    Thread start is called and not its ready to run
    But not running yet, waiting for sheduler to give it Time
    t1.start()

RUNNING:
    Sheduler gives the thread time and now its running

BLOCKED:
    Thread is blocked because another thread has the lock

WAITING:
    waiting for other thread to release the lock

TERMINTED:
    Thread has finished execution

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between wait(), notify(), and notifyAll().
Difference between ExecutorService and ThreadPool.
Difference between Callable and Runnable.
PartitioningBy()

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between Optional and Nullable.

Nullable
A variable can have the value null, meaning it doesnt reference any object
String name = null; 

Optional
Designed to avoid null checks and make the absence of a value more explicit.
It basically a container that may or may not hold a non-null value.

Optional<String> name = Optional.ofNullable(null);
System.out.println(name.isPresent()); // false
System.out.println(name.orElse("Name not provided")); // "Name not provided"

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between peek() and map() in streams.

map()

Transforming operation.
Takes each element from the stream and applies a function to produce a new element.
Returns a new stream of transformed elements.
Its an intermediate operation.

peek()

Debugging/inspection operation.
Lets you look at each element in the stream as it flows, but does not change it.
Its an intermediate operation (like map), but returns the same elements unmodified.
Mostly used for logging/debugging.

Ex:
List<String> result = names.stream()
        .peek(n -> System.out.println("Before map: " + n))
        .map(String::toUpperCase)
        .peek(n -> System.out.println("After map: " + n))
        .collect(Collectors.toList());

System.out.println(result); // [ALICE, BOB, CHARLIE]

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What are classloaders in Java?

It is a part of JVM that loads class into memory
Class is not loaded into memory when created 
It gets loaded into the memory when an object is created, or static method is called

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Saga Design Pattern:
The Saga pattern is used in microservices to manage distributed transactions while maintaining data consistency without using a single global transaction.


1: Choreography-Based Saga

No central coordinator.
Each service publishes events when a transaction step is completed.
Other services listen to events and perform their local transaction.
If a step fails, compensating transactions are triggered by listening to failure events.

Example:
    Order Service creates an order → emits OrderCreatedEvent.
    Payment Service listens → process payment → emits PaymentCompletedEvent.
    Inventory Service listens → reserve stock → emits StockReservedEvent.
    If Payment fails → Payment Service emits PaymentFailedEvent → Order Service cancels order (compensating transaction).

2: Orchestration-Based Saga
Central orchestrator (Saga Coordinator) controls the flow.
Orchestrator tells each service what to do next.
On failure, orchestrator triggers compensating transactions.
Each service must provide a method to undo its work.

Example:
    Orchestrator calls Order Service → create order.
    Orchestrator calls Payment Service → process payment.
    Orchestrator calls Inventory Service → reserve stock.
    If any step fails, orchestrator calls the compensation of previous steps.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Design Patterns in Microservices:

Communication Pattern:
Client side Discovery
Server side Discovery
Kafka, RabbitMQ for Communication

Resilience Patterns:
Use Circuit Breaker, Retry, BulkHead

Service Design Patterns:
API Gateway
Saga pattern

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle failure of services in a microservices ecosystem?

Circuit Breaker:
Prevents repeated calls to a failing service using CB
Provide an alternative response if a service fails using FallBackResponse
Avoid waiting indefinitely for a slow service, use request timeouts
use Health checks, monitoring, logs, tracing 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@SpringBootApplication Annotation:
It consist of 3 annotations:

1: @EnableAutoConfiguration:
Automatically configure beans based on:
Dependencies in pon.xml
application.properties

Example:
If spring-boot-starter-web is present → configures DispatcherServlet, Tomcat, etc.

2: ComponentScan:
Scans the package and subpackage to create bean who has annotatins like @Component, @Service etc etc 

3: Configuration:
Marks the class to initialize the bean definition

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What steps or processes do you follow for application deployment?

Compile and package the application:
    `mvn clean install`

Run unit & integration tests:
    `mvn test`

Create Docker File, Build docker image
Push Docker image to AWS ECR

push code to github
Follow branching strategy:
main - production
develop - staging
feature branches

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to store customer sensitive data like account information in database:

1:  Account Information:

Never Store Plain Text
Use Encryption (Not Hashing) for Account Data:
    You may need to read it back
    Hashing is one-way, encryption is reversible
AES-256 (symmetric encryption) - industry standard
Create encrypt() and decrypt() to encrypt and decrypt the data
Store the encrpt data and returns the decrypt data


2: Password:
Use Hashing for password, never decrypt the passwords

3: Keys:
Use a Secure Key Management System:
AWS KMS

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Why do we make a constructor private?
We make a constructor private to restrict object creation. 
Its commonly used in singletons, factory methods, utility classes, and to prevent inheritance.
To make singleton class, so there will only be 1 instance of that class
To make utility class, Every method static and constructor private so no one can create an instance of the class, like math.utility

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constructor vs Setter Dependency Injection:

Constructor Injection:
Once the object is created, dependencies cannot be changed.
The object cannot be created without required dependencies.
Easy to pass mocks through the constructor.
Works well with @RequiredArgsConstructor in Lombok.
Not suitable when you need to replace/modify dependency later.

Setter Injection:
You provide them only when needed.
Dependencies can be changed or reconfigured at runtime.
Object may be used before dependencies are set → NullPointerException.
Must remember to call setter before test; mocks not forced.

Autowired:
Annotation used by spring boot to inject dependencies
It uses reflection to inject dependency
Feild must not be final 

Note:
When you 1 constructor of the class dependencies will automatically gets injected using constructor Injection
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

Static vs Dynamic Binding

Static Binding:
It happens at compile time and applies to private, static and final methods

Dynamic Binding:
It happens at runtime when you override the methods and it chooses at run time which method to call parent one or the child one

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RestTemplate vs FeignClient vs WebClient:
https://chatgpt.com/c/693a2b9d-9c18-8321-bbef-50045bf34c3f




