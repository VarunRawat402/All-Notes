------------------------------------------------------------------------------------------------------------------------------------------------------------
ORDER BY:
    → Sorts the result
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

-- Sort by ASC price
SELECT * FROM products ORDER BY price ASC;

-- Sort by DESC price
SELECT * FROM products ORDER BY price DESC;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 3: Advanced Sorting Techniques:

-- First sort by category, if same then sort by price
SELECT * FROM products ORDER BY category DESC, price DESC;

-- Sort by column position (4 = price column)
SELECT * FROM products ORDER BY 4;

-- Fetch only Electronics products sorted by price
SELECT * FROM products WHERE category = 'Electronics' ORDER BY price;

-- Case-sensitive sorting (lowercase comes after uppercase)
SELECT * FROM products ORDER BY BINARY category;

------------------------------------------------------------------------------------------------------------------------------------------------------------

Section 4: Function-Based Sorting:

-- Sort by length of their name (shortest first)
SELECT * FROM products ORDER BY LENGTH(product_name);

-- Sort by the day of the month they were last updated
SELECT * FROM products ORDER BY DAY(last_updated);

-- Fetch the single product with the highest stock quantity
SELECT * FROM products ORDER BY stock_quantity DESC LIMIT 1;

------------------------------------------------------------------------------------------------------------------------------------------------------------