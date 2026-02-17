-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to Fix Slow APIs / Database Query Optimization
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: Indexing:
    → Speeds up lookups by avoiding full table scans.
    → Creates a B-tree structure internally.
    → Query without index : scans every row → O(N)
    → Query with index    : tree traversal → O(log N)

CREATE INDEX idx_user_email ON users(email);                    //Index of 1 col
CREATE INDEX idx_user_name_status ON users(name, status);       //Index of multiple col

SB Annotation:
@Table(
    indexes = {
        @Index(name = "idx_email", columnList = "email"),
        @Index(name = "idx_name_status", columnList = "name,status")
    }
)
public class User

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

2: Efficient Queries:
    → Avoid SELECT *  → fetch only required columns.
    → Use DTO projections instead of fetching entire entities

@Query("SELECT new com.example.dto.StudentDTO(s.name, s.age) FROM Student s")
List<StudentDTO> getStudentBasicInfo();

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: N+1 Problem:

→ Fetching nested entities lazily causes multiple queries.
→ Fetching 1 Student and their 5 Courses  → 1 query for Student + 5 queries for Courses = 6 queries.

→ SELECT s FROM Student s JOIN FETCH s.courses WHERE s.id = :id
→ Reduces the number of queries drastically.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

4: Batch Operations:
    → Use batch inserts/updates for bulk operations.
    → Reduces network/database round-trips.

→ Bulk user registrations
→ Bulk order processing

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

5: Caching:
    → Reduce repeated DB hits for frequently accessed data.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

6: Pagination:
    → Fetch only the required rows using LIMIT/OFFSET.
    → Avoid returning huge datasets in single API call.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

7: Connection Pooling:
    → Ensure DB connections are pooled (HikariCP in Spring Boot).
    → Reduces overhead of opening/closing connections for every request.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

8: Asynchronous / Parallel Processing:
    → Offload heavy operations to async tasks if real-time processing is not needed.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------