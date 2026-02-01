----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is exception propagation?
    → When an exception is not caught in the method where it occurs, 
    → it propagates up the call stack to the calling method.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STACK:
    → Primitive values
    → Local variables
    → References of objects
    → Method() calls

HEAP:
    → Objects
    → Arrays
    → Instance variables

Metaspace:
    → Class info (class name, class structure)
    → Static variables

Example:

int a = 10;         
    → a and 10 stored in stack

String s = "Varun"; 
    → s in stack, "Varun" in heap

static int b = 20; 
    → b and 20 stored in metaspace

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Concurrent Hashmap():
    → Thread-safe implementation of Map
    → Alternative to Collections.synchronizedMap()

Collections.synchronizedMap():
    → One global lock → poor concurrency

ConcurrentHashMap:
→ No global lock ✅
→ Reads (get) 🔹 lock-free, very fast
    → hash → bucket → read volatile value
→ Writes (put) 🔹 fine-grained locking
    → hash → bucket → lock bucket → insert/update → unlock
    → Multiple threads can work on different buckets concurrently

Notes:
→ volatile → guarantees memory visibility
→ Reads dont need locks → very fast
→ Writes lock only the affected bucket → high throughput

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Finalize vs Try with resource:
    → Used to close the resources like file, database connection etc

Finalize:
    → Method() in Object class
    → When object has no reference, GC call finalize() automatically
    → GC can call it after some time, or may never call it you dont know and resource will never gets closed.

Try with resource:
    → Use close() method in AutoCloseable interface
    → close() is automatically called after try block executes
    → Works even if exception occurs

Example:
try (Resource res = new Resource()) {
    res.use();                              // Auto-closes after this block
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What are classloaders in Java?

→ ClassLoader is a part of JVM that loads class into memory
→ Class is not loaded into memory when created 
→ Class gets loaded into the memory when:
    object is created / static method is called / static variable is accessed

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Why Do We Make a Constructor private:
    → A private constructor is used to restrict object creation from outside the class.

1. Singleton Pattern
   └─ Only one instance of the class exists

2. Utility Classes
   └─ Class has only static methods, no object needed

3. Factory Methods
   └─ Force usage of static method for object creation

4. Prevent Inheritance
   └─ Subclasses cannot call super(), class cannot be extended

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Serialization vs Deserialization in Java:

Serialization   : Java object → byte stream 
Deserialization : byte stream → Java object

→ Serializable is a marker interface (no methods).
→ It is used to tag the class so JVM Can apply special behavior to it.
→ Implement Serializable for objects that need to be transferred or stored.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ArrayList vs LinkedList:

ArrayList
    → Dynamic array
    → Fast random access (index-based) ✅
    → Less memory overhead
    → Best for read-heavy operations

LinkedList
    → Doubly linked list
    → Fast insert/delete at start/middle ✅
    → No random access
    → More memory usage

When to use:

ArrayList
    → Returning list from REST API
    → DTO collections
    → Index-based loops

LinkedList
    → Task queues
    → Sliding window
    → BFS traversal

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Race Conditions:
    Occurs when multiple threads try to modify the same data concurrently → data corruption

Example: Wallet Balance Update
→ 2 threads read balance = 100
→ Thread A deducts 60 → new balance 40
→ Thread B deducts 70 → new balance 30
→ Final value depends on which thread writes last

1. Pessimistic Locking:
    → SELECT * FROM wallet WHERE user_id = ? FOR UPDATE;

2: Atomic operations:
    → AtomicInteger count = new AtomicInteger();
    → count.incrementAndGet();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What is Thread starvation?
    → When a thread is continuously ignored and other threads keep executing over it

Common causes:

1. Unfair locks

2. Thread pool too small:
    → Pool = 2 threads
    → 2 long-running tasks occupy them
    → Short tasks never execute

3. Blocking operations inside threads:
    → Database calls, Network calls, Thread.sleep()
    → Threads stay busy → others starve

How to prevent thread starvation:
1. Good thread pool sizing
2. Use fair locks when needed
3. Avoid blocking calls

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Exception Swallow:
    → when exception is caught but not rethrown or logged properly

Why exceptions should NOT be swallowed:

1. Bugs are hidden
    → Application continues in invalid state
    → Root cause of exception is lost

3. Breaks observability:
    → Monitoring/alerts rely on thrown exceptions
    → Swallowed errors never reach:
        → Logs with stack traces
        → Error metrics

4: Violoates @Transactional:
    → Error is not thrown, Transaction will not rollback


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
    → It is used to make database operations execute as one atomic unit
    → either all commit or all rollback.

How @Transactional works internally:

→ Spring creates a proxy for the class
→ Method is called through proxy
Proxy:
    → Opens DB connection
    → Disables auto-commit
    → Starts transaction
    → Executes method
    → If success → COMMIT
    → If exception → ROLLBACK

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
    → Transaction roll backs automatically for RuntimeException
    → Transaction does not roll back if exception is catched
    → Rollbackfor is used to roll back the transaction for specific checked exceptions

@Transactional(rollbackFor = Exception.class)
public void process() throws Exception {
    throw new Exception();
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Propagation:
    → Propagation defines how transactions behave when one method calls another.

1: REQUIRED (default):
    → If no transaction, creates one
    → If already present, join that

2: REQUIRES_NEW:
    →Stops existing transaction, creates new

3: SUPPORTS:
    → Runs if transaction exists
    → If not runs without transaction

4. MANDATORY
    → Fails if no transaction exists

5. NOT_SUPPORTED
    → Suspends transaction, runs non-transactional

7. NEVER
    → Throws exception if transaction exists

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
    → Updates the entire entity with the provided data
    → If feilds are missing, they are considered null or defaulted

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. PATCH:
    → Updates only the speicified feilds which are provided
    → If feilds are missing, they are left unchanged

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------