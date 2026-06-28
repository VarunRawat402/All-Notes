------------------------------------------------------------------------------------------------------------------------------------------------------------
NORMALIZATION:
    → Organizing data to reduce duplicate data and improve accuracy
------------------------------------------------------------------------------------------------------------------------------------------------------------

1NF:
    → Every column contains single value
    → Every row must be unique (primary key required)

-- Violates 1NF → Courses column has multiple values:
    StudentID   StudentName     Courses
    101         Alice           Math, Physics   ❌

-- Fixed → split into separate rows:
    StudentID   StudentName     Course
    101         Alice           Math
    101         Alice           Physics
    Primary Key = (StudentID + Course)

------------------------------------------------------------------------------------------------------------------------------------------------------------

2NF:
    → Already 1NF
    → Every non-key column must depend on the ENTIRE primary key
    → Only applies to tables with composite primary keys

------------------------------------------------------------------------------------------------------------------------------------------------------------

3NF:
    → Already 2NF
    → Non-key columns must depend ONLY on primary key, not on other non-key columns

------------------------------------------------------------------------------------------------------------------------------------------------------------

First Normal Form (1NF)
    Each column should contain single value.
    If a column has multiple values, split them into separate rows so that every cell holds only one value.

Second Normal Form (2NF)
    Must already satisfy 1NF.
    Every non-key column must depend on the whole primary key, not just part of it.
    If the table has a composite primary key, separate the data into multiple tables so that each non-key column fully depends on the entire primary key.
    Often involves creating two tables and a relation table connecting them.

Third Normal Form (3NF)
    Must already satisfy 2NF.
    Non-key column should depend only on the primary key and not on another non-key column.
    If a non-key column depends on another non-key column, move it to a separate table and link it using a foreign key.

------------------------------------------------------------------------------------------------------------------------------------------------------------