------------------------------------------------------------------------------------------------------------------------------------------------------------
Limit:
    Used to restrict the number of rows returned

Offset:
    -- It skips the first x pages
    -- It is used with limit, cannot use alone

------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:

-- Show only first 5 students
SELECT * FROM students LIMIT 5;

-- Skip first 2 rows, then fetch next 5 rows
SELECT * FROM students LIMIT 5 OFFSET 2;

Combined Syntax:
SELECT * FROM students LIMIT X, Y;
-- X = OFFSET (rows to skip)
-- Y = LIMIT (rows to fetch)

-- Skip first 5 students, fetch all remaining
SELECT * FROM students LIMIT 5, 18446744073709551615;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Alias:
    -- It is used to giving a temporary nickname to a column or a table to make your query easier to read or write.
    -- It does not change the actual column or table name in the database.
    -- It only exists for that result.

Types of Aliases:

--Rename a column in the output
SELECT first_name AS name, emp_salary AS salary 
FROM employees;

-- Salary increased by 20%
SELECT *, salary * 1.2 AS new_salary 
FROM employees;

--concat 2 col
SELECT CONCAT(first_name, ' ', second_name) AS full_name 
FROM employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

DISTINCT:
    -- It is used to eliminate duplicate rows or data

-- Unique departments
SELECT DISTINCT department FROM employees;

-- Unique combinations of department and salary
SELECT DISTINCT department, salary  
FROM employees;

-- Count unique departments
SELECT COUNT(DISTINCT department) AS unique_departments 
FROM employees;

-- Unique name-department combinations
SELECT DISTINCT CONCAT(name, '-', department) 
FROM employees;

-- Unique salaries sorted descending
SELECT DISTINCT salary 
FROM employees 
ORDER BY salary DESC;

-- Unique departments where salary > 50000
SELECT DISTINCT department 
FROM employees 
WHERE salary > 50000;

------------------------------------------------------------------------------------------------------------------------------------------------------------