-----------------------------------------------------------------------------------------------------------------------------------------------------
Volatile vs Atomic : 
-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread visibility Problem:

→ In Java, each thread caches variables values in its own working memory.

This means:
→ A thread may read a value once from main memory.
→ It may then continue using its cached value, even if another thread updates the variable.
→ As a result, threads may see stale (old) values, leading to incorrect behavior.
→ For example, if Thread A updates a variable, Thread B might not immediately see that update because it is still reading the old value from its local cache.
→ This issue is known as the visibility problem.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Volatile:

→ volatile solves visibility, not atomicity.
→ When a variable is declared volatile, All threads always see the latest value
→ Prevents thread-local caching
→ It does not make operations atomic like i++, i += 1, or check-then-act.
→ Used for boolean flags

Example: 
    volatile boolean running = true;

-----------------------------------------------------------------------------------------------------------------------------------------------------

Atomic:

→ Atomic solves visibility and atomicity.
→ Use CAS (Compare-And-Swap)
→ Lock-free and thread-safe

Common Atomic Classes:
    → AtomicInteger
    → AtomicLong
    → AtomicBoolean
    → AtomicReference

Safe atomic operations
    → incrementAndGet()
    → addAndGet()
    → compareAndSet()

→ These operations are atomic, meaning no race conditions.

Example:
AtomicInteger count = new AtomicInteger(0);
count.incrementAndGet();  // Thread-safe

-----------------------------------------------------------------------------------------------------------------------------------------------------

Best used for modifing states
    → volatile guarantees visibility but not atomicity. Atomic types guarantee both visibility and atomicity. 
    → Therefore, volatile is safe only for reads, while AtomicInteger is safe for operations like increment.

-----------------------------------------------------------------------------------------------------------------------------------------------------