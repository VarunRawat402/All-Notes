-----------------------------------------------------------------------------------------------------------------------------------------------------
Lock
-----------------------------------------------------------------------------------------------------------------------------------------------------

Intrinsic Locks:
    → Every Java object has an intrinsic lock
    → synchronized keyword acquire this lock and automatically released when the method exits
    → Simple and safe, but less flexible.

Explicit Locks:
    → You manually control locking and unlocking
    → More flexible: tryLock(), timeout, interruptible lock, fairness policies.
    → Lock lock = new ReentrantLock();

-----------------------------------------------------------------------------------------------------------------------------------------------------

lock.lock() : 
    → Acquires the lock object
    → Code between lock and unlock is blocked section
    → Must always unlock in finally block

Code:
public class Counter {

    private final Lock lock = new ReentrantLock();

    public void getHello(){
        lock.lock();
        try {System.out.println("Hello world");}
        finally {lock.unlock();}
    }
} 

-----------------------------------------------------------------------------------------------------------------------------------------------------

ReentrantLock():
    → Same thread can lock the same lock multiple times without unlocking
    → Prevents self-deadlock
    → Relocking happens only on same threads

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

tryLock() : 
    → If lock is free → acquires lock → returns true
    → If not → returns false
    → It does not block or wait
    → Used with if()

tryLock(2, TimeUnit.SECONDS) :
    → If lock is free → acquires lock → returns true
    → If not → it waits up to the given time
    → If the lock is still not available → returns false
    → This method can throw InterruptedException

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

InterruptedException:
    → Thrown when a blocking operation is interrupted

Common methods that throw it:
    Thread.sleep()
    wait()
    join()
    BlockingQueue.take()
    lock.lockInterruptibly()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread scheduling is non-deterministic

→ When you call .start(), the thread goes to the OS queue
→ Then scheduler decides which thread to run first
→ So even though Thread-1 was created first, the CPU might run Thread-2 earlier or for longer.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Fair Lock:
    → Threads acquire the lock in the order they requested it

Unfair Lock (default):
    → Some threads skip the queue and acquire the lock before requested threads.

→ Fair lock ensures predictable behavior — no thread is starved.
→ Unfair lock gives better performance, but some threads might get starved if others keep jumping ahead.

→ Lock lock = new ReentrantLock(true);    // fair lock
→ Lock lock = new ReentrantLock();        // unfair lock

-----------------------------------------------------------------------------------------------------------------------------------------------------

Read & Write Locks:
    → Used when Data is read frequently, but modified rarely.

Read Lock:
    → Multiple threads can lock the read lock simultaneously.
    → No write lock can be acquired when read locks are active.

Write Lock:
    → Only one thread can hold the lock at a time.
    → No read or write locks can be acquired when the write lock is active.

→ ReadWriteLock rwLock = new ReentrantReadWriteLock();
→ Lock readLock = rwLock.readLock();
→ Lock writeLock = rwLock.writeLock();

-----------------------------------------------------------------------------------------------------------------------------------------------------