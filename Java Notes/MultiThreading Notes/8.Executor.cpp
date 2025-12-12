-------------------------------------------------------------------------------------------------------------------------------
Executors Framework:
-------------------------------------------------------------------------------------------------------------------------------

The Executors Framework is used to manage and control thread execution in a flexible and scalable way.
It helps developers avoid manual thread creation and provides built-in thread pooling and task scheduling features.

Why Use Executor Framework?

Simplifies multithreading
Manages thread life cycle efficiently
Prevents resource exhaustion by reusing threads
Provides better performance with thread pools

-------------------------------------------------------------------------------------------------------------------------------

Core Interfaces:

Executors - the base interface with a single method:
ExecutorService - a more advanced interface with methods to manage lifecycle and submit tasks:
ScheduledExecutorService - for executing tasks with delay or periodically.

Instead of creating threads manually and managing it Java will do it for us:

Syntax:
    ExecutorService pool = Executors.newFixedThreadPool(3)                          //fixed-size thread pool.
    ExecutorService pool = Executors.newCachedThreadPool()                          //Threads will get created dynamically based on number of tasks
    ExecutorService pool = Executors.newSingleThreadExecutor()                      // single worker thread.
    ExecutorService pool = Executors.newScheduledThreadPool(int corePoolSize)       //fixed-size thread pool for schedule tasks

-------------------------------------------------------------------------------------------------------------------------------

shutdown():
It tells that all the tasks that are running before calling me should be finished and no more tasks is Allowed
after me

shutdownNow():
It forcefully shutdown the executor even if tasks are still running

isShutdown():
Returns True or False based on if shutdown() is called yet or not

awaitTermimation():
When all tasks are finished and shutdown is done then we reach terminated state
It is used to do some tasks after all the threads completed and shutdown is done

-------------------------------------------------------------------------------------------------------------------------------

pool.submit() :
    It is used to define the tasks that needs to be run by threads
    It Returns a future Object, You can return anything in submit

future.get():
    It is used to get the result of the submit
    It Stops the application untill thread finishes or get Exception etc
    Its like join() to wait for thread to finish

Ex:
ExecutorService pool = Executors.newSingleThreadExecutor();

//It will print as soon as main starts
System.out.println("Before Submit");
Future<?> submit = pool.submit(() -> {
    try {
        sleep(3000);
    } catch (InterruptedException e) {
        throw new RuntimeException(e);
    }
    System.out.println("This is Pool and Thread id is " + Thread.currentThread().getName());
});

//It will print after submit thread finishes the task
//If submit.get() wasnt here then this would have also printed as soon as main starts
submit.get();
System.out.println("After submit");
pool.shutdown();

-------------------------------------------------------------------------------------------------------------------------------

Ex:
Calculate time taken in a task:

ExecutorService pool = Executors.newFixedThreadPool(10);
long timeBeforeTask = System.currentTimeMillis();          //Time Before Task

//Task -> Printing a line 10 times 
for(int i=1;i<=10;i++){

    int id = i;
    pool.submit(()->{
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("This is Pool and Thread id is " + Thread.currentThread().getName());
    });
}

//It will make sure all the task are finished before it and no task is allowed after this
pool.shutdown();

//It will check if all tasks are finished before shutdown or 100s are passed if true then returns true
//If false returns false based on that we can do calculations
if(pool.awaitTermination(100,TimeUnit.SECONDS)){
    long timeTaken = System.currentTimeMillis()-timeBeforeTask;
    System.out.println(timeTaken);
}

O/p:
If used 10 Threads -> 1 sec 
If used 1 Thread -> 10 sec

-------------------------------------------------------------------------------------------------------------------------------

CALLABLE VS RUNNABLE:

Runnable is a functional interface used to represent a task that can run on a separate thread without returning a result.

Doesnt return anything.
Cant throw checked exceptions.
Mainly used for simple tasks like printing or background work.
When you just want a task to run, and you dont need a result back.

Callable<V> is a generic interface that represents a task which returns a result and can throw checked exceptions.

Returns a value of type V.
Can throw checked exceptions.
Must be submitted to an ExecutorService using submit() to get a Future<V>.
When you need to get a result from the task or handle checked exceptions.

-------------------------------------------------------------------------------------------------------------------------------

Callable Example:

We will calculate the factorial of a number in a thread and prints it;

Code:
ExecutorService pool = Executors.newFixedThreadPool(3);

//Calculate the factorial inside a thread and returns the answer
Future<Integer> submit = pool.submit(() -> {
    int first = 1;
    for (int i = 1; i <= 5; i++) {
        first = first * i;
    }
    return first;
});

//Main thread will wait due to submit.get()
int factorial = submit.get();
System.out.println(factorial);

-------------------------------------------------------------------------------------------------------------------------------

InvokeALL():
Takes a collection of Callable<T> tasks
Run all the callable task together instead of 1 by 1 like we do
Waits until all tasks complete
Returns a List of Future<T> objects — one for each task

Code:

ExecutorService pool = Executors.newFixedThreadPool(3);

//Created 3 Seperate tasks
Callable<String> c1 = ()->{
    System.out.println("This is Task 1 completed by " + Thread.currentThread().getName());
    return "Task 1 is completed";
};
Callable<String> c2 = ()->{
    System.out.println("This is Task 2 completed by " + Thread.currentThread().getName());
    return "Task 2 is completed";
};
Callable<String> c3 = ()->{
    System.out.println("This is Task 3 completed by " + Thread.currentThread().getName());
    return "Task 3 is completed";
};

//Add them in a list because invokeAll take collection
List<Callable<String>> tasks = Arrays.asList(c1,c2,c3);

//Invoked all the tasks and main thread will untill all tasks are finished
pool.invokeAll(tasks);

//Run all the tasks that can be run in 2 seconds after that stop all tasks
pool.invokeAll(tasks,2,TimeUnit.SECONDS);

-------------------------------------------------------------------------------------------------------------------------------

ScheduledExecutorService:
Its ExecutorService, but with delayed and periodic task scheduling.
You can schedule a task at a given time or run a task at fixed rate or interval

-------------------------------------------------------------------------------------------------------------------------------

schedule(): 
    Runs a task once after a given delay

Code:
scheduler.schedule(() -> {
    System.out.println("Task runs after 3 seconds");
}, 3, TimeUnit.SECONDS);

-------------------------------------------------------------------------------------------------------------------------------

scheduleAtFixedRate():
    Run a task at a fixed interval
    First run after 1 sec and after that every run will be after 2 sec
    It does not matter if task is completed next task will run after 2 sec 
    and tasks can overlap

    InOrder to shutdown with FixedRate() we need to schedule the shutdown() too
    otherwise the shutdown will be instant

Code:
ScheduledExecutorService pool = Executors.newScheduledThreadPool(1);

pool.scheduleAtFixedRate(()->{
    System.out.println("This will run every second");
},1,1,TimeUnit.SECONDS);

pool.schedule(()->{
    pool.shutdown();
},8,TimeUnit.SECONDS);

-------------------------------------------------------------------------------------------------------------------------------

scheduleWithFixedDelay():
    Run a task at a fixed interval after previous task is finished
    First run after 1 sec and next run will be 2 seconds after previous task is finished
    If previous task took 10 sec then it will run after 10 + 2 sec

Code:
scheduler.scheduleWithFixedDelay(() -> {
    System.out.println("Fixed Delay: " + System.currentTimeMillis());
}, 1, 2, TimeUnit.SECONDS); // Initial delay 1s, then wait 2s *after each run*

-------------------------------------------------------------------------------------------------------------------------------

CountDownLatch():
It stops current thread and make it wait until all the tasks are finished in other threads
Used when you need all the threads to get finished first before moving on
Cannot reuse the same object again, Need to create another object to use it again

If there are 15 functions you cannot write 15 get() 

Code:

//Created Thread pool and CountDownLatch Object and pass number of tasks inside it
ExecutorService pool = Executors.newCachedThreadPool();
CountDownLatch latch = new CountDownLatch(2);

//A and B class have one method
A a = new A();
B b = new B();

System.out.println("All tasks are starting");

//latch.countDown() will decrease 1 from latch
//So, After 2 tasks latch will be 0 and main thread will run
pool.submit(()->{
    try {
        a.getName();
    } catch (InterruptedException e) {
        throw new RuntimeException(e);
    }finally {
        latch.countDown();
    }
});
pool.submit(()->{
    try {
        b.getName();
    } catch (InterruptedException e) {
        throw new RuntimeException(e);
    }finally {
        latch.countDown();
    }
});

latch.await();                //Tells main thread to stop and let latch be 0
pool.shutdown();
System.out.println("All tasks are finished");

-------------------------------------------------------------------------------------------------------------------------------

CyclicBarrier():
A CyclicBarrier is a synchronization tool where multiple threads wait for each other to reach a common point (called the barrier),
and once all of them arrive, they all proceed together.

Syntax:

//Normal
CyclicBarrier barrier = new CyclicBarrier(int tasks);

//This will get printed when all threads reached the barrier
CyclicBarrier barrier = new CyclicBarrier(3, () -> {
    System.out.println("All workers reached the barrier.");
});

Code:

ExecutorService pool = Executors.newCachedThreadPool();
CyclicBarrier barrier = new CyclicBarrier(3);

A a = new A();
B b = new B();

//Task 1 after finished wait at barrier.await()
System.out.println("All tasks are starting");
pool.submit(()->{
    try {
        a.getName();
        barrier.await();
    } catch (Exception e) {
        throw new RuntimeException(e);
    }
});
//Task 2 after finished wait at barrier.await()
pool.submit(()->{
    try {
        b.getName();
        barrier.await();
    } catch (Exception e) {
        throw new RuntimeException(e);
    }
});

//Main thread is also waiting at barrier await
//When all threads will reach barrier await then the flow will get forward
barrier.await();
System.out.println("All tasks are finished");
pool.shutdown();

-------------------------------------------------------------------------------------------------------------------------------

CyclicBarrier vs CountDownLatch:

CyclicBarrier can be re-used
CountDownLatch cannot be re-used

In CyclicBarrier all threads wait at barrier
In CountDownLatch Only main thread will wait to  get tasks finished

CyclicBarrier is used why you have to sync multiple threads 
CountDownLatch is used when you have to wait for other threads to be finished

-------------------------------------------------------------------------------------------------------------------------------