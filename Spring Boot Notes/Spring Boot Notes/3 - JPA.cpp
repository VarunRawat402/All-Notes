-----------------------------------------------------------------------------------------
JPA and HIBERNATE 
-----------------------------------------------------------------------------------------

In JPA :
1: Tables are created automatically using annotations in the model class.
2: No manual DB connection setup in code; Hibernate handles connection through configuration.
3: CRUD operations are performed using predefined methods from JpaRepository.
4: No manual SQL, no manual mapping, no boilerplate code.

---------------------------------------------------------------------------------------------------------------------------------------

Connect Application to the DB:

spring.datasource.url=jdbc:mysql://localhost:3306/office?createDatabaseIfNotExist=true
spring.datasource.username=root
spring.datasource.password=root402
spring.jpa.hibernate.ddl-auto=update

Hibernate DDL Auto (startup behavior):

create - Drops and recreates tables every time
update - Updates schema without dropping data
validate - Validates schema, does not modify
create-drop - Creates on start, drops on shutdown

Dialect:
Tells Hibernate how to generate SQL for the specific database.

Examples:
MySQL: org.hibernate.dialect.MySQL8Dialect
PostgreSQL: org.hibernate.dialect.PostgreSQLDialect

---------------------------------------------------------------------------------------------------------------------------------------

REPOSITORY:
JPA is a specification, so we create a repository interface and extend JpaRepository<Person, Integer>.

Code:
public interface PersonRepository extends JpaRepository<Person,Integer> {
    
}

---------------------------------------------------------------------------------------------------------------------------------------

@Entity
public class Person {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
}

@GeneratedValue:
    Automatically generates values for the primary key.

GenerationType.AUTO :
Hibernate decides the best strategy for each DB
Good for batch insertions 
Good when you have different type of DB

GenerationType.IDENTITY: 
Database  generates the ID.
Each table maintains its own auto-increment sequence.
No batch insertions
Good when you have one type of DB

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
Definition:
1 record in Table A is associated with exactly 1 record in Table B.
Example: 1 student has 1 ID card.

@OneToMany (One-to-Many Relationship)
Definition:
1 record in Table A is associated with multiple records in Table B.
Example: 1 order has multiple items.

@ManyToOne (Many-to-One Relationship)
Definition:
Multiple records in Table A are linked to 1 record in Table B.
Example: Many items belong to 1 order.

@ManyToMany (Many-to-Many Relationship)
Definition:
Multiple records in Table A are linked to multiple records in Table B.
Example: 1 student can belong to multiple departments, and 1 department can have multiple students.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@JoinColumm : 
    Creates and used on the foreign key column in the table
    Represents the owning side of the relationship.
    
mappedBy = "user" :  
    Tells JPA which feild is the foreign key in other table
    java variable name is used not database column name
    Represents the inverse / non-owning side

Code:

class Student {             // Owning side

    private Long id;
    private String name;

    @ManyToOne
    @JoinColumn(name = "department_id")     // FK in Student table
    private Department department;
}

class Department {          // Non-owning side

    private Long id;
    private String name;

    @OneToMany(mappedBy = "department", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private List<Student> students;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade Types:

CascadeType.ALL     - Applies all operations: Persist, Merge, Remove, Refresh, Detach
CascadeType.PERSIST - Saves child when parent is saved
CascadeType.MERGE   - Updates child when parent is updated
CascadeType.REMOVE  - Deletes child when parent is deleted
CascadeType.DETACH  - Detaches child from persistence context

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade:

cascade will always be added on the saving side
If you are saving student and want user to be saved automatically then you need to add cascade in student entity at user attribute
If you are saving user and want student to be saved automatically then you need to add cascade in user entity at student attribute

Ex:
public class User{

    private int id;
    private String username;
    private String password;
    private List<String> roles = new ArrayList<>();
}

public class Student {

    private int id;
    private String name;
    private int age;

    @OneToOne(cascade = CascadeType.PERSIST)    //cascade is in the student entity because we are saving student and want user to be saved automatically
    @JoinColumn
    private User user;

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching:

Lazy Fetching:

Do not load related data until it is actually accessed.
Used when the related data is big or not always needed.
JPA loads only the main entity

Eager Fetching:

Load related data immediately, along with the main entity.
Used when the related data is always required (but used rarely in practice).

------------------------------------------------------------------------------------------------------------------------------------------------------------------------