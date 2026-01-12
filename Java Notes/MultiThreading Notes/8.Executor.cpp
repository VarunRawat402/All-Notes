-------------------------------------------------------------------------------------------------------------------------------
Thread Pool:
-------------------------------------------------------------------------------------------------------------------------------

A thread pool is a group of pre-created, reusable threads
Tasks are submitted to threadPool
Available threads pick and execute them
Threads are reused, not destroyed after each task

-------------------------------------------------------------------------------------------------------------------------------

Thread Communication:

Threads coordinate with each other
One thread tells another:
    When to wait
    When to continue

Java Methods Used:

wait() → thread waits
notify() → wakes one waiting thread
notifyAll() → wakes all waiting threads
⚠ These methods must be called inside a synchronized block

-------------------------------------------------------------------------------------------------------------------------------

Where Is Thread Communication Used:

When threads depend on each other
When tasks must run in a specific order

Producer-Consumer Example
    Producer → produces data
    Consumer → consumes data

They communicate:
    Producer: “Data ready”
    Consumer: “Data consumed”

This avoids:
    Busy waiting
    CPU wastage

-------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
Executor Framework:
-------------------------------------------------------------------------------------------------------------------------------

Executor: 
    Base interface
    Has execute(Runnable)

ExecutorService: 
    Main interface used in real apps
    Submit tasks, manage lifecycle
    Methods: submit(), shutdown(), awaitTermination()

ScheduledExecutorService: 
    Run tasks with delay or periodically.

Executors: 
    Utility class
    Used to create thread pools

-------------------------------------------------------------------------------------------------------------------------------

Common Thread Pools:

ExecutorService threadPool = Executors.newFixedThreadPool(3);                                //fixed-size thread pool.
ExecutorService threadPool = Executors.newCachedThreadPool();                               //Threads will get created dynamically based on number of tasks
ExecutorService threadPool = Executors.newSingleThreadExecutor();                           //Single worker thread.
ScheduledExecutorService threadPool = Executors.newScheduledThreadPool(2);               //fixed-size thread pool for schedule tasks

-------------------------------------------------------------------------------------------------------------------------------

shutdown():
    after shutdown(), No new tasks accepted
    Existing tasks should complete normally

shutdownNow():
    Tries to stop running tasks, Tasks may not finish
    Interrupts threads

isShutdown():
    true if shutdown started, false if not

awaitTermimation():
    When all tasks are finished and shutdown is done then we reach terminated state
    It is used to do some tasks after all the threads completed and shutdown is done

-------------------------------------------------------------------------------------------------------------------------------

submit() :
    Used to submit task to thread pool
    return Future object

future.get():
    It is used to get the result from the future object
    Blocks current thread, Waits till task finishes
    Gets result or exception

-------------------------------------------------------------------------------------------------------------------------------

RUNNABLE:
    Functional interface
    No return value
    Cannot throw checked exception
    Used for simple tasks
    Runnable r = () -> System.out.println("Running");

CALLABLE:
    Functional interface & Generic interface
    Returns value
    Can throw checked exception
    Used when result is needed
    Callable<Integer> c = () -> 5 * 5;

-------------------------------------------------------------------------------------------------------------------------------

Callable Example:
We will calculate the factorial of a number in a thread and prints it;

Code:

ExecutorService threadPool = Executors.newFixedThreadPool(1);
Future<Integer> ans = threadPool.submit(() -> {
    int fact = 1;
    for (int i = 1; i < 5; i++) {
        fact = fact * i;
    }
    Thread.sleep(2000);
    return fact;
});

int factorial = submit.get();           //This is blocking operation
System.out.println(factorial);

-------------------------------------------------------------------------------------------------------------------------------

InvokeALL():
    Run all the callable task together instead of 1 by 1
    Takes list of Callable tasks, returns list of Future objects results
    It is a blocking operation

Code:

ExecutorService threadPool = Executors.newFixedThreadPool(3);

//3 Callable tasks
Callable<String> c1 = ()->{
    return "Task 1 completed";
};

Callable<String> c2 = ()->{
    return "Task 2 completed";
};

Callable<String> c3 = ()->{
    return "Task 3 completed";
};

List<Callable<String>> tasks = Arrays.asList(c1,c2,c3);
pool.invokeAll(tasks);                                                  //This is a blocking operation

pool.invokeAll(tasks,2,TimeUnit.SECONDS);                               //Run all the tasks that can be run in 2 seconds after that stop all tasks

-------------------------------------------------------------------------------------------------------------------------------

ScheduledExecutorService:
    Used for delayed or repeated execution.
    You can schedule a task at a given time or run a task at fixed rate or interval

-------------------------------------------------------------------------------------------------------------------------------

schedule(): 
    Run a task once after delay

Code:
threadPool.schedule(() -> {
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
ScheduledExecutorService threadPool = Executors.newScheduledThreadPool(1);

threadPool.scheduleAtFixedRate(()->{
    System.out.println("This will run every second");
},1,2,TimeUnit.SECONDS);

threadPool.schedule(()->{
    pool.shutdown();
},8,TimeUnit.SECONDS);

-------------------------------------------------------------------------------------------------------------------------------

scheduleWithFixedDelay():
    Run a task at a fixed interval after previous task is finished
    First run after 1 sec and next run will be 2 seconds after previous task is finished
    If previous task took 10 sec then it will run after 10 + 2 sec

Code:
threadPool.scheduleWithFixedDelay(() -> {
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