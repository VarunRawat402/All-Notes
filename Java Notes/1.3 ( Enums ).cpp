-------------------------------------------------------------------------------------------------------------------------------
Enums:
-------------------------------------------------------------------------------------------------------------------------------

→ Used to define constants
→ Alternate to public static final 

→ Enums improve readability, maintainability, and type safety.
→ Enum objects cannot be created using the new keyword.

-------------------------------------------------------------------------------------------------------------------------------

public class Constants {
    public static final String USER = "USER";
    public static final String STUDENT = "STUDENT";
    public static final String ADMIN = "ADMIN";
}

public enum Constants {
    USER, STUDENT, ADMIN
}

-------------------------------------------------------------------------------------------------------------------------------

Enums Can Have:
    → Variables
    → Constructors (always private internally)
    → getters + static methods

Cannot have:
→ Public constructors
→ Setters (enum values should be immutable)

Code:

enum Size {

    SMALL(10), MEDIUM(20), LARGE(30); 

    private int value;                      // Assigned 10, 20, 30

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
        System.out.println(s.getValue());
    }
}

-------------------------------------------------------------------------------------------------------------------------------