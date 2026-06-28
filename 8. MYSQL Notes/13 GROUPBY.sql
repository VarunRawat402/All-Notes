------------------------------------------------------------------------------------------------------------------------------------------------------------
GROUP BY:
    → Groups rows that have the same value in specified columns
    → Used with aggregate functions: COUNT, SUM, AVG, MIN, MAX
    → Can only SELECT columns that are in GROUP BY or inside an aggregate function

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Count how many students are in each department
SELECT department, COUNT(*) FROM student GROUP BY department;

-- Calculate total salary paid per department
SELECT department, SUM(salary) FROM student GROUP BY department;

-- Calculate average salary per department
SELECT department, AVG(salary) FROM student GROUP BY department;

-- Find highest salary in each department
SELECT department, MAX(salary) FROM student GROUP BY department;

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Filter rows BEFORE grouping using WHERE
-- Count students per department but only from New York
SELECT department, COUNT(*) FROM student
WHERE city = 'New York'
GROUP BY department;

-- Filter groups AFTER grouping using HAVING
-- Show only departments that have more than 5 students
SELECT department, COUNT(*) AS total
FROM student
GROUP BY department
HAVING total > 5;

------------------------------------------------------------------------------------------------------------------------------------------------------------

WHERE vs HAVING:
    WHERE  → filters rows BEFORE grouping
    HAVING → filters groups AFTER grouping
    → Cannot use aggregate functions in WHERE, use HAVING instead

------------------------------------------------------------------------------------------------------------------------------------------------------------