----------------------------------------------------------------------------------------------------------------------
Transaction:
----------------------------------------------------------------------------------------------------------------------

There are 2 types of transaction we can do :
1: issue
2: Return

----------------------------------------------------------------------------------------------------------------------

Issue:

In order for a student to issue a book from the libarary:

1: Student must be a valid entity in the student table
2: Book shoule be present in the table and must be available
3: Create a transaction --> Saving in the transaction table
4: Make the book unavailable

@Transactional:
    This annotation is used on top of the transaction service so that service is run in transaction manner
    Transactional manner means everything in the code will run or nothing will run.
    Ex:
        If there are 3 operations: Insert, Find, Insert
        It manages to do the first insertion and failed at find so first insertion should be rolled back too.

Even if we put the @Transactional annotation the code will still not run in atomic way untill we know how 
to use Isoloation and Propogation with it perfectly.

----------------------------------------------------------------------------------------------------------------------

---------- Read About Isoloation and Propogation in @Transactional Annotation----------




