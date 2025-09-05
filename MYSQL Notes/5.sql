------------------------------------------------------------------------------------------------------------------------------------------------------------
ORDER BY:
    It is used to order or sort the table
------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 1: Database and Table Setup

CREATE DATABASE db12;
USE db12;

-- Create a products table with various data types
CREATE TABLE products (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(100),
    category VARCHAR(50),
    price DECIMAL(10,2),
    stock_quantity INT,
    last_updated TIMESTAMP
);

-- Insert initial sample data
INSERT INTO products VALUES
(1, 'Laptop Pro', 'Electronics', 1299.99, 50, '2024-01-15 10:00:00'),
(2, 'Desk Chair', 'Furniture', 199.99, 30, '2024-01-16 11:30:00'),
(3, 'Coffee Maker', 'Appliances', 79.99, 100, '2024-01-14 09:15:00'),
(4, 'Gaming Mouse', 'Electronics', 59.99, 200, '2024-01-17 14:20:00'),
(5, 'Bookshelf', 'Furniture', 149.99, 25, '2024-01-13 16:45:00');

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 2: Basic Sorting Operations: (asc is default)

SELECT * FROM products ORDER BY price ASC;
SELECT * FROM products ORDER BY price DESC;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 3: Advanced Sorting Techniques

-- //Sorting Using Multiple Col ( first sort by category, if equal then sort using price )
SELECT * FROM products ORDER BY category DESC, price DESC;

-- //Sort using position of col number ( price is 4 col in the table )
SELECT * FROM products ORDER BY 4;

-- //Combining 'where' with 'order by'
SELECT * FROM products WHERE category = 'Electronics' ORDER BY price;

-- //Case sensitiive sorting
SELECT * FROM products ORDER BY BINARY category;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 4: Function-Based Sorting

-- //Sort by length of the name ( calculates the length of the name and sort it using that )
SELECT * FROM products ORDER BY LENGTH(product_name);

-- //Sort by day
SELECT * FROM products ORDER BY DAY(last_updated);

-- //Product with highest stock quantity
SELECT * FROM products ORDER BY stock_quantity DESC LIMIT 1;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Custom sorting with FIELD:
    It sorts using the priority
    It gives them priority like 1, 2, 3 and if not mentioned then 0

-- //Sort the products by category and the order should be ( 'Electronics','Furniture','Appliances')
SELECT * FROM products ORDER BY FIELD(category, 'Electronics','Furniture','Appliances');

------------------------------------------------------------------------------------------------------------------------------------------------------------

Custom Sorting using Case:  
    It is same as Feild but with more flexibility on giving priority
    It lets you define multiple if conditions and give them priority to let you control the order


-- //Order the products like first electronics, then furniture, then appliances, then everything else
SELECT * FROM products ORDER BY 
        CASE category
           WHEN 'Electronics' THEN 1
           WHEN 'Furniture' THEN 2
           WHEN 'Appliances' THEN 3
           ELSE 4   //to items that are not mentioned
        END;

-- //Order the products like first which has price more than 150 then category is appliances then everything else
SELECT * FROM products ORDER BY 
        CASE
           WHEN price > 150 then 1
           WHEN category = 'appliances' then 2
           ELSE 4   
        END;


------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting based on Null values:
    In asc, null comes first
    In desc, null comes last

-- //First null values will come
SELECT product_id, product_name, price FROM products ORDER BY price ASC;

-- //Null values will come last
SELECT product_id, product_name, price FROM products ORDER BY price DESC;

Complete Control with CASE:

SELECT * FROM products 
        ORDER BY CASE 
           WHEN price IS NULL THEN 999999   -- put NULLs last
           ELSE price
        END ASC;


SELECT * FROM products 
        ORDER BY CASE 
           WHEN price IS NULL THEN -1      -- put NULLs first
           ELSE price
        END ASC;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting using calculated columns:

-- //created a col of total ( addition of phy, chem and maths ) and sorted them by total in asc order
select *, phy+chem+maths as total from student order by total;

-- //Creating a col of priority using 'CASE' then sorting based on that priority col
SELECT *,
    CASE
        WHEN price > 150 then 1
        WHEN category = 'appliances' then 2
        ELSE 4   
    END AS priority 
FROM products 
ORDER BY priority;

------------------------------------------------------------------------------------------------------------------------------------------------------------