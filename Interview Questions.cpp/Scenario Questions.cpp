----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Scenario Interview Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you improve API performance:
    → fetch only required fields (DTOs)
    → Pagination for large datasets
    → Caching frequently accessed data
    → Proper indexing on frequently searched fields
    → Avoid N+1 queries
    → Use async for non-critical or long-running tasks
    → Rate limiting

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle concurrent updates to the same database row:

1: Pessimistic Locking / Database-level row lock:
    → DB locks the row
    → Other transactions trying SELECT ... FOR UPDATE wait
    → Transaction A updates balance → COMMIT
    → Transaction B acquires lock → updates balance

2: Optimistic Locking / Versioning:
    → Add version column in table
    → Transaction A reads wallet (version=1)
    → Transaction B reads wallet (version=1)
    → Transaction A updates balance → increments version=2 → succeeds
    → Transaction B tries update → fails → OptimisticLockException
    → Retry or abort

CREATE TABLE wallet (
    id BIGINT PRIMARY KEY,
    balance DOUBLE,
    version BIGINT
);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Connection pooling:
    → Maintain a set of pre-created connections (DB/Redis/HTTP)
    → Reuse connections instead of creating new ones per request

Without pooling:
    → Each request opens new connection → high latency, DB overload

With pooling:
    → Faster response
    → Controlled connections → better resource utilization

How It Works:
    → App starts → pool creates N connections
    → Request arrives → borrow connection → execute query → return to pool
    → No connection available → thread waits → timeout → exception

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What Causes Memory Leaks:
    → A memory leak occurs when objects are no longer needed but still referenced, so the garbage collector cannot reclaim memory.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Logging Best Practices:
    → Every log should answer → What happened? Where? Why?

Success:
    → log.info("Order created", kv("orderId", orderId), kv("userId", userId));

Exception:
    → log.error("Failed to create order", e);

Production Level: INFO / WARN / ERROR

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Database is slow - what steps will you take:
    → Confirm DB is bottleneck → compare API latency vs query time
    → Check connection pool wait time
    → Check CPU / Memory / Disk I/O on DB

Slow Queries:
    → Full table scans, missing indexes, N+1 queries

Connection Pool Issues:
    → Increase pool size (within DB limits)
    → Close leaked connections

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How do you handle failure of services in a microservices ecosystem?

→ Circuit Breaker → stop cascading failures
→ Fallback → return fallback response
→ Retries → only for transient errors
→ Health Checks → detect faulty services
→ Monitoring & Tracing → visibility & debugging

Transient Errors: temporary → retry
    Network glitches, short service overload, DB deadlock

Non-Transient Errors: permanent → no retry
    Invalid input, auth failures, 404

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application Deployment Process (Production-Oriented):

1. Code Development & Version Control:
    → Code is developed locally
    → feature → develop → main

2. Push Code to Git Repository:
    → Create PR (Pull Request)    → Code review
    → Merge after approval        → Triggers CI pipeline

3. Build & Package Application:
    → mvn clean install   → Generate JAR files
    → mvn test            → run unit tests

4. Create Docker Image:
    → Write Dockerfile
    → Build Docker image

5. Push Docker Image to Container Registry:
    → Authenticate with AWS ECR
    → Tag image
    → Push image

6. Deployment to Environment:
    → Kubernetes (EKS)
    → kubectl apply -f deployment.yaml

7  Post-Deployment Verification:
    → Health checks
    → Smoke tests
    → Monitor logs and metrics
    → Rollback if required

We follow a CI/CD-based deployment where code is built, tested, containerized, pushed to a registry, and deployed using automated pipelines with verification and rollback.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to Store Customer Sensitive Data:

1. Account Information (Bank / Card / PII):
    → Never store in plain text
    → Use encryption (AES-256)
    → Encrypt → store → Decrypt → use

2. Passwords
    → Never encrypt/decrypt → hash only
    → Hashing for verification → original value not needed

3. Encryption Keys Management:
    → Never store keys in code/config
    → Use AWS KMS / Vault

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Saga Design Pattern:
    → Saga is used to manage distributed transactions in microservices.
    → Maintains data consistency

1. Choreography-Based Saga:
    → No central coordinator
    → Services communicate via events
    → Each service performs local transaction → publishes event → listens to others
    → On failure → compensating actions triggered

Example:
    → OrderCreatedEvent → PaymentCompletedEvent → StockReservedEvent
    → Payment fails → PaymentFailedEvent → Order cancelled (compensation)

2. Orchestration-Based Saga:
    → Central orchestrator controls flow
    → Calls services in order → triggers compensations on failure
    → Services do not talk to each other

Example:
    → Orchestrator → Order Service → create order
    → Orchestrator → Payment Service → process payment
    → Orchestrator → Inventory Service → reserve stock
    → Payment fails → Orchestrator triggers Order Service cancel
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------