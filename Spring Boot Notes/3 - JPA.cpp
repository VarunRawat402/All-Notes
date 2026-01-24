-----------------------------------------------------------------------------------------
JPA and HIBERNATE 
-----------------------------------------------------------------------------------------

Connecting Spring Boot to Database:

spring.datasource.url=jdbc:mysql://localhost:3306/office?createDatabaseIfNotExist=true
spring.datasource.username=root
spring.datasource.password=root402
spring.jpa.hibernate.ddl-auto=update

Hibernate DDL Auto (startup behavior):
create          - Drops + recreates tables every startup
update          - Updates schema, keeps old data
validate        - Only checks schema, no changes
create-drop     - Create on start, drop on shutdown

Production: usually validate or none
Development: update

---------------------------------------------------------------------------------------------------------------------------------------

REPOSITORY:
    Interface that gives CRUD + query methods.

CrudRepository              → basic CRUD
PagingAndSortingRepository  → pagination
JpaRepository               → CRUD + pagination + JPA features

Code:
public interface PersonRepository extends JpaRepository<Person,Integer> {
}

---------------------------------------------------------------------------------------------------------------------------------------

@Entity
public class Person {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
}

GenerationType.AUTO :
    → Hibernate chooses best strategy (DB independent)
    → Good when you have different type of DB

GenerationType.IDENTITY: 
    → DB generates ID (MySQL auto_increment)
    → Best when using single DB

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
JPA Relationships:-
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Jpa relationships are used to connect 2 entities
    Automatically Handle foreign keys
    Cascade operations
    Lazy Loading
    Reducing Boilerplate code

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@OneToOne (One-to-One Relationship)
    1 entity ↔ 1 entity
    Example: 1 user has 1 profile.

@OneToMany (One-to-Many Relationship)
    One → many
    Example: 1 customer can have many orders.

@ManyToOne (Many-to-One Relationship)
    Many → one
    Example: Many orders belong to 1 customer.

@ManyToMany (Many-to-Many Relationship)
    Many ↔ many
    Uses join table
    Avoid in real projects → prefer separate entity
    Example: A student can enroll in many courses, and a course can have many students.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@JoinColumm : 
    Creates foreign key column
    Represents the owning side
    
mappedBy = "user" :  
    Tells JPA which feild is the foreign key in other table
    java variable name is used not database column name
    Represents the non-owning side

Code:
class Student {                 // Owning side

    @Id
    private Long id;

    @ManyToOne
    @JoinColumn(name = "department_id")
    private Department department;
}

class Department {              // Non-owning side

    @Id
    private Long id;

    @OneToMany(mappedBy = "department",cascade = CascadeType.ALL,fetch = FetchType.LAZY)
    private List<Student> students;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade Types:

CascadeType.ALL     - All operations
CascadeType.PERSIST - Saves child when parent saved
CascadeType.MERGE   - Updates child when parent updated
CascadeType.REMOVE  - Deletes child when parent deleted
CascadeType.DETACH  - Detach child from persistence context

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade:
    cascade will always be added on the saving side
    If you are saving student and want user to be saved automatically then you need to add cascade in student entity at user attribute
    If you are saving user and want student to be saved automatically then you need to add cascade in user entity at student attribute

Ex:
public class Student {

    private int id;
    private String name;
    private int age;

    @OneToOne(cascade = CascadeType.PERSIST)    //User will be saved automatically when saving student
    @JoinColumn
    private User user;

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching:

Lazy Fetching:
    Loads related data only when accessed
    Better performance
    Used in real projects

Eager Fetching:
    Loads related data immediately
    Can cause performance issues
    Avoid unless necessary

------------------------------------------------------------------------------------------------------------------------------------------------------------------------