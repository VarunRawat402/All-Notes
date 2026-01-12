-------------------------------------------------------------------------------------------------------------------------------
Lock
-------------------------------------------------------------------------------------------------------------------------------

Intrinsic Locks:
    Every Java object has an intrinsic lock
    Used by the synchronized keyword
    synchronized keyword acquire this lock and automatically released when the method exits
    Simple and safe, but less flexible.

Explicit Locks:
    You manually control locking and unlocking
    More flexible: tryLock(), timeout, interruptible lock, fairness policies.

    Lock lock = new ReentrantLock();

-------------------------------------------------------------------------------------------------------------------------------

lock.lock() : 
    Acquires the lock
    Must always unlock in finally block

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
    Same thread can acquire the same lock multiple times without unlocking
    Prevents self-deadlock
    Relocking happens only on same threads

//Thread first locks in method1(), then locks the same lock again in method2()
//then unlocked the lock 2 times in finally blocks
//It only happens in same thread if thread 2 lock the method2() we cannot prevent that
Code:
public class ReentrantExample {

    private final ReentrantLock lock = new ReentrantLock();

    public void method1() {
        lock.lock();
        try {
            System.out.println("method1()");
            method2();
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
    If lock is free → acquires lock → returns true
    If not → returns false
    It does not block or wait
    Used with if()

tryLock(2, TimeUnit.SECONDS) :
    If lock is free → acquires lock → returns true
    If not → it waits up to the given time
    If the lock is still not available → returns false
    This method can throw InterruptedException

Example:
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
Thrown when a blocking operation is interrupted

Common methods that throw it:
    Thread.sleep()
    wait()
    join()
    BlockingQueue.take()
    lock.lockInterruptibly()

-------------------------------------------------------------------------------------------------------------------------------

Thread scheduling is non-deterministic

When you call .start(), the thread goes to the queue of the OS.
Then the OS scheduler (not Java!) decides:
Which thread to run first
How much CPU time to give it
When to pause/resume each one
So even though Thread-1 was created first, the CPU might run Thread-2 earlier or for longer.

-------------------------------------------------------------------------------------------------------------------------------

Fair vs Unfair Locks

✅ Fair Lock:
    Threads acquire the lock in the order they requested it — like a queue (FIFO).

❌ Unfair Lock (default):
    Some threads skip the queue and acquire the lock before requested threads.

Fair lock ensures predictable behavior — no thread is starved.
Unfair lock gives better performance, but some threads might get starved if others keep jumping ahead.

-------------------------------------------------------------------------------------------------------------------------------

Read & Write Locks:
Used when Data is read frequently, but modified rarely.

Read Lock:
Multiple threads can lock the read lock simultaneously.
No write lock can be acquired when read locks are active.

Write Lock:
Only one thread can hold the lock at a time.
No read or write locks can be acquired when the write lock is active.

-------------------------------------------------------------------------------------------------------------------------------
Syntax:

//Interface Reference
ReadWriteLock rwLock = new ReentrantReadWriteLock();
Lock readLock = rwLock.readLock();
Lock writeLock = rwLock.writeLock();

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
