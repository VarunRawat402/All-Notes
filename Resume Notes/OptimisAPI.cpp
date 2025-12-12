-----------------------------------------------------------------------------------------------------------------------
HOW TO FIX SLOW API:
-----------------------------------------------------------------------------------------------------------------------

Database Query Optimization:

Indexing - "I create indexes on frequently searched or joined columns to speed up lookups."
Efficient Queries - "I avoid SELECT *, fetch only required columns, and use JOINs wisely."
Caching - "I use caching mechanisms like Redis or Hibernate 2nd-level cache to reduce repeated database hits."
Batch Operations - "For bulk inserts/updates, I use batch processing to reduce database round-trips."
Avoid N+1 Problems - "In ORMs like Hibernate, I use JOIN FETCH or eager fetching to prevent multiple queries for related entities."

-----------------------------------------------------------------------------------------------------------------------

1: N+1 Problem DB Query Optimization:
    When we fetch nested entites too we make n+1 queries to the DB
    By default it uses lazy loading, use JPQL to eager loading
    https://chatgpt.com/c/6939f8df-24c4-8320-861b-47816bac3008
    EntityGraph

-----------------------------------------------------------------------------------------------------------------------

2: Avoid select * for DB:
Avoid select * from student when fetching data
fetch only data which is required

Create a studentResponseDTO and fetch only data required by ResponseDTO
It will return StudentDTO directly
@Query("SELECT new com.example.dto.StudentDTO(s.name, s.age) FROM Student s")
List<StudentDTO> getStudentBasicInfo();

-----------------------------------------------------------------------------------------------------------------------

3: Indexing:
An index creates a B-tree structure that allows the database to locate matching rows directly using logarithmic search instead of full table scanning.
It stores all the values in the sorted way with row number.

Create index on user email:

Mysql Way:

CREATE INDEX idx_user_email ON users(email);                    //Index of 1 col
CREATE INDEX idx_user_name_status ON users(name, status);       //Index of multiple col

SB Annotation Way:
@Table(
    indexes = {
        @Index(name = "idx_email", columnList = "email"),
        @Index(name = "idx_name_status", columnList = "name,status")
    }
)
public class User

Indexing makes queries like this fast:
SELECT * FROM users WHERE email = 'test@gmail.com';                 //use single index
SELECT * FROM users WHERE name='John' AND status='ACTIVE';          //use composite index

Explanation:

Without index:
Reads every row and check if email = "test@gmail.com";
(logn)

With index:

Instead of scanning every row, it does:
Jump to mid-point of tree, Compare value
Go left or right, Repeat until found
On found, gets the row number and returns it
Time complexity becomes: O(log N)

-----------------------------------------------------------------------------------------------------------------------

4: Batch Operations - "For bulk inserts/updates, I use batch processing to reduce database round-trips."

-----------------------------------------------------------------------------------------------------------------------

