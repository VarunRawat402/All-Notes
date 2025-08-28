
Normal Variable:
A normal variable is the basic form of a variable in Java. 
When accessed by multiple threads without synchronization, its not thread-safe.

2. Volatile Variable
A volatile variable is one where every read and write happens directly in main memory, not in a thread-local cache.
Threads read data directly from main memory not from cache

3: Atomic Variables (like AtomicInteger)
AtomicInteger is a special Java class that lets you safely update numbers from multiple threads without using synchronized.
"An integer that protects itself from race conditions.



