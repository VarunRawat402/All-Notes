-------------------------------------------------------------------------------------------------------------------------------------------------------------
CRUD In MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

Create Student Table:

CREATE TABLE 'table_name' ( 
    'col1', datatype, Constraints, 
    'col2', datatype, Constraints,
    table_constraints 
);

create table student(
    student_id      int                 primary key auto_increment,
    first_name      varchar(255)        not null,
    last_name       varchar(255)        not null,
    hire_date       date                default (current_date()),
    email           varchar(255)        not null unique,
    phone_no        varchar(255)        not null unique,
    salary          decimal(10,2)       not null check (salary>0.00),
    created_at      timestamp           default current_timestamp,
    updated_at      timestamp           default current_timestamp on update current_timestamp,
    role            enum ('student','admin','teacher')
);

------------------------------------------------------------------------------------------------------------------------------------------------------------

Insert In student Table:
    Column count should match values count
    If column value is not added it will get default values automatically


INSERT INTO 'table_name' ( col1, col2, col3, col4 )
    VALUES ('val1','val2','val3','val4');

insert into student(
    first_name, last_name, hire_date, email, phone_no, salary, role )
    values ( 'Varun', 'Rawat', '2022-11-10', 'varunrawat402@gmail.com', '+91 8448222398', 29000, 'student' )
;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Alter Table:
It is used to modify the structure of an existing table.
[ Add columns, Drop columns, Modify column data type, default values, Rename columns, Add or remove constraints, Rename the whole table ];

ALTER TABLE 'table_name' 'action';

ALTER TABLE student add age int;
ALTER TABLE student DROP COLUMN age;

Note:
If you add constraints on the column which old records dont follow it will reject
If you add column age with NOT NULL constraint then old records will have null values when you add it so it will reject it

1: Allow NULL values at first, Then insert the values, Then add the constraints
2: Add default values, Then change to actual values if need

Note:
Mysql is lenient in this so, If you add constraint it will automatically add the column with default values
'' for varchar , 0  for int
Use Strict Mode for rejecting the queries

------------------------------------------------------------------------------------------------------------------------------------------------------------

Some Alter Table Commands:

-- //Add a column
ALTER TABLE student ADD age INT;                                            

-- //Add a column with constraints
ALTER TABLE student ADD email VARCHAR(100) NOT NULL UNIQUE;

-- //Modify the existing table by adding constraints
ALTER TABLE student MODIFY age INT NOT NULL;            

-- //Modify the existing table datatype
ALTER TABLE student MODIFY name VARCHAR(200);

-- //Change the column name, datatype, constraints
ALTER TABLE student CHANGE student_id std_id VARCHAR(200);

-- //change the column name only
alter table student rename column std_id to student_id;

-- //Rename the table name
ALTER TABLE student RENAME TO learners;

-- //Delete the column
ALTER TABLE student DROP COLUMN middle_name;

-- //Make student_id primary key
ALTER TABLE student ADD PRIMARY KEY (student_id);

-- //Primary key will be dropped and they will become normal column
ALTER TABLE student DROP PRIMARY KEY;

-- //set the default value to existing column
ALTER TABLE student ALTER age SET DEFAULT 18;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Connect 2 Tables using foreign key:
    Student and Department Table

-- // If department Id is already created and values are added in student table:
alter table student add constraint fk_department foreign key(department_id) references departments(department_id);

-- //If department id is not created in student table
alter table student add department_id int, add constraint fk_department foreign key(department_id) references departments(department_id);

-- //Remove the foreign key title from column
ALTER TABLE student DROP FOREIGN KEY fk_department;

-- //Drop the foreign key and column both
ALTER TABLE student DROP FOREIGN KEY fk_department, DROP COLUMN department_id;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SELECT:
    Used to retrieve data from one or more tables
    SELECT 'col1', 'col2' FROM 'table_name';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Fetching columns:

-- // Fetch name and age column from student
    select name, age from student;                                                        

-- //Select every column
    select * from student;                                                                                  

-- // Fetching columns and changing their name in result_set:
    select name as Full_Name, age as Age from student;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Order By:
    Used to sort the result 

select * from student order my marks asc;
select * from student order my marks desc;
select * from student order by first_name;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Limit: 
    used to limit the rows

-- //First 10 students:
    select * from student limit 10;

-- //Student with Highest marks in Maths:
    select * from student order by marks desc limit 1;

-- //Student with lowest marks in Maths:
    select * from student order by marks asc limit 1;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Advanced:
    () inside this you can write expressions

-- //adding phy,chem and maths column as total
    select name, (phy_marks + chem_marks + math_marks) as Total from student;

-- //adding phy,chem and maths column as total and sorting by total in ascending order
    select name, (phy_marks + chem_marks + math_marks) as Total from student order by total asc;

-- //Fetching name and salary and increasing salary by 20%
    select name, salary*1.2 from students

-- //Concating first and last name
    select concat(first_name , ' ' , last_name) as FULL_NAME from student;

------------------------------------------------------------------------------------------------------------------------------------------------------------





