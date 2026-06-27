------------------------------------------------------------------------------------------------------------------------------------------------------------
JOINS:
    → Combine rows from two or more tables using a related column
    
------------------------------------------------------------------------------------------------------------------------------------------------------------

INNER JOIN:
    → Returns rows that have matching values in BOTH tables
    → Non-matching rows from either table are excluded

-- Syntax
SELECT * FROM table1 INNER JOIN table2
ON t1.column = t2.column;

-- Fetch all columns from authors and books where author_id matches
SELECT * FROM authors AS a
INNER JOIN books AS b ON a.author_id = b.author_id;

-- Fetch author id, name and book price where book price is greater than 10
SELECT a.author_id, a.first_name, b.price
FROM authors AS a
JOIN books AS b ON a.author_id = b.author_id
WHERE b.price > 10;

------------------------------------------------------------------------------------------------------------------------------------------------------------

OuterJoin:
    → It is used to get the matching and non matching records

------------------------------------------------------------------------------------------------------------------------------------------------------------

Left join:
    → Returns ALL rows from left table + matching rows from right table

SELECT * FROM table1
LEFT JOIN table2 ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

RIGHT JOIN:
    → Returns ALL rows from right table + matching rows from left table

SELECT * FROM table1
RIGHT JOIN table2 ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

FULL OUTER JOIN:
    → Returns ALL rows from BOTH tables
    → Non-matching rows on either side show NULL
    → Not supported in MySQL → supported in PostgreSQL and SQL Server

SELECT * FROM table1
FULL OUTER JOIN table2 ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

CROSS JOIN:
    → Combines EVERY row from table1 with EVERY row from table2
    → Called Cartesian Product
    → table1 has 3 rows, table2 has 4 rows → result has 12 rows

SELECT * FROM table1 CROSS JOIN table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SELF JOIN:
    → A table joined with itself
    → Useful to find relationships within the same table
    → Use aliases to differentiate the two copies

-- Fetch each employee and their manager (both in same employees table)
SELECT e.name AS Employee, m.name AS Manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.emp_id;

------------------------------------------------------------------------------------------------------------------------------------------------------------

UNION:
    → Combine result from multiple SELECT queries into a single result set
    → Removes duplicate rows from the result.
    → Stacks results of two SELECT queries vertically
    → Both queries must have same number of columns + compatible types

-- Combine unique results from both tables
SELECT column1, column2 FROM table1
UNION
SELECT column1, column2 FROM table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

UNION ALL:
    → Same as UNION but keeps duplicate rows

SELECT column1, column2 FROM table1
UNION ALL
SELECT column1, column2 FROM table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------


