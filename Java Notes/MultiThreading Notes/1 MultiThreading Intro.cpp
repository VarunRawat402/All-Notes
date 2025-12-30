-------------------------------------------------------------------------------------------------------------------------------
Multi Threading:
-------------------------------------------------------------------------------------------------------------------------------

Core
A core is a physical processing unit inside the CPU. 
Each core can execute one thread at a time (or more with technologies like hyper-threading), enabling parallel execution.

Program
A program is a set of instructions written to perform a specific task. It is stored on disk and is not active until executed.

Process
A process is an instance of a program that is currently being executed. It has its own memory space and system resources.

Thread
A thread is the smallest unit of execution within a process. 
A process can have one or multiple threads that share the same memory space but can execute independently.

-------------------------------------------------------------------------------------------------------------------------------

Single Core vs Multi Core:

1. Time-sharing (in single-core CPUs):

A single core runs one task at a time.
The operating system rapidly switches between tasks.
Each task gets a small time slice.
To the user, it feels like all tasks are running together — but in reality, they take turns very quickly.

2. True parallelism (in multi-core CPUs):

A multi-core CPU can run multiple tasks at the same exact time, because:
Each core can handle a task/thread simultaneously.
This leads to better performance, especially for heavy or many tasks.

-------------------------------------------------------------------------------------------------------------------------------

What is Multithreading?
Multithreading is a programming technique where a single process is divided into multiple threads, 
and these threads run independently but share the same memory and data.
Each thread performs a part of the task, so the work gets done faster and more efficiently.

-------------------------------------------------------------------------------------------------------------------------------

Concurrency:

Multiple tasks are in progress at the same time.
But only one task may actually run at a given instant (especially on a single-core CPU).
The system switches between tasks quickly — this is called context switching.
It gives the illusion of tasks running simultaneously.

Parallelism:

Actually doing many things at the same time (physically)
Multiple tasks run simultaneously on multiple cores.
No switching — tasks truly happen in parallel.
Needs multi-core CPU or multiple processors.

Time Slice:
A time slice is a fixed amount of CPU time given to a process or thread.
After its time slice ends, the CPU may give the turn to another task.
Also called a time quantum.

Context Switching:
Context switching is the process of saving the state of one thread/process and loading the state of another.
Happens when switching between tasks — including at the end of a time slice.

-------------------------------------------------------------------------------------------------------------------------------