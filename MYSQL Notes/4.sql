------------------------------------------------------------------------------------------------------------------------------------------------------------
WHERE in MYSQL:
    It is used to filter records and return only those rows which satisfy the condition
    SELECT column1, column2 FROM table_name WHERE condition;
------------------------------------------------------------------------------------------------------------------------------------------------------------

Basic Commands:

-- //Fetch books with categort technology
select * from books where category='Technology' ;

-- //Fetch books where price is less than 30
SELECT * FROM books WHERE price < 30.00;

-- //Fetch books where date is greater than 
SELECT * FROM books WHERE publication_date >= '2023-03-01';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Logical Operators:

-- //And where both condition should be true
select * from books where category = 'Technology' and price < 30;

-- //Or where one of the condition should be true
select * from books where category = 'Technology' or price < 30;

-- //Using multiple logical operators together
-- //First it will filter based on category then it filter further based on price
select * from books where (category = 'Technology' or category = 'Mystery') and price < 25; 

-- //Fetch where category is not true ( not operator )
select * from books where not category = 'Technology';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Finding NULL values:
    Null is used with 'is' not '=' like others

-- //Fetch where author is null
select * from books where author is null;

-- //Fetch where author is not null
select * from books where author is not null;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Pattern matching:
    'Like' is used to match the pattern in the text
    '%' means multiple words
    '_' means single word

-- //Fetch books where title has 'sql' somewhere in the text
select * from books where title like '%SqL%';

-- //Fetch books where title has 'sql' in the starting
select * from books where title like 'sql%';

-- //Fetch books where title has 'sql' in the ending
select * from books where title like '%sql';

-- //binary keyword makes the value case sensitive ( sql is wrong due to case sensitive )
select * from books where title like binary '%SQL%';

-- //Fetch books where author is 1 word in the starting and 2, 3 and 4 word is ohn and after that could be anything
select * from books where author like '_ohn%';

-- //Fetch books where author is of 4 word ( _ _ _ _ ) each underscore means 1 word 
select * from books where author like '____';

------------------------------------------------------------------------------------------------------------------------------------------------------------

RANGE OPERATORS:
    "between", 'and' is used for range
    20 and 30 are inclusive

-- //Fetch books between 20 and 30
select * from books where price between 20 and 30;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SUBQUERIES
    They are written in ()

-- //First it will run subquery then main query
select * from books where price > ( select avg(price) from books );


------------------------------------------------------------------------------------------------------------------------------------------------------------

In:
    Its used when you want to match a columns value against multiple values.
    It will fetch based on all the feilds 

-- //Fetch books where course is java or c++ or python
SELECT * FROM student WHERE course IN ('Java', 'C++', 'Python');

------------------------------------------------------------------------------------------------------------------------------------------------------------