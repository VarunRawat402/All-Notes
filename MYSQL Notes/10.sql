GROUP BY:
    It is used to group the data and aggregate the grouped data
    You can only select the columns that are part of group by clause
    You cannot select other columns that are not part of group by clause
    You can only select other columns if they are part of aggregate functions like count, sum, avg, min, max

Synatx:

select * from table_name group by col1, col2
select * from table_name where condition group by col1
select * from table_name where condition group by col1 having condition

Count Students in each Department:
select department, count(*) from student group by department

Sum of salaries by department:
select department, sum(salary) from student group by department