-------------------------------------------------------------------------------------------------------------------------------
Exception:
An exception is an error that occurs during program execution, disrupting normal flow.
-------------------------------------------------------------------------------------------------------------------------------

1: Checked Exception :

Occurs at compile time
Must Handle them or compilation error will come

Example: 
IOException → Issues during reading a file
FileNotFoundException = path of file doesnt exist

-------------------------------------------------------------------------------------------------------------------------------

2: Unchecked Exception : 
Occurs at Run time 
No need to handle them explicitly
Should still be handled to avoid application crashes

Example: 
ArrayIndexOutOfBoundsException = When accessing the index that out of size
ArithmeticException = illegal arithmetic expression

-------------------------------------------------------------------------------------------------------------------------------

Exception Handling:
    Handling exceptions ensures the application continues running instead of crashing.

1. Try-Catch Block:
    Place risky code inside try
    If an exception occurs, it is caught in the catch block

public class Main {
    public static void main(String[] args) {

        try {
            int result = 10 / 0;                            // 🚨 This will cause an exception
        } catch (ArithmeticException e) {
            System.out.println("Cannot divide by zero!");
        }
    }
}

Catching Multiple Exceptions:

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
    Always executes, whether an exception occurs or not
    Executes even if the try block returns a value
    Commonly used to close resources (database connection, files, streams, etc.)

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
    Used to manually throw an exception inside a method.

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
    Used to specify what exceptions the method might throw
    Informs the caller that they must handle the exception
    A method can either handle the exception using try–catch or pass it upward using throws

-------------------------------------------------------------------------------------------------------------------------------

Exception Handled inside the method (no need for throws):

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

Not handled inside the method → must declare throws:

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

Key Takeaways (for interviews & exams)

Checked exceptions = compile-time errors → must handle.
Unchecked exceptions = runtime errors → may crash app if not handled.
finally always executes → best for closing resources.
throw → to actually throw an exception.
throws → declares exceptions a method might throw
Custom exceptions → extend Exception

-------------------------------------------------------------------------------------------------------------------------------

GLOBAL EXCEPTION HANDLING:

//Used to handle exceptions globally in whole application
@RestControllerAdvice
public class GlobalExceptionHandler {

    @ExceptionHandler(ResourceNotFoundException.class)
    public ResponseEntity<ErrorResponse> handleNotFound(ResourceNotFoundException ex) {
        ErrorResponse error = new ErrorResponse();
        error.setMessage(ex.getMessage());
        error.setStatus(HttpStatus.NOT_FOUND.value());
        error.setTimestamp(System.currentTimeMillis());

        return new ResponseEntity<>(error, HttpStatus.NOT_FOUND);
    }

    @ExceptionHandler(Exception.class)
    public ResponseEntity<String> handleGenericException(Exception ex) {
        return new ResponseEntity<>("Something went wrong", HttpStatus.INTERNAL_SERVER_ERROR);
    }
}


Custom Error Response:

ErrorResponse Class:
public class ErrorResponse {
    private String message;
    private int status;
    private long timestamp;
}

-------------------------------------------------------------------------------------------------------------------------------
