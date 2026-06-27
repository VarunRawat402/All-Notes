------------------------------------------------------------------------------------------------------------------------------------------------------------
MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

CREATE: 
→ Used to create a new database or table

-- Creates database 
CREATE DATABASE IF NOT EXISTS student_db;

-- Creates table
CREATE TABLE student (
    student_id INT PRIMARY KEY AUTO_INCREMENT, -- unique, auto increments
    email      VARCHAR(255) UNIQUE NOT NULL,   -- no duplicates, required
    salary     DECIMAL(10,2) CHECK (salary > 0) -- must be positive
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

SELECT:
→ Used to fetch data from database

-- Fetch specific columns
SELECT name, age FROM student;

-- Fetch all columns
SELECT * FROM student;

-- Fetch and rename column
SELECT name AS Full_Name FROM student;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SELECT with Expressions:
→ Expressions inside () with SELECT

-- Fetch total marks as Total
SELECT name, (phy + chem + math) AS Total FROM student;

-- Sort by calculated column
SELECT name, (phy + chem + math) AS Total
FROM student ORDER BY Total ASC;

-- Fetch 20% salary increase without changing DB
SELECT name, salary * 1.2 AS Increased_Salary FROM student;

-- Merge first and last name into one column
SELECT CONCAT(first_name, ' ', last_name) AS Full_Name FROM student;

------------------------------------------------------------------------------------------------------------------------------------------------------------

UPDATE:
    → Modifies existing records in a table

-- Increase price of all products by 10%
UPDATE products SET price = price * 1.10 WHERE product_id > 0;

-- Update multiple columns for a specific product
UPDATE products SET price = 100, stock_quantity = 10 WHERE product_id = 3;

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