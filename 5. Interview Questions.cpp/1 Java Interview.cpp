-----------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Finalize vs Try with resource:
    → Used to close the resources like file, database connection etc

Finalize:
    → Method() in Object class
    → Called by GC when object have no reference
    → GC can call it after some time, or may never call it you dont know and resource will never gets closed.

Try with resource:
    → Automatically close resource after try block ends
    → Class must implement AutoCloseable + override close()
    → Guaranteed to run
    → Works even if exception occurs

Example:
try (Resource res = new Resource()) {
    res.use();                              // Auto-closes after this block
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why Do We Make a Constructor private:
    → Prevents anyone from creating object directly
    → You control HOW the object is created

1. Singleton Pattern
    → Only ONE instance should exist in entire app
    → Private constructor → no one can create new instance

2. Utility Classes
    → Class has only static methods, no need to create object

3. Factory Methods
    → Control object creation through a factory method
    → Add logic before creating object

4. Prevent Inheritance
    → Subclasses cannot call super(), class cannot be extended

-----------------------------------------------------------------------------------------------------------------------------------------------------

Serialization vs Deserialization in Java:

Serialization:
    → Converting Java object → byte stream
    → Save to file, send over network, store in DB
    → Serializable is a marker interface (no methods).
    → It is used to tell JVM this class is allowed to serialize

Deserialization:
    → Converting byte stream → back to Java object
    → Reconstruct object from saved/received data

Serial Version UID:
→ It is a unique Id of the class which is used during deserialization to verify compatibility.
→ If you dont define one, JVM will create one automatically
→ If you change something in class, Serial ID will also change and throws InvalidClassException

Note:
    → Static and Transient variables are not serialized
    → If Parent class is not serializable, Child class can still be serializable

Real world use:
→ REST APIs     → Java object → JSON (Jackson does this automatically)
→ Caching       → store object in Redis
→ Messaging     → send object over Kafka/RabbitMQ

-----------------------------------------------------------------------------------------------------------------------------------------------------

Race Conditions:
    → When multiple threads modify same data simultaneously → data corruption

Example (Wallet):
→ Thread A reads balance = 100 → deducts 60 → writes 40
→ Thread B reads balance = 100 → deducts 70 → writes 30
→ One deduction is lost → data corrupted
→ Result depends on which thread writes last (unpredictable)

Fixes:

1. Pessimistic Locking (DB level):
    → SELECT * FROM wallet WHERE user_id = ? FOR UPDATE
    → locks row until transaction completes, no other thread can touch it

2. Atomic Operations (Java level):
    → AtomicInteger count = new AtomicInteger();
    → count.incrementAndGet();
    → thread safe operations without synchronization

-----------------------------------------------------------------------------------------------------------------------------------------------------

Thread Starvation:
    → A thread keeps getting ignored while other threads keep running
    → Thread never gets CPU time → task never executes

Common Causes:
    → Unfair locks → same threads keep getting lock
    → High priority threads always preferred → low priority starves
    → Long synchronized blocks → other threads waiting forever
    → Thread pool too small → tasks pile up, some never execute

Fix:
    → Fair locks → ReentrantLock(true) → threads get lock in order
    → Avoid long synchronized blocks
    → Increase thread pool size

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference between PUT and PATCH with a real API example:

1. PUT:
    → Replaces ENTIRE object with what you send
    → Missing fields → set to null/default

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. PATCH:
    → Updates ONLY the fields you send
    → Missing fields → stay unchanged

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transactions:
    → All operations commit together or none commit
    → Only rolls back DB operations, not in-memory changes
    → @Transactional does not work on static + private methods
    → Must be called from ANOTHER class (Spring proxy limitation)

Internal Working:

→ Spring creates a PROXY around your class
→ Method called through proxy → opens DB connection
→ Disables auto-commit
→ Executes method
→ Success   → COMMIT ✅
→ Exception → ROLLBACK ❌

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction rollback rules:
    → Transaction roll backs automatically → RuntimeException
    → Transaction does not roll back if exception is catched
    → Rollbackfor is used to roll back the transaction for specific checked exceptions
    → @Transactional(rollbackFor = Exception.class)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Propagation:
    → Defines what happens when @Transactional method is called inside another transaction

1: REQUIRED (default):
    → Join existing transaction if one exists
    → If no transaction → create new one
    → Both methods share same transaction → one fails = both rollback

2: REQUIRES_NEW:
    → Always creates a brand new transaction
    → Pauses outer transaction (T1) → runs its own (T2) → resumes T1
    → T2 commits/rollbacks independently of T1

3: MANDATORY:
    → Must have existing transaction → if not → exception

4: SUPPORTS:
    → Runs WITH transaction if one exists
    → Runs WITHOUT transaction if none exists
-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Isolation:
    → Protects a transaction from changes made by other concurrent transactions

-----------------------------------------------------------------------------------------------------------------------------------------------------
3 Problems Isolation Solves:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Dirty Read:
    → Reading data that is not yet commited by another transaction            
    → Reading UNCOMMITTED data from another transaction
    → T1 updates balance 1000 → 5000 (not committed)
    → T2 reads 5000 → T1 rolls back → T2 used 5000 instead of 1000

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Non-Repeatable Read:
    → Same query gives DIFFERENT result within same transaction
    → T1 reads balance = 1000
    → T2 updates balance = 2000 → commits
    → T1 reads again → gets 2000 → inconsistent data

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Phantom Read:
    → New ROWS appear during same transaction
    → T1 counts ACTIVE users = 10
    → T2 inserts new ACTIVE user → commits
    → T1 counts again → gets 11 → unexpected 

-----------------------------------------------------------------------------------------------------------------------------------------------------
Isolation Levels:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: READ_UNCOMMITTED:
    → can read uncommitted data
    → Dirty read ❌ | Non-repeatable ❌ | Phantom ❌
    → Almost never used in production

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: READ_COMMITTED
    → Only reads committed data
    → Dirty read ✅ | Non-repeatable ❌ | Phantom ❌
    → Default in PostgreSQL, Oracle

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: REPEATABLE_READ
    → Rows read once → locked → can't be changed by others until txn ends
    → Dirty read ✅ | Non-repeatable ✅ | Phantom ❌
    → Default in MySQL
    → T1 reads balance → T2 tries to update → blocked until T1 finishes

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: SERIALIZABLE:
    → Highest safety → transactions run as if one by one
    → Dirty read ✅ | Non-repeatable ✅ | Phantom ✅
    → Slowest → use only when data accuracy is critical

-----------------------------------------------------------------------------------------------------------------------------------------------------

Example:

@Transactional(
  propagation = Propagation.REQUIRED,
  isolation = Isolation.READ_COMMITTED,
  rollbackFor = Exception.class
)
public void transfer(Long from, Long to, BigDecimal amount) {

    debit(from, amount);   // step 1
    credit(to, amount);    // step 2
}


-----------------------------------------------------------------------------------------------------------------------------------------------------