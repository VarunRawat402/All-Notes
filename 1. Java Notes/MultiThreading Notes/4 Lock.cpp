-----------------------------------------------------------------------------------------------------------------------------------------------------
Lock
-----------------------------------------------------------------------------------------------------------------------------------------------------

Intrinsic Locks:
    → Every Java object has an intrinsic lock
    → synchronized acquires this lock + automatically release when the method exits

Explicit Locks:
    → You manually lock + unlock
    → More flexible → tryLock, timeout, interrupt, fairness
    → ALWAYS unlock in finally block → or lock never released

Code:
    private final Lock lock = new ReentrantLock();
    lock.lock();
    try { 
        // critical section 
    }
    finally { lock.unlock(); }

-----------------------------------------------------------------------------------------------------------------------------------------------------

ReentrantLock():
    → Same thread can lock same lock multiple times without unlocking itself
    → Prevents self-deadlock when method calls another method with same lock
    → Must unlock same number of times as locked

//Thread first locks in method1(), then locks the same lock again in method2()
//then unlocked the lock 2 times in finally blocks

Code:
public class ReentrantExample {

    private final ReentrantLock lock = new ReentrantLock();

    public void method1() {

        lock.lock();
        try {
            method2();
        } finally { lock.unlock(); }
    }

    public void method2() {
        lock.lock();
        try {
            System.out.println("method2()");
        } finally { lock.unlock(); }
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

tryLock() : 
    → If lock is free → acquires lock → returns true
    → If not → returns false
    → Used with if()

Example:
    if (lock.tryLock()) { ... }                        // instant try
    if (lock.tryLock(2, TimeUnit.SECONDS)) { ... }     // wait max 2 seconds

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

Fair Lock:
    → Threads acquire the lock in the order they requested it
    → No thread is starved.

Unfair Lock:
    → Threads can skip other waiting threads and acquire the lock
    → Better performance, but some threads might get starved if others keep jumping ahead.

→ Lock lock = new ReentrantLock(true);    // fair lock
→ Lock lock = new ReentrantLock();        // unfair  + Default

-----------------------------------------------------------------------------------------------------------------------------------------------------

Read & Write Locks:
    → Use when reads are frequent, writes are rare

Read Lock:
    → Multiple threads can lock the read lock simultaneously.
    → No write lock can be acquired when read locks are active.

Write Lock:
    → Only one thread can hold the lock at a time.
    → No read + write locks can be acquired when the write lock is active.

→ ReadWriteLock rwLock = new ReentrantReadWriteLock();
→ Lock readLock = rwLock.readLock();
→ Lock writeLock = rwLock.writeLock();

-----------------------------------------------------------------------------------------------------------------------------------------------------

InterruptedException:
    → Thrown when thread is interrupted during a blocking operation
    → Common in: sleep(), wait(), join(), tryLock(timeout), take()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread scheduling is non-deterministic:

→ When you call .start(), the thread goes to the OS queue
→ Then scheduler decides which thread to run first
→ So even though Thread-1 was created first, the CPU might run Thread-2 earlier or for longer.

-----------------------------------------------------------------------------------------------------------------------------------------------------