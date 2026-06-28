------------------------------------------------------------------------------------------------------------------------------------------------------------
MYSQL:
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