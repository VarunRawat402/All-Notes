-------------------------------------------------------------------------------------------------------------------------------
Multithreading Notes:
-------------------------------------------------------------------------------------------------------------------------------

Java supports Multithreading:

1: java.lang.Thread Class
2: java.lang.Runnable Interface

When Java program starts, One thread begins running immediately, which is called Main Thread.
The Main Thread is responsible for running the main() method.

To get the current thread:
    Thread.currentThread().getName();

Thread Safe:
When Multiple threads access or modify shared data simultaneously without corrupting it or causing bugs.

Why is it needed?
    When multiple threads read/write the same variable or object, things can go wrong like:
    Inconsistent state
    Race conditions
    Crashes or weird outputs

-------------------------------------------------------------------------------------------------------------------------------

How to create a new Thread:

1: Using Thread Class:

Create a class extends it with Thread class
Override the Run method and write the task
Create the object of class and call the start method

Code:
public class Student extends Thread{

    @Override
    public void run(){
        for(int i=0;i<500;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
}

Main:
Student student1 = new Student();
student1.start();
Student student2 = new Student();
student2.start();

2: Using Runnable Interface:

Create a class implement it with Runnable Interface
Override the Run method and write the task
Create the object of class and use that object to create multiple threads

public class Student implements Runnable{

    @Override
    public void run() {
        for(int i=0;i<500;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
}

Main:
Student student = new Student();
Thread t1 = new Thread(student);
t1.start();
Thread t2 = new Thread(student);
t2.start();

-------------------------------------------------------------------------------------------------------------------------------

Thread vs Runnable:

Thread:
Class + cannot extend another class + Each thread requires a new object
5 threads = 5 student object

Runnable:
Interface + Can extend another class + Multiple threads can share one Runnable object

-------------------------------------------------------------------------------------------------------------------------------

Join():

Makes all the threads wait untill current thread is finished
Makes the code synchronized
Throws InterruptedException ( Must handle or declare it )

Example:
    Thread A → prepares data
    Thread B → uses that data (must wait for A)

Code:
public class DemoApplication {
    public static void main(String[] args) throws InterruptedException {

        //This will print first
        System.out.println("Main Thread!!!!!!!!!!!");
        
        Student student = new Student();
        student.start();
        student.join();         //Main thread will wait to finish student thread

        //After completion of Student thread this will get printed
        System.out.println("New Thread!!!!!!!!!!!!!");
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Daemon Thread:

A daemon thread is a background thread
When all threads are finished JVM will exit and daemon threads will be terminated automatically
setDaemon(true) → to make a thread daemon thread

//t1 thread will not print hello world because main thread will finish first and jvm will exit
Code:
Thread t1 = new Thread(()->{
        Thread.sleep(1000);
    System.out.println("Hello world");
});
t1.setDaemon(true);
t1.start();

-------------------------------------------------------------------------------------------------------------------------------
Multiple Ways of Creating a Thread:
-------------------------------------------------------------------------------------------------------------------------------

1: Class

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
