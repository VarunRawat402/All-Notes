-------------------------------------------------------------------------------------------------------------------------------
InnerClasses:
-------------------------------------------------------------------------------------------------------------------------------

An inner class is a class inside another class. It helps in grouping related logic and encapsulating details.

Why Use Inner Classes?
✅ To logically group classes that are used only in one place.
✅ To improve encapsulation (hide implementation details).
✅ To make code more readable and maintainable.

-------------------------------------------------------------------------------------------------------------------------------

1: Member Inner Class

A regular class inside another class.
Inner class Can access private members of the outer class.
Needs an object of the outer class to create an instance.
Cannot use inner class method using outer class object
Inner class object cannot use outer class methods inside main it 
can only access inside the inner class

Code:

class Outer {

    private String message = "Hello from Outer!";

    public void sayHello(){
        System.out.println("Hello");
    }

    // Member inner class
    class Inner { 
        void showMessage() {
            System.out.println(message); // ✅ Can access private members
        }
    }
}

public class Main {
    public static void main(String[] args) {

        Outer outer = new Outer();              // Create Outer class object
        Outer.Inner inner = outer.new Inner();  // Create Inner class object
        inner.showMessage();                    // Call method
        inner.sayHello();                       //Cannot call outer class method using inner object
    }
}

-------------------------------------------------------------------------------------------------------------------------------

2: Static Nested Class

A static class inside another class.
Can only access static variables of outer class
Can be created without an instance of the outer class.

class Outer {

    static String message = "Hello from Outer!";

    // Static Nested Class
    static class Inner { 
        void display() {
            System.out.println(message); // ✅ Can access only static members
        }
    }
}

public class Main {
    public static void main(String[] args) {

        // ✅ No need for Outer class object
        Outer.Inner inner = new Outer.Inner(); 
        inner.display();
    }
}

-------------------------------------------------------------------------------------------------------------------------------

3: Anonymous Inner Class

A class without a name.
Used for quick, one-time use.
Created while defining an object.


interface Greeting {
    void sayHello();
}

public class Main {
    public static void main(String[] args) {

        // Anonymous inner class implementing Greeting interface
        Greeting greet = new Greeting() {
            public void sayHello() {
                System.out.println("Hello from Anonymous Inner Class!");
            }
        };

        // Calling method
        greet.sayHello(); 
    }
}

-------------------------------------------------------------------------------------------------------------------------------