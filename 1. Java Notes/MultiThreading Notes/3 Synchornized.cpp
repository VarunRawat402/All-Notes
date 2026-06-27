-----------------------------------------------------------------------------------------------------------------------------------------------------
Synchronization:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Only ONE thread can access synchronized method/block at a time

-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Method Level (locks entire method):

public synchronized void withdraw(int amount) {
    balance -= amount;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Block-Level Synchronization (Best Practice):
    → Locks only critical section
    → Better performance than method-level

public void withdraw(int amount) {
    synchronized (this) {
        balance -= amount;       // only this part locked
    }
    System.out.println(balance); // runs without lock
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Deadlock:
    → Two threads waiting for each others lock → both stuck forever
    → T1 holds R1 → waits for R2
    → T2 holds R2 → waits for R1
    → Neither releases → deadlock

-----------------------------------------------------------------------------------------------------------------------------------------------------

synchronized can cause deadlock
    → synchronized cannot recover from deadlock once it happens

Reason:
    → No tryLock
    → No timeout
    → No interrupt while waiting

-----------------------------------------------------------------------------------------------------------------------------------------------------