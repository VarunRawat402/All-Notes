-------------------------------------------------------------------------------------------------------------------------------------------------------------
MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

ALTER TABLE:
    → Used to modify an existing table

-- Add new column
ALTER TABLE student ADD age INT;

-- Remove column
ALTER TABLE student DROP COLUMN age;

-- Add column with constraints
ALTER TABLE student ADD email VARCHAR(100) NOT NULL UNIQUE;

-- Change column datatype or constraints
ALTER TABLE student MODIFY age INT NOT NULL;

-- Rename table
ALTER TABLE student RENAME TO users;

-- Remove primary key
ALTER TABLE student DROP PRIMARY KEY;

-- Add primary key
ALTER TABLE student ADD PRIMARY KEY (student_id);

------------------------------------------------------------------------------------------------------------------------------------------------------------

Note:
    → New constraints must be valid for existing data

Example:
→ Adding NOT NULL to a column containing NULL values will fail
→ Adding UNIQUE when duplicate values exist will fail
→ Add column allowing NULL → update existing rows → add constraint later
→ Add column with DEFAULT value

-- Step 1: add column allowing NULL
ALTER TABLE student ADD email VARCHAR(100);

-- Step 2: fill existing rows
UPDATE student SET email = 'default@gmail.com' WHERE email IS NULL;

-- Step 3: now add constraint safely
ALTER TABLE student MODIFY email VARCHAR(100) NOT NULL;

------------------------------------------------------------------------------------------------------------------------------------------------------------






