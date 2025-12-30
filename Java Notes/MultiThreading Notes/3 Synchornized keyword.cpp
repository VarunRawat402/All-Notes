-------------------------------------------------------------------------------------------------------------------------------
Synchronization:
-------------------------------------------------------------------------------------------------------------------------------

synchronized keyword:
It is used to make a method or block thread-safe.
When a method is synchronized, only one thread can access it at a time for a given object.

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

