-----------------------------------------------------------------------------------------------------------------------------------------------------
Scenario Interview Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you improve API performance:
    → fetch only required fields (DTOs) from the repository
    → Pagination for large datasets
    → Caching frequently accessed data
    → Proper indexing on frequently searched fields
    → Avoid N+1 queries
    → Use async for non-critical or long-running tasks
    → Rate limiting

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

What Causes Memory Leaks:
    → When objects are no longer needed but still referenced due to this GC cannot reclaim the memory causes Memory Leaks.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Database is slow - what steps will you take:
    → Confirm DB is bottleneck → compare API latency vs query time
    → Check connection pool wait time
    → Check CPU / Memory / Disk I/O on DB

Slow Queries:
    → Full table scans, missing indexes, N+1 queries

Connection Pool Issues:
    → Increase pool size (within DB limits)
    → Close leaked connections

-----------------------------------------------------------------------------------------------------------------------------------------------------

Production Code Lifecycle:

main        → Production code (always stable)
develop     → Integration branch for next release
feature/    → New features, extracted from develop branch
bugfix/     → Non-production fixes, extracted from develop branch
release/    → Release preparation
hotfix/     → Urgent production fixes, extracted from main branch


Flow:

→ Feature branch is created from develop branch
→ Feature is created , run and unit tested locally

→ Pull Request is created to develop branch
→ After code approval, feature branch is merged to develop branch

CI/CD Pipeline triggers:
    → mvn clean verify
    → Run unit tests
    → Run integration tests
    → Security scan (Snyk/Trivy/etc)
    → Build artifact (JAR/WAR)

→ Realease branch is used to release all the features to production
→ After Multiple Features created and merged into develop branch
→ Develop branch is merged into Release branch

→ CI/CD Pipeline triggers
    → Run all tests
    → Create Docker image and push to ECR

→ Release is merged to main for releasing the features

Note:
→ bugfix branch : Created from develop, fix the bug locally, merge to develop
→ hotfix branch : Created from main, fix the live production bug, merged to develop and release both

-----------------------------------------------------------------------------------------------------------------------------------------------------

How to Store Customer Sensitive Data:

1. Account Information (Bank / Card / PII):
    → Never store in plain text
    → Use encryption (AES-256)
    → Encrypt → store → Decrypt → use

2. Passwords
    → Never encrypt/decrypt → hash only
    → Hashing for verification → original value not needed

-----------------------------------------------------------------------------------------------------------------------------------------------------

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
    
-----------------------------------------------------------------------------------------------------------------------------------------------------

