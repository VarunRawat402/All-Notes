-------------------------------------------------------------------------------------------------------------------------------
DeadLock:
-------------------------------------------------------------------------------------------------------------------------------

Deadlock happens when two or more threads are blocked forever

Thread 1 → holds R1 → waits for R2
Thread 2 → holds R2 → waits for R1

-------------------------------------------------------------------------------------------------------------------------------

synchronized can cause deadlock
synchronized cannot recover from deadlock once it happens

Reason:
    No tryLock
    No timeout
    No interrupt while waiting

-------------------------------------------------------------------------------------------------------------------------------

Deadlock Example:

Thread-1 holds lock1, waits for lock2
Thread-2 holds lock2, waits for lock1
Results in Deadlock situation

Code:
public class SimpleDeadlock {

    static final Object lock1 = new Object();
    static final Object lock2 = new Object();

    public static void main(String[] args) {

        Thread t1 = new Thread(() -> {
            synchronized (lock1) {
                System.out.println("Thread 1 locked lock1");
                sleep(100);
                synchronized (lock2) {
                    System.out.println("Thread 1 locked lock2");
                }
            }
        });

        Thread t2 = new Thread(() -> {
            synchronized (lock2) {
                System.out.println("Thread 2 locked lock2");
                sleep(100);
                synchronized (lock1) {
                    System.out.println("Thread 2 locked lock1");
                }
            }
        });

        t1.start();
        t2.start();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

TryLock() ( remvoes deadlock ):

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

-------------------------------------------------------------------------------------------------------------------------------
