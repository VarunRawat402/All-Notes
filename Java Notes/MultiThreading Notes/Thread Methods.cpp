-------------------------------------------------------------------------------------------------------------------------------
Thread Methods:
-------------------------------------------------------------------------------------------------------------------------------

start():    
    Creates a new thread and calls run() method
    start does not mean run now, it means it gives the thread to scheduler in a queue and 
    scheduler decides which thread to run first
    So If Thread 1 and Thread 2 are getting start one after another does not mean thread 1 will run first

-------------------------------------------------------------------------------------------------------------------------------

run() : Normally calls the run method like a normal call

sleep() : Pauses the thread for given time ( milliseconds )

join() : Tells the current thread to wait until another thread finishes

join(1000) : Waits for another thread to finish or until this specific Time

isAlive() : Returns true if thread is still running

setName() & getName() : To Set and Get the threads name

getId() : To get the Thread unique Id

getPriority() / setPriority() : Gets or sets thread priority (1 to 10).

yield() : Tells the current thread to pause and let others run (suggestion to the scheduler).

isInterrupted()	: Checks if a thread has been interrupted.

currentThread()	: Static method — returns a reference to the currently running thread.

-------------------------------------------------------------------------------------------------------------------------------

Code:

p
ublic class DemoApplication {
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


