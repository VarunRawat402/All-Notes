-------------------------------------------------------------------------------------------------------------------------------
Volatile vs Atomic : 
-------------------------------------------------------------------------------------------------------------------------------

Thread visibility Problem:

In Java, each thread can keep a cached copy of shared variables in its own working memory.

This means:
A thread may read a value once from main memory.
It may then continue using its cached value, even if another thread updates the variable.
As a result, threads may see stale (old) values, leading to incorrect behavior.
For example, if Thread A updates a variable, Thread B might not immediately see that update because it is still reading the old value from its local cache.
This issue is known as the visibility problem.

-------------------------------------------------------------------------------------------------------------------------------

Volatile:

volatile solves visibility, not atomicity.
When a variable is declared volatile, all threads always see the latest written value.
It prevents caching the value in thread-local memory.
It does not make operations like i++, i += 1, or check-then-act atomic.

Used for boolean flags
Best used for read and write operations not modify

-------------------------------------------------------------------------------------------------------------------------------

Atomic:
Atomic classes (AtomicInteger, AtomicLong, AtomicReference) solve atomicity + visibility.

They provide lock-free thread-safe operations like:
    incrementAndGet()
    compareAndSet()
    addAndGet()
    These operations are atomic, meaning no race conditions.

Best used for modifing states

“volatile guarantees visibility but not atomicity. Atomic types guarantee both visibility and atomicity. 
Therefore, volatile is safe only for reads/writes, while AtomicInteger is safe for operations like increment.”

-------------------------------------------------------------------------------------------------------------------------------