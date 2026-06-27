-----------------------------------------------------------------------------------------------------------------------------------------------------
JPA:
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

Types of REPOSITORY:
    
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

Why @Repository annotation is not needed in JpaRepository Interface;

→ Spring Data automatically scans the JpaRepository Interface 
→ It automatically creates a bean for them at startup so no need to use the annotation
→ Converts DB exceptions to Spring Exception so we dont need to take care of vendor specific exception like Hibernate or EclipsLink

-----------------------------------------------------------------------------------------------------------------------------------------------------
JPA Relationships:-
-----------------------------------------------------------------------------------------------------------------------------------------------------

@OneToOne (One-to-One Relationship)
    → Example: 1 Student has 1 Library Card

@OneToMany (One-to-Many Relationship)
    → Example: 1 Student has many Books

@ManyToOne (Many-to-One Relationship)
    → Example: Many Books belong to 1 Student
    → Usually paired with @OneToMany on other side

@ManyToMany (Many-to-Many Relationship)
    → Example: Student ↔ Courses ( one student many courses, one course many )
    → Avoid in real projects → prefer separate entity
    → Uses a join table in DB


-----------------------------------------------------------------------------------------------------------------------------------------------------

@JoinColumm : 
    → Represents the owning side
    → This table contains the foreign key column of another table 
    
mappedBy = "user" :  
    → Represents the non-owning side
    → user is the name of the feild in the owning side
    → Java variable name is used not database column name
    

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

    @OneToMany(mappedBy = "department",fetch = FetchType.LAZY)
    private List<Student> students;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------
Fetching:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Lazy Fetching:
    → Load related data only when you actually access it.
    → Better performance

Example:
    // SELECT * FROM users WHERE id = 1  ← only this
    User user = userRepo.findById(1);
    
    // SELECT * FROM orders WHERE user_id = 1
    user.getOrders(); // NOW orders SQL fires

-----------------------------------------------------------------------------------------------------------------------------------------------------

Eager Fetching:
    → Load everything immediately
    → Can cause performance issues
    → Avoid unless necessary

Example:
    // SELECT * FROM users WHERE id = 1
    // SELECT * FROM orders WHERE user_id = 1  ← fired immediately too
    User user = userRepo.findById(1);

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