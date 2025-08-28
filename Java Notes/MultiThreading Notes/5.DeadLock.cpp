-------------------------------------------------------------------------------------------------------------------------------
DeadLock:
-------------------------------------------------------------------------------------------------------------------------------

Deadlock is a situation where two or more threads are blocked forever
waiting for each other to release a resource
Everyone's holding something, waiting for someone else — and no one lets go.

P1 → holds R1 → waiting for R2
P2 → holds R2 → waiting for R1

-------------------------------------------------------------------------------------------------------------------------------

You cannot remove deadlock using synchronized keyword because synchronized is:
    Non-interruptible: once a thread starts waiting, it waits forever
    Blocking: no timeout, no backoff
    No try-acquire option: you either get the lock or you dont — but you cant “give up and try later”

-------------------------------------------------------------------------------------------------------------------------------

Thread 1 Locks the lock1 Object and now want to lock lock2 Object
Thread 2 Locks the lock2 Object and now want to lock lock1 Object
Results in Deadlock situation

You can remove the Deadlock using TryLock()

Code:
public class SimpleDeadlock {
    static final Object lock1 = new Object();
    static final Object lock2 = new Object();

    public static void main(String[] args) {
        // Thread 1: locks lock1, then tries to lock lock2
        Thread t1 = new Thread(() -> {
            synchronized (lock1) {
                System.out.println("Thread 1: Locked lock1");
                
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
                
                synchronized (lock2) {
                    System.out.println("Thread 1: Locked lock2");
                }
            }   
        });

        // Thread 2: locks lock2, then tries to lock lock1
        Thread t2 = new Thread(() -> {
            synchronized (lock2) {
                System.out.println("Thread 2: Locked lock2");

                try { Thread.sleep(100); } catch (InterruptedException ignored) {}

                synchronized (lock1) {
                    System.out.println("Thread 2: Locked lock1");
                }
            }
        });

        t1.start();
        t2.start();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Removing Deadlock Using Try Lock():

o/p:
Nikhil Locked the Cafeteria
Varun Locked the 1:1 Meeting
Varun Could not lock the Cafeteria
Varun Unlocked the 1:1 Meeting
Nikhil Could not lock the 1:1 Meeting
Nikhil Unlocked the Cafeteria

Room Class:
public class Room {

    private String name;

    Lock lock = new ReentrantLock();

    Room(String name){
        this.name = name;
    }

    public String getName(){
        return name;
    }

    public void enter(String person){
        System.out.println(person + " entered the " + name);
        sleep(500);
        System.out.println(person + " Leaving the " + name);
    }
}

public class DemoApplication {
    public static void main(String[] args){

        Room room1 = new Room("1:1 Meeting");
        Room room2 = new Room("Cafeteria");

        // Thread 1 - Varun
        new Thread(() -> {

            //Try to lock Room1
            if (room1.lock.tryLock()) {
                try {
                    System.out.println("Varun Locked the " + room1.getName());
                    sleep(1000);

                    //Try to lock Room2
                    if (room2.lock.tryLock()) {
                        try {
                            System.out.println("Varun Locked the " + room2.getName());
                        } finally {
                            System.out.println("Varun Unlocked " + room2.getName());
                            room2.lock.unlock();
                        }
                    } else {
                        System.out.println("Varun Could not lock the " + room2.getName());
                    }
                } finally {
                    System.out.println("Varun Unlocked the " + room1.getName());
                    room1.lock.unlock();
                }
            } else {
                System.out.println("Varun Could not lock the " + room1.getName());
            }
        }).start();

        // Thread 2 - Nikhil
        new Thread(() -> {
            //Try to lock Room2
            if (room2.lock.tryLock()) {
                try {
                    System.out.println("Nikhil Locked the " + room2.getName());
                    sleep(1000);

                    //Try to lock Room1
                    if (room1.lock.tryLock()) {
                        try {
                            System.out.println("Nikhil Locked the " + room1.getName());
                        } finally {
                            System.out.println("Nikhil Unlocked " + room1.getName());
                            room1.lock.unlock();
                        }
                    } else {
                        System.out.println("Nikhil Could not lock the " + room1.getName());
                    }

                } finally {
                    System.out.println("Nikhil Unlocked the " + room2.getName());
                    room2.lock.unlock();
                }
            } else {
                System.out.println("Nikhil Could not lock the " + room2.getName());
            }
        }).start();
    }
}


