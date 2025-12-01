-----------------------------------------------------------------------------------------
Lecture 4: Spring Boot with JPA and HIBERNATE 1
-----------------------------------------------------------------------------------------

In JPA :
1: Tables are created automatically using annotations in the model class.
2: No manual DB connection setup in code; Hibernate handles connection through configuration.
3: CRUD operations are performed using predefined methods from JpaRepository.
4: No manual SQL, no manual mapping, no boilerplate code.

---------------------------------------------------------------------------------------------------------------------------------------

How To connect application to the DB:

spring.datasource.url=jdbc:mysql://localhost:3306/office?createDatabaseIfNotExist=true
spring.datasource.username=root
spring.datasource.password=root402

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
Person → entity class
Integer → type of primary key

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

---------------------------------------------------------------------------------------------------------------------------------------