---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Data Management Patterns:
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

It define how data is stored, owned, and shared across Microservices
One microservice → One database

A: Database Per Service:
    Each microservice owns its own database.
    Loose coupling
    Independent scaling

B: Shared Database:
    Schema changes break services
    Deployment lockstep

C: Data Duplication (CQRS-style):
    Services replicate required data locally instead of querying other DBs.
    Avoid synchronous calls
    User Service → UserCreatedEvent
    Order Service → stores userId + userName
    Order Service stores some data of user, to avoid calling user-service for user data

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------