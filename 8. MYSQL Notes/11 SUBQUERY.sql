------------------------------------------------------------------------------------------------------------------------------------------------------------
Mastering SUBQUERIES:
------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch all customers who have placed at least one order
SELECT * FROM customers
WHERE customer_id IN (SELECT DISTINCT customer_id FROM orders);

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch all customers who have never placed an order
SELECT * FROM customers
WHERE customer_id NOT IN (SELECT DISTINCT customer_id FROM orders);

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch all products that cost more than the average product price
SELECT * FROM products
WHERE price > (SELECT AVG(price) FROM products);

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch categories that have more than 2 products
SELECT category, COUNT(*) AS c FROM products
GROUP BY category HAVING c > 2;

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch all orders placed by customers from Texas
SELECT * FROM orders
WHERE customer_id IN (SELECT customer_id FROM customers WHERE state = 'TX');

-- Fetch all customers who have ordered Electronics products (nested subquery)
SELECT * FROM customers
WHERE customer_id IN
    (SELECT customer_id FROM orders WHERE order_id IN
        (SELECT DISTINCT order_id FROM order_items WHERE product_id IN
            (SELECT product_id FROM products WHERE category = 'Electronics')));

------------------------------------------------------------------------------------------------------------------------------------------------------------

Advanced Subqueries:
    → Use IN when subquery returns a list of values
    → Use FROM + alias when subquery returns a result set (table)

------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Fetch customers who spent more than the average customer spending
SELECT * FROM customers
WHERE
    -- Total spending of this specific customer
    (SELECT SUM(total_amount) FROM orders WHERE customer_id = customers.customer_id)
    >
    -- Average spending across all customers
    (SELECT AVG(spent) FROM
        (SELECT customer_id, SUM(total_amount) AS spent
         FROM orders GROUP BY customer_id) AS customer_table);

------------------------------------------------------------------------------------------------------------------------------------------------------------