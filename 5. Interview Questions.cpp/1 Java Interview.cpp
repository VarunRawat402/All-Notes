-----------------------------------------------------------------------------------------------------------------------------------------------------
Java Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Finalize vs Try with resource:
    → Used to close the resources like file, database connection etc

Finalize:
    → Method() in Object class
    → When object has no reference, GC call finalize() automatically
    → GC can call it after some time, or may never call it you dont know and resource will never gets closed.

Try with resource:
    → Use close() method in AutoCloseable interface
    → close() is automatically called after try block executes
    → Works even if exception occurs

Example:
try (Resource res = new Resource()) {
    res.use();                              // Auto-closes after this block
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why Do We Make a Constructor private:
    → A private constructor is used to restrict object creation from outside the class.

1. Singleton Pattern
   └─ Only one instance of the class exists

2. Utility Classes
   └─ Class has only static methods, no object needed

3. Factory Methods
   └─ Force usage of static method for object creation

4. Prevent Inheritance
   └─ Subclasses cannot call super(), class cannot be extended

-----------------------------------------------------------------------------------------------------------------------------------------------------

Serialization vs Deserialization in Java:

Serialization   : Java object → byte stream 
Deserialization : byte stream → Java object

→ Serializable is a marker interface (no methods).
→ It is used to tell JVM this class is allowed to serialize
→ Uses : Store object in file / sent over network / cached

Serial Version UID:
→ It is a unique Id of the class which is used during deserialization to verify compatibility.
→ If you dont define one, JVM will create one automatically
→ If you change something in class, JVM version Id will also change

Note:
    → Static and Transient variables are not seialized
    → If Parent class is not serializable, Child class can still be serializable

-----------------------------------------------------------------------------------------------------------------------------------------------------

Race Conditions:
    → When multiple threads try to modify the same data concurrently → data corruption

Example: Wallet Balance Update
→ 2 threads read balance = 100
→ Thread A deducts 60 → new balance 40
→ Thread B deducts 70 → new balance 30
→ Final value depends on which thread writes last

1. Pessimistic Locking:
    → SELECT * FROM wallet WHERE user_id = ? FOR UPDATE;

2: Atomic operations:
    → AtomicInteger count = new AtomicInteger();
    → count.incrementAndGet();

-----------------------------------------------------------------------------------------------------------------------------------------------------

What is Thread starvation?
    → When a thread is continuously ignored and other threads keep executing over it

Common causes:

1: Unfair Locks
2: High priority Thread keeps running, low priority threads starving
3: Long synchronized blocks making other threads starve
4: Small thread pool size

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference between PUT and PATCH with a real API example:

1. PUT:
    → Updates the entire entity with the provided data
    → If feilds are missing, they are considered null or defaulted

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. PATCH:
    → Updates only the speicified feilds which are provided
    → If feilds are missing, they are left unchanged

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transactions:
    → In Transaction either all methods are commited or no one gets commited
    → @Transactional does not work on static + private methods
    → Only roll back database operations not memory operations
    → Needs to call the method from another service

How @Transactional works internally:

→ Spring creates a proxy
→ Method is called through proxy
→ Opens 1 DB connection
→ Disables auto-commit
→ Executes method
→ If success → COMMIT
→ If exception → ROLLBACK

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction rollback rules:
    → Transaction roll backs automatically for RuntimeException
    → Transaction does not roll back if exception is catched
    → Rollbackfor is used to roll back the transaction for specific checked exceptions

@Transactional(rollbackFor = Exception.class)
public void process() throws Exception {
    throw new Exception();
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Propagation:
    → Propagation defines how Transactional method behaves when called inside another transaction.

1: REQUIRED (default):
    → Join existing txn

2: REQUIRES_NEW:
    → Always start NEW transaction.
    → Pause T1 → Creates T2 → resumes T1

3. MANDATORY
    → Fails, if no transaction exists

4: SUPPORTS:
    → Runs if transaction exists
    → If not runs without transaction

-----------------------------------------------------------------------------------------------------------------------------------------------------

Transaction Isolation:
    → How one transaction is protected from changes made by other running transactions.

-----------------------------------------------------------------------------------------------------------------------------------------------------
Isolation Protects From 3 Problems:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Dirty Read:
    → Reading data that is not yet commited by another transaction            

Example:
    → Initial balance → 1000
    → T1    → update balance = 5000   (not committed yet)
    → T2    → reads: balance = 5000   ← sees uncommitted value
    → Then T1 rolls back.                     
    → Real balance = 1000
    → But T2 used 5000 → wrong.   

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Non-Repeatable Read:
    → Same query gives different result inside same transaction.

Example:
    → T1    → read balance   → 1000
    → T2    → update balance → 2000     → commit
    → T1    → again reads    → balance  → 2000

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Phantom Read:
    → New rows appear during same transaction.

Example:
    → T1    → select count(*) where status='ACTIVE' → 10
    → T2    → insert new ACTIVE row     → commit
    → T1    → again                     → count → 11

-----------------------------------------------------------------------------------------------------------------------------------------------------
Isolation Levels:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: READ_UNCOMMITTED:
    → Lowest Safety
    → Can read uncommitted changes
    
Allows:
    → dirty read ❌
    → non-repeatable read ❌
    → phantom read ❌

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: READ_COMMITTED
    → Most Common Default
    → Only committed data visible
    → Prevents: dirty read ✅ blocked

Allows:
    → non-repeatable read ❌
    → phantom read ❌

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: REPEATABLE_READ
    → Rows read once cannot change during txn

Prevents:
    → dirty read ✅
    → non-repeatable read ✅

Allows:
    → phantom read ❌ (depending on DB engine)

Example:
    → T1 reads balance = 1000
    → T2 tries to update same row → blocked until T1 finishes
    → T1 reads again → still 1000

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: SERIALIZABLE:
    → Highest Safety
    → Transactions behave like they run one by one

Prevents:
    → dirty read ✅
    → non-repeatable read ✅
    → phantom read ✅

Example:
    → If T1 running:
    → T2 must wait      → even for inserts affecting query range.

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