------------------------------------------------------------------------------------------------------------------------------------------------------------
JOINS:
    It is used to join the 2 or more tables using related column
------------------------------------------------------------------------------------------------------------------------------------------------------------

InnerJoin:
    It is used to get the matching records from both the tables

Syntax:

SELECT columns
FROM table1 AS t1
INNER JOIN table2 AS t2 
ON t1.common_column = t2.common_column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetch all columns from authors and books based on authorId:

Select * from 
authors as a
join books as b
on a.author_id = b.author_id

Fetch authorId, authorName of books where price of books is greater than 10 dollars

select a.author_id, a.first_name, b.price 
from authors as a join books as b
on a.author_id = b.author_id
where b.price > 10;

------------------------------------------------------------------------------------------------------------------------------------------------------------

OuterJoin:
    It is used to get the matching and non matching records

------------------------------------------------------------------------------------------------------------------------------------------------------------

Left Outer join:
    Return all records from the left table and matching records on the right table

SELECT columns
FROM table1
LEFT OUTER JOIN table2
ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Right Outer join:
    Return all records from the right table and matching records on the left table

SELECT columns
FROM table1
RIGHT OUTER JOIN table2
ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Full Outer join:
    It is not supporeted in mysql, It is supported in postgresql and sql server 
    Return all the records from the left and right table

SELECT columns
FROM table1
FULL OUTER JOIN table2
ON table1.column = table2.column;

------------------------------------------------------------------------------------------------------------------------------------------------------------

UNION:
UNION allows us to combine result from multiple SELECT queries into a single result set

Key points:
- Combines rows from multiple queries into a single result set
- Appends rows vertically (stacks them on top of each other)
- Requires that all queries have the same number of columns
- Column data types must be compatible across all queries
- Eliminates duplicate rows by default (use UNION ALL to keep duplicates)
- Uses the column names from the first SELECT statement for the final result set
- Ignores column names from subsequent queries



Combines results from two or more SELECT statements.
Removes duplicate rows from the result.
It does not join tables 

--Combines data of col1 and col2 from table1 and table2
SELECT column1, column2 FROM table1
UNION
SELECT column1, column2 FROM table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

UNION ALL
Combines results from two or more SELECT statements.
Includes all rows, even duplicates.

SELECT column1, column2 FROM table1
UNION ALL
SELECT column1, column2 FROM table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

cross join:
A CROSS JOIN is used to combine every row from one table with every row from another table.
This is also called a Cartesian Product.
If table1 has m rows and table2 has n rows, the result set will have m * n rows.

SELECT *
FROM table1
CROSS JOIN table2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Self Join:
    A self join is when a table is joined with itself. 
    It is useful when you want to compare rows within the same table or find relationships among rows in the same table.

    SELECT a.column1, b.column2
    FROM table_name a
    JOIN table_name b
    ON a.common_column = b.common_column;

    SELECT e.name AS Employee, m.name AS Manager
    FROM employees e
    LEFT JOIN employees m
    ON e.manager_id = m.emp_id;


------------------------------------------------------------------------------------------------------------------------------------------------------------

