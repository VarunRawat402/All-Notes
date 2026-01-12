-------------------------------------------------------------------------------------------------------------------------------
Multithreading Notes:
-------------------------------------------------------------------------------------------------------------------------------

Thread vs Runnable:

Thread:
Class + cannot extend another class + Each thread requires a new object
5 threads = 5 student object

Runnable:
Interface + Can extend another class + Multiple threads can share one object

-------------------------------------------------------------------------------------------------------------------------------

How to create a new Thread:

1: Using Thread Class:
    Extend Thread class, Override run()

Code:
public class Student extends Thread{

    @Override
    public void run(){
        for(int i=0;i<500;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
}
Student s1 = new Student();
s1.start();

-------------------------------------------------------------------------------------------------------------------------------

2: Using Runnable Interface:
    Implement Runnable Interface, Override run()
    Pass object to Thread

public class Student implements Runnable{

    @Override
    public void run() {
        for(int i=0;i<500;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
}
Student student = new Student();
Thread t1 = new Thread(student);
t1.start();

-------------------------------------------------------------------------------------------------------------------------------

Join():

Makes other threads wait untill join thread finish
Throws InterruptedException ( Must handle or declare it )

Example:
    Thread A → prepares data
    Thread B → uses that data (must wait for A)

Code:
    System.out.println("Before!!!!");
    
    Student student = new Student();
    student.start();
    student.join();                     //Main thread will wait to finish student thread

    System.out.println("After!!!!");

-------------------------------------------------------------------------------------------------------------------------------

Daemon Thread:

Background thread, runs in background
When all threads are finished JVM will exit and daemon threads are killed automatically
setDaemon(true) → to make a thread daemon thread

Code:
Thread t1 = new Thread(()->{
        Thread.sleep(1000);
    System.out.println("Hello world");              //Not executed
});
t1.setDaemon(true);
t1.start();

-------------------------------------------------------------------------------------------------------------------------------
Multiple Ways of Creating a Thread:
-------------------------------------------------------------------------------------------------------------------------------

1: Entity Class

Code:
    Admin admin = new Admin();
    Thread t1 = new Thread(admin);
    t1.start();

-------------------------------------------------------------------------------------------------------------------------------

2: Anonymous class:

Code:
Runnable task1 = new Runnable() {
    @Override
    public void run() {
        wallet.withDraw(50);
    }
};
Thread t2 = new Thread(task1);
t1.start();

-------------------------------------------------------------------------------------------------------------------------------

3: Create Thread Directly:

Thread t3 = new Thread(()->{
    wallet.withDraw(50);
});
t3.start();

-------------------------------------------------------------------------------------------------------------------------------

4: Anonymous Thread:

new Thread(()->{
    wallet.withDraw(50);
}).start();

-------------------------------------------------------------------------------------------------------------------------------
