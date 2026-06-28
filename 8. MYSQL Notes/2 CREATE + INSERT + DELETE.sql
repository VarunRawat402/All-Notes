------------------------------------------------------------------------------------------------------------------------------------------------------------
MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

CREATE: 
    → Creates Table / Database

-- Creates database 
CREATE DATABASE IF NOT EXISTS student_db;

-- Creates table
CREATE TABLE student (
    id         INT              PRIMARY KEY AUTO_INCREMENT,     -- unique, auto increments
    email      VARCHAR(255)     UNIQUE NOT NULL,                -- no duplicates, required
    salary     DECIMAL(10,2)    CHECK (salary > 0)              -- must be positive
);

------------------------------------------------------------------------------------------------------------------------------------------------------------

INSERT:
    → Used to insert data into a table

-- Insert single row
INSERT INTO student(first_name, last_name, email) VALUES ('Varun', 'Rawat', 'varunrawat402@gmail.com');

-- Insert multiple row
INSERT INTO student(first_name, last_name, email)
VALUES
    ('John', 'Doe', 'john.doe@gmail.com'),
    ('Jane', 'Smith', 'jane.smith@gmail.com');

------------------------------------------------------------------------------------------------------------------------------------------------------------

DELETE:
    → Deletes specific rows, scans row by row
    → Supports WHERE to target specific rows
    → Can be rolled back

-- Delete all employees in HR department
DELETE FROM employees WHERE department = 'HR';

-- Delete all rows from table (keeps structure)
DELETE FROM employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------