-----------------------------------------------------------------------------------------
Lecture 4: Spring Boot with JPA and HIBERNATE 1
-----------------------------------------------------------------------------------------

In JPA :
1: Tables are created automatically using annotations in the model class.
2: No manual DB connection setup in code; Hibernate handles connection through configuration.
3: CRUD operations are performed using predefined methods from JpaRepository.
4: No manual SQL, no manual mapping, no boilerplate code.

---------------------------------------------------------------------------------------------------------------------------------------

@Entity: 
Placed on top of the class, Tells Hibernate to create a table for this class.
Each attribute becomes a column.

@Transient: 
Used on fields that should not become database columns.

HikaryPool: 
A fast connection pool used internally by Spring Boot + Hibernate to communicate with the database.

@Id: 
Used to make the attribute as Primary Key of the table.
Mandatory for JPA entities.

@Column: 
Used to customize column properties such as name, length, nullable, etc.
Example: @Column(length = 30) → VARCHAR(30)

@Table:
Used to customize the table name and other table-level properties.

Note:
    These annotations come from JPA, not Hibernate.
    This is because JPA is framework-independent.
    Hibernate automatically converts camelCase into snake_case.
    Example: firstName → first_name

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
Hibernate decides the best strategy.
Uses a global table hibernate_sequence.
IDs are shared across all entities.

But Lets say there are 2 tables and so if we insert in those 2 tables alternatively then the table id will look
like 
person - 1 3 5 7
author - 2 4 6 8
hibernate_sequence - 1 2 3 4 5 6 7 8 

GenerationType.IDENTITY: 
Database (MySQL) generates the ID.
Each table maintains its own auto-increment sequence.
No skipping due to other tables inserting.

---------------------------------------------------------------------------------------------------------------------------------------