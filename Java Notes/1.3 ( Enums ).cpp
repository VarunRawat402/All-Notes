-------------------------------------------------------------------------------------------------------------------------------
Enums:
-------------------------------------------------------------------------------------------------------------------------------

An enum is a special type in Java used to define set of constant values.
Alternative to using public static final constants.
Enums improve readability, maintainability, and type safety.
Enum objects cannot be created using the new keyword.

-------------------------------------------------------------------------------------------------------------------------------

Without enum (less maintainable, less readable):

public class Constants {
    public static final String USER = "USER";
    public static final String STUDENT = "STUDENT";
    public static final String ADMIN = "ADMIN";
}

With enum (cleaner, safer):

public enum Constants {
    USER, STUDENT, ADMIN
}

-------------------------------------------------------------------------------------------------------------------------------

Enums Can Have:
    Variables
    Constructors
    Methods (getters, custom logic)
    You cannot make setters because enum fields should not be changed

Code:

enum Size {

    SMALL(10), MEDIUM(20), LARGE(30); 

    private int value;              // Assigned 10, 20, 30

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
        // Size s = new Size(10);  // ❌ Not allowed — cannot create enum objects

        System.out.println("Size: " + s + ", Value: " + s.getValue());
        // Output: Size: MEDIUM, Value: 20
    }
}

-------------------------------------------------------------------------------------------------------------------------------