------------------------------------------------------------------------------------------------------------------------------------------------------------
Limit:
    -- It is used to limit the number of records returned by query

Offset:
    -- It is used to tell from which row to start returning data
    -- It skips the first x pages
    -- It is used with limit, cannot use alone

------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:

-- Show only first 5 students
select * from students limit 5

-- Skips first 2 rows then fetch 5 rows
select * from students limit 5 offset 2

Comined Syntax:
    select * from students limit X, Y;
    where x = offset and y = limit

-- Print all the students but skip first 5 students
select * from students limit 5, 100000000000000

------------------------------------------------------------------------------------------------------------------------------------------------------------

Alias:
    -- It is used to giving a temporary nickname to a column or a table to make your query easier to read or write.
    -- It does not change the actual column or table name in the database.
    -- It only exists for that result.

Types of Aliases:

-- 1. Column Alias
-- -- You rename a column in the output.
    SELECT first_name AS name, emp_salary AS salary FROM employees;

-- 2: Expression Alias:
-- Fetch all the details with 20% increased salary as new salary 
    select *,salary*1.2 as new_salary from employees;

-- 3: concat Alias:
    select concat(first_name, " ", second_name) as full_name from employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

DISTINCT:
    -- It is used to eliminate duplicate rows or data

-- Example 1: Using DISTINCT on a single column
    SELECT DISTINCT department FROM employees;

-- Example 2: Using DISTINCT on multiple columns
    SELECT DISTINCT department, salary  FROM employees;

-- Example 3: Using DISTINCT with aggregate functions
-- Count number of unique departments
SELECT COUNT(DISTINCT department) AS unique_departments FROM employees;

-- Example 4: Using DISTINCT with string functions
-- Get unique name-department combinations
SELECT DISTINCT CONCAT(name, '-', department) FROM employees;

-- Example 5: Using DISTINCT with ORDER BY
-- Get unique salaries in descending order
SELECT DISTINCT salary FROM employees ORDER BY salary DESC;

-- Example 6: Using DISTINCT with WHERE clause
-- Get unique departments where salary is greater than 50000
SELECT DISTINCT department FROM employees WHERE salary > 50000;

-- Example 7: Handling NULL values with DISTINCT
-- Show how DISTINCT handles NULL values
    SELECT DISTINCT department FROM employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------