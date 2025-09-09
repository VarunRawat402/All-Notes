-------------------------------------------------------------------------------------------------------------------------------
BASICS:
-------------------------------------------------------------------------------------------------------------------------------

What is the difference between JDK, JRE, and JVM?

JVM : Engine that run the byte code or java applications
JRE : It contains JVM + libraries, which application needs to exeucute
JDK : JRE + tools, tools to develop the java applications like compiler, debugger etc

-------------------------------------------------------------------------------------------------------------------------------

What are the main features of Java?
    
Platform Independent (Write Once, Run Anywhere)
Object-Oriented (Based on objects and classes)
Simple (Easy to learn and use)
Robust (Strong memory management, exception handling)
High Performance (Uses Just-In-Time compiler)
Multi-threaded (Supports concurrent operations)

-------------------------------------------------------------------------------------------------------------------------------

What is encapsulation and how do you achieve it in Java?

Binding of data and methods into a class is known as encapsulation:
Ex: 
class Student{
    private int id;
    private String name;
}

-------------------------------------------------------------------------------------------------------------------------------

What is abstraction? Difference between abstraction and encapsulation.

abstraction:
    Hides Implementation details
    Tells what object does

encapsulation:
    Hides data and protect data
    Implementation of object how it does things

-------------------------------------------------------------------------------------------------------------------------------

How does try-with-resources work?:
It is used to automatically close the resource without using finally block
The resource declared in the try must implement AutoCloseable interface
JVM automatically calls close() method when try block exits

Before that we needed to use finally to close the resources

-------------------------------------------------------------------------------------------------------------------------------

Difference between Error and Exception.:

Both are Subclassses of Throwable

Error:
    Unchecked only, Runtime
    Not Recoverable, application should terminate
    outOfMemoryError

Exception:
    Both checked and Unchecked
    Can handle and application can continue
    Should be caught or handled
    NullPointerException

-------------------------------------------------------------------------------------------------------------------------------

Difference between synchronized and Lock.

Synchronized

Keyword in Java.
Used to achieve implicit locking.
When a thread enters a synchronized block/method, it acquires the lock automatically, and releases it when the block/method ends.
Works at method level or block level.

Lock 
Interface introduced in Java 5 (ReentrantLock, ReadWriteLock, etc.).
Provides explicit locking — the programmer must manually acquire and release the lock.
More flexible than synchronized.

-------------------------------------------------------------------------------------------------------------------------------

What is starvation?

Starvation happens when a thread is ready to run but is continuously ignored because other higher-priority threads keep taking resources.
Thread scheduling policies.

-------------------------------------------------------------------------------------------------------------------------------

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

-------------------------------------------------------------------------------------------------------------------------------

Difference between wait(), notify(), and notifyAll().

Difference between ExecutorService and ThreadPool.

Difference between Callable and Runnable.

Difference between ReentrantLock and synchronized.

-------------------------------------------------------------------------------------------------------------------------------

Difference between Optional and Nullable.

Nullable
A variable can have the value null, meaning it doesnt reference any object
String name = null; 

Optional
Designed to avoid null checks and make the absence of a value more explicit.
Its basically a container that may or may not hold a non-null value.

Optional<String> name = Optional.ofNullable(null);
System.out.println(name.isPresent()); // false
System.out.println(name.orElse("Name not provided")); // "Name not provided"

-------------------------------------------------------------------------------------------------------------------------------

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


List<String> names = Arrays.asList("Alice", "Bob", "Charlie");

List<String> result = names.stream()
        .peek(n -> System.out.println("Before map: " + n))
        .map(String::toUpperCase)
        .peek(n -> System.out.println("After map: " + n))
        .collect(Collectors.toList());

System.out.println(result); // [ALICE, BOB, CHARLIE]

-------------------------------------------------------------------------------------------------------------------------------

What is a Method Reference?

A Method Reference in Java is a shorthand syntax for calling an existing method by name when using lambda expressions.
It was introduced in Java 8 as part of functional programming with Streams and Lambdas.
Instead of writing a lambda like (x) -> doSomething(x), you can directly write ClassName::methodName.

names.forEach(s -> System.out.println(s));
names.forEach(System.out::println);

-------------------------------------------------------------------------------------------------------------------------------


What are classloaders in Java?

It is a part of JVM that loads class into memory
Class is not loaded into memory when created 
It gets loaded into the memory when an object is created, or static method is called

-------------------------------------------------------------------------------------------------------------------------------