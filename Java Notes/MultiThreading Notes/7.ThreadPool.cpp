-------------------------------------------------------------------------------------------------------------------------------
Thread Pool:
-------------------------------------------------------------------------------------------------------------------------------

A Thread Pool is like a team of workers 🧑‍🔧🧑‍🔧 ready to do tasks for you.

Instead of creating new threads every time (which is costly), you:
Create a pool of reusable threads 🔁
Submit tasks to them 📦
They pick and execute tasks 🏃‍♂️

-------------------------------------------------------------------------------------------------------------------------------

Why Use Thread Pools?
✅ Saves resources
✅ Improves performance
✅ Avoids creating too many threads
✅ You get more control (size, timeouts, etc.)

-------------------------------------------------------------------------------------------------------------------------------

Normally we would have to create 5 threads for 5 iterations
Instead we used thread pool of 3 threads
3 threads did the first 3 iterations and finished it and then we re used 2 threads
again to do last 2 iterations

Code:

public class DemoApp {
    public static void main(String[] args) {

        // Create a thread pool of 3 Threads
        ExecutorService pool = Executors.newFixedThreadPool(3);

        // Submit 5 tasks
        for (int i = 1; i <= 5; i++) {
            int taskId = i;
            //here we usually create new thread but instead we using thread pool 
            pool.submit(() -> {
                System.out.println("Task " + taskId + " is running on " + Thread.currentThread().getName());
                sleep(1000);
                System.out.println("Task " + taskId + " is done");
            });
        }

        // Shutdown the pool once all tasks are submitted
        pool.shutdown();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Thread Communication:

One thread tells another thread that something has happened.

In Java, this is usually done using:
    wait()
    notify()
    notifyAll()

-------------------------------------------------------------------------------------------------------------------------------

Where do we use it?

When you have multiple threads working together and you dont want them to run at the same time, but instead in a coordinated way.

Example:
One thread produces data (Producer)
Another thread consumes that data (Consumer)

They need to talk:
Producer: "Hey! I added something, you can consume!"
Consumer: "Hey! I finished consuming, you can produce again!"

-------------------------------------------------------------------------------------------------------------------------------