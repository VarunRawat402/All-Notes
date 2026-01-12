------------------------------------------------------------------------------------------------------------------------------------------------------------
NORMALIZATION:
    Normalization is the process of organizing data in a database to reduce 
    1: Reduce redundancy (avoid duplicate data)
    2: Improve data integrity (ensure accuracy and consistency)

------------------------------------------------------------------------------------------------------------------------------------------------------------

1NF:
    Each column must contain a single value, not a list or set of values.
    Each row is unique (primary key required).
    Columns contain values of the same type.

--Violates 1NF
-- Courses column has multiple values → not atomic
Ex:
    StudentID	StudentName	    Courses
    101	        Alice	        Math, Physics   
    102	        Bob	            English, Chemistry


--Fixed
--Primary Key ( StudentId + Course )
Correct:
    StudentID	    StudentName	        Course
    101	            Alice	            Math
    101	            Alice	            Physics
    102	            Bob	                English
    102	            Bob	                Chemistry

------------------------------------------------------------------------------------------------------------------------------------------------------------

2NF:
    Already 1NF.
    No partial dependency, This means all non-key columns must depend on entire primary key.
    If your primary key is single column then its already 2NF, It is done for tables that have composite primary keys

--Violates 2NF
StudentID (PK)	        Course (PK)	            StudentName	            Instructor	        InstructorOffice
101	                    Math	                Alice	                Dr. Smith	            Room 101
101	                    Physics	                Alice	                Dr. Jones	            Room 202
102	                    English	                Bob	                    Prof. Davis	            Room 303
102	                    Chemistry	            Bob	                    Dr. Brown	            Room 404

Partial dependency:

StudentName depends only on StudentID
StudentName is alice weather she is taking maths or physics it depends on ID only not course

Instructor and InstructorOffice depend only on Course
Dr smith will teach in room 101 only if course is math it does not depend on StudentID

Both have partial dependency on Primary key 

--Fixed
    Divide this main table into 2 smaller tables student & course
    Make third table to connect them using primary keys

Table 1: Students
    StudentID (PK)	    StudentName
    101	                Alice
    102	                Bob

Table 2: Courses

    Course (PK)	        Instructor	    InstructorOffice
    Math	            Dr. Smith	        Room 101
    Physics	            Dr. Jones	        Room 202
    English	            Prof. Davis	        Room 303
    Chemistry	        Dr. Brown	        Room 404

Table 3: Enrollment (the junction table that connects them)

    StudentID (PK/FK)	    Course (PK/FK)
    101	                     Math
    101	                     Physics
    102	                     English
    102	                     Chemistry

------------------------------------------------------------------------------------------------------------------------------------------------------------

3NF:
    Already 2NF.
    No transitive dependency. non-key columns must depend only on the primary key, not on other non-key columns.
    All non-key attributes must depend only on the primary key.

InstructorOffice depends on Instructor, not Course
Changing office would require updating multiple rows → violates 3NF

Table 1: Courses (now simplified)

Course (PK)	        InstructorID (FK)
    Math	                1
    Physics	                2

Table 2: Instructors (new table)

InstructorID (PK)	    Instructor	        InstructorOffice
    1	                Dr. Smith	        Room 101
    2	                Dr. Jones	        Room 202

Now InstructorOffice depends on the primary key InstructorID
To change the office of any Instructor, we only need to change it one time in the Instructor Table

------------------------------------------------------------------------------------------------------------------------------------------------------------

First Normal Form (1NF)
    Each column should contain single value.
    If a column has multiple values, split them into separate rows so that every cell holds only one value.

Second Normal Form (2NF)
    Must already satisfy 1NF.
    Every non-key column must depend on the whole primary key, not just part of it.
    If the table has a composite primary key, separate the data into multiple tables so that each non-key column fully depends on the entire primary key.
    Often involves creating two tables and a relation table connecting them.

Third Normal Form (3NF)
    Must already satisfy 2NF.
    Non-key column should depend only on the primary key and not on another non-key column.
    If a non-key column depends on another non-key column, move it to a separate table and link it using a foreign key.

------------------------------------------------------------------------------------------------------------------------------------------------------------