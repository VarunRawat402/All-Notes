-----------------------------------------------------------------------------------------------------------------------------------------------------
JPA and HIBERNATE :
-----------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot Application Connection to Database:

spring.datasource.url=jdbc:mysql://localhost:3306/office?createDatabaseIfNotExist=true
spring.datasource.username=root
spring.datasource.password=root402
spring.jpa.hibernate.ddl-auto=update

Hibernate DDL Auto (startup behavior):
1: create          → Drops + recreates tables every startup
2: update          → Updates schema, keeps old data
3: validate        → Only checks schema, no changes
4: create-drop     → Create on start, drop on shutdown

→ Production: usually validate or none
→ Development: update

-----------------------------------------------------------------------------------------------------------------------------------------------------

REPOSITORY:
    → Interface that gives CRUD + query methods.
    
1: CrudRepository:
    → Basic CRUD methods
    → save(), findById(), findAll(), delete(), count()

2: PagingAndSortingRepository:
    → Extends CrudRepository
    → CRUD + Pagination + Sorting
    → findAll(Sort sort), findAll(Pageable pageable)

3: JpaRepository:
    → Extends PagingAndSortingRepository
    → CRUD + Pagination + JPA features
    → flush(), saveAndFlush(), deleteInBatch(), getOne() (lazy fetch)

Code:
public interface PersonRepository extends JpaRepository<Person,Long>{}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why @Repository is not needed in JpaRepository Interface;

→ Spring Data automatically scans the JpaRepository Interface 
→ Creates a proxy implementation class at runtime
→ Register it as a spring bean
→ Converts JPA Exception to Spring Exception so we dont need to take care of vendor specific exception like Hibernate or EclipsLink

-----------------------------------------------------------------------------------------------------------------------------------------------------
JPA Relationships:-
-----------------------------------------------------------------------------------------------------------------------------------------------------

@OneToOne (One-to-One Relationship)
    → 1 entity ↔ 1 entity
    → Example: 1 user has 1 profile.

@OneToMany (One-to-Many Relationship)
    → One ↔ many
    → Example: 1 customer can have many orders.

@ManyToOne (Many-to-One Relationship)
    → Many ↔ one
    → Example: Many orders belong to 1 customer.

@ManyToMany (Many-to-Many Relationship)
    → Many ↔ many
    → Uses join table
    → Avoid in real projects → prefer separate entity
    → Example: A student can enroll in many courses, and a course can have many students.

-----------------------------------------------------------------------------------------------------------------------------------------------------

@JoinColumm : 
    → Creates foreign key column
    → Represents the owning side
    
mappedBy = "user" :  
    → user is the name of the feild in the owning side
    → Java variable name is used not database column name
    → Represents the non-owning side

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

Fetching:

Lazy Fetching:
    → Loads related data only when accessed
    → Better performance

Eager Fetching:
    → Loads related data immediately
    → Can cause performance issues
    → Avoid unless necessary

-----------------------------------------------------------------------------------------------------------------------------------------------------

Cascade Types:

1: CascadeType.ALL      → All operations
2: CascadeType.PERSIST  → Saves child when parent saved
3: CascadeType.MERGE    → Updates child when parent updated
4: CascadeType.REMOVE   → Deletes child when parent deleted
5: CascadeType.DETACH   → Detach child from persistence context

-----------------------------------------------------------------------------------------------------------------------------------------------------

Cascade:
    → Cascade will always be added on the saving side
    → If you are saving student and want user to be saved automatically then you need to add cascade in student entity at user attribute
    → If you are saving user and want student to be saved automatically then you need to add cascade in user entity at student attribute

Ex:
public class Student {

    private int id;
    private String name;
    private int age;

    @OneToOne(cascade = CascadeType.PERSIST)    //User will be saved automatically when saving student
    @JoinColumn
    private User user;

}

-----------------------------------------------------------------------------------------------------------------------------------------------------