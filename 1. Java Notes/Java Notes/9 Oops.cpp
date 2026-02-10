-----------------------------------------------------------------------------------------------------------------------------------------------------
Java OOPs:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Destructor:
    → Java does not have destructors.
    → Java uses Garbage Collection (GC).
    → Resource cleanup is done using close() or try-with-resources.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Default Constructor:
    → Automatically generated when no constructor is defined
    → If you define any constructor, default is not generated
    → Takes no parameters.

Parameterized Constructor:
    → Takes parameters to create object 

Copy Constructor: 
    → Takes another object as a parameter and creates a new object with the same values.
    → Used to duplicate objects.

Constructor Chaining:
    → When you create an object of a child class, the parent class constructor is called first, then the child class constructor.
    → Happens using super().

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
Primitive types are passed by value:
    → Changes inside method do not change the original value

Objects are passed by reference:
    → Changes inside method change the actual object

-----------------------------------------------------------------------------------------------------------------------------------------------------

Access Modifiers:

1: Public:
    → Accessible from anywhere (any class, any package).

3: Private:
    → Not accessible from any other class.

3: Protected:
    → Accessible within the same package.
    → Accessible in another package only through inheritance (subclass).

4: Default:
    → Accessible within the same package only.
    → Not accessible outside the package.

-----------------------------------------------------------------------------------------------------------------------------------------------------

POLYMORPHISM:
    → One object behaving in multiple forms.

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Method Overloading:
    → Compile time Polymorphism
    → Same method name, different parameters

Ex:
    public class Calculator {
        public int add(int a, int b) {
            return a + b;
        }

        public int add(int a, int b, int c) {
            return a + b + c;
        }
    }

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Method Overriding:
    → Runtime Polymorphism
    → A child class provides its own implementation of a parent class method.
    → The method call is decided at runtime based on the object type.

Ex:
    public class Animal {
        public void makeSound() {
            System.out.println("Some generic sound");
        }
    }

    public class Cat extends Animal {
        @Override
        public void makeSound() {
            System.out.println("Meow");
        }
    }

    Animal cat = new Cat();
    cat.makeSound();            // Calls Cat's makeSound() method

-----------------------------------------------------------------------------------------------------------------------------------------------------

INHERITANCE:
    → Using properties and methods of a parent class in a child class.

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Single Level Inheritance:

Ex:
    class Animal {}

    class Dog extends Animal {}

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Multilevel Inheritance:

Ex:
    class Animal {}

    class Dog extends Animal {}

    class Breed extends Dog{}

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Multiple Inheritance:    
    → In Multiple Inheritance 1 class can extends 2 classes or more.
    → In java we dont have multiple inheritance but we can acheive it through Interfaces.

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Hierarchical Inheritance:

Ex:
    class Animal {}

    class Dog extends Animal {}

    class Cat extends Animal{}

-----------------------------------------------------------------------------------------------------------------------------------------------------

ENCAPSULATION:
    → Binding data + methods together and hiding internal data from outside access.

Key Concepts of Encapsulation

Private fields          → Restricts the access of data.
Public getters/setters  → Controlled access of Data from oustide.
Better Control          → You can validate, restrict, or modify behavior when getting or setting values.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Super():
    → Calls parent class constructor
    → Used to initialize parent variables through constructor
    → Access parent class variables/methods (non-private) using super.variable / super.method()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Parent reference with Child object:

→ Parent p1 = new Child();
→ You can access parent variables and parent methods
→ You cannot access child variables and child methods
→ If parent methods are overriden then overriden methods will get executed ( run time polymorphism )

Note:
    → What you can access depends on the reference
    → What is going to be executed depends on the object

-----------------------------------------------------------------------------------------------------------------------------------------------------

Object Class:
    → The root class of all Java classes.
    
hashCode():
    → Returns a unique hash value of the object

equals():
    → Default: compares reference of the objects.
    → Overridden in String, Integer, etc., to compare values.

toString():
    → It is used to return the String representation of Object

Finalize():
    → It is called automatically by the GC when object has no reference
    → It is used for cleanup Functions
    → Depricated after java 9

-----------------------------------------------------------------------------------------------------------------------------------------------------

Shallow Copy
    → Top-level object does not share reference
    → Nested objects share same reference
    → Default Behavior

Deep Copy
    → Top-level and nested objects both does not share reference
    → Changes do not affect the other object
    → Must override clone()
    → Manually clone nested objects

Cloneable:
    Cloneable   → Marker Interface, Tells JVM that cloning is allowed
    clone()     → Method from Object class, Used to create copy of an object

-----------------------------------------------------------------------------------------------------------------------------------------------------