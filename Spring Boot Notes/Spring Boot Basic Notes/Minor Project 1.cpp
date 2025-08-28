-----------------------------------------------------------------------------------------
Lecture 12: Minor Project 1 : LIBRARY MANAGEMENT SYSTEM:
-----------------------------------------------------------------------------------------

We will have CRUD Operations for the Student

We will have CRUD Operations for the Book

We will not have CRUD Operations for the author because we will get the details of the author in the book

But We will have seperate tables for the author and the book for Normalization to decrease the redundant data.
Explaination:
Bookid        bookName    ............   AuthorName    AuthorEmail     AuthorNumber     Author...........
1               ABC                         Varun       varun@               91              
2               DEF                         Varun       varun@               91
3               GHI                         Varun       varun@               91

Now if varun write 100 books its different for book columns but AuthorName, AuthorEmail and AuthorNumber are same for 100 rows
so we can say we are storing duplicate data / repeating data in the table which is expanding this table.

So, we will make a seperate table for author and have a column of AuthorId which will be in Book table as a foreign key
which will be used to retrieve the data of author using joins SQL commands.
Example: 

AuthorID       AuthorName         AuthorEmail          AuthorNumber
1                 Varun              varun@                 91

Bookid        bookName    ............   AuthorID   
1               ABC                          1 
2               DEF                          1
3               GHI                          1

----------------------------------------------------------------------------------------------------------------------

Never store your foreign key as a list, your queries will become slow
always store column as a foreign key which have a single value.

We store student as a foreign key in book table because it has 1:M relationship to Book
In Book entity    - use @JoinColumn on student to make student foreign key and map the student to the book
In Student entity - use mappedby to map the book entity to the student if you want a bidirectional relationship

----------------------------------------------------------------------------------------------------------------------

Time Stamp is taken from the application server time stamp not the DB server time stamp.

@CreationTimestamp:
    This annotation is used to automatically set the value of the annotated field to the current timestamp when the entity is first inserted.

@UpdateTimestamp:
    This annotation is used to automatically update the value of the annotated field to the current timestamp whenever the entity is updated and inserted.

Ex:
    @CreationTimestamp
    private Date createdOn;

    @UpdateTimestamp
    private Date updatedOn;

----------------------------------------------------------------------------------------------------------------------

JPA relationship:

1: UNI-DIRECTIONAL
2: BI-DIRECTIONAL:

Lets say there are 2 class - book and student

In book table we are storing the StudentId as a foreign key to map the books to Student which means we 
are storing the student object in the book class.
So storing Student in the book class and not storing/using book in student class
is called UNI-DIRECTIONAL relationship.

But

In simple terms having any relation with book in student class and not
having that shown in table is called BI-DIRECTIONAL Relationship.
Like List<Book> book() is just a placeholder in the student class and not be storing in the DB table.
So when we make a GET API to get all the details of the student we will get the details of the student
and also the list of books he has.

----------------------------------------------------------------------------------------------------------------------

FOREIGN KEY CONSTRAINTS:

1: Adding a student in book table which does not exist in the student table
Ex-
We assigned book b1 to student s3 but only 2 student are in the student table s1 and s2
so it will give us the error

2: Deleting a student from the student table while it has a reference from the book table
Ex:
In book table book b1 is assigned to student s1 but we are Deleting the student s1 so this
will give error because student s1 has a reference in the book table.

Question: Why we use integers make the primary key not the strings?
Ans : Because when we search with the help of primary key we search in the primary key and searching requires
comparing and comparison of strings is much more time consuming and expensive than any other datatype 
and integer has the least so thats the reason we use integer in primary key.

----------------------------------------------------------------------------------------------------------------------


