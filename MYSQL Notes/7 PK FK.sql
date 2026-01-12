-------------------------------------------------------------------------------------------------------------------------------------------------
PRIMARY KEYS:
-- A primary key is a column that uniquely identifies each row in a table.
-------------------------------------------------------------------------------------------------------------------------------------------------

Primary Keys - Key Benefits:
    -- They uniquely identify each record in a table
    -- They ensure no duplicate records exist
    -- They provide a reference point for relationships between tables
    -- They optimize database performance for record retrieval

-------------------------------------------------------------------------------------------------------------------------------------------------

-- SECTION 1: Implementing Primary key with column 
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100)
);

-------------------------------------------------------------------------------------------------------------------------------------------------

-- SECTION 2: Primaray key with auto_increment
CREATE TABLE products (
    product_id INT AUTO_INCREMENT PRIMARY KEY,
    product_name VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    description TEXT
);

-------------------------------------------------------------------------------------------------------------------------------------------------

-- SECTION 3: Making Primary key after initialization
CREATE TABLE orders (
    order_id INT,
    customer_id INT,
    order_date DATE NOT NULL,
    total_amount DECIMAL(10, 2) NOT NULL,
    PRIMARY KEY (order_id)
);

-------------------------------------------------------------------------------------------------------------------------------------------------

-- Create table without primary key
CREATE TABLE suppliers (
    supplier_id INT,
);

-- Adding a primary key to an existing table
ALTER TABLE suppliers ADD PRIMARY KEY (supplier_id);

--Droping existing primary key
--Make current primary key normal columnn
ALTER TABLE suppliers DROP PRIMARY KEY;

-------------------------------------------------------------------------------------------------------------------------------------------------

-- SECTION 4: Composite Primary Keys
-- Creating a table with a composite primary key (multiple columns)
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    enrollment_date DATE NOT NULL,
    grade VARCHAR(2),
    PRIMARY KEY (student_id, course_id)
);

-------------------------------------------------------------------------------------------------------------------------------------------------

Primary Key Best Practices:
-- 1. Always include a primary key in every table
-- 2. Use auto-increment unless you have a specific reason not to
-- 3. Keep primary keys simple - use INT or BIGINT for numeric IDs

-------------------------------------------------------------------------------------------------------------------------------------------------

Foreign Keys in SQL: Database Relationships
-- A foreign key is a column in one table that refers to the primary key in another table. 
-- It creates a link between the two tables, establishing a parent-child relationship.
-- Parent table: Contains the primary key that is referenced
-- Child table: Contains the foreign key that references the primary key of the parent table

------------------------------------------------------------------------------------------------------------------------------------------------------------

TYPES OF TABLE RELATIONSHIPS

-- 1. One-to-One (1:1): Each record in Table A relates to exactly one record in Table B
CREATE TABLE employee_details (
    employee_id INT NOT NULL,
    passport_number VARCHAR(20),
    marital_status VARCHAR(20),
    emergency_contact VARCHAR(100),
    PRIMARY KEY (employee_id),
    FOREIGN KEY (employee_id) REFERENCES employees(employee_id)
);

-- 2. One-to-Many (1:N): Each record in Table A relates to multiple records in Table B
CREATE TABLE employees (
    employee_id INT NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    department_id INT,
    PRIMARY KEY (employee_id),
    FOREIGN KEY (department_id) REFERENCES departments(department_id)
);
-- Here, multiple employee can have the same department_id meaning they can have same departments

-- 3. Many-to-Many (N:M): Multiple records in Table A relate to multiple records in Table B 
-- Create Students table
CREATE TABLE Students (
    student_id INT PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL
);

-- Create Courses table
CREATE TABLE Courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL,
    instructor VARCHAR(100) NOT NULL
);

-- Create Enrollments junction table with foreign keys
CREATE TABLE Enrollments (
    enroll_id INT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    grade VARCHAR(5),
    FOREIGN KEY (student_id) REFERENCES Students(student_id),
    FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Add a foreign key constraint after table creation
ALTER TABLE projects
ADD FOREIGN KEY (manager_id) REFERENCES employees(employee_id);

-- View the table structure including the foreign key
SHOW CREATE TABLE projects;

-- Remove a foreign key constraint
ALTER TABLE projects DROP FOREIGN KEY projects_ibfk_1;

-- Verify the foreign key was removed
SHOW CREATE TABLE projects;

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- EXERCISE: IMPLEMENTING EMPLOYEE SKILLS TABLE

-- Create a table for employee skills with a foreign key to employees
CREATE TABLE employee_skills (
    skill_id INT NOT NULL,
    employee_id INT NOT NULL,
    skill_name VARCHAR(50) NOT NULL,
    proficiency_level ENUM('Beginner', 'Intermediate', 'Advanced', 'Expert') NOT NULL,
    PRIMARY KEY (skill_id),
    CONSTRAINT fk_employee_skill FOREIGN KEY (employee_id) REFERENCES employees(employee_id)
);

------------------------------------------------------------------------------------------------------------------------------------------------------------