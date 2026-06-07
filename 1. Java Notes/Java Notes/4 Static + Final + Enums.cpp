-----------------------------------------------------------------------------------------------------------------------------------------------------
Static:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Static Methods():
    → Can only access static variables and static methods
    → Used for utility classes
    → Cannot be overridden

Static Blocks:
    → Executes one time when the class is loaded into memory
    → Runs before main()
    → Used to initialize connections
    → Multiple static blocks allowed → run in order written

-----------------------------------------------------------------------------------------------------------------------------------------------------
Final Keyword:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Final Variables:
    → Cannot change once assigned
    → Initialized directly or in constructor

2. Final functions:
    → Cannot be overridden by child classes

3. Final Classes:
    → Cannot be extended.
    → All methods automatically become final methods

4. Final Objects:
    → You can change the properties of final object
    → You cannot reassign the object again

-----------------------------------------------------------------------------------------------------------------------------------------------------
Enums:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Used to define constants
→ Alternate to public static final 

→ Enums improve readability, maintainability, and type safety.
→ Enum objects cannot be created using the new keyword.

-----------------------------------------------------------------------------------------------------------------------------------------------------

public class Constants {
    public static final String USER = "USER";
    public static final String STUDENT = "STUDENT";
    public static final String ADMIN = "ADMIN";
}

public enum Constants {
    USER, STUDENT, ADMIN
}

-----------------------------------------------------------------------------------------------------------------------------------------------------