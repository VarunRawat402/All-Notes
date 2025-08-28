-------------------------------------------------------------------------------------------------------------------------------
Enums:
-------------------------------------------------------------------------------------------------------------------------------

A special class in Java used to define constants (fixed values).

📌 Instead of using final static variables, we use enum.
📌 Each value inside an enum is a constant.
📌 Enum can have variables and getters and setters
📌 Enum can have constructors

-------------------------------------------------------------------------------------------------------------------------------

We can define constants like this but its more syntax like this 
public class constants{
    private final static user = "USER";
    private final static student = "STUDENT";
    private final static admin = "ADMIN";
}

//Readable, Less code
public enum constants{
    USER,STUDENT,ADMIN
}

-------------------------------------------------------------------------------------------------------------------------------

Enum with Methods and Constructor
Enums can have fields, constructors, and methods like normal classes.

You have to initialize variables inside the class,
You cannot add values on the time of creation of object because they are constants and need
to be initialize at the compile time

Code:

enum Size {

    // Enum values with sizes
    SMALL(10), MEDIUM(20), LARGE(30); 

    private int value; // Variable inside enum

    // Constructor
    Size(int value) {
        this.value = value;
    }

        // Method to get value
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