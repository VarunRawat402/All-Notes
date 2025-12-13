------------------------------------------------------------------------------------------------------------------------------------------------------------
NORMALIZATION:
    Normalization is the process of organizing data in a database to reduce 
    redundancy (duplicate data) and improve data integrity (make sure your data is accurate and consistent).
------------------------------------------------------------------------------------------------------------------------------------------------------------

1NF:
    It only contains atomic (indivisible) values. Each cell must contain a single value, not a list or set of values.
    It has a unique primary key to identify each row.
    Each column contains data of the same type.

    Ex:
        StudentID	StudentName	    Courses
        101	        Alice	        Math, Physics   
        102	        Bob	            English, Chemistry

    In this Alice and bob has 2 courses which makes the queries like 'Find all students with course = physics'
    It violates the atomic value rule 

    We fix it by having single value of course by allowing different records with same StudentID
    Primary key will be ( StudentId + Course )
    Correct:
        StudentID	    StudentName	        Course
        101	            Alice	            Math
        101	            Alice	            Physics
        102	            Bob	                English
        102	            Bob	                Chemistry

------------------------------------------------------------------------------------------------------------------------------------------------------------

2NF:
    It is already in 1NF.
    It has no partial dependency. This means all non-key attributes (columns that arent part of the primary key) must depend on the entire primary key.
    If your primary key is single column then its already 2NF, It is done for tables that have composite primary keys

        StudentID (PK)	        Course (PK)	            StudentName	            Instructor	        InstructorOffice
        101	                    Math	                Alice	                Dr. Smith	            Room 101
        101	                    Physics	                Alice	                Dr. Jones	            Room 202
        102	                    English	                Bob	                    Prof. Davis	            Room 303
        102	                    Chemistry	            Bob	                    Dr. Brown	            Room 404

    Partial dependency:
        StudentName is only dependent on StudentId 
            StudentName is alice weather she is taking maths or physics it depends on ID only not course
        
        Instructor and InstructorOffice is only dependent on course
            Dr smith will teach in room 101 only if course is math it does not depend on StudentID
        
        Both have partial dependency on Primary key 

    Correct:
        Divide this main table into 2 smaller tables student & course
        Make third table to join them

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
    It is already in 2NF.
    It has no transitive dependency. This means no non-key attribute should depend on another non-key attribute. 
    All non-key attributes must depend only on the primary key.

    In Previous 2NF courses table, InstructorOffice depends on instructor not course
    Dr smith will teach in room101 everytime irrespective of the course
    If Dr smith room changes to 105, Then we need to update every record which contains Dr smith

    Remove that attribute to its own table

        Table 1: Courses (now simplified)

            Course (PK)	        nstructorID (FK)
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
Each column must contain single, atomic values.
Each row must be unique.
If a column has multiple values, split them into separate rows so that every cell holds only one value.

Second Normal Form (2NF)
Must already satisfy 1NF.
Every non-key column must depend on the whole primary key, not just part of it.
If the table has a composite primary key, separate the data into multiple tables so that each non-key column fully depends on the entire primary key.
Often involves creating two tables and a relation table connecting them.

Third Normal Form (3NF)
Must already satisfy 2NF.
There should be no transitive dependency, meaning a non-key column should depend only on the primary key and not on another non-key column.
If a non-key column depends on another non-key column, move it to a separate table and link it using a foreign key.

------------------------------------------------------------------------------------------------------------------------------------------------------------