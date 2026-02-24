-----------------------------------------------------------------------------------------------------------------------------------------------------
Synchronization:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ When a method is synchronized, only one thread can access it.

What Exactly Gets Locked?
    → synchronized always locks a monitor
    → Monitor can be:
        → Object lock   → this
        → Class lock    → ClassName.class

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Object-Level Synchronization

class Printer {
    private int balance = 1000;

    public synchronized void withdraw(int amount) {
        balance -= amount;
        System.out.println("Remaining Balance: " + balance);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Block-Level Synchronization (Best Practice):
    → Locks only critical section
    → Better performance than method-level

class BankAccount {
    private int balance = 1000;

    public void withdraw(int amount) {
        synchronized (this) {
            balance -= amount;
        }
        System.out.println("Remaining Balance: " + balance);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

DeadLock:
    → Deadlock happens when two or more threads are blocked forever
    → Thread 1 → holds R1 → waits for R2
    → Thread 2 → holds R2 → waits for R1

-----------------------------------------------------------------------------------------------------------------------------------------------------

synchronized can cause deadlock
    → synchronized cannot recover from deadlock once it happens

Reason:
    → No tryLock
    → No timeout
    → No interrupt while waiting

-----------------------------------------------------------------------------------------------------------------------------------------------------