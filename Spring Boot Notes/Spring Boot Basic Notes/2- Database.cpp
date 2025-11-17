---------------------------------------------------------------------------------------------------------------
Spring Boot ( JDBC, JPA, H2, HIBERNATE ):
---------------------------------------------------------------------------------------------------------------

H2:
    H2 is an in-memory, embedded relational database, mainly used for development and testing.
    It provides a lightweight, quick setup database without installing MySQL or PostgreSQL.

---------------------------------------------------------------------------------------------------------------

Spring JDBC:
    JDBC (Java Database Connectivity) allows interacting with relational databases using raw SQL queries.
    You manually write SQL for CRUD operations.
    Unlike Spring Data JPA (which uses Hibernate and ORM), JDBC gives full control over SQL.

Dependencies:
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-jdbc</artifactId>
    </dependency>

Application.properties:
spring.h2.console.enabled=true                 // enable H2 UI
spring.datasource.url=jdbc:h2:mem:testdb       // custom H2 DB URL

---------------------------------------------------------------------------------------------------------------

JDBC Practice Code:

@Repository
public class JDBCRepository {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    private static String insertq = """
        insert into Student(id,name,course) values(?,?,?)
    """;

    private static String selectq = """
        select * from student where id = ?
    """;

    public void insertQuery(Student student) {
        jdbcTemplate.update(insertq,
                student.getId(),
                student.getName(),
                student.getCourse());
    }

    public Student selectQuery(int id) {
        return jdbcTemplate.queryForObject(
                selectq,
                new BeanPropertyRowMapper<>(Student.class),
                id);
    }
}


---------------------------------------------------------------------------------------------------------------

JPA:
JPA is a specification that defines how Java objects are mapped to database tables.
It only provides interfaces and rules, not the implementation.

Hibernate:
Hibernate is an ORM framework that implements JPA.
Converts java objects to tables automatically, removes JDBC boiler plate code		
Supports features like lazy loading, caching, criteria API, transaction management, etc.	


@Repository
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

SQL properties file ( queries.sql ):
    Used to run SQL queries automatically at application startup.
    Location : same folder as application.properties is in
    Spring Boot will pick it up (if using JPA + Hibernate + schema initialization enabled).
    Jpa picks up this folder and run all the sql queries in it as soon as the application starts

Ex:
create table Student(
    id int not null,name varchar(255) not null,course varchar(255) not null,primary key(id)
);

---------------------------------------------------------------------------------------------------------------