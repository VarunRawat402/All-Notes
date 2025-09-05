------------------------------------------------------------------------------------------------------------------------------------------------------------
Mastering SUBQUERIES:
------------------------------------------------------------------------------------------------------------------------------------------------------------

Find all customers who have placed atleast one order:
select * from customers where customer_id in (select distinct customer_id from orders);

Find all customers who havent placed any order:
select * from customers where customer_id not in (select distinct customer_id from orders)

Find Products with a price higher than average:
select * from products where price > (select avg(price) from products)

Find categories that have more than 2 products:
select category, count(*) as c from products group by category having c >2

Find all orders made by customer from texas
select * from orders where customer_id in (select customer_id from customers where state = 'TX')

Find all customers who ordered electronics products:
select * from customers where customer_id in 
(select customer_id from orders where order_id in 
(select  distinct order_id from order_items where product_id in 
(select product_id from products where category = 'Electronics')))

Advanced Subqueries:
    -- We used in when have the a list of things
    -- But when we want to use result_set table as subquery then use from with alias of result_set table

Find customers who spent more than average:
    -- calculates total spending of each customer
    -- calculate average of total spending 
    -- identify customers whose total spending is greater than avg

select * from customers where (select sum(total_amount) from orders where customer_id = customers.customer_id) 
>
(select avg(spent) from (select customer_id, sum(total_amount) as spent from orders group by customer_id) as customer_table)

Find customers who have ordered all products in the 'Electronics' category:
