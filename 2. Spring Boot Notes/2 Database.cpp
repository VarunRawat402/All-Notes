-----------------------------------------------------------------------------------------------------------------------------------------------------
( JDBC, JPA, H2, HIBERNATE ):
-----------------------------------------------------------------------------------------------------------------------------------------------------

H2:
    → H2 is an in-memory, mainly used for development and testing.

-----------------------------------------------------------------------------------------------------------------------------------------------------

JDBC:
    → Used to interact with databases using SQL queries.
    → You manually write SQL for CRUD operations.
    → JDBC gives full control over SQL queries unlike JPA which autogenerates SQL.

Dependencies:
    → spring-boot-starter-jdbc

Application.properties:
spring.h2.console.enabled=true                 // enable H2 UI
spring.datasource.url=jdbc:h2:mem:testdb       // custom H2 DB URL

-----------------------------------------------------------------------------------------------------------------------------------------------------

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
        jdbcTemplate.update(insertq, student.getId(), student.getName(), student.getCourse());
    }

    public Student selectQuery(int id) {
        return jdbcTemplate.queryForObject(selectq, new BeanPropertyRowMapper<>(Student.class), id);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

JPA:
    → It is a specification that defines how java objects are mapped to database.
    → It only provides interfaces and rules, not the implementation.

Hibernate:
    → It is an ORM framework that implements JPA.
    → Converts java objects to tables automatically, removes JDBC boiler plate code		
    → Supports features like lazy loading, caching, criteria API, transaction management, etc.	

-----------------------------------------------------------------------------------------------------------------------------------------------------