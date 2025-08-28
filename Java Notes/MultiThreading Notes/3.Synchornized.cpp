-------------------------------------------------------------------------------------------------------------------------------
Synchronization:
-------------------------------------------------------------------------------------------------------------------------------

synchronized keyword:

The synchronized keyword in Java is used to control access to a block of code or a method by multiple threads, 
ensuring that only one thread can execute it at a time for a given object or class.

synchronized Methods
synchronized blocks
synchronized objects

-------------------------------------------------------------------------------------------------------------------------------

Thread t1 and t2 starts together and working independently and changing the same counter simultaneously

Thread t1 and t2 both incrementing the counter by 1 simultaneously so there will be a moment where
they both increment together and it will count as 1 and data will get corrupted 

Making increment function synchronized will make only 1 thread getting accesed to counter 
so both threads cannot modify the counter simultaneously

-------------------------------------------------------------------------------------------------------------------------------
Ex:

Counter Class:
public class Counter {

    private int counter;                            //Counter

    public synchronized void increment(){           //Increase the counter by 1
        counter++;
    }

    public  int getCounter(){                       //Get the counter
        return counter;
    }
}

public class DemoApplication {
    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();

        Runnable task1 = new Runnable() {
            @Override
            public void run() {
                for(int i=1;i<=1000;i++){
                    counter.increment();
                }
            }
        };

        Thread t1 = new Thread(task1);
        Thread t2 = new Thread(task1);

        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(counter.getCounter());

    }
}

-------------------------------------------------------------------------------------------------------------------------------

