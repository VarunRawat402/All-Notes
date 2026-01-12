-------------------------------------------------------------------------------------------------------------------------------
Thread Methods:
-------------------------------------------------------------------------------------------------------------------------------

run()           : Normally calls the run method, does not create thread

start()         : Creates a new thread, Internally calls run()

sleep()         : Pauses the thread for given time ( milliseconds )

join()          : Tells the current thread to wait until another thread finishes

isAlive()       : Returns true if thread is still running

getId()         : To get the Thread unique Id

yield()         : Tells the current thread to pause and let others run (suggestion to the scheduler).

isInterrupted()	: Checks if a thread has been interrupted.

currentThread()	: Static method — returns a reference to the currently running thread.

setName() & getName()           : To Set and Get the threads name

getPriority() / setPriority()   : Gets or sets thread priority (1 to 10).

-------------------------------------------------------------------------------------------------------------------------------

Code:

public class DemoApplication {
    public static void main(String[] args) throws InterruptedException {

        Student student = new Student();            //Create Object of Student class

        student.start();                            //Creates a new thread and calls run() method
        student.run();                              //Normally call run() method

        student.join();                             //Main thread will wait until student thread finishes
        student.join(20000);                        //Main thread will wait until student finishes or 2000ms whichever is low

        Boolean check = student.isAlive();          //Check if thread is running or finished
        System.out.println(check);

        student.setName("Student Thread");          //Sets the thread name
        String threadName = student.getName();      //Gets the thread name

        long threadId = student.getId();            //Gets the Student Thread Id

        student.setPriority(8);                     //Set Priority of Thread
        int priority = student.getPriority();       //Get Priority of Thread

        //Functions to perform on Current Thread 
        
        String currentName = Thread.currentThread().getName();                  //Current Thread name
        String state = String.valueOf(Thread.currentThread().getState());       //Current Thread state
        Class<? extends Thread> Class = Thread.currentThread().getClass();      //Current Thread class
    }   
}

-------------------------------------------------------------------------------------------------------------------------------


