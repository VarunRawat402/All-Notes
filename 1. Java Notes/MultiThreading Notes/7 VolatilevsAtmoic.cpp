-----------------------------------------------------------------------------------------------------------------------------------------------------
Volatile vs Atomic : 
-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread visibility Problem:

→ In Java, each thread caches variable's values in its own working memory.
→ A thread read a variable's value from main memory and cached it 
→ Thread A updates variable in main memory
→ Thread B still reads old cached value → incorrect behaviour

-----------------------------------------------------------------------------------------------------------------------------------------------------

Volatile:

→ Forces thread to always read/write directly from main memory
→ Solves VISIBILITY problem only
→ Does NOT solve atomicity → i++ still not thread safe
→ Use for simple flags

volatile boolean running = true;

-----------------------------------------------------------------------------------------------------------------------------------------------------

Atomic:

→ Thread safe operations WITHOUT locks
→ Internally uses CAS (Compare-And-Swap)
    → reads value → compares with expected → updates only if matches
    → if someone else changed it → retry

Common Atomic Classes:

1: AtomicInteger
2: AtomicLong
3: AtomicBoolean
4: AtomicReference

Example:

AtomicInteger count = new AtomicInteger(0);
count.incrementAndGet();            // +1 and return integer
count.addAndGet(5);                 // +5 and return integer

-----------------------------------------------------------------------------------------------------------------------------------------------------