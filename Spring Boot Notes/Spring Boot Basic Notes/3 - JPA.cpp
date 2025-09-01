---------------------------------------------------------------------------------------------------------------
Spring Boot ( JDBC, JPA, H2, HIBERNATE ):
---------------------------------------------------------------------------------------------------------------

SQL properties file ( queries.sql ):
Location : same folder as application.properties is in

Jpa picks up this folder and run all the sql queries in it as soon as the application starts
    Ex:
    create table Student(
        id int not null,name varchar(255) not null,course varchar(255) not null,primary key(id)
    );

---------------------------------------------------------------------------------------------------------------

H2:
H2 is an in-memory, embedded relational database that is often used for development and testing.
It allows developers to work with a lightweight database without setting up an external DBMS like MySQL or PostgreSQL.

---------------------------------------------------------------------------------------------------------------

Spring JDBC:
JDBC (Java Database Connectivity) in Spring Boot allows interaction with relational databases using standard SQL queries.
Unlike Spring Data JPA, which uses ORM (like Hibernate), JDBC gives you direct control over SQL execution.
In JDBC you have to write manual sql queries and functions to perform CRUD Operations.

Dependencies:
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-jdbc</artifactId>
    </dependency>

Application.properties:
    spring.h2.console.enabled=true                      //to enable h2 database
    spring.datasource.url=jdbc:h2:mem:testdb            //To make the custom url to access h2 db

---------------------------------------------------------------------------------------------------------------

JDBC Practice Code:

@Repository
public class JDBCRespository {

    @Autowired
    private JdbcTemplate jdbcTemplate;
    private static String insertq = """
          insert into Student(id,name,course) values(?,?,?);""";
    private static String selectq = """
           select * from student where id = ?""";

    public void insertQuery(Student student){
        jdbcTemplate.update(insertq,student.getId(),student.getName(),student.getCourse());
    }
    public Student selectQuery(int id){
        return jdbcTemplate.queryForObject(selectq,
                new BeanPropertyRowMapper<>(Student.class),id);
    }
}

---------------------------------------------------------------------------------------------------------------

JPA:
It is a specification or interface that defines how java objects can be stored, retrieved and managed in relational DB
Its a set of rules, Does not provide implementation

Hibernate:
It is an ORM, object relational mapping which implements the JPA Interface
Converts java objects to tables automatically, removes JDBC boiler plate code		
Supports advanced features like lazy loading, caching, criteria queries, transaction management.		


Code:
@Repository
@Transactional
public class JpaRepository {


    @Autowired
    EntityManager entityManager;

    public void insert(Student student){
        entityManager.merge(student);
    }
    public Student findById(int id){
        return entityManager.find(Student.class,id);
    }
    public void deleteById(int id){
        Student student = entityManager.find(Student.class,id);
        entityManager.remove(student);
    }

}

---------------------------------------------------------------------------------------------------------------
