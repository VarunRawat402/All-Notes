------------------------------------------------------------------------------------------------------------------------------------------------------------
UPDATE:
    It is used to update the records in Database
------------------------------------------------------------------------------------------------------------------------------------------------------------

Syntax:
UPDATE table_name
SET column1 = value1, column2 = value2 
WHERE condition;

--Set is used to modify the col and its value
--Where is used to tell which record will get modify by these values

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Update the price by 10%:
update products set price = price*1.10 where product_id > 0;

-- Update the price and quantity of Coffee Maker:
update products set price = 100, stock_quantity = 10 where product_id = 3;

------------------------------------------------------------------------------------------------------------------------------------------------------------

DELETE:
    It is used to delete records

------------------------------------------------------------------------------------------------------------------------------------------------------------

Syntax:
DELETE FROM table_name
WHERE condition;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Key Points:
-- Row-by-row deletion → MySQL scans each row and deletes it.
-- Can use WHERE → delete only specific rows.

------------------------------------------------------------------------------------------------------------------------------------------------------------

--Delete records where department is HR
DELETE FROM employees WHERE department = 'HR';

--Delete whole table
DELETE FROM employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

TRUNCATE:
    -- It is used to delete every record present in the table
    -- All or nothing
    -- It keeps the structure
    -- After truncate next record will start with 1
    -- Rollback is not possible with truncate

------------------------------------------------------------------------------------------------------------------------------------------------------------

Syntax:
    TRUNCATE TABLE table_name

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Truncate employee table:
TRUNCATE TABLE employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

ON DELETE:
    -- It is used to define what should happen to child table rows if parent table row is deleted
    -- Used with foreign key

------------------------------------------------------------------------------------------------------------------------------------------------------------

1: CASCADE:
    If a parent row is deleted, the child rows referencing it also deleted 

2: SET NULL:
    If a parent row is deleted, the childs foreign key value becomes NULL
    Only If foreign key allows null

3: RESTRICT:
    Prevents deleting the parent row if child row exists

4: NO ACTION:
    Same as RESTRICT

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Key differences between TRUNCATE and DELETE:
-- Speed: TRUNCATE is generally faster because it drops and recreates the table rather than removing rows one by one.
-- Logging: DELETE logs individual row removals, while TRUNCATE only logs table deallocation.
-- WHERE clause: DELETE supports WHERE conditions to remove specific rows, while TRUNCATE always removes all rows.
-- Auto-increment: TRUNCATE resets auto-increment counters to their initial value, while DELETE preserves the current counter value.
-- Triggers: DELETE activates DELETE triggers, while TRUNCATE does not fire any triggers.
-- Rollback: DELETE operations can be rolled back in a transaction, while TRUNCATE generally cannot
-- SQL Categories: TRUNCATE is a DDL (Data Definition Language) command, DELETE is a DML (Data Manipulation Language) command

------------------------------------------------------------------------------------------------------------------------------------------------------------

REPLACE:
    It is used to insert the data and delete the older data together
    If the new row conflicts with an existing rows PRIMARY KEY or UNIQUE index, MySQL deletes the old row and inserts the new one.

Syntax:
REPLACE INTO table_name (col1, col2, ...)
VALUES (val1, val2, ...);

Difference between INSERT, UPDATE, and REPLACE
-- INSERT → Adds a new row. Fails if duplicate primary/unique key.
-- UPDATE → Modifies existing row(s). No new row created.
-- REPLACE → If duplicate found → delete + insert new row.

Caution:
-- Since REPLACE actually deletes then inserts, it may:
-- Trigger DELETE + INSERT triggers
-- Reset AUTO_INCREMENT values unexpectedly
-- Cause data loss if not used carefully