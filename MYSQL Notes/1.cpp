------------------------------------------------------------------------------------------------------------------------------------------------------------
DBMS:
------------------------------------------------------------------------------------------------------------------------------------------------------------

RDBMS: 
    Stores data in tables (rows & columns)
    MYSQL, PostgreSQL, ORACLE, SQLSERVER

NOSQL DBMS: 
    Schema-less or flexible schema
    MongoDB (Document), Cassandra (Column), DynamoDB (Key-Value)

In Memory DB: 
    Data stored in RAM instead of disk
    Redis, Memcached 

Types of SQL Commands: 
    DDL, DML, DCL, TCL

------------------------------------------------------------------------------------------------------------------------------------------------------------

1. DDL - Data Definition Language:
Deals with the structure of the database, not the data itself.

CREATE   :    Create table, database
ALTER    :    Modify table structure
DROP     :    Delete table/database
TRUNCATE :    Remove all rows, keep structure

2. DML - Data Manipulation Language:
Deals with actual data inside tables.

INSERT :    Add new rows
UPDATE :    Modify existing rows
DELETE :    Remove rows
SELECT :    Retrieve data

3. DCL - Data Control Language:
Controls permissions and access to database objects.

GRANT :     Give access
REVOKE :    Remove access

4. TCL - Transaction Control Language:
Used to manage transactions

COMMIT      :   Save changes permanently
ROLLBACK    :   Undo changes
SAVEPOINT   :   Roll back to a specific point

------------------------------------------------------------------------------------------------------------------------------------------------------------

Schema:
    Structure of the database

Tables
Columns
Data types
Relationships

Example: 

SchoolDB Schema:
Students(student_id, name, age)
Courses(course_id, course_name)

------------------------------------------------------------------------------------------------------------------------------------------------------------\

Primary Key:
    Uniquely identifies each row
    Must Be unique
    Cannot be NULL

Foreign Key:
    Column that refers to primary key of another table
    Maintains referential integrity

------------------------------------------------------------------------------------------------------------------------------------------------------------

Common SQL Constraints:

Unique:
    Ensures all values are different
    Allows NULL values
    email VARCHAR(100) UNIQUE

NOT NULL:
    Values cannot be NULL
    name VARCHAR(50) NOT NULL

Default:
    Assigns default value if none is provided
    status VARCHAR(20) DEFAULT 'Pending'
    
------------------------------------------------------------------------------------------------------------------------------------------------------------

