-------------------------------------------------------------------------------------------------------------------------------
Exception:
An exception is an error that occurs during program execution, disrupting normal flow.
-------------------------------------------------------------------------------------------------------------------------------

There are 2 types of Exception:

-------------------------------------------------------------------------------------------------------------------------------

1: Checked Exception :

Occurs at compile time
Must Handle them or compilation error will come

Ex:
FileReader fileReader = new FileReader("/users/pa/sample.txt");

IOException = Reading a file that does not exist
FileNotFoundException = path of file doesnt exist

-------------------------------------------------------------------------------------------------------------------------------

2: Unchecked Exception : 
Occurs at Run time 
No need to handle them explicitly
But should handle them otherwise runTimeException will come and application will break down

Ex:
int a = 1/0;
This will give us Arithmetic Exception which is a part of Runtime Exception.

ArrayIndexOutOfBoundsException = When accessing the index that out of size
ArithmeticException = illegal arithmetic expression

-------------------------------------------------------------------------------------------------------------------------------

Exception Handling:

1. Try-Catch Block:

// Put the risky code in try and if any exception comes 
// catch that in the catch block
public class Main {
    public static void main(String[] args) {

        try {
            int result = 10 / 0; // 🚨 This will cause an exception
        } catch (ArithmeticException e) {
            System.out.println("Cannot divide by zero!");
        }
    }
}

//We can catch multiple exceptions too using try catch
//If the code can give multiple exceptions based on user values
public class Main {
    public static void main(String[] args) {
        try {
            int[] numbers = {1, 2, 3};
            System.out.println(numbers[5]); // 🚨 Invalid index
        } catch (ArithmeticException e) {
            System.out.println("Arithmetic error!");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index access!");
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------

2: Finally block :
It will get executed no matter what
Weather you get exception or you code runs without exception
Even if you return something in the try block it will still
get executed.

It is generally used to release the database connection 

Ex:
public static void main(String[] args){
    System.out.println(hello());
}

public static String hello(){
    try{
        FileReader fileReader = new FileReader("C:/Users/varun.rawat/OneDrive - HCL Technologies Ltd/Desktop/sample1.txt.txt");
        return "String is returned through try case";
    }catch (IOException e){
        e.printStackTrace();
    }finally {
        System.out.println("In the final block");
    }
    return null;
}

-------------------------------------------------------------------------------------------------------------------------------

3: Throw Keyword:
We can manually throw an exception using throw.

Ex:
public class Main {

    public static void checkAge(int age) {
        if (age < 18) {
            throw new IllegalArgumentException("You must be 18 or older.");
        }
        System.out.println("Welcome!");
    }

    public static void main(String[] args) {
        checkAge(16);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

4: Throws Keyword:
The throws keyword in Java is used in method signatures to declare exceptions that a method might throw during execution.
It tells the caller of the method that they need to handle the exception.

-------------------------------------------------------------------------------------------------------------------------------

In this Example I handled the Exception using try catch block so I dont
need to use Throws Exception:

public static void main(String[] args) {
    hello();
}

public  static void hello(){
    try{
        FileReader fileReader = new FileReader("users/path/sample.txt");    
    }catch (IOException e){
        e.printStackTrace();
    }
}

In this Example I didnt handled the exception in the method instead
I throwed the exception to the back function due to this I had to use
Throws IOException in the method declaration and In the back function
I handled the function using try catch block So I didnt needed to
use the throws IOException in the main method:

public static void main(String[] args) {
    try{
        hello();
    }catch (IOException e){
        e.printStackTrace();
    }
}

public  static void hello() throws IOException{
    FileReader fileReader = new FileReader("users/path/sample.txt");
}

-----------------------------------------------------------------------------------------

5: Custom Exception:

We can create our own exceptions by extending the Exception class.

Ex:

// Custom exception
class AgeException extends Exception { 
    public AgeException(String message) {
        super(message);
    }
}

public class Main {

    static void checkAge(int age) throws AgeException {
        if (age < 18) {
            throw new AgeException("You are too young!");
        }
        System.out.println("Access granted.");
    }

    public static void main(String[] args) {
        try {
            checkAge(15);
        } catch (AgeException e) {
            System.out.println(e.getMessage());
        }
    }
}

-------------------------------------------------------------------------------------------------------------------------------