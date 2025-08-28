-----------------------------------------------------------------------------------------
Lecture 4: Spring Boot with JPA and HIBERNATE 1
-----------------------------------------------------------------------------------------

Without JPA:
1: We made a model class Person and store the details of the person in the Person object.
2: Then we made a connection to the DB using DBConfig File.
3: Then in Repository we will create table by writing manual sql queries and store the details of the person in the DB table
    using the person object with the help of preparedStatement and statement.

In JPA :
1: We will create table in DB using annotation in the model class rather than creating by writing manual sqls.
2: We will not make connection to connect to the database instead we will use hibernate commands to connect to the db.
3: We will store the details of the person using pre defined functions given by JPA Repository in the service class.
4: With the help of JPA we dont need to write manual sql queries / Map data manually / and create basic functions.

---------------------------------------------------------------------------------------------------------------------------------------

@Entity: 
It is used on top of the class and to tell the hibernate to create a table of this class in the DB.
Every Attribute in the model class will become the column.

@Transient: 
It is used on top of that attribute which we dont want as column in our DB.

HikaryPool: 
It is a pool which is used by Hibernate to communicate with the internal DB.

@Id: 
It is used on top of that attribute which we have to make primary key in DB.
It is mandatory because in order to map with Hibernate we have to define the primary key.

@Column: 
It is used to change the name of the column and set the values like size of the attribute
Ex- column(length = 30) -> varchar(30)

@Table: It is used to change the properties like name of table in DB.

Note:
    This is present in JPA and not in hibernate because If the developer wants to use other frameworks
    instead of hibernate then we will not be able to use this annotation so that is why it is 
    present in the JPA.
    Hibernate converts the camelcase structure of attributes to the underscore structure automatically.
    Ex - firstName will be first_Name

---------------------------------------------------------------------------------------------------------------------------------------

How To connect application to the DB:

To connect to the mysql DB:
    spring.datasource.url = jdbc:mysql://localhost:3306/office?createDatabaseIfNotExist=true

Username & password of mysql:
    spring.datasource.username = root
    spring.datasource.password = root402

To manage how DB operates on startup:
    It has 4 modes : create, update, validate, create-drop
    spring.jpa.hibernate.ddl-auto = update

Note:
Dialect: A dialect is used to tell the hibernate/jpa how to generate SQL queries as different databases uses different dialects
Ex:  
MySQL      -    org.hibernate.dialect.MySQL8Dialect
PostgreSQL -	org.hibernate.dialect.PostgreSQLDialect

---------------------------------------------------------------------------------------------------------------------------------------

REPOSITORY:
JPA is an interface and to use JPA We need to make the Repository interface and extends it with JpaRepository<Person,Integer>
where Person is the class whose object we will be saving and Integer is the datatype of the primary key of that class.

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

@GeneratedValue: It is used to automatically generate the value of the Id.

It has 2 types:
GenerationType.AUTO : In this hibernate will generate the id for me 
In this there is a common table hibernate_sequence where after every insertion id is incremented by 1 and 
given to tables ID.

But Lets say there are 2 tables and so if we insert in those 2 tables alternatively then the table id will look
like 
person - 1 3 5 7
author - 2 4 6 8
hibernate_sequence - 1 2 3 4 5 6 7 8 

GenerationType.IDENTITY: In this my DB will generate the id for me like mysql 
In this every table increases his Id by its own so there is no skipping of ID 
even when we insert alternatively.

---------------------------------------------------------------------------------------------------------------------------------------