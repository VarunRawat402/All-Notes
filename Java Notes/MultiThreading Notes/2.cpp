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

join() makes one thread wait until another thread finishes.
Throws InterruptedException ( Must handle or declare it )
Optional timeout can be provided
If you dont use join(), threads will run independently and may overlap in unpredictable ways.

When thread execution order matters:
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

A daemon thread is a background thread that supports other threads.
JVM does not wait for daemon threads to finish
When all main/user threads are done, JVM will exit even if daemon threads are still running.
You must call setDaemon(true) before starting the thread, Cannot set Daemon after starting the thread.

//Student Thread and Main thread will get printed
//After sleep will not get printed coz it is a daemon thread and it stops as soon as main thread is finished
Code:

public class Student extends Thread{

    @Override
    public void run(){

        System.out.println("Student Thread");

        try {
            Thread.sleep(100000000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println("After Sleep");
    }
}

Main():

Student student = new Student();
student.setDaemon(true);
student.start();
System.out.println("Main");

-------------------------------------------------------------------------------------------------------------------------------

Multiple Ways of Creating a Thread:

-------------------------------------------------------------------------------------------------------------------------------

1: Creating a class:

Code:
    Admin admin = new Admin();
    Thread t1 = new Thread(admin);
    t1.start();

-------------------------------------------------------------------------------------------------------------------------------

2: Anonymous class ( One Step Less ):
{No Class Initialization}

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

3: Create Thread Directly ( 2 Step Less ):
{ No Class and Anonymous class object }
Initialize thread directly and write method directly inside thread using Lambda Function
Start the thread

Thread t3 = new Thread(()->{
    wallet.withDraw(50);
});
t3.start();

-------------------------------------------------------------------------------------------------------------------------------

4: Anonymous Thread ( 0 Initialization ):
No class, No Runnable Object, No Thread Initialization
Create Anonymous Thread, Write Method directly inside thread and start the thread

new Thread(()->{
    wallet.withDraw(50);
}).start();

-------------------------------------------------------------------------------------------------------------------------------
