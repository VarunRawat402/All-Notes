CHEATSHEET SQL:

Create TABLE:

create table student(
id int primary key auto_increment,
name varchar(255) not null,
email varchar(255) not null unique,
age int not null
);

Insert VALUES:

insert into student(name,email,age) 
VALUES ("varun","var@gmail.com",25), ("nandni","nan@gmail.com",24);

ALTER TABLE:

Add column:
ALTER TABLE student add age int;

Remove Column:
ALTER TABLE student DROP COLUMN age;

WHERE:
Filter records based on condition

Order By:
Usefd for sorting:

