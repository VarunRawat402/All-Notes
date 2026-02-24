------------------------------------------------------------------------------------------------------------------------------------------------------------
WHERE in MYSQL:
    Used to filter records and return only those rows that satisfy condition.
------------------------------------------------------------------------------------------------------------------------------------------------------------

Basic Commands:

-- Fetch books with category Technology
SELECT * FROM books WHERE category = 'Technology';

-- Fetch books where price is less than 30
SELECT * FROM books WHERE price < 30.00;

-- Fetch books where publication date is on or after 1st March 2023
SELECT * FROM books WHERE publication_date >= '2023-03-01';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Logical Operators:

-- AND: both conditions must be true
SELECT * FROM books WHERE category = 'Technology' AND price < 30;

-- OR: any one condition must be true
SELECT * FROM books WHERE category = 'Technology' OR price < 30;

-- Multiple logical operators together
-- First OR is evaluated, then AND (due to brackets)
SELECT * FROM books WHERE (category = 'Technology' OR category = 'Mystery') AND price < 25;

-- NOT: excludes matching records
SELECT * FROM books WHERE NOT category = 'Technology';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Finding NULL values:
    NULL represents absence of value, not zero or empty string.

-- Fetch rows where author is NULL
SELECT * FROM books WHERE author IS NULL;

-- Fetch rows where author is NOT NULL
SELECT * FROM books WHERE author IS NOT NULL;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Pattern matching:
    'Like' is used to match the pattern in the text
    '%' means multiple words
    '_' means single word

-- Title contains 'sql' anywhere
SELECT * FROM books WHERE title LIKE '%sql%';

-- Title starts with 'sql'
SELECT * FROM books WHERE title LIKE 'sql%';

-- Title ends with 'sql'
SELECT * FROM books WHERE title LIKE '%sql';

-- Case-sensitive search using BINARY
SELECT * FROM books WHERE title LIKE BINARY '%SQL%';

-- Author name: 1 character + 'ohn' + anything
SELECT * FROM books WHERE author LIKE '_ohn%';

-- Author name exactly 4 characters long
SELECT * FROM books WHERE author LIKE '____';

------------------------------------------------------------------------------------------------------------------------------------------------------------

BETWEEN:

-- Fetch books priced between 20 and 30
SELECT * FROM books WHERE price BETWEEN 20 AND 30;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SUBQUERIES
    A subquery is a query written inside parentheses.
    Subquery executes first, then the outer query.

-- Fetch books priced above average price
SELECT * FROM books 
WHERE price > (SELECT AVG(price) FROM books);

------------------------------------------------------------------------------------------------------------------------------------------------------------