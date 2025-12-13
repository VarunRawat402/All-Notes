------------------------------------------------------------------------------------------------------------------------------------------------------------
DBMS:
------------------------------------------------------------------------------------------------------------------------------------------------------------

RDBMS: 
    ( MYSQL, PostgreSQL, ORACLE, SQLSERVER )

NOSQL DBMS: 
    ( MongoDB, Cassandra, DynamoDB )

In Memory DB: 
    ( Redis, Memcached )

Types of SQL Commands: 
    ( DDL, DML, DCL, TCL )

------------------------------------------------------------------------------------------------------------------------------------------------------------

1. DDL - Data Definition Language:
    It deals with structure of the Database like Table, Column, Type etc but not actual data

    CREATE   :    make a new table, database, view, etc.
    ALTER    :    modify structure (add column, change datatype).
    DROP     :    delete a table, database, etc.
    TRUNCATE :    remove all rows but keep structure.

2. DML - Data Manipulation Language:
    It deals with the actual data like information of the employees

    INSERT :    add new rows.
    UPDATE :    change existing rows.
    DELETE :    remove rows.
    SELECT :    retrieve data (sometimes called DRL - Data Retrieval Language).

3. DCL - Data Control Language:
    It Deals with permissions & access control.

    GRANT :     give privileges to user.
    REVOKE :    take back privileges.

4. TCL - Transaction Control Language:
    It Deals with transactions in the database.

    COMMIT      :   save changes permanently.
    ROLLBACK    :   undo changes.
    SAVEPOINT   :   set a checkpoint to roll back to.

------------------------------------------------------------------------------------------------------------------------------------------------------------

Database:
A database is an organized collection of data stored electronically so it can be easily accessed, managed, and updated.

Schema
A schema is the structure that defines how the data is organized or stored in a database
It tells what tables exist, what columns they have, and how they relate.

Example: 
    In SchoolDB, the schema may define:
    A Students table with columns (student_id, name, age)
    A Courses table with columns (course_id, course_name)

Table:
    A table is a collection of related data in rows and columns inside a database.

Column:
    A column is a vertical field in a table that stores a specific type of data for all rows
    Each column is an attribute of the entity
    Ex: Name, Age, Id, Salary

Row:
    A row represents a single entry of data in a table.
    One row represents actual values of one entity
    Ex: Values of Name, Age, Id, Salary

Primary Key:
    A primary key is a special column that uniquely identifies each row or entry in a table.
    Must Be unique
    Cannot be NULL
    Ex: student_id, employee_id, course_id

Foreign Key:
    A foreign key is a column in one table that refers to the primary key in another table.
    It creates a relationship between two tables, ensuring referential integrity

------------------------------------------------------------------------------------------------------------------------------------------------------------

Common SQL Constraints:

Unique:
    All values should be unique
    Values can be NULL
    CREATE TABLE Users ( user_id INT PRIMARY KEY, email VARCHAR(100) UNIQUE );

NOT NULL:
    Values cannot be NULL
    CREATE TABLE Employees ( emp_id INT PRIMARY KEY, name VARCHAR(50) NOT NULL );

CHECK:
    It is a condition 
    Every value should satisfy the condition
    CREATE TABLE Products ( product_id INT PRIMARY KEY, price DECIMAL CHECK (price > 0) );

Default:
    It takes a value    
    If value is not given it will take default one
    CREATE TABLE Orders ( order_id INT PRIMARY KEY, status VARCHAR(20) DEFAULT 'Pending' );

AUTO_INCREMENT:
    Automatically generates a unique number 
    CREATE TABLE Customers ( customer_id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50) );

------------------------------------------------------------------------------------------------------------------------------------------------------------

