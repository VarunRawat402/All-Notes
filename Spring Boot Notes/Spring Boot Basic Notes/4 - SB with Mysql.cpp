-----------------------------------------------------------------------------------------
Lecture 3: Spring Boot with mysql without JPA
-----------------------------------------------------------------------------------------

CONNECTION:
In order to save data in the Database we need to first establish a connection to connect to the database.
There are 2 ways to establish the connection

---------------------------------------------------------------------------------------------------------------------------------------

1: In the Repository:
    In this we will make new connection for every new Repository for example if we have person Repository
    we will make 1 connection there and if we have another Repository author we will create another connection in that Repository

Code:

@Repository
public class PersonRepository {

    private Connection connection;
    //This connection will be initialized by default constructor only once when the application will start
    PersonRepository() throws SQLException {
        this.connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/jbdl33_person", "root",
                "root402");
    }
}

---------------------------------------------------------------------------------------------------------------------------------------

2: In configuration class:
    In this we will make a configuration class and configure the connection there and will use
    that connection in every Repository we will make by using @Autowired annotation
    We can use that class connection in the Repository classes by
    @Autowired
    private Connection connection;

Code:

@Configuration
public class DBconfig {

    @Bean
    public Connection getConnection() {
        try {
            return (Connection) DriverManager.getConnection("jdbc:mysql://localhost:3306/jbdl33_person", "root",
                    "root402");
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
}

The Advantage of using the DBconfig class is we are only using 1 connection to connect to the database
Using the first method we will have as many connnection as Repository class which can lead to more heap memory
and our database has limited number of connection so it is also called overusing of connection.

---------------------------------------------------------------------------------------------------------------------------------------

Question : We are getting error in this when we are autowired the connetion bean in the Repository class why?
Ans : If you have @Autowired dependency and constructor the constructor will get invoke first.

Code:

@Repository
public class PersonRepository {
    
    @Autowired
    private Connection connection;

    PersonRepository() throws SQLException{
        createTable();
    }
}

In this @Autowired is correct but the problem is our constructor is getting called first and createTable function requires 
connection bean to work but since our constructor is getting invoked before @Autowired it means our connection is not 
injected here so we are getting error. 
In these type of scenarios we will use constructor dependency injection to correct this.
In this constructor is getting invoked and our connection is getting injected then createTable is getting invoked.

Code:
@Repository
public class PersonRepository {
    
    private Connection connection;

    PersonRepository(Connection connection) throws SQLException{
        this.connection = connection;
        createTable();
    }
}

---------------------------------------------------------------------------------------------------------------------------------------

Statement:

It is an interface which is used to write SQL queries to perform some actions in the database.
//This will initialize the statement to write sql queries then we write the sql queries using execute method.
Statement statement = connection.createStatement();
statement.execute("insert into person (id, first_name, last_name, age) VALUES(1,'Varun','Rawat'23)");

---------------------------------------------------------------------------------------------------------------------------------------

Difference Between execute and executeUpdate in Statement interface.

statement.execute: The execute method is used to execute SQL statements that can return multiple results,
such as SELECT statements.
It is typically used for executing queries that return result sets, and it can handle both queries and updates.
It returns a boolean value, indicating whether the first result is a ResultSet. 
If its true, you can retrieve a ResultSet with getResultSet().
If the SQL statement being executed is an INSERT, UPDATE, DELETE, or any other statement that does not return a result set, 
the execute method will still work, but you wont be able to retrieve any results.

statement.executeUpdate = The executeUpdate method is used to execute SQL statements that perform data manipulation operations,
such as INSERT, UPDATE, or DELETE.
It is used when you want to execute SQL statements that modify the database (adding records, updating data, or deleting).
It returns an integer value representing the number of rows affected by the SQL statement.

Insert / Update / Delete - ExecuteUpdate
Select - ExecuteQuery

---------------------------------------------------------------------------------------------------------------------------------------

Code to write sql query using statement:

This is a static query in which p values cannot be passed
public void createPerson(Person p){

    try {
        Statement statement = connection.createStatement();
        int result = statement.executeUpdate("insert into person (id, first_name, last_name, age, dob) " +
                "VALUES(1, 'ABC', 'DEF', 20, '01-01-2002')");
    } catch(SQLException e){
        e.printStackTrace();
    }
}

---------------------------------------------------------------------------------------------------------------------------------------

Prepared Statement;

It is used to write Dynamic queries where we write the sql query and put the values in the query later.
It is an interface.

Code to write sql query using PreparedStatement;

We can also initialize PreparedStatement in the createPerson function but then everytime this function gets called
a new prepareStatement will be initialized which is not bad but initializing it in the starting will be better so
only 1 prepareStatement will be used for the whole process.

? in the sql query is placed so we can place Dynamic values there later.
To fill the ? we have many options like
statement.setInt()
statement.setString()
it takes 2 parameter, First is the column number and second is the value.
Since we are not filling ID so the first column will be first_name and so on.

@Repository
public class PersonRepository {
    
    private Connection connection;
    private PreparedStatement statement;

    PersonRepository(Connection connection) throws SQLException{
        this.connection = connection;
        createTable();
        this.statement = connection.prepareStatement("insert into person (first_name, last_name, age, dob) " +
                     "VALUES(?,?,?,?)");
    }

    public void createPerson(Person p){

        try {
            statement.setString(1,p.getFirstName());
            statement.setString(2, p.getLastName());
            statement.setInt(3, p.getAge());
            statement.setString(4, p.getDob());
            int result = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

---------------------------------------------------------------------------------------------------------------------------------------

How to get all the person details which are present in the database?

We used statement here because we are not fetching and mapping details from the user
The details are already there so we can use statement.

So we will use executeQuery and use SQL command to get all the values which will give us
the whole result set like tables and columns so from the result set we need to convert it into
the List of persons so we will make a list of person then we will iterate through the result set
using while then with the commands of resultset we can get all the details one by one using get command
and store it in the variables 
Now there is 2 ways to get the values from the columns
First is to get by using the name of the column
Second is to get by using the number of the column
Now Problem is in both 
Lets say we use name and then someone changed the name of the column so our code will fail
Lets say we use column number and someone added a column inbetween then our code will fail
Lets say we dont know the database then we dont know the name of the columns or number
Lets say there are 100 columns then we need to write 100 lines of code and 100 varibale.
This problem is solved by HIBERNATE which will automatically map the java object to 
DB which we will study in next chapter.
HIBERNATE = ORM = Object Relation Mapping where object is java object and Relation is database.

Meanwhile we do this with mysql.

Code:
public List<Person> getPeople(){
    
    Statement statement;
    try {
        statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("select * from person");
        List<Person> l1 = new ArrayList<>();

        while(resultSet.next()){

            int id = resultSet.getInt("id");
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");
            int age = resultSet.getInt(4);
            String dob = resultSet.getString(5);

            Person person = Person.builder().firstName(firstName).lastName(lastName).age(age).dob(dob).id(id).build();
            l1.add(person);
        }
        return l1;
    } catch (SQLException e) {
        e.printStackTrace();
    }
    return null;
}

---------------------------------------------------------------------------------------------------------------------------------------

JDBC : Protocol which is used to connect java application to the DB 
JDBC Template : Dependency which allows you to map your java object to DB Relation
just like HIBERNATE.
RowMapper : Same like Hibernate.

JPA : Java Persistence API

It is like an interface where we will initialize functions like save(), find(), delete()
and Hibernate is like a class where we will define the functionality of those functions.
We will be interacting with the JPA.
We can use other things also if we dont want to use Hibernate like eclipse link, open JPA.

There are 2 Types of DBs:

1: No-Relational - In this you only need DB Driver to use database and there is no common framework for DB
because every No-Relational DB store the data in different manner and there is no structure thats why there is no
common framework.

2: Relational - In this you need Hibernate/JPA and DB Driver to use database because in this the data
is stored in tables and rows and structure is Relational and common in every DB so we have common framework to use.

Lets say we have a instagram page and we see 5 post and then we scroll and it loads and see next 5 post and this is 
like infinite scrolling so how to do it?

This is done by using limit and offset

select * from person limit 5 offset 5;

limit : it means the number of post / data we will show in one time.
If the limit value is 5 It will show only 5 post / data in one time.

Offset : It skips the post / data based on value
If the value of offset is 10 then it means it will skip the 10 post / data from the start.
It is calculated by Page Number * limit.

Ex: 

Select * from person where limit 5 offset 5;

First the offset value will be 0 because page number will be 0 so It will skip 0 post and show first 5 post.
Next page number will be 1 so offset value will be 1*5 = 5 so it will skip first 5 post and it will show 5-10 post
and so on and so on.

---------------------------------------------------------------------------------------------------------------------------------------