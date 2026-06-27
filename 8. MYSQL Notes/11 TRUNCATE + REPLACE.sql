------------------------------------------------------------------------------------------------------------------------------------------------------------

TRUNCATE:
    → Deletes ALL rows at once, keeps table structure
    → Faster than DELETE (drops and recreates table internally)
    → Resets AUTO_INCREMENT back to 1
    → Cannot be rolled back
    → Does NOT fire triggers

-- Remove all records from employees table
TRUNCATE TABLE employees;

------------------------------------------------------------------------------------------------------------------------------------------------------------

ON DELETE (Foreign Key Behavior):
    → Defines what happens to child rows when parent row is deleted

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
    → Insert new row, but if PRIMARY KEY or UNIQUE key conflicts → delete old row + insert new
    → Internally does DELETE + INSERT (not UPDATE)

REPLACE INTO products (product_id, product_name, price) VALUES (1, 'New Laptop', 999.99);

Use carefully:
    → Fires both DELETE + INSERT triggers
    → May reset AUTO_INCREMENT unexpectedly
    → Can cause data loss on unintended conflicts

------------------------------------------------------------------------------------------------------------------------------------------------------------

INSERT vs UPDATE vs REPLACE:
    INSERT  → adds new row, fails if duplicate key
    UPDATE  → modifies existing row, no new row
    REPLACE → duplicate found → delete + insert fresh row

------------------------------------------------------------------------------------------------------------------------------------------------------------