------------------------------------------------------------------------------------------------------------------------------------------------------------
ORDER BY:
    Sort the result
------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 1: Database and Table Setup

CREATE TABLE products (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(100),
    category VARCHAR(50),
    price DECIMAL(10,2),
    stock_quantity INT,
    last_updated TIMESTAMP
);

INSERT INTO products VALUES
(1, 'Laptop Pro', 'Electronics', 1299.99, 50, '2024-01-15 10:00:00'),
(2, 'Desk Chair', 'Furniture', 199.99, 30, '2024-01-16 11:30:00'),
(3, 'Coffee Maker', 'Appliances', 79.99, 100, '2024-01-14 09:15:00'),
(4, 'Gaming Mouse', 'Electronics', 59.99, 200, '2024-01-17 14:20:00'),
(5, 'Bookshelf', 'Furniture', 149.99, 25, '2024-01-13 16:45:00');

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 2: Basic Sorting Operations:

-- ASC is default
SELECT * FROM products ORDER BY price ASC;
SELECT * FROM products ORDER BY price DESC;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 3: Advanced Sorting Techniques:

-- Multiple column sorting
-- First sort by category, if same then sort by price
SELECT * FROM products 
ORDER BY category DESC, price DESC;

-- Sort using column position (price is 4th column)
SELECT * FROM products ORDER BY 4;

-- Using WHERE with ORDER BY
SELECT * FROM products WHERE category = 'Electronics' 
ORDER BY price;

-- Case-sensitive sorting
SELECT * FROM products ORDER BY BINARY category;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 4: Function-Based Sorting:

-- Sort by length of product name
SELECT * FROM products ORDER BY LENGTH(product_name);

-- Sort by day extracted from timestamp
SELECT * FROM products ORDER BY DAY(last_updated);

-- Product with highest stock quantity
SELECT * FROM products 
ORDER BY stock_quantity DESC LIMIT 1;

------------------------------------------------------------------------------------------------------------------------------------------------------------