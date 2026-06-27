-----------------------------------------------------------------------------------------------------------------------------------------------------
Executor Framework:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Executor                  → base interface + execute() method
ExecutorService           → Run tasks + submit(), shutdown(), awaitTermination() methods
ScheduledExecutorService  → Run tasks with delay or periodically
Executors                 → utility Class to create thread pools

-----------------------------------------------------------------------------------------------------------------------------------------------------

Common Thread Pools:

ExecutorService threadPool = Executors.newFixedThreadPool(3);                                 //fixed 3 threads, tasks queue if all busy
ExecutorService threadPool = Executors.newCachedThreadPool();                                 //creates threads dynamically as needed, reuses idle
ExecutorService threadPool = Executors.newSingleThreadExecutor();                             //single thread, tasks execute one by one
ScheduledExecutorService threadPool = Executors.newScheduledThreadPool(2);                    //fixed threads for scheduled/periodic tasks

-----------------------------------------------------------------------------------------------------------------------------------------------------

ExecutorService Methods:

1: shutdown():
    → Stop accepting new tasks
    → Already submitted tasks finish normally

2: shutdownNow():
    → Stop accepting new tasks
    → Interrupts all running tasks immediately
    → Returns list of tasks that never started

3: isShutdown():
    → true  → shutdown started 
    → false → still running

4: awaitTermimation():
    → Blocks until all tasks finish + shutdown completes
    → Use to do cleanup AFTER all threads are done

5: submit() :
    → Submits task to thread pool
    → Returns Future object

6: future.get():
    → Used to get the result from the future object
    → waits until task finishes → returns result
    → Throws exception if task failed
    → Future<Integer> future = pool.submit(() -> 10 + 20);
    → Integer result = future.get(); // blocks until done → 30

-----------------------------------------------------------------------------------------------------------------------------------------------------

RUNNABLE:
    → Functional interface
    → No return value 
    → Used when result is not needed
    → Cannot throw checked exception
    → Runnable r = () -> System.out.println("Running");

CALLABLE:
    → Functional & Generic interface
    → Returns value → Callable<Integer>
    → Used when result is needed
    → Can throw checked exception
    → Callable<Integer> c = () -> 5 * 5;

-----------------------------------------------------------------------------------------------------------------------------------------------------

Callable Example:
    → Factorial of number

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

int factorial = ans.get();           //This is blocking operation
System.out.println(factorial);

-----------------------------------------------------------------------------------------------------------------------------------------------------

InvokeALL():
    → Takes list of Callable tasks and executes them together
    → Returns list of Future results
    → It is a blocking operation

Code:

ExecutorService threadPool = Executors.newFixedThreadPool(3);
Callable<String> c1 = ()->{return "Task 1 completed";};
Callable<String> c2 = ()->{return "Task 2 completed";};
Callable<String> c3 = ()->{return "Task 3 completed";};

List<Callable<String>> tasks = Arrays.asList(c1,c2,c3);

pool.invokeAll(tasks);                                                  //This is a blocking operation
pool.invokeAll(tasks,2,TimeUnit.SECONDS);                               //Run all the tasks that can be run in 2 seconds after that stop all tasks

-----------------------------------------------------------------------------------------------------------------------------------------------------

ScheduledExecutorService:
    → Used for scheduled tasks
    → Run tasks once after delay OR repeatedly at intervals

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: schedule(): 
    → Run task ONCE after given delay

Code:
    threadPool.schedule(() -> System.out.println("runs after 3s"), 3, TimeUnit.SECONDS);

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: scheduleAtFixedRate():
    → Run task repeatedly at fixed interval
    → Starts next run based on START time of previous task
    → Tasks can OVERLAP if previous task takes longer than interval

    → InOrder to shutdown with FixedRate() we need to schedule the shutdown() too
    → otherwise the shutdown will be instant

Code:
ScheduledExecutorService threadPool = Executors.newScheduledThreadPool(1);

// first run after 1s → then every 2s from start time
threadPool.scheduleAtFixedRate(()->{System.out.println("This will run every second");} , 1, 2 , TimeUnit.SECONDS);

//To stop → must schedule shutdown() separately
threadPool.schedule(() -> threadPool.shutdown(), 8, TimeUnit.SECONDS);

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: scheduleWithFixedDelay():
    → Run task repeatedly but waits for previous task to FINISH
    → Delay starts AFTER previous task completes → no overlap

Code:

// first run after 1s → waits for finish → then waits 2s → runs again
// if task takes 10s → next run after 10 + 2 = 12s
threadPool.scheduleWithFixedDelay(task, 1, 2, TimeUnit.SECONDS);

-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread Communication:

→Threads coordinate with each other
→ One thread tells another:
    → When to wait
    → When to continue

Java Methods Used:

wait() → thread waits
notify() → wakes one waiting thread
notifyAll() → wakes all waiting threads
⚠ These methods must be called inside a synchronized block

-----------------------------------------------------------------------------------------------------------------------------------------------------

Where Is Thread Communication Used:

→ When threads depend on each other
→ When tasks must run in a specific order

Producer-Consumer Example
    → Producer → produces data
    → Consumer → consumes data

They communicate:
    → Producer: “Data ready”
    → Consumer: “Data consumed”

This avoids:
    → Busy waiting
    → CPU wastage

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

CyclicBarrier vs CountDownLatch:

CyclicBarrier can be re-used
CountDownLatch cannot be re-used

In CyclicBarrier all threads wait at barrier
In CountDownLatch Only main thread will wait to  get tasks finished

CyclicBarrier is used why you have to sync multiple threads 
CountDownLatch is used when you have to wait for other threads to be finished

-----------------------------------------------------------------------------------------------------------------------------------------------------
