------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Microservices Notes :
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Monolithic Architecture :
→ Application where all components (UI, business logic, database access) are built and deployed as a single unit.
→ Spring Boot app handling users, orders, payments in one codebase.

Advantages:
    → Simple to build and deploy
    → Easy debugging (everything in one place)
    → Low complexity (no service-to-service calls)

Disadvantages:
    → Cannot scale specific parts (scale whole app only)
    → Tight coupling (one change can affect entire system)
    → Single technology stack (no flexibility)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Microservices Architecture:
→ Application split into multiple small services
→ Each service handles one business function
→ Each service is independently deployable and scalable
→ Example: User Service, Order Service, Payment Service

Advantages:
    → Independent development and deployment
    → Easy scaling (scale only required service)
    → Loose coupling (changes don’t affect other services)
    → Technology flexibility (different tech per service)

Disadvantages:
    → High complexity (network calls, APIs, service discovery)
    → Difficult debugging (distributed system)
    → Requires DevOps tools (Docker, Kubernetes)
    → Data consistency issues (distributed transactions)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Microservices Fundamentals
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ What Are Microservices?
→ Monolith vs Microservices
→ Microservices Architecture Explained
→ Creating & Running Multiple Services Locally

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Inter-Service Communication
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Microservices Communication Patterns
→ REST Communication Between Microservices
→ Feign Client & Implementation
→ Handling Timeouts and Retries
→ Circuit Breaker Pattern
→ Rate Limiters

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Service Discovery
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ What is Service Discovery? Implementing Service Discovery
→ Registering Services Automatically
→ Client Side Load Balancing
→ Problem with Configuration in Microservices
→ Implementing Centralized Config
→ Dynamic Configuration Refresh
→ Why Microservices Need an API Gateway

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Logging and Monitoring
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Centralized Logging for Microservices
→ Distributed Tracing
→ Monitoring Microservices Metrics
→ Visualizing Metrics Dashboards

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Event Driven Microservices
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Event Driven Architecture Explained
→ Messaging Systems for Microservices
→ Producing and Consuming Events
→ Kafka & Rabbitmq

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Microservices Security
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ JWT/OAuth
→ Gateway Based Authentication

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Containerization
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Docker Containers
→ Deploy microservices to cloud

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
