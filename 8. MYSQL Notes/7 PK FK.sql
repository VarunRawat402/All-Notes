-------------------------------------------------------------------------------------------------------------------------------------------------
PRIMARY KEYS:
    → Uniquely identifies each row in a table
    → Must be UNIQUE + NOT NULL
    → Optimizes record retrieval performance
    → Reference point for relationships between tables

-------------------------------------------------------------------------------------------------------------------------------------------------

-- Define primary key
CREATE TABLE products (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(100) NOT NULL
);

-------------------------------------------------------------------------------------------------------------------------------------------------

-- Define primary key after all columns
CREATE TABLE orders (
    order_id INT,
    order_date DATE NOT NULL,
    PRIMARY KEY (order_id)
);

-------------------------------------------------------------------------------------------------------------------------------------------------

-- Add primary key to existing table
ALTER TABLE suppliers ADD PRIMARY KEY (supplier_id);

-- Remove primary key (makes it a normal column)
ALTER TABLE suppliers DROP PRIMARY KEY;

-------------------------------------------------------------------------------------------------------------------------------------------------

-- Composite primary key (two columns together = unique identifier)
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    enrollment_date DATE NOT NULL,
    PRIMARY KEY (student_id, course_id) -- combination must be unique
);

-------------------------------------------------------------------------------------------------------------------------------------------------

FOREIGN KEY:
    → Column in child table that references PRIMARY KEY of parent table
    → Creates parent-child relationship between tables
    → Prevents orphan records (cant add child without parent)

------------------------------------------------------------------------------------------------------------------------------------------------------------