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
    → Improves performance and responsiveness.

Thread Safe:
    → When Multiple threads access the same data without causing data corruption.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Single Core vs Multi Core:

1. Time-sharing / Concurrency (in single-core CPUs):

→ A single core runs one task at a time.
→ The operating system rapidly switches between tasks.
→ Each task gets a small time slice.
→ To the user, it feels like all tasks are running together — but in reality, they take turns very quickly.

2. True parallelism (in multi-core CPUs):

→ A multi-core CPU can run multiple tasks at the same exact time, because:
→ Each core can handle a task/thread simultaneously.
→ No switching — tasks truly happen in parallel.
→ This leads to better performance, especially for heavy or many tasks.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Time Slice:
    → It is a small amount of CPU time given to threads to run by scheduler before switching to the next thread.

Context Switching:
    → Saving the state of one thread to run another thread and restoring it later.

-----------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW:
    → Thread object created, start() not called
    → Thread t1 = new Thread(() ->);

RUNNABLE:
    → start() called
    → Waiting for CPU

RUNNING:
    → Scheduler assigns CPU, and thread is running

BLOCKED:
    → Thread is blocked because another thread holds the lock

WAITING:
    → Thread is waiting for another thread to get completed
    → thread.join()  → waiting for another thread to finish

TERMINTED:
    → Thread has finished execution
    → run() execution completed

-----------------------------------------------------------------------------------------------------------------------------------------------------