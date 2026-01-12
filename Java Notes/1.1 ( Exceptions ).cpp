-------------------------------------------------------------------------------------------------------------------------------
Exception:
An exception is an error that occurs during program execution, disrupting normal flow.
-------------------------------------------------------------------------------------------------------------------------------

1: Checked Exception :
    Occurs at compile time
    Must Handle them or compilation will fail

Example: 
IOException → Issues during file reading
FileNotFoundException → File path does not exist

-------------------------------------------------------------------------------------------------------------------------------

2: Unchecked Exception : 
    Occurs at Run time 
    Should be handled to avoid application crashes

Example: 
ArrayIndexOutOfBoundsException → Accessing invalid array index
ArithmeticException → Illegal arithmetic operation (e.g., divide by zero)

-------------------------------------------------------------------------------------------------------------------------------

Exception Handling:
    Ensures the application continues running instead of crashing

1. Try-Catch Block:
    Place risky code inside try
    If an exception occurs, it is caught in the catch block

    try {
        int result = 10 / 0;  // Exception
    } catch (ArithmeticException e) {
        System.out.println("Cannot divide by zero!");
    }

-------------------------------------------------------------------------------------------------------------------------------

2: Finally block :
    Always executes whether exception occurs or not
    Commonly used to close resources

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
}

-------------------------------------------------------------------------------------------------------------------------------

4: Throws Keyword:
    Specify which exceptions a method might throw
    Caller must handle or propagate

-------------------------------------------------------------------------------------------------------------------------------

5: Custom Exception:
    Create your own exceptions by extending Exception class

Ex:
class AgeException extends Exception {
    public AgeException(String message) {
        super(message);
    }
}
-------------------------------------------------------------------------------------------------------------------------------

Key Takeaways

Checked exceptions      → compile-time → must handle
Unchecked exceptions    → runtime → may crash app if unhandled
finally                 → always executes → good for closing resources
throw                   → to actually throw an exception
throws                  → declares which exceptions a method might throw
Custom exceptions       → extend Exception

-------------------------------------------------------------------------------------------------------------------------------

Global Exception Handling (Spring Boot):

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
