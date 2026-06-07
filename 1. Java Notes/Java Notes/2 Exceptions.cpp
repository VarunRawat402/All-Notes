-----------------------------------------------------------------------------------------------------------------------------------------------------
Exception:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Checked Exception :
    → Compile time exception
    → IOException             → Error while reading or writing a file
    → FileNotFoundException   → Wrong file path / file not exist

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Unchecked Exception : 
    → Runtime Exception
    → ArrayIndexOutOfBoundsException  → Accessing invalid array index
    → NullPointerException            → Accessing null value

-----------------------------------------------------------------------------------------------------------------------------------------------------
Exception Handling:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Try-Catch Block:

    try {
        int result = 10 / 0;
    } catch (ArithmeticException e) {
        System.out.println("Cannot divide by zero!");
    }

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Finally block :
    → Always executes whether exception occurs or not
    → Commonly used to close resources
    → If you return something in try, catch and finally, then finally overrides the other two returns.

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Throw Keyword:
    → Used to manually throw an exception inside a method.

Ex:
public void checkAge(int age) {
    if (age < 18) {
        throw new IllegalArgumentException("You must be 18 or older.");
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Throws Keyword:
    → Used to tell what exception this method might throw
    → Caller must handle or propagate

-----------------------------------------------------------------------------------------------------------------------------------------------------

5: Custom Exception:

Ex:
class AgeException extends Exception {
    public AgeException(String message) {
        super(message);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------
Global Exception Handling (Spring Boot):
-----------------------------------------------------------------------------------------------------------------------------------------------------

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

public class ErrorResponse {
    private String message;
    private int status;
    private long timestamp;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------
