-------------------------------------------------------------------------------------------------------------------------------
Enums:
-------------------------------------------------------------------------------------------------------------------------------

enum is a special class in Java used to define a collection of constants (fixed values).
Alternative to using public static final constants.
Enums improve readability, maintainability, and type safety.
You cannot create new enum objects using new keyword.

-------------------------------------------------------------------------------------------------------------------------------

// Without enum (harder to manage, less readable)
public class Constants {
    public static final String USER = "USER";
    public static final String STUDENT = "STUDENT";
    public static final String ADMIN = "ADMIN";
}

// With enum (cleaner, safer, less code)
public enum Constants {
    USER, STUDENT, ADMIN
}

-------------------------------------------------------------------------------------------------------------------------------

Enums can have:
    Variables
    Constructors
    Methods (getters, setters, custom methods)

Code:

enum Size {

    SMALL(10), MEDIUM(20), LARGE(30); 

    private int value;      //This is 10,20,30 for small,medium,large

    Size(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}

public class Main {
    public static void main(String[] args) {
        Size s = Size.MEDIUM;
        Size s = new Size(10);              //Error
        
        System.out.println("Size: " + s + ", Value: " + s.getValue());
        //Size: MEDIUM, Value: 20
    }
}

-------------------------------------------------------------------------------------------------------------------------------