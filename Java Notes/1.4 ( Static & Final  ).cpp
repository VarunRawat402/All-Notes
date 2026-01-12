-------------------------------------------------------------------------------------------------------------------------------
Static:
    static is used when you want a variable or method to belong to the class itself instead of each object.

-------------------------------------------------------------------------------------------------------------------------------

Static Variables (Class-Level Variables)
    Belong to the class, not to individual objects
    Changing the static variable affects all objects
    this cannot be used inside static methods because this refers to an object.

-------------------------------------------------------------------------------------------------------------------------------

Static Methods (Class-Level Methods)

Can be called using the class name (no object needed).
Can only access static variables and static methods.
Used for utility/helper logic

-------------------------------------------------------------------------------------------------------------------------------

Static methods can only access static variables:

public class Student {

    String name = "Varun";
    static int age = 24;

    static void getName() {                      //Error (non-static)
        System.out.println(name);              
    }

    static void getAge() {
        System.out.println(age);                // ✅ Allowed
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static Block (Runs Once When Class Loads):

Executes once when the class is loaded into memory
Runs before main()
Used to initialize static variables

Code:
class Example {
    static int value;

    static {
        value = 100;
        System.out.println("Static block executed");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("Value: " + Example.value);
    }
}


-------------------------------------------------------------------------------------------------------------------------------
Final Keyword:
-------------------------------------------------------------------------------------------------------------------------------

1. Final Variables:
    Can be assigned only once.
    Must be initialized at declaration or in constructor

Ex:
final int a = 5;

class Hello {
    final int x;
    Hello() {
        x = 10;     // Allowed
    }
}

-------------------------------------------------------------------------------------------------------------------------------

2. Final functions:
    Cannot be overridden by child classes

Ex :
public final void hello() {
}

-------------------------------------------------------------------------------------------------------------------------------

3. Final Classes:
    Cannot be inherited.
    All methods automatically become non-overridable

Ex - 
public final class Person{
}

-------------------------------------------------------------------------------------------------------------------------------

4. Final Objects:
You can change the value of the final objects
But You cannot reassign the final object 

Ex: 
final Student s1 = new Student("Varun");

s1.setName("New Name");         // ✅ Allowed
s1 = new Student("X");          // ❌ Not allowed

-----------------------------------------------------------------------------------------------------------------------------------------