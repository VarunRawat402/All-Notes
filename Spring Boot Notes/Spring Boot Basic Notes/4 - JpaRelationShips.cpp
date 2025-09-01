------------------------------------------------------------------------------------------------------------------------------------------------------------------------
JPA Relationships:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

JPA (Java Persistence API) allows defining relationships between database tables using annotations.
These relationships are based on primary keys and foreign keys.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

JPA supports four types of relationships:

One-to-One (@OneToOne)
One-to-Many (@OneToMany)
Many-to-One (@ManyToOne)
Many-to-Many (@ManyToMany)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@OneToOne (One-to-One Relationship)
Definition:
Each record in Table A is associated with exactly one record in Table B.
Example: 1 student has only 1 ID card.

@OneToMany (One-to-Many Relationship)
Definition:
One record in Table A is linked to multiple records in Table B.
Example: 1 Department has multiple Students.

@ManyToOne (Many-to-One Relationship)
Definition:
Many records in Table A are associated with one record in Table B.
Example: Many students belong to 1 department.

@ManyToMany (Many-to-Many Relationship)
Definition:
Multiple records in Table A are linked to multiple records in Table B.
Example: Students can enroll in multiple courses, and each course can have multiple students.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@JoinColumm : represents the owning side and foreign key
mappedBy = :  represents the inverse side
    always give the java attribute name in mappedBy not the mysql table name 

Code:
@Entity
class Department {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @OneToMany(mappedBy = "department", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private List<Student> students
}

@Entity
class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @ManyToOne
    @JoinColumn(name = "department_id")  // Foreign Key in Student table
    private Department department;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cascade Types:
CascadeType.ALL	    :   Applies all operations (Persist, Merge, Remove, Refresh, Detach).
CascadeType.PERSIST	:   Saves child entities when the parent is saved.
CascadeType.MERGE	:   Updates child entities when parent is updated.
CascadeType.REMOVE	:   Deletes child entities when parent is deleted.
CascadeType.DETACH	:   Detaches child entities from persistence context.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching:
When working with JPA relationships data can be fetched in two ways:
Lazy Fetching (FetchType.LAZY) - Data is loaded only when needed (on demand).
Eager Fetching (FetchType.EAGER) - Data is always loaded immediately (at query time).


Lazy Fetching:
    Students are loaded from the database only when dept.getStudents() is called.

Code:
    Department dept = entityManager.find(Department.class, 1L);

    System.out.println(dept.getName()); // ✅ Only Department data is fetched. ❌ Students are NOT loaded yet.
    System.out.println(dept.getStudents());      // Now Hibernate fetches students from the database.


Eager Fetching:
    ID Card is automatically loaded with the Student.

Code:
    Student student = entityManager.find(Student.class, 1L);

    System.out.println(student.getName()); // ✅ Student data is fetched and ID Card is also fetched automatically.
    System.out.println(student.getIdCard()); // ✅ ID Card is already fetched.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------