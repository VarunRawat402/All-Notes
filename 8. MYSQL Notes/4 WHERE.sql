------------------------------------------------------------------------------------------------------------------------------------------------------------
WHERE:
    → Filters rows based on a condition
------------------------------------------------------------------------------------------------------------------------------------------------------------

Basic Commands:

-- Fetch all books in the Technology category
SELECT * FROM books WHERE category = 'Technology';

-- Fetch all books where price is less than 30
SELECT * FROM books WHERE price < 30.00;

-- Fetch all books published on or after 1st March 2023
SELECT * FROM books WHERE publication_date >= '2023-03-01';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Logical Operators:

-- AND: Fetch Technology books that also cost less than 30
SELECT * FROM books WHERE category = 'Technology' AND price < 30;

-- OR: Fetch books that are either Technology OR cost less than 30
SELECT * FROM books WHERE category = 'Technology' OR price < 30;

-- Brackets: Fetch Technology or Mystery books that cost less than 25
-- OR inside brackets runs first, then AND
SELECT * FROM books WHERE (category = 'Technology' OR category = 'Mystery') AND price < 25;

-- NOT: Fetch all books that are NOT in Technology category
SELECT * FROM books WHERE NOT category = 'Technology';

------------------------------------------------------------------------------------------------------------------------------------------------------------

Finding NULL values:
    → NULL means value is absent, not zero or empty string
    → Use IS NULL / IS NOT NULL (= NULL does not work)

-- Fetch books where author is missing
SELECT * FROM books WHERE author IS NULL;

-- Fetch books where author is present
SELECT * FROM books WHERE author IS NOT NULL;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Pattern matching:
    % → matches any number of characters
    _ → matches exactly one character

-- Fetch books where title contains 'sql' anywhere
SELECT * FROM books WHERE title LIKE '%sql%';

-- Fetch books where title starts with 'sql'
SELECT * FROM books WHERE title LIKE 'sql%';

-- Fetch books where title ends with 'sql'
SELECT * FROM books WHERE title LIKE '%sql';

-- Case-sensitive: fetch books where title contains exactly 'SQL' (uppercase)
SELECT * FROM books WHERE title LIKE BINARY '%SQL%';

-- Fetch authors where name is like 'John', 'Bohn' (1 char + ohn + anything)
SELECT * FROM books WHERE author LIKE '_ohn%';

-- Fetch authors where name is exactly 4 characters long
SELECT * FROM books WHERE author LIKE '____';

------------------------------------------------------------------------------------------------------------------------------------------------------------

BETWEEN:
    → Fetches rows where value falls within a range (inclusive on both ends)

-- Fetch books where price is between 20 and 30 (including 20 and 30)
SELECT * FROM books WHERE price BETWEEN 20 AND 30;

------------------------------------------------------------------------------------------------------------------------------------------------------------

SUBQUERIES
    → A query inside another query, inner query runs first

-- Fetch all books that cost more than the average price of all books
SELECT * FROM books
WHERE price > (SELECT AVG(price) FROM books);

------------------------------------------------------------------------------------------------------------------------------------------------------------