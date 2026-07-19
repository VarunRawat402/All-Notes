-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to Fix Slow APIs — Database Query Optimization:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: Indexing:

→ Avoids full table scans and speeds up lookups.
→ Creates a B-tree structure internally.
→ Without index → scans every row          → O(N)
→ With index    → binary tree traversal    → O(log N)

SQL:
CREATE INDEX idx_user_email        ON users(email);           // single column
CREATE INDEX idx_user_name_status  ON users(name, status);    // composite index

JPA Annotation:
@Table(
    indexes = {
        @Index(name = "idx_email",       columnList = "email"),
        @Index(name = "idx_name_status", columnList = "name, status")
    }
)
public class User { }

Note: For composite indexes, column order matters — the index is only used if the query filters on the leftmost column(s) first.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

2: Efficient Queries:

→ Avoid SELECT * — fetch only the columns your API actually needs.
→ Use DTO projections to skip loading full Entity objects.

@Query("SELECT new com.example.dto.StudentDTO(s.name, s.age) FROM Student s")
List<StudentDTO> getStudentBasicInfo();

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: N+1 Problem:

→ When you load a parent entity and its child collection is lazy-loaded,
    JPA fires one query per parent row to fetch the children.
→ Example: 1 Student with 5 Courses
    → 1 query for the Student
    → 5 queries for the Courses (one per course)
    → = 6 queries total instead of 1

Use JOIN FETCH to load everything in a single query:
@Query("SELECT s FROM Student s JOIN FETCH s.courses WHERE s.id = :id")
Student findStudentWithCourses(@Param("id") Long id);

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

4: Batch Operations:

→ Group multiple inserts/updates into a single DB round-trip.
→ Drastically reduces network overhead for bulk operations.

Use cases:
    → Bulk user registrations
    → Bulk order processing

JPA batch config (application.yml):
spring:
  jpa:
    properties:
      hibernate:
        jdbc:
          batch_size: 50          # insert/update 50 rows per round-trip
        order_inserts: true       # group inserts by entity type for efficiency
        order_updates: true

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

5: Caching:
    → Reduce repeated DB hits for frequently accessed data.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

6: Pagination:
    → Fetch only the required rows using LIMIT/OFFSET.
    → Avoid returning huge datasets in single API call.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

7: Connection Pooling:

→ Opening a new DB connection per request is expensive.
→ Connection pooling (HikariCP in Spring Boot) maintains a pool of reusable connections — requests borrow and return them.
→ Eliminates connection setup overhead on every API call.

spring:
  datasource:
    hikari:
      maximum-pool-size: 10
      minimum-idle: 5
      connection-timeout: 30000

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

8: Asynchronous / Parallel Processing:
    → Offload heavy operations to async tasks if real-time processing is not needed.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

QUICK REFERENCE — WHEN TO USE WHAT

Slow lookups / filters       → Indexing
Fetching too much data       → DTO Projections + SELECT specific cols
Too many queries per request → Fix N+1 with JOIN FETCH
Bulk inserts are slow        → Batch Operations
Same data fetched repeatedly → Caching
Large datasets in one call   → Pagination
Connection overhead          → Connection Pooling (HikariCP)
Heavy non-blocking work      → Async Processing

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------