----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is exception propagation?
When an exception does not get caught it travels all the way back from where it gets propogated untill it gets caught or program crashes

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STACK:
method calls + local variables +  Reference of objects + Primitive values

HEAP:
objects + arrays + Instance variable

Metaspace:
Class info ( class name, class structure ) + static variables

Example:

int a = 10;                         //a and 10 both in stack
String s = "Varun"                  //s in stack, Varun in heap
Student s = new Student()           //s in stack, Object in heap

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Contract Between .equals() and Hashcode():

hashCode()  - decides bucket location
equals()    - used to check the value

Explanation:

You have 2 objects you want to store in the hashmap
hashcode() -> creates hashcode of both Keys

Put:
if hashcode() is different both will be added in different buckets
if hashcode() is same then both will be added in same bucket

Get:
If hashcode() is same, then .equals() method is used to get the correct key from the bucket

If a.equals(b) is true
    Then, a.hashCode() == b.hashCode() 

If a.hashCode() == b.hashCode()
    Then, a.equals(b) may be true or false

Example:
k1 = "varun" & k2 = "arun"
Asssume both hashcode are same
k1 and k2 will be stored in same bucket due to same hashcode() means hashing collision
Now when you get k1, hashcode() of k1 will be used to find the bucket
now in bucket there are 2 values stored, which one to get
now .equals() method is used to get the correct value by checking each key with "varun"

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

What is starvation?

Starvation happens when a thread is ready to run but is continuously ignored because other higher-priority threads keep taking resources.
Thread scheduling policies.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW:
    Thread is created, but thread is not started yet
    Thread t1 = new Thread(() -> {
        // task
    });

RUNNABLE:
    Thread start is called, Thread is ready to run
    It may or may not be running now
    JVM Scheduler needs to give it CPU time
    t1.start()

RUNNING:
    Sheduler gives the thread time and now its running

BLOCKED:
    Thread is blocked because another thread holds the lock
    Thread will move to runnable when lock is released

WAITING:
    Thread is waiting for another thread to completed
    thread.join()  → waiting for another thread to finish

TERMINTED:
    Thread has finished execution
    run() method has finished.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between wait(), notify(), and notifyAll().
Difference between ExecutorService and ThreadPool.
Difference between Callable and Runnable.
PartitioningBy()

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

map() vs peek():

map()
Takes each element and converts it into a new value
Returns a new stream of transformed elements
Intermediate operation

peek()
Allows you to observe elements as they flow through the stream
Does NOT change the elements
Intended mainly for logging / debugging

Example:
List<String> result = names.stream()
        .peek(n -> System.out.println("Before map: " + n))
        .map(String::toUpperCase)
        .peek(n -> System.out.println("After map: " + n))
        .collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What are classloaders in Java?

ClassLoader is a part of JVM that loads class into memory
Class is not loaded into memory when created 
Class gets loaded into the memory when:
    object is created / static method is called / static variable is accessed

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Saga Design Pattern:
    Saga Pattern is used in microservices to manage distributed transactions
    Maintains data consistency

1. Choreography-Based Saga:

No central coordinator.
Services communicate using events
Each service:
    Performs its local transaction
    Publishes an event
    Listens to other service events
On failure, compensating actions are triggered by listening to failure events

Example:
    Order Service → OrderCreatedEvent
    Payment Service → PaymentCompletedEvent
    Inventory Service → StockReservedEvent
    Payment fails → PaymentFailedEvent → Order Service cancels order (compensating transaction).

2. Orchestration-Based Saga:

Central orchestrator controls the flow.
Orchestrator:
    Calls services in order
    Decides next step
    Triggers compensations on failure
Services do not talk to each other directly

Example:
Orchestrator    → Order Service → create order
Orchestrator    → Payment Service → process payment
Orchestrator    → Inventory Service → reserve stock
Payment fails   → Orchestrator calls → Order Service → cancel order (compensation) 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle failure of services in a microservices ecosystem?

Circuit Breaker → stop cascading failures
Fallback → Returns fallback response instead of errors
Retries → only for transient errors
Health Checks → Detects faulty services
Monitoring & Tracing → visibility and debugging

What Are Transient Errors?
Transient errors are temporary failures that resolve on their own after a short time.
For transient errors Retries are used

Example:
Temporary network glitches
Short service overload
Database Deadlock

Not Transient Errors:
Invalid input
Authentication / authorization failures
Missing resource (404)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@SpringBootApplication Annotation:
    It consist of 3 annotations

1: @EnableAutoConfiguration:
Automatically configures beans based on:
    Dependencies in pom.xml
    Properties in application.properties / application.yml

Example:
If spring-boot-starter-web is present → configures DispatcherServlet, Tomcat, etc.

2: ComponentScan:
Scans the package and subpackage to create bean who has annotatins like @Component, @Service etc etc 

3: Configuration:
Marks the class as a source of bean definitions
Allows use of @Bean methods

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application Deployment Process (Production-Oriented):

1. Code Development & Version Control:
    Code is developed locally
    feature → develop → main

2. Push Code to Git Repository:
    Create PR (Pull Request) → Code review
    Merge after approval → Triggers CI pipeline

3. Build & Package Application:
    mvn clean install   → Generate JAR files'
    mvn test            → run unit tests

4. Create Docker Image:
    Write Dockerfile
    Build Docker image

5. Push Docker Image to Container Registry:
    Authenticate with AWS ECR
    Tag image
    Push image

6. Deployment to Environment:
    Kubernetes (EKS)
    kubectl apply -f deployment.yaml

7   . Post-Deployment Verification:
    Health checks
    Smoke tests
    Monitor logs and metrics
    Rollback if required

We follow a CI/CD-based deployment where code is built, tested, containerized, pushed to a registry, and deployed using automated pipelines with verification and rollback.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to Store Customer Sensitive Data:

1. Account Information (Bank / Card / PII):
Never Store in Plain Text
Use Encryption (NOT hashing)

Why encryption and not hashing?
    Account data may need to be read back
    Hashing is one-way
    Encryption is reversible
Use AES-256 (symmetric encryption) — industry standard
Plain Data → Encrypt → Store in DB
Read → Decrypt → Use

2. Passwords
Never Encrypt and DecryptPasswords
Why hashing?
    Passwords are used only for verification
    No need to read original value

3. Encryption Keys Management:
Never Store Keys in Code or Config Files
Use a Secure Key Management System, AWS KMS


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Why Do We Make a Constructor private:
A private constructor is used to restrict object creation from outside the class.

1. Singleton Pattern:
Ensures only one instance of a class exists
Constructor is private so no other class can create objects using new

2. Utility Classes:
Utility classes contain only static methods
Object creation is unnecessary

3. Factory Methods:
Object creation is controlled via static factory methods
Constructor is private to force usage of factory

public class User {

    private User() { }

    public static User createUser() {
        return new User();
    }
}


4. Prevent Inheritance:
If a class has only private constructors, it cannot be extended
Subclass cannot call super()

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constructor vs Setter Dependency Injection:

Constructor Injection:
    The object cannot be created without required dependencies.
    Once the object is created, dependencies are immutable
    Easy to pass mocks through the constructor.
    Works well with @RequiredArgsConstructor in Lombok.

Setter Injection:
    Dependencies are injected after object creation
    Dependencies are mutable
    Dependencies can be changed or reconfigured at runtime.
    Object may be used before dependencies are set → NullPointerException.
    Must remember to call setter before test; mocks not forced.

Autowired:
Used by Spring to inject dependencies
Uses reflection internally

Note:
When you have 1 constructor of the class dependencies will automatically gets injected using constructor Injection
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

Concurrent Hashmap and Internal working:
    ConcurrentHashMap is a thread-safe implementation of Map

Why HashMap is not thread-safe
    Multiple threads can modify the same bucket simultaneously
    Can cause data corruption, infinite loops, lost updates

Collections.synchronizedMap() fixes this by:
    Using one global lock
    Result: poor performance

Internal working:
    No global lock
    Lock only small portions
    Reads are mostly lock-free
    Writes use fine-grained locking

Thread-safe READ operation (get):

What happens internally
    Hash key → index
    Read bucket without lock
    Uses volatile fields to ensure visibility

Why safe?
    value is volatile
    Memory visibility guaranteed
    No modification → no locking required
    Reads are non-blocking and very fast

Thread-safe WRITE operation (put):

Internal steps:
    Compute hash
    Find bucket index
    Lock only that bucket
    Insert or update node
    Unlock bucket

synchronized (bucketHeadNode) {
   // modify only this bucket
}

Multiple threads can write when working with different buckets 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Serialization vs Deserialization in Java:

Serialization is the process of converting a Java object into a byte stream so it can be: saved to a file, sent over a network.
Deserialization is the reverse process: converting the byte stream back into a Java object.

Serializable is a marker interface
Marker Interface is a interface with no methods, It is used to tag the class so JVM Can apply special behavior to it.
public interface Serializable {

}
You implement Serializable on classes whose objects need to be transferred or stored.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between ArrayList and LinkedList - when would you choose each?

ArrayList:
    Dynamic array
    Elements stored contiguously in memory

LinkedList
    Doubly linked list
    Each element stores data + prev + next references

When to choose ArrayList:
    Frequent random access
    Mostly read operations
    Memory efficiency matters

    Returning list from REST API
    DTO collections
    Index-based loops


When to choose LinkedList:
    Frequent insertions/removals at beginning or middle
    No random access required

    Task queues
    Sliding window
    BFS traversal

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What are race conditions? Have you faced one in production:

A race condition occurs when:
    Multiple threads/processes access shared data
    At least one modifies it
    The final result depends on execution timing
    This leads to inconsistent or incorrect behavior.

Real production-style example (common):

Wallet balance update
    balance = balance - amount; 

Two concurrent transactions:
    Both read balance = 100
    Both deduct 60
    Final balance = 40 ❌ (should fail one)

1. Database-level locking (most common):
SELECT * FROM wallet WHERE user_id = ? FOR UPDATE;

2: Atomic operations:
AtomicInteger count = new AtomicInteger();
count.incrementAndGet();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is thread starvation and how do you prevent it?:
Thread starvation happens when a thread never (or very rarely) gets CPU time or resources because other threads keep getting priority or locks.

Common causes:

1. Unfair locks
2. Thread pool too small:
    Pool has 2 threads
    2 long-running tasks occupy them
    Short tasks never execute
3. Blocking operations inside threads:
    Database calls
    Network calls
    Thread.sleep()
    Threads stay busy → others starve.

How to prevent thread starvation:

1. Proper thread pool sizing
2. Use fair locks when needed
3. Avoid blocking calls
    DB / REST calls inside tight synchronized blocks
    Move blocking work outside

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Exception Swallow:

An exception is swallowed when it is:
    Caught only 
    Only logged
    Not thrown or handled meaningfully

Why exceptions should NOT be swallowed:

1. Bugs are hidden
Application continues in invalid state
Root cause of exception is lost

3. Breaks observability:

Monitoring/alerts rely on thrown exceptions

Swallowed errors never reach:
    Logs with stack traces
    Error metrics

Violoates @Transactional:
Error is not thrown, Transaction will not rollback

@Transactional
public void process() {
    try {
        repo.save();
    } catch (Exception e) {
        // swallowed
    }
}

What to do instead (correct patterns):

1. Handle and rethrow:
catch (SQLException e) {
    log.error("DB error", e);
    throw new DatabaseException("Failed to save", e);
}

2. Translate exception:
catch (IOException e) {
    throw new ExternalServiceException("Payment service down", e);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How does Spring manage transactions internally:
    Spring wraps your method with “start transaction → run code → commit or rollback“

Flow:

1. You write this:
@Transactional
public void createOrder() {
    saveOrder();
    savePayment();
}

2. Spring secretly creates a wrapper:
    Spring does not call your method directly.

Controller
   ↓
Spring proxy (not your class)
   ↓  → BEGIN TRANSACTION
createOrder()
   ↓
saveOrder()
savePayment()
   ↓
Spring proxy
   ↓  → COMMIT or ROLLBACK

What actually is a “transaction” here?
    Spring takes one DB connection
    Turns off auto-commit
    Uses the same connection for all DB calls
    At the end:
    commit() OR rollback()

Spring stores DB Connection in threads 
Thread 1 → DB Connection A
Thread 2 → DB Connection B

If Exception occures → rollback
If No Exception → commit
If Exception swallos → commit

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle concurrent updates to the same database row:

1: Database-level row lock:
    DB locks the row
    Other transactions trying to SELECT ... FOR UPDATE wait
    Other reads may be blocked depending on isolation level
    Transaction A updates balance and commits:
    COMMIT
    Transaction B now acquires the lock and updates

SELECT * FROM wallet WHERE id = 101 FOR UPDATE;

@Transactional
public void debitWallet(Long userId, double amount) {
    Wallet wallet = walletRepo.findByIdForUpdate(userId);
    wallet.setBalance(wallet.getBalance() - amount);
    walletRepo.save(wallet);
}

2: Versioning:
    Add a version column to your table:
    Transaction A reads wallet (version = 1)
    Transaction B reads wallet (version = 1)
    Transaction A updates balance → increments version to 2:
    Update succeeds because version = 1 matches
    Transaction B tries to update balance → fails:
    No rows updated → OptimisticLockException in JPA
    Transaction B can retry or abort

CREATE TABLE wallet (
    id BIGINT PRIMARY KEY,
    balance DOUBLE,
    version BIGINT
);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between PUT and PATCH with a real API example:

1. PUT:
Replace the entire resource with the new representation.
If fields are missing, they are considered null or defaulted (depending on implementation).

Current:
{
  "username": "john_doe",
  "email": "old_email@example.com",
  "age": 25,
  "address": "NYC"
}

Requested:
{
  "username": "john_doe",
  "email": "john@example.com",
  "age": 30
}

Result:
{
  "username": "john_doe",
  "email": "john@example.com",
  "age": 30,
  "address": null    // removed because PUT replaces full resource
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. PATCH:
Partially update a resource.
Only the fields provided in the request are updated.

Current:
{
  "username": "john_doe",
  "email": "old_email@example.com",
  "age": 25,
  "address": "NYC"
}

Requested:
{
  "email": "john@example.com"
}

Result:
{
  "username": "john_doe",
  "email": "john@example.com",
  "age": 25,
  "address": "NYC"   // unchanged
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------