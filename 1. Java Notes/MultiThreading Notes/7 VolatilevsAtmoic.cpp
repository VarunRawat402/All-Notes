-----------------------------------------------------------------------------------------------------------------------------------------------------
Volatile vs Atomic : 
-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread visibility Problem:

→ In Java, each thread caches variable's values in its own working memory.

→ A thread read a variable's value from main memory and cached it 
→ Another thread updates the variable in main memory
→ First thread still reading the old value from its own memory which may lead to incorrect behaviour
→ This is called visibility problem

-----------------------------------------------------------------------------------------------------------------------------------------------------

Volatile:

→ It ensures threads always reads latest value from main memory 

→ volatile solves visibility, not atomicity.
→ It does not make operations like i++, i+=1 thread-safe
→ Used for boolean flags

Example: 
    volatile boolean running = true;

-----------------------------------------------------------------------------------------------------------------------------------------------------

Atomic:

→ It allows thread-safe operations without lock / synchronization
→ Internally use CAS (Compare-And-Swap)

Common Atomic Classes:

1: AtomicInteger
2: AtomicLong
3: AtomicBoolean
4: AtomicReference

Safe atomic operations
    → incrementAndGet()     →    +1 and return integer
    → addAndGet(5)          →     +5 and return integer

Example:

AtomicInteger count = new AtomicInteger(0);
count.incrementAndGet();  // Thread-safe

-----------------------------------------------------------------------------------------------------------------------------------------------------