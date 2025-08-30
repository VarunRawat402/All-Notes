-------------------------------------------------------------------------------------------------------------------------------
Static:

Static is used to share a method or variable across all instances of a class instead of creating separate copies for each object.
-------------------------------------------------------------------------------------------------------------------------------

Static Variables (Class-Level Variables)

Belongs to the class, not to any specific object.
Shared by all objects of the class (only one copy exists in memory).
Changes to a static variable affect all objects.
You cannot use 'this' in static
Outer classes cannot be static, Only inner classes can be static because inner classes have reference of outer class

-------------------------------------------------------------------------------------------------------------------------------

Code:

// school is static, so all objects share the same value.
// If one object changes school, all objects see the updated value.
class Student {

    // Static variable
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
Cannot access non-static (instance) variables directly.
Used for utility/helper functions that dont depend on object data.

Code:

class MathUtils {
    static int square(int x) { // Static method
        return x * x;
    }
}

public class Main {
    public static void main(String[] args) {
        int result = MathUtils.square(5); // Calling static method using class name
        System.out.println("Square of 5: " + result);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static methods can only access static variables
Ex:

public class Student{

    String name = "varun";
    static int age = 24;
    
    //Cannot access non static variable
    static void getName(){
        System.out.println(name);           //Error
    }

    //Can access static variable
    static void getAge(){
        System.out.println(age);
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Static Block (Runs Once When Class Loads)

Executes when the class is loaded into memory (before any object is created).
Used for static initialization.

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
Used for grouping related classes together.
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
        Outer.Inner obj = new Outer.Inner(); // No need to create Outer class object
        obj.show();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Final Keyword:

1: Variables -> These can be defined while declaring or in the constructor.
Final variable can be defined only once you can either define it while declareing or in the
constructor later.  
Ex - final int a=5;
Ex- class hello(final int a){
    a = 5;
}

2: Functions : Final functions cannot be overriden in the child classes.
Ex - public final void hello(){
}

3: Classes: Final classes cannot be inherited by the child class.
Every function in the final class are automatically final since final class cannot be
inherited there is not way to override the function in the final class.
Ex - public final class Person{
}

4: Objects:
You can change the value of the final objects
But You cannot reassign the final object 

Ex: 
Student s1 = new Studene("varun")
s1.setName = "new name";                    //Allowed
s1 = new Student("New name")                //Not Allowed


-----------------------------------------------------------------------------------------------------------------------------------------