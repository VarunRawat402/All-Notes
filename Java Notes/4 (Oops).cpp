-----------------------------------------------------------------------------------------------------------------------------------------
Java OOPs:
-----------------------------------------------------------------------------------------------------------------------------------------

Destructor:
Java does not have destructors.
Java uses Garbage Collection (GC).
Resource cleanup (files, DB connections) should be done explicitly using close() or try-with-resources.

-----------------------------------------------------------------------------------------------------------------------------------------

Default Constructor:
    Default constructor is generated only if no constructor is defined
    If you define any constructor, default is not created
    Takes no parameters.

Parameterized Constructor:
Takes parameters to create object 

Copy Constructor: 
Takes another object as a parameter and creates a new object with the same values.
Used to duplicate objects.

Constructor Chaining:
When you create an object of a child class, the parent class constructor is called first, then the child class constructor.
Happens using super().

Constructor Overloading:
When you have mutliple constructors with same name but they are taking different values and assigning

-----------------------------------------------------------------------------------------------------------------------------------------

Note:
Primitive types are passed by value
    → Changes inside method do not affect original value

Objects are passed by reference (reference value)
    → Changes inside method affect the same object

-----------------------------------------------------------------------------------------------------------------------------------------

Access Modifiers:

1: Public:
    Accessible from anywhere (any class, any package).

2: Protected:
    Accessible within the same package.
    Accessible in another package only through inheritance (subclass).

3: Private:
    Accessible only within the same class.
    Not accessible from any other class.

4: Default:
    Accessible within the same package only.
    Not accessible outside the package.

-----------------------------------------------------------------------------------------------------------------------------------------

POLYMORPHISM:
    One object behaving in multiple forms.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Method Overloading ( Compile time Polymorphism ):
Same method name, different parameters

Ex:
    public class Calculator {
        public int add(int a, int b) {
            return a + b;
        }

        public int add(int a, int b, int c) {
            return a + b + c;
        }
    }

-----------------------------------------------------------------------------------------------------------------------------------------

2: Method Overriding ( Run time Polymorphism ):
A child class provides its own implementation of a parent class method.
The method call is decided at runtime based on the object type.

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

-----------------------------------------------------------------------------------------------------------------------------------------

INHERITANCE:
    Using properties and methods of a parent class in a child class.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Single Level Inheritance:
    Only 1 child class and 1 parent class.

Ex:
    class Animal {}

    class Dog extends Animal {}

-----------------------------------------------------------------------------------------------------------------------------------------

2: Multilevel Inheritance:
    Chaining of inheritance where 2 class inherits 1 class then 3 class inherits 2 class

Ex:
    class Animal {
    }

    class Dog extends Animal {
    }

    class Breed extends Dog{
    }

-----------------------------------------------------------------------------------------------------------------------------------------

3: Multiple Inheritance:    
    In Multiple Inheritance 1 class can extends 2 classes or more.
    In java we dont have multiple inheritance but we can acheive it through Interfaces.

-----------------------------------------------------------------------------------------------------------------------------------------

4: Hierarchical Inheritance:
    Multiple classes extends 1 single class 

Ex:
    class Animal {
    }

    class Dog extends Animal {
    }

    class Cat extends Animal{
    }

-----------------------------------------------------------------------------------------------------------------------------------------

ENCAPSULATION:
    Binding data and methods together while hiding internal implementation.

Key Concepts of Encapsulation

Private fields          → cannot be accessed directly.
Public getters/setters  → controlled access of private fields.
Better Control          → You can validate, restrict, or modify behavior when getting or setting values.

-----------------------------------------------------------------------------------------------------------------------------------------

Super():
    Calls parent class constructor
    Used to initialize parent variables through constructor
    Access parent class variables/methods (non-private) using super.variable / super.method()

-----------------------------------------------------------------------------------------------------------------------------------------

Parent reference with Child object:

Parent p1 = new Child();

You can access parent variables and parent methods
You cannot access child variables and child methods
If parent methods are overriden then overriden methods will get executed ( run time polymorphism )

Note:
    What you can access depends on the reference
    What is going to be executed depends on the object

-----------------------------------------------------------------------------------------------------------------------------------------

Object Class:
    The root class of all Java classes.
    
hashCode():
    Returns a unique integer hash value of the object
    used in HashMap, HashTable, HashSet
    Unique value is not guranteed, coz some objects can have same hashCode due to hash collisions
    If a.equals(b) is true then Hashcode of a and b should be same
    If equals() is overridden → hashCode() must also be overridden.

equals():
    Default: compares reference of the objects.
    Overridden in String, Integer, etc., to compare values.

toString():
    It is used to return the String representation of Object

Finalize():
    It is called automatically by the GC when object is destroyed
    It is used for cleanup Functions
    Not reliable and should NOT be used
    Depricated after java 9

-----------------------------------------------------------------------------------------------------------------------------------------