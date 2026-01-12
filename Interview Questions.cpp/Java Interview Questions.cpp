----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is exception propagation?
    When an exception is not caught in the method where it occurs, 
    it propagates up the call stack to the calling method.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STACK:
    Method calls + Local variables +  Reference of objects + Primitive values

HEAP:
    objects + arrays + Instance variable

Metaspace:
    Class info ( class name, class structure ) + static variables

Example:
int a = 10;                         //a and 10 both in stack
String s = "Varun"                  //s in stack, Varun in heap
Student s = new Student()           //s in stack, Object in heap

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Contract Between equals() and hashCode():

hashCode()   → decides bucket location
equals()     → checks values

If a.equals(b) is true
    Then, a.hashCode() == b.hashCode() 

If a.hashCode() == b.hashCode()
    Then, a.equals(b) may be true or false

Explanation:
You have 2 objects you want to store in the hashmap

Put:
Different hashcode()    → both will be added in different buckets
Same hashcode()         → both will be added in same bucket

Example:

k1 = "varun" & k2 = "arun"
Assume same hashCode → stored in same bucket
hashcode() of k1 is used to find the bucket
Now in bucket there are 2 values stored, which one to get
now .equals() method is used to get the correct value by checking each key with "varun"

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Garbage Collection:

Garbage Collection is a JVM process that automatically frees heap memory by removing objects that are no longer reachable.
    Prevent memory leaks
    Efficient memory management

How GC Works (High-level)
    JVM identifies unreachable objects
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
try (Resource res = new Resource()) {
    res.use();                              // Auto-closes after this block
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW:
    Thread object created, start() not called
    Thread t1 = new Thread(() ->);

RUNNABLE:
    start() called
    Waiting for CPU

RUNNING:
    Scheduler assigns CPU, and thread is running

BLOCKED:
    Thread is blocked because another thread holds the lock

WAITING:
    Thread is waiting for another thread to get completed
    thread.join()  → waiting for another thread to finish

TERMINTED:
    Thread has finished execution
    run() execution completed

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

map() vs peek():

map()
Takes each element and converts it into a new value

peek()
Observes data, Does not change elements
Used for debugging/logging

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

Why Do We Make a Constructor private:
A private constructor is used to restrict object creation from outside the class.

1. Singleton Pattern:
    Ensures only one instance of a class exists

2. Utility Classes:
    Utility classes contain only static methods


3. Factory Methods:
    Constructor is private to force usage of static method for creation

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

Concurrent Hashmap and Internal working:
    ConcurrentHashMap is a thread-safe implementation of Map

Collections.synchronizedMap()   :
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

Serialization   : converting a Java object into a byte stream so it can be: saved to a file, sent over a network.
Deserialization : converting the byte stream back into a Java object.

Serializable is a marker interface
Marker Interface is a interface with no methods, It is used to tag the class so JVM Can apply special behavior to it.
public interface Serializable {

}
You implement Serializable on classes whose objects need to be transferred or stored.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference between ArrayList and LinkedList - when would you choose each?

ArrayList:
    Dynamic array
    Fast random access
    Less memory overhead
    Best for read-heavy operations

LinkedList
    Doubly linked list
    Fast insert/delete (middle/start)
    No random access
    More memory usage

When to choose ArrayList:
    Returning list from REST API
    DTO collections
    Index-based loops


When to choose LinkedList:
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

What is Thread starvation?
Starvation happens when a thread is ready to run but is continuously ignored because other higher-priority threads keep taking resources.

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

4: Violoates @Transactional:
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

Transactions:
@Transactional is used to make database operations execute as one atomic unit — either all succeed (commit) or all fail (rollback).

How @Transactional works internally:

Spring creates a proxy for the class
Method is called through proxy
Proxy:
    Opens DB connection
    Disables auto-commit
    Starts transaction
    Executes method
    If success → COMMIT
    If exception → ROLLBACK

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Self Invocation does not work:

public class PaymentService {
    
    public void pay() {
        process(); // ❌ transactional ignored
    }

    @Transactional
    public void process() { }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Transaction rollback rules:
    Transaction roll backs if RuntimeException or any exception occures
    Transaction does not roll back if exception is catched

Use Rollback for checked Exception:

@Transactional(rollbackFor = Exception.class)
public void process() throws Exception {
    throw new Exception();
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Propagation:
    Propagation defines how transactions behave when one method calls another.

1: REQUIRED (default):
If no transaction, creates one
If already present, join that

2: REQUIRES_NEW:
Stops existing transaction, creates new

3: SUPPORTS:
Runs if transaction exists
If not runs without transaction

4. MANDATORY
Fails if no transaction exists

5. NOT_SUPPORTED
Suspends transaction, runs non-transactional

7. NEVER
Throws exception if transaction exists

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Isolation Levels:
    READ_UNCOMMITTED	
    READ_COMMITTED	
    REPEATABLE_READ	
    SERIALIZABLE

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example:
@Transactional(
  propagation = Propagation.REQUIRED,
  isolation = Isolation.READ_COMMITTED,
  rollbackFor = Exception.class
)
public void transfer(Long from, Long to, BigDecimal amount) {

    debit(from, amount);   // step 1
    credit(to, amount);    // step 2
}

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