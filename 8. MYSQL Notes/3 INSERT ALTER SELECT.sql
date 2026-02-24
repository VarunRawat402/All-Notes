-------------------------------------------------------------------------------------------------------------------------------------------------------------
CRUD In MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

CREATE TABLE table_name ( 
    col1 datatype constraints, 
    col2 datatype constraints,
    table_constraints
);

create table student(
    student_id      int                 primary key auto_increment,
    first_name      varchar(255)        not null,
    last_name       varchar(255)        not null,
    hire_date       date                default (current_date),
    email           varchar(255)        not null unique,
    phone_no        varchar(255)        not null unique,
    salary          decimal(10,2)       not null check (salary>0.00),
    created_at      timestamp           default current_timestamp,
    updated_at      timestamp           default current_timestamp on update current_timestamp,
    role            enum ('student','admin','teacher')
);

------------------------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------------
INSERT INTO TABLE:
------------------------------------------------------------------------------------------------------------------------------------------------------------

INSERT INTO 'table_name' ( col1, col2, col3, col4 ) VALUES ('val1','val2','val3','val4');

insert into student( first_name, last_name, email) values ( 'Varun', 'Rawat', 'varunrawat402@gmail.com');

------------------------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------------
ALTER TABLE:
    Used to modify the structure of an existing table.
    [ Add columns, Drop columns, Modify column data type, default values, Rename columns, Add or remove constraints, Rename the whole table ];
    ALTER TABLE 'table_name' 'action';
------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Add a column
ALTER TABLE student ADD age INT;

-- Drop a column
ALTER TABLE student DROP COLUMN age;

-- Add column with constraints
ALTER TABLE student ADD email VARCHAR(100) NOT NULL UNIQUE;

-- Modify column datatype or constraints
ALTER TABLE student MODIFY age INT NOT NULL;

-- Rename table
ALTER TABLE student RENAME TO learners;

-- Drop primary key
ALTER TABLE student DROP PRIMARY KEY;

-- Add primary key
ALTER TABLE student ADD PRIMARY KEY (student_id);

-- Set default value
ALTER TABLE student ALTER age SET DEFAULT 18;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Note:
If you add constraints on the column which old records dont follow it will reject
If you add column age with NOT NULL constraint then old records will have null values when you add it so it will reject it

1: Allow NULL values at first, Update existing rows, Add constraint later
2: Add column with DEFAULT, Then change to actual values if need

------------------------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------------
SELECT:
------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching columns:

-- Fetch specific columns
SELECT name, age FROM student;

-- Fetch all columns
SELECT * FROM student;

-- Rename columns in result set
SELECT name AS Full_Name, age AS Age FROM student;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Advanced:
    Expressions inside () with SELECT

-- Total marks
SELECT name, (phy_marks + chem_marks + math_marks) AS Total FROM student;

-- Sort by calculated column
SELECT name, (phy_marks + chem_marks + math_marks) AS Total 
FROM student 
ORDER BY Total ASC;

-- Increase salary by 20%
SELECT name, salary * 1.2 AS Increased_Salary 
FROM student;

-- Concatenate names
SELECT CONCAT(first_name, ' ', last_name) AS FULL_NAME 
FROM student;

------------------------------------------------------------------------------------------------------------------------------------------------------------





