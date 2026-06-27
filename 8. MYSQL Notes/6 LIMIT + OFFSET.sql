------------------------------------------------------------------------------------------------------------------------------------------------------------
Limit:
    → Fetch limited rows

Offset:
    → Skips the first X rows before fetching
    → Cannot be used without LIMIT

------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:

-- Fetch first 5 rows
SELECT * FROM students LIMIT 5;

-- Skip first 2 rows, then fetch next 5 rows
SELECT * FROM students LIMIT 5 OFFSET 2;

-- Combined shorthand syntax: LIMIT offset, count
SELECT * FROM students LIMIT 2, 5;  -- skip 2, fetch 5

-- Skip first 5 rows, fetch all remaining rows
SELECT * FROM students LIMIT 5, 18446744073709551615;

------------------------------------------------------------------------------------------------------------------------------------------------------------

ALIAS:
    → Gives a temporary name to a column or table in the result
    → Does not change actual column/table name in database
    → Only exists for that query result

-- Rename columns in output
SELECT first_name AS name, emp_salary AS salary FROM employees;

-- Show salary increased by 20% with a readable column name
SELECT *, salary * 1.2 AS new_salary FROM employees;

-- Combine first and last name into one column
SELECT CONCAT(first_name, ' ', second_name) AS full_name FROM employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

DISTINCT:
    → Removes duplicate rows from the result

-- Fetch all unique departments
SELECT DISTINCT department FROM employees;

-- Fetch unique combinations of department and salary
SELECT DISTINCT department, salary FROM employees;

-- Count how many unique departments exist
SELECT COUNT(DISTINCT department) AS unique_departments FROM employees;

-- Unique name-department combinations as one string
SELECT DISTINCT CONCAT(name, '-', department) FROM employees;

-- Fetch unique salaries sorted highest to lowest
SELECT DISTINCT salary FROM employees ORDER BY salary DESC;

-- Fetch unique departments where salary is above 50000
SELECT DISTINCT department FROM employees WHERE salary > 50000;

------------------------------------------------------------------------------------------------------------------------------------------------------------