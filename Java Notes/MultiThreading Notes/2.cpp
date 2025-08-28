-------------------------------------------------------------------------------------------------------------------------------
Multithreading Notes:
-------------------------------------------------------------------------------------------------------------------------------

Java supports Multithreading:

1: java.lang.Thread Class
2: java.lang.Runnable Interface

When Java program starts, One thread begins running immediately, which is called Main Thread.
Main Thread is responsible for executing the main method of the program

To get the current thread:
    Thread.currentThread().getName();

Thread Safety:
When Multiple threads can access or modify shared data simultaneously without corrupting it or causing bugs.

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
Thread is a concrete class that you extend 
Since Java doesn't support multiple inheritance, extending Thread prevents your class from extending any other class
Need to create the new object to create the new thread

Code:
Student student = new Student();
student.start();
Student student1 = new Student();
student1.start()

Runnable:
Runnable is an interface that you implement
Your class can still extend another class while implementing Runnable
can use the same object for new threads

Code:
Employee employee = new Employee();
Thread t1 = new Thread(employee);
Thread t2 = new Thread(employee);

-------------------------------------------------------------------------------------------------------------------------------

Join():

It is a method that allows one thread to wait for the completion of another thread.
Throws InterruptedException Exception ( Must handle or declare it )
You can also specify a timeout in milliseconds or nanoseconds.
If you dont use join(), threads will run independently and may overlap in unpredictable ways.

Useful when threads are working in dependent order, like:
    Thread A prepares data
    Thread B uses the data → so B should wait for A to finish

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

A daemon thread is a background thread that helps other threads do their work.
The JVM will not wait for daemon threads to finish.
When all main/user threads are done, JVM will exit even if daemon threads are still running.
Cannot set Daemon after starting the thread.

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
Wallet Class:

//Create Threads to run withDraw()
public class Wallet {

    private int balance = 100;
    private final Lock lock = new ReentrantLock();

    public synchronized void withDraw(int amount){

        //lock.lock();
        System.out.println(Thread.currentThread().getName() + " Attempting to withdraw money ");

        if(amount<=balance) {

            try {
                System.out.println(Thread.currentThread().getName() + " Money is being processed");
                Thread.sleep(3000);
                balance-=amount;
                System.out.println(Thread.currentThread().getName()  + " Balance left is " + balance);
            }catch (Exception e){
            }finally {
                //lock.unlock();
            }
        }
        else{
            System.out.println(Thread.currentThread().getName() + " Insufficient Balance");
        }
    }
} 

-------------------------------------------------------------------------------------------------------------------------------

1: Creating a class:
    Create Admin class and implement Runnable Interface
    Run the wallet method in @Override run method
    Create the object of Admin
    Create a thread and initialize the thread using Admin object
    Start the thread

Code:
    Admin admin = new Admin();
    Thread t1 = new Thread(admin);
    t1.start();

-------------------------------------------------------------------------------------------------------------------------------

2: Anonymous class ( One Step Less ):
{No Class Initialization}
Create Anonymous class object using Lambda Function
Initialize @Override run method in the Anonymous object
Create a thread and initialize the thread using Anonymous class object
Start the thread

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
