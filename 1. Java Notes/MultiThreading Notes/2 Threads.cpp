-----------------------------------------------------------------------------------------------------------------------------------------------------
Multithreading Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread Class:
    → Extend Thread + no multiple inheritance
    → Each thread needs its own object → 5 threads = 5 objects
    → Needs to Override run() method 

Runnable Interface:
    → Implement Runnable + multiple inheritance allowed
    → 1 object = multiple threads
    → Needs to Override run() method 

Why Thread class exists:
    → Thread class creates + manages threads (start(), join() etc)
    → Runnable just defines the TASK, not the thread
    → Runnable execution → Thread created → Thread.run() → calls Runnable.run()

-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Thread Class:

public class Student extends Thread {
    public void run() { System.out.println("Hello"); }
}
Student s1 = new Student();
s1.start();


2. Runnable Interface:

public class Student implements Runnable {
    public void run() { System.out.println("Hello"); }
}
Thread t1 = new Thread(new Student());
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

Join():
    → Makes other threads wait untill join thread finishes
    → Throws InterruptedException → must handle
    → t1.start();
    → t1.join(); // main thread waits for t1 to finish

-----------------------------------------------------------------------------------------------------------------------------------------------------

Daemon Thread:
    → Background thread (ex: GC, logs)
    → If all normal threads finish, JVM will exit even if daemon threads are still running.
    → Must set BEFORE start()
    → setDaemon(true) → to make a thread daemon thread

Code:
    t1.setDaemon(true);
    t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------
Multiple Ways of Creating a Thread:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Custom Class (implements Runnable):

Admin admin = new Admin();
Thread t1 = new Thread(admin);
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Anonymous class:

Runnable task1 = new Runnable() {
    @Override
    public void run() {
        System.out.println("Hello world");
    }
};
Thread t1 = new Thread(task1);
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Create Thread Directly:

Thread t3 = new Thread(()->{
    System.out.println("Hello world");
});
t3.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Anonymous Thread:

new Thread(()->{
    System.out.println("Hello world");
}).start();

-----------------------------------------------------------------------------------------------------------------------------------------------------
