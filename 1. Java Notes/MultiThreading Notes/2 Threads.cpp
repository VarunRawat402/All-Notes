-----------------------------------------------------------------------------------------------------------------------------------------------------
Multithreading Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread Class:
    → Class + No Multiple Inheritance + Each thread requires a new object
    → 5 threads = 5 student object

Runnable Interface:
    → Interface + Can extend another class + Multiple threads can share one object

-----------------------------------------------------------------------------------------------------------------------------------------------------
How to create a new Thread:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Using Thread Class:
    → Extend Thread class
    → Override run()

public class Student extends Thread{
    @Override
    public void run(){
        System.out.println("Hello world");
    }
}
Student s1 = new Student();
s1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Using Runnable Interface:
    → Implement Runnable Interface
    → Override run()

public class Student implements Runnable{
    @Override
    public void run(){
        System.out.println("Hello world");
    }
}
Student student = new Student();
Thread t1 = new Thread(student);
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

Join():
    → Makes other threads wait untill join thread finish
    → Throws InterruptedException ( Must handle or declare it )

Code:
Thread t1 = new Thread(()->{System.out.println("Hello world");});
t1.start();
t1.join();

-----------------------------------------------------------------------------------------------------------------------------------------------------

Daemon Thread:
    → Background thread, runs in background
    → If all normal threads finish, JVM will exit even if daemon threads are still running.
    → setDaemon(true) → to make a thread daemon thread

Code:
Thread t1 = new Thread(()->{System.out.println("Hello world");});
t1.setDaemon(true);

-----------------------------------------------------------------------------------------------------------------------------------------------------
Multiple Ways of Creating a Thread:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Custom Class:

Admin admin = new Admin();
Thread t1 = new Thread(admin);
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Anonymous class:

Runnable task1 = new Runnable() {
    @Override
    public void run() {
        wallet.withDraw(50);
    }
};
Thread t2 = new Thread(task1);
t1.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Create Thread Directly:

Thread t3 = new Thread(()->{
    wallet.withDraw(50);
});
t3.start();

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Anonymous Thread:

new Thread(()->{
    wallet.withDraw(50);
}).start();

-----------------------------------------------------------------------------------------------------------------------------------------------------
