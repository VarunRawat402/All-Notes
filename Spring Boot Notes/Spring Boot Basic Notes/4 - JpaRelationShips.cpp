------------------------------------------------------------------------------------------------------------------------------------------------------------------------
JPA Relationships:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

JPA allows creating relationships between tables using annotations. 
These relationships are based on primary key → foreign key mappings.

JPA supports four types of relationships:

One-to-One (@OneToOne)
One-to-Many (@OneToMany)
Many-to-One (@ManyToOne)
Many-to-Many (@ManyToMany)

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
    Represents the owning side of the relationship.
    Specifies the foreign key column in the owning entity table.

mappedBy = :  represents the inverse side
    Used on the non-owning side.
    Points to the Java variable name of the owning side, not the database column name.

Code:
@Entity
class Department {          // Non-owning side

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @OneToMany(mappedBy = "department", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private List<Student> students;
}

@Entity
class Student {             // Owning side

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @ManyToOne
    @JoinColumn(name = "department_id")     // FK in Student table
    private Department department;
}


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade Types:

CascadeType.ALL - Applies all operations: Persist, Merge, Remove, Refresh, Detach
CascadeType.PERSIST - Saves child when parent is saved
CascadeType.MERGE - Updates child when parent is updated
CascadeType.REMOVE - Deletes child when parent is deleted
CascadeType.DETACH - Detaches child from persistence context

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade:

cascade will always be added on the saving side
If you are saving student and want user to be saved automatically then you need to add cascade in student entity at user attribute
If you are saving user and want student to be saved automatically then you need to add cascade in user entity at student attribute

Ex:

public class User{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String username;
    private String password;

    private List<String> roles = new ArrayList<>();
}

public class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
    private int age;

    @OneToOne(cascade = CascadeType.PERSIST)    //cascade is in the student entity because we are saving student and want user to be saved automatically
    @JoinColumn
    private User user;

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching:
    JPA fetches related data in two ways:

Lazy Fetching (FetchType.LAZY) - Data is loaded only when needed (on demand).
Eager Fetching (FetchType.EAGER) - Data is always loaded immediately (at query time).


Lazy Fetching:
    Child data is loaded only when accessed.
    Default for most relationships (OneToMany, ManyToMany).

Code:
    System.out.println(dept.getName());             // Only Department is fetched.
    System.out.println(dept.getStudents());         // Students are loaded now.


Eager Fetching:
    Related data is loaded immediately with the parent.
    Default for @ManyToOne and @OneToOne.

Code:

System.out.println(student.getName());     // Student + IDCard loaded together.
System.out.println(student.getIdCard());   // Already fetched.


------------------------------------------------------------------------------------------------------------------------------------------------------------------------