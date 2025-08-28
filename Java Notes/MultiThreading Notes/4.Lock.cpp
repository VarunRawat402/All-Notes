-------------------------------------------------------------------------------------------------------------------------------
Lock
-------------------------------------------------------------------------------------------------------------------------------

There are 2 Types of Locking:

Intrinsic Locks (a.k.a. Monitor Locks):

These are the locks implicitly used when you use the synchronized keyword.
Every object in Java has an intrinsic lock.
synchronized blocks or methods acquire this lock.
Automatically released when the block/method exits (even on exceptions).
Simple and safe, but less flexible.

Explicit Locks:

These are manually controlled using classes from the java.util.concurrent.locks package, like ReentrantLock.
Must be manually acquired (lock()) and released (unlock()).
More flexible: tryLock(), timeout, interruptible lock, fairness policies.
More error-prone if you forget to unlock.

Syntax:
    Lock lock = new ReentrantLock();

-------------------------------------------------------------------------------------------------------------------------------

ReentrantLock():
    This lock prevents the self locking and deadlock
    Relocking happens only on same threads

//Usually Thread 1 will acquire lock in Method 1 and In Method 2 it will wait for itself to get unlocked 
//which is impossible resulting in deadlock
//In ReentrantLock a thread can relock itself again
Code:
public class ReentrantExample {
    private final ReentrantLock lock = new ReentrantLock();

    public void method1() {
        lock.lock();
        try {
            System.out.println("method1()");
            method2(); // same thread can re-acquire the lock
        } finally {
            lock.unlock();
        }
    }

    public void method2() {
        lock.lock();
        try {
            System.out.println("method2()");
        } finally {
            lock.unlock();
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------

lock.lock() : 
    This locks the current thread and other threads will wait until locked thread is unlocked 

Code:
public class LockExample {
    private final Lock lock = new ReentrantLock();

    public void access() {
        lock.lock(); // blocks until acquired
        try {
            System.out.println(Thread.currentThread().getName() + " got the lock.");
            Thread.sleep(1000); // simulate some work
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            lock.unlock();
        }
    }
}    

-------------------------------------------------------------------------------------------------------------------------------

tryLock() : 
    This checks if any thread is locked if not then This method tries to acquire the lock:
    Returns immediately with true if successful.
    Returns false if the lock is held by another thread.
    There's also a version with a timeout.

tryLock( 2, Time.SECONDS ) :
    This checks if any thread is locked if not then This method tries to acquire the lock:
    Wait till given time to acquire the lock

Code tryLock():

public class TryLockExample {
    private final Lock lock = new ReentrantLock();

    public void tryAccess() {
        if (lock.tryLock()) {
            try {
                System.out.println(Thread.currentThread().getName() + " got the lock.");
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            } finally {
                lock.unlock();
            }
        } else {
            System.out.println(Thread.currentThread().getName() + " could NOT get the lock.");
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------

InterruptedException:
This is a checked exception thrown when a blocking operation is interrupted.

Methods that throw InterruptedException:
Thread.sleep()
wait()
join()
BlockingQueue.take()
lock.lockInterruptibly()
Thread.join()

-------------------------------------------------------------------------------------------------------------------------------

Thread.currentThread().interrupt():
This is how you set the interrupt flag on a thread. It doesnt stop the thread immediately—it just marks it as interrupted.
This is useful when youre catching an InterruptedException and want to propagate the interruption:
If you catch InterruptedException and dont intend to stop the thread, always restore the interrupt like this:

Code:
try {
    Thread.sleep(1000);
} catch (InterruptedException e) {
    // restore the interrupted status
    Thread.currentThread().interrupt();
    // now the thread knows it's interrupted
}

Why restore it? Because catching InterruptedException clears the interrupt flag, and some code checks this flag like:
if (Thread.currentThread().isInterrupted()) {
    // stop doing work
}

-------------------------------------------------------------------------------------------------------------------------------

lockInterruptibly(): 
Imagine you want to cancel a thread while its waiting for a lock (e.g., shutdown or timeout logic). lockInterruptibly() makes this possible.

Normally, when you call lock(), a thread will:
Block and wait if the lock isnt available.
It cannot be interrupted while waiting.

-------------------------------------------------------------------------------------------------------------------------------

With lockInterruptibly():
The thread still blocks, but it can be interrupted while waiting for the lock.
If its interrupted, it throws an InterruptedException.

Code:

public class LockInterruptiblyExample {
    private static final ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) {

        //Thread 1 Doing some task and locking the lock
        Thread t1 = new Thread(() -> {
            try {
                lock.lock();
                System.out.println("Thread-1 acquired the lock.");
                Thread.sleep(5000); // Hold the lock for 5 sec
            } catch (InterruptedException e) {
                System.out.println("Thread-1 interrupted.");
            } finally {
                lock.unlock();
                System.out.println("Thread-1 released the lock.");
            }
        });

        //Thread 2 doing some another task locking the lock with lockInterruptibly
        Thread t2 = new Thread(() -> {
            try {
                System.out.println("Thread-2 trying to acquire lock...");
                lock.lockInterruptibly(); // This is the key!
                System.out.println("Thread-2 acquired the lock.");
            } catch (InterruptedException e) {
                System.out.println("Thread-2 was interrupted while waiting.");
            } finally {
                if (lock.isHeldByCurrentThread()) {
                    lock.unlock();
                    System.out.println("Thread-2 released the lock.");
                }
            }
        });

        //Starts the Thread 1 and sleep for 100ms so Thread 1 always starts first and Thread 2 Second
        t1.start();                                                 
        try { Thread.sleep(100); } catch (InterruptedException ignored) {}
        t2.start();

        //Thread 1 started and locks the lock
        //Thread 2 started and now waiting for thread 1 to get finished

        //Thread 1 will sleep for 5 sec and Thread 2 will wait for 1 sec
        try { Thread.sleep(1000); } catch (InterruptedException ignored) {}

        t2.interrupt(); // 🚨 This interrupts t2 while it’s waiting for the lock and return the interrupted exception
        //If there is no t2.interrupt t1 and t2 both will run perfectly
    }
}

Why its useful
    Without lockInterruptibly(), t2 would have kept waiting forever, ignoring the interrupt.
    This is super helpful when:
    You want to implement cancelable tasks
    You are building systems that need to shut down gracefully
    You want responsive, non-blocking behavior

-------------------------------------------------------------------------------------------------------------------------------    

Fair vs Unfair Locks

When multiple threads are trying to acquire a lock, you have two choices:

✅ Fair Lock:
Threads acquire the lock in the order they requested it — like a queue (FIFO).

❌ Unfair Lock (default):
Threads might skip the queue if the lock becomes available and they happen to run first.

Why does it matter?
Fair lock ensures predictable behavior — no thread is starved.

Unfair lock gives better performance, but some threads might get starved if others keep jumping ahead.

-------------------------------------------------------------------------------------------------------------------------------

//This creates 5 Threads and starts it and 5 threads called lock method So, 5 Threads are now in queue in Scheduler to run
//Any Thread can run and first, It Depends on scheduler

//If you use Fair Lock Then which Thread gets in queue of lock first will run first 
Code:

ReentrantLock lock = new ReentrantLock(true); // fair
ReentrantLock lock = new ReentrantLock(); // Unfair

for (int i = 1; i <= 5; i++) {
    final int threadId = i;
    new Thread(() -> {
        lock.lock();
        try {
            System.out.println("Thread-" + threadId + " acquired the lock");
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }).start();
}

-------------------------------------------------------------------------------------------------------------------------------

Thread scheduling is non-deterministic

When you call .start(), the thread goes to the ready queue of the OS.
Then the OS scheduler (not Java!) decides:
Which thread to run first
How much CPU time to give it
When to pause/resume each one
So even though Thread-1 was created first, the CPU might run Thread-2 earlier or for longer.

-------------------------------------------------------------------------------------------------------------------------------

Example of Fair and Unfair Lock Deeply:

In Fair:

Thread 1 and Thread 2 Starts the thread at same time, Now any Thread can lock the lock first
Each Thread tries to lock the lock 2 times in J loop
Lets Say Thread 1 got the lock first and locks the lock
Now it will print -> Sleep for 100 -> print -> unlock the lock -> sleep for 50, Then start the next iteration
So Thread 2 is waiting in line when Thread 1 got the lock So, As soon as Thread 1 releases the lock and goes to 50ms Sleep
Thread-2 gets the lock — because it was waiting in line. This continues back and forth like a queue.
📌 Fair = First Come, First Served

In Unfair
So Thread 2 is waiting in line when Thread 1 got the lock So, As soon as Thread 1 releases the lock and goes to 50ms Sleep
Thread 2 should get the lock now right? coz its in line and Thread 1 is sleeping for 50ms but Thread 1 will get the lock 
again even Thread 2 was in line and Thread 1 was sleeping for 50ms coz it is unfair Lock
It does not matter if you were in line Thread 1 can still cut it

-------------------------------------------------------------------------------------------------------------------------------

Conclusion:

In Fair : Threads get the lock in the order they come in lock queue
In UnFair : Threads can cut other threads in queue line even if they starts later resulting 
in some threads never getting the chance to lock


public class FairVsUnfair {

    // 👇 Change to `true` for fair lock
    static Lock lock = new ReentrantLock(false); // false = unfair, true = fair

    public static void main(String[] args){

        for(int i=1;i<=2;i++){
            int id = i;
            new Thread(()->{
                for(int j=1;j<3;j++){
                    lock.lock();
                    try {
                        System.out.println("Thread " + id + " got the lock");
                        Thread.sleep(100);
                        System.out.println("Thread " + id + " released the lock");
                        lock.unlock();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }).start();
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Read & Write Locks:

A ReadWriteLock is a type of lock that allows concurrent access for multiple reader threads, as long as no writer thread is active.
However, if a writer thread holds the lock, all other readers and writers are blocked until the writer releases it.

Read Lock:
Can be held by multiple threads at the same time.
Allowed only if no thread holds the write lock.

Write Lock:
Exclusive — only one thread can hold it.
Blocks all readers and other writers.

Use ReadWriteLock when:

You have a shared resource that is read often but rarely modified.
You want to improve performance over a standard lock (e.g. synchronized or ReentrantLock) by allowing multiple reads.

-------------------------------------------------------------------------------------------------------------------------------

Syntax:

//Generic Use
ReadWriteLock rwLock = new ReentrantReadWriteLock();
Lock readLock = rwLock.readLock();
Lock writeLock = rwLock.writeLock();

//Need advanced features
ReentrantReadWriteLock lock = new ReentrantReadWriteLock(false);
ReentrantReadWriteLock.ReadLock  readLock = lock.readLock();
ReentrantReadWriteLock.WriteLock writeLock = lock.writeLock();

-------------------------------------------------------------------------------------------------------------------------------

//All 3 Threads can access Read lock and read from the data together as long as write lock is not there
//No Thread can access lock when write lock is active
Code:
public class RWLock {

    //Initializing Read and write lock
    private static final ReentrantReadWriteLock lock = new ReentrantReadWriteLock(false);
    private static final ReentrantReadWriteLock.ReadLock  readLock = lock.readLock();
    private static final ReentrantReadWriteLock.WriteLock writeLock = lock.writeLock();
    private static List<String> data = new ArrayList<>();

    public static void main(String[] args){


        //Infinite Loop to write in Data using write Lock
        new Thread(()->{
            int counter = 0;
            while(true){
                writeLock.lock();
                System.out.println("Writer has acquired the lock");

                String item = "item " + ++counter;
                data.add(item);;
                System.out.println("Writer has released the lock");
                writeLock.unlock();
                sleep(5000);
            }
        }).start();

        //Infinite Loop for 3 threads to read from data using read lock
        for(int i=1;i<=3;i++){
            int id = i;
            new Thread(()->{
                while(true){

                    readLock.lock();
                    System.out.println("Reader " + id+ " has acquired the lock");

                    System.out.println("Reader " + id + " is reading " + data);
                    sleep(1000);

                    System.out.println("Reader " + id + " has released the lock");
                    readLock.unlock();
                    sleep(5000);
                }
            }).start();
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------
