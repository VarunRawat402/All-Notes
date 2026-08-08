-----------------------------------------------------------------------------------------------------------------------------------------------------
Scenario Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you improve API performance:
    → fetch only required fields using DTOs from the repository
    → Pagination for large datasets
    → Caching frequently accessed data
    → Proper indexing on frequently searched fields
    → Avoid N+1 queries
    → Use async for non-critical or long-running tasks
    → Rate limiting

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle concurrent updates to the same database row:

1: Pessimistic Locking / Database-level row lock:
    → DB locks the row when transaction starts
    → Other transactions trying to access same row → WAIT
    → T1 locks row → updates → commits → lock released
    → T2 acquires lock → updates → commits
    → SELECT * FROM wallet WHERE id = ? FOR UPDATE
    → Downside: other transactions blocked → slower throughput

2: Optimistic Locking / Versioning:
    → No lock → add version column to table
    → T1 reads wallet (version=1)
    → T2 reads wallet (version=1)
    → T1 updates → version becomes 2 → succeeds 
    → T2 tries update WHERE version=1 → version already 2 → fails 
    → OptimisticLockException → retry or abort
    → Downside: conflicts cause retries

@Version
private Long version;  // JPA handles automatically

-----------------------------------------------------------------------------------------------------------------------------------------------------

Connection pooling:
    → Pre-created set of DB connections ready to use
    → Reuse connections instead of creating new one per request

Without pooling:
    → Every request → open connection → query → close connection
    → High latency + DB overload 

With pooling:
    → Connections created at app startup → ready to use
    → Request → borrow connection → query → return to pool
    → Faster + controlled resource usage 

spring.datasource.hikari.maximum-pool-size=10
spring.datasource.hikari.connection-timeout=30000

-----------------------------------------------------------------------------------------------------------------------------------------------------

What Causes Memory Leaks:
    → Objects no longer needed but still referenced
    → GC cant collect them → memory keeps growing → OutOfMemoryError

-----------------------------------------------------------------------------------------------------------------------------------------------------

What is Garbage Collection:
    → It automatically removes objects with no reference from heap memory.
    → If no reference of objects → eligible for Garbage collection

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you ensure Garbage Collection is working correctly:
    → Avoid memory leaks ( remove references of objects when no need )
    → Heap usage is stable over time
    → Monitor via VisualVM / JConsole
    → Check GC logs

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you debug OutOfMemoryError:
    → Read error: tells which memory area is full
    → Take heap dump: -XX:+HeapDumpOnOutOfMemoryError
    → Analyze with Eclipse MAT or VisualVM
    → Look for leaked objects

-----------------------------------------------------------------------------------------------------------------------------------------------------

DB is Slow - Debugging Steps:

1. Confirm DB is the bottleneck:
    → Compare total API latency vs actual query execution time
    → If query time ≈ API time → DB is the problem

2. Check Slow Queries:
    → Full table scans → missing indexes → add indexes
    → N+1 queries → use JOIN FETCH or @EntityGraph
    → Complex queries → optimize or break down

3. Check Connection Pool:
    → Threads waiting for connection → pool size too small → increase it
    → Leaked connections → connections borrowed but never returned → fix with try-with-resources

Fix Priority:
    → Indexes first (biggest impact, easiest fix)
    → Then N+1 queries
    → Then connection pool tuning
    → Then caching frequently accessed data

-----------------------------------------------------------------------------------------------------------------------------------------------------

How to Store Customer Sensitive Data:

1. Account Information (Bank / Card / PII):
    → Never store plain text
    → Encrypt → store ciphertext → decrypt only when needed
    → Encryption keys stored separately (not in DB, not in code)
    → Use environment variables or secret managers (AWS Secrets Manager)

2. Passwords
    → Never encrypt and decrypt
    → Hash only → BCrypt

-----------------------------------------------------------------------------------------------------------------------------------------------------

Saga Design Pattern:
    → Manages distributed transactions across microservices
    → No single DB transaction possible across services → Saga coordinates it
    → On failure → runs compensating transactions to undo previous steps
    → Maintains data consistency

1. Choreography-Based Saga:
    → No central coordinator
    → Services communicate via events, no coordinator
    → Each service → does its job → publishes event → next service listens

Example:
    Order Created → Payment Failed → PaymentFailedEvent → Order Service listens → cancels order (compensation) 
    → simple, no single point of failure
    → hard to track flow, event chains get complex

2. Orchestration-Based Saga:
    → Orchestrator tells each service what to do in order
    → Services dont talk to each other

Example:
    → Orchestrator → Order Service → create order
    → Orchestrator → Payment Service → process payment → Payment fails
    → Orchestrator → tells Order Service to cancel 
    → easy to track, clear flow
    → orchestrator = single point of failure
    
-----------------------------------------------------------------------------------------------------------------------------------------------------

