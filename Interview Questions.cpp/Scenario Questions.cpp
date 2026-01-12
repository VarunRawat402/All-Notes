----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Scenario Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you improve API performance:
    Avoid Over Fetching, Fetch only Required feilds from DB ( DTOs )
    Pagination for large data
    Caching
    Proper Indexing on frequently searched feilds
    Avoid N+1 Queries
    Use Async for non critical and long tasks
    Rate limiting

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle concurrent updates to the same database row:

1: Pessimistic Locking / Database-level row lock:
    DB locks the row
    Other transactions trying to SELECT ... FOR UPDATE wait
    Other reads may be blocked depending on isolation level
    Transaction A updates balance and commits:
    COMMIT
    Transaction B now acquires the lock and updates

2: Optimistic Locking / Versioning:
    Add a version column to your table:
    Transaction A reads wallet (version = 1)
    Transaction B reads wallet (version = 1)
    Transaction A updates balance → increments version to 2:
    Update succeeds because version = 1 matches
    Transaction B tries to update balance → fails:
    No rows updated → OptimisticLockException in JPA
    Transaction B can retry or abort

CREATE TABLE wallet (
    id BIGINT PRIMARY KEY,
    balance DOUBLE,
    version BIGINT
);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection pooling:
It is a technique where a set of pre-created connections (DB / Redis / HTTP) is maintained and reused instead of creating a new connection for every request.

Without pooling:
    Every request opens a new connection
    High latency
    DB overload

With pooling:
    Faster response time
    Controlled number of connections
    Better resource utilization

How Connection Pooling Works (Internals):
    Application starts
    Pool creates N connections (min size)
    Request arrives
    Thread borrows a connection from pool
    Query executes
    Connection is returned to pool
    If no connection is available → thread waits (timeout) → After timeout → exception

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What Causes Memory Leaks:
    A memory leak occurs when objects are no longer needed but still referenced, so the garbage collector cannot reclaim memory.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Logging best practices:

Every log should answer what happened, where, and why
Production → INFO / WARN / ERROR

Succesfull:
    log.info("Order created", kv("orderId", orderId), kv("userId", userId));

Exception:
    log.error("Failed to create order", e);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Database is slow - what steps will you take:

1. Confirm DB is the bottleneck:
    Check API latency vs DB query time
    Check connection pool wait time
    Check CPU, memory, disk I/O on DB

2. Check slow queries:
    Identify:
        Full table scans
        Missing indexes
        N+1 queries

3: Connection pool issues:
    Increase pool size (within DB limits)
    Close leaked connections

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle failure of services in a microservices ecosystem?

Circuit Breaker         → stop cascading failures
Fallback                → Returns fallback response instead of errors
Retries                 → only for transient errors
Health Checks           → Detects faulty services
Monitoring & Tracing    → visibility and debugging

What Are Transient Errors?
Transient errors are temporary failures that resolve on their own after a short time.
For transient errors Retries are used

Example:
    Temporary network glitches
    Short service overload
    Database Deadlock

Not Transient Errors:
    Invalid input
    Authentication / authorization failures
    Missing resource (404)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application Deployment Process (Production-Oriented):

1. Code Development & Version Control:
    Code is developed locally
    feature → develop → main

2. Push Code to Git Repository:
    Create PR (Pull Request)    → Code review
    Merge after approval        → Triggers CI pipeline

3. Build & Package Application:
    mvn clean install   → Generate JAR files
    mvn test            → run unit tests

4. Create Docker Image:
    Write Dockerfile
    Build Docker image

5. Push Docker Image to Container Registry:
    Authenticate with AWS ECR
    Tag image
    Push image

6. Deployment to Environment:
    Kubernetes (EKS)
    kubectl apply -f deployment.yaml

7   . Post-Deployment Verification:
    Health checks
    Smoke tests
    Monitor logs and metrics
    Rollback if required

We follow a CI/CD-based deployment where code is built, tested, containerized, pushed to a registry, and deployed using automated pipelines with verification and rollback.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to Store Customer Sensitive Data:

1. Account Information (Bank / Card / PII):
    Never Store in Plain Text
    Use Encryption (NOT hashing)
    Hashing is not reversible
    Use AES-256 (symmetric encryption)
    Plain Data → Encrypt → Store in DB
    Read → Decrypt → Use

2. Passwords
    Never Encrypt and DecryptPasswords
    Why hashing?
        Passwords are used only for verification
        No need to read original value

3. Encryption Keys Management:
    Never Store Keys in Code or Config Files
    Use AWS KMS / Vault

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Saga Design Pattern:
    Saga is used to manage distributed transactions in microservices.
    Maintains data consistency

1. Choreography-Based Saga:

No central coordinator.
Services communicate using events
Each service:
    Performs its local transaction
    Publishes an event
    Listens to other service events
On failure, compensating actions are triggered by listening to failure events

Example:
    Order Service → OrderCreatedEvent
    Payment Service → PaymentCompletedEvent
    Inventory Service → StockReservedEvent
    Payment fails → PaymentFailedEvent → Order Service cancels order (compensating transaction).

2. Orchestration-Based Saga:

Central orchestrator controls the flow.
Orchestrator:
    Calls services in order
    Decides next step
    Triggers compensations on failure
Services do not talk to each other directly

Example:
    Orchestrator    → Order Service → create order
    Orchestrator    → Payment Service → process payment
    Orchestrator    → Inventory Service → reserve stock
    Payment fails   → Orchestrator calls → Order Service → cancel order (compensation) 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------