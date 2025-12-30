-------------------------------------------------------------------------------------------------------------------------------
Lock
-------------------------------------------------------------------------------------------------------------------------------

There are 2 Types of Locking:

Intrinsic Locks:
    Every object in Java has an intrinsic lock.
    These locks are used by synchronized keyword
    synchronized acquire this lock and automatically released when the method exits
    Simple and safe, but less flexible.

Explicit Locks:
    These are manually controlled locks
    You manually acquire the lock and release the lock
    More flexible: tryLock(), timeout, interruptible lock, fairness policies.

Syntax:
    Lock lock = new ReentrantLock();

-------------------------------------------------------------------------------------------------------------------------------

lock.lock() : 
    This locks the object and prevent other threads to access the locked object

Code:
public class Counter {

    private final Lock lock = new ReentrantLock();

    public void getHello(){
        lock.lock();
        try{
            System.out.println("Hello world");
        }finally {
            lock.unlock();
        }
    }
} 

-------------------------------------------------------------------------------------------------------------------------------

ReentrantLock():
    It allows self locking multiple times without unlocking the lock first
    self deadlock : when same thread tries to lock the same lock again without unlocking it first
    Relocking happens only on same threads

//Thread 1 calls the method1() and locks the object
//Inside method1(), It calls method2() and locks the object again, now it has 2 locks
//method2() finishes, unlocked the lock, same for method()1
//It only happens in same thread if thread 2 lock the method2() we cannot prevent that
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

tryLock() : 
It tries to lock the object 
    If the lock is free → acquires the lock and returns true
    If not → it returns false immediately
    It does not block or wait

tryLock(2, TimeUnit.SECONDS) :
    If the lock is free → acquires it immediately
    If not → it waits up to the given time
    If the lock is still not available → returns false
    This method can throw InterruptedException

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

✅ Fair Lock:
    Threads acquire the lock in the order they requested it — like a queue (FIFO).

❌ Unfair Lock (default):
    Some threads skip the queue and acquire the lock before requested threads.


Fair lock ensures predictable behavior — no thread is starved.
Unfair lock gives better performance, but some threads might get starved if others keep jumping ahead.

-------------------------------------------------------------------------------------------------------------------------------

Thread scheduling is non-deterministic

When you call .start(), the thread goes to the queue of the OS.
Then the OS scheduler (not Java!) decides:
Which thread to run first
How much CPU time to give it
When to pause/resume each one
So even though Thread-1 was created first, the CPU might run Thread-2 earlier or for longer.

-------------------------------------------------------------------------------------------------------------------------------

Read & Write Locks:

In ReadWriteLock, Multiple threads can acquire the read locks simultaneously, but only one thread can acquire the write lock at a time.

Read Lock:
Multiple threads can hold the read lock simultaneously.
No write lock can be acquired when read locks are active.

Write Lock:
Only one thread can hold the lock at a time.
No read or write locks can be acquired when the write lock is active.


Use ReadWriteLock when:
You have a shared resource that is read often but rarely modified.

-------------------------------------------------------------------------------------------------------------------------------
Syntax:

//Interface Reference
ReadWriteLock rwLock = new ReentrantReadWriteLock();    
Lock readLock = rwLock.readLock();
Lock writeLock = rwLock.writeLock();

//Class Reference
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
