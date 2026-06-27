-----------------------------------------------------------------------------------------------------------------------------------------------------
Multi Threading:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Process
    → It is a program with its owm memory and resources.
    → Example: Chrome, Intellij

Thread
    → It is a smallest unit of task in process
    → They share resources but run independently.

What is Multithreading?
    → When multiple threads are working together to complete a task.
    → Improves performance

Thread Safe:
    → When Multiple threads modify the same data without causing data corruption.


-----------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW         
    → Thread object created, start() not called yet
    → Thread t1 = new Thread(() -> { });

RUNNABLE    
    → start() called → waiting for CPU to pick it up

RUNNING     
    → CPU assigned → thread actively executing

BLOCKED     
    → waiting for a lock held by another thread
    → (trying to enter synchronized block)

WAITING     
    → waiting for another thread to finish
    → thread.join() → waits until that thread completes

TERMINATED  
    → run() finished → thread done, cant restart

-----------------------------------------------------------------------------------------------------------------------------------------------------