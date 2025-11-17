-------------------------------------------------------------------------------------------------------------------------------
Static:
    static is used when you want a variable or method to belong to the class itself instead of each object.

-------------------------------------------------------------------------------------------------------------------------------

Static Variables (Class-Level Variables)
    Belong to the class, not to individual objects.
    Only one copy exists in memory, shared by all objects.
    Changing the static variable updates it for all instances.
    this cannot be used inside static methods because this refers to an object.
    Outer (top-level) classes cannot be static.
    Only inner classes can be static because a static inner class does not need a reference to the outer class.

-------------------------------------------------------------------------------------------------------------------------------

Code:
// 'school' is static, so all Student objects share the same value.

class Student {

    static String school = "Mayo International School"; 
    String name;

    Student(String name) {
        this.name = name;
    }

    void display() {
        System.out.println(name + " studies at " + school);
    }
}

public class Main {
    public static void main(String[] args) {

        Student s1 = new Student("Alice");
        Student s2 = new Student("Bob");

        s1.display();                   //Alice studies at Mayo International School
        s2.display();                   //Bob studies at Mayo International School

        // Changing static variable affects all instances
        Student.school = "XYZ School";
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static Methods (Class-Level Methods)

Can be called using the class name (no object needed).
Can only access static variables and static methods.
Used for utility/helper functions that dont depend on object data.

Code:

class MathUtils {
    static int square(int x) {
        return x * x;
    }
}

public class Main {
    public static void main(String[] args) {
        int result = MathUtils.square(5);                   // Calling static method using class name
        System.out.println("Square of 5: " + result);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static methods can only access static variables
Ex:

public class Student{

    String name = "varun";
    static int age = 24;
    
    static void getName(){                  //Cannot access non static variable
        System.out.println(name);           //Error
    }

    static void getAge(){                   //Can access static variable
        System.out.println(age);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static Block (Runs Once When Class Loads):

Executes automatically when the class is loaded into memory.
Runs before the main method and before any object is created.
Used for initializing static variables.

Code:

class Example {
    static int value;

    // Static block runs when class is loaded
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

Static Nested Class (Independent Inner Class)

A static nested class does not need an instance of the outer class.
Useful for grouping related classes without requiring an outer class object.
No need to create an object of Outer to access Inner.

Code:
class Outer {
    static class Inner {
        void show() {
            System.out.println("Static Inner Class");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Outer.Inner obj = new Outer.Inner();            // No need to create Outer class object
        obj.show();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Final Keyword:

1. Final Variables:
    Can be assigned only once.
    Must be initialized either at declaration or in the constructor.
    Cannot be changed later.

Ex:
final int a=5;

Ex:
class Hello {
    final int x;
    Hello() {
        x = 10;     // Allowed (initialized in constructor)
    }
}

2. Final functions:
    Final functions cannot be overriden in the child classes.

Ex - public final void hello(){
}

3. Final Classes:
    Cannot be inherited.
    Since the class cannot be extended, its methods also cannot be overridden.

Ex - public final class Person{
}

4. Final Objects:
You can change the value of the final objects
But You cannot reassign the final object 

Ex: 

final Student s1 = new Student("Varun");

s1.setName("New Name");     // Allowed (modifying data inside object)
s1 = new Student("X");      // Not allowed (reassigning reference)

-----------------------------------------------------------------------------------------------------------------------------------------