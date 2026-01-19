-------------------------------------------------------------------------------------------------------------------------------
Multi Threading:
-------------------------------------------------------------------------------------------------------------------------------

Process
    A process is an running program with its own memory space

Thread
    A thread is a small unit of work inside a process.
    A process can have one or multiple threads that share the same memory space but can execute independently.

What is Multithreading?
    Multithreading is a programming technique where a single process is divided into multiple threads, 
    and these threads run independently but share the same memory and data.
    Each thread performs a part of the task, so the work gets done faster and more efficiently.

Thread Safe:
    When Multiple threads access or modify shared data simultaneously without corrupting it or causing bugs.

-------------------------------------------------------------------------------------------------------------------------------

Single Core vs Multi Core:

1. Time-sharing / Concurrency (in single-core CPUs):

A single core runs one task at a time.
The operating system rapidly switches between tasks.
Each task gets a small time slice.
To the user, it feels like all tasks are running together — but in reality, they take turns very quickly.

2. True parallelism (in multi-core CPUs):

A multi-core CPU can run multiple tasks at the same exact time, because:
Each core can handle a task/thread simultaneously.
No switching — tasks truly happen in parallel.
This leads to better performance, especially for heavy or many tasks.

-------------------------------------------------------------------------------------------------------------------------------

Time Slice:
A time slice is a fixed amount of CPU time given to a process or thread.
After its time slice ends, the CPU may give the turn to another task.
Also called a time quantum.

Context Switching:
Context switching is the process of saving the state of one thread/process and loading the state of another.
Happens when switching between tasks — including at the end of a time slice.

-------------------------------------------------------------------------------------------------------------------------------

LifeCycle of Thread:

NEW:
    Thread object created, start() not called
    Thread t1 = new Thread(() ->);

RUNNABLE:
    start() called
    Waiting for CPU

RUNNING:
    Scheduler assigns CPU, and thread is running

BLOCKED:
    Thread is blocked because another thread holds the lock

WAITING:
    Thread is waiting for another thread to get completed
    thread.join()  → waiting for another thread to finish

TERMINTED:
    Thread has finished execution
    run() execution completed

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------