-------------------------------------------------------------------------------------------------------------------------------
Synchronization:
-------------------------------------------------------------------------------------------------------------------------------

synchronized keyword:
When a method is synchronized, only one thread can access it.

What Exactly Gets Locked?
    synchronized always locks a monitor
    Monitor can be:
        Object lock → this
        Class lock → ClassName.class

-------------------------------------------------------------------------------------------------------------------------------

1: Object-Level Synchronization

Lock is on the object instance
Threads using the same object → synchronized
Threads using different objects → NOT synchronized

class Printer {
    private int balance = 1000;

    public synchronized void withdraw(int amount) {
        balance -= amount;
        System.out.println("Remaining Balance: " + balance);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

2: Block-Level Synchronization (Best Practice):
    Locks only critical section
    Better performance than method-level

class BankAccount {
    private int balance = 1000;

    public void withdraw(int amount) {
        synchronized (this) {
            balance -= amount;
        }
        System.out.println("Remaining Balance: " + balance);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

