-----------------------------------------------------------------------------------------------------------------------------------------
Java OOPs:
-----------------------------------------------------------------------------------------------------------------------------------------

Destructor:
Java does not have destructors. Memory cleanup is handled automatically by the Garbage Collector. 
When objects or variables are no longer referenced, Java removes them on its own.

Constructor:
It is used to create an object of the class.
It has same name as the class.
No return type.

-----------------------------------------------------------------------------------------------------------------------------------------

Default Constructor:
It is created automatically by the class if we dont initialize it.
Takes no parameters.
Used to create objects without passing any values.

Parameterized Constructor:
It takes some parameters to assign values when creating an object of the class.

Copy Constructor: 
Takes another object as a parameter and creates a new object with the same values.
Used to duplicate objects.

Constructor Chaining:
When you create an object of the child class then constructor of parent class will gets call first then child
class's constructor will be called.

Constructor Overloading:
When you have mutliple constructors with same name but they are taking different values and assigning

-----------------------------------------------------------------------------------------------------------------------------------------

Ex:

class Student{

    String name;
    int age;

    Student(){                              //Default Constructor
    }

    Student(String name, int age){          //Parameterized Constructor
        this.name = name;
        this.age = age;
    }

    Student(String name){                   //Constructor Overloading
        this.name = name;
    }
    
    Student(Student original){              //Copy Constructor
        this.name = original.name;
        this.age = original.age;
    }

    public void printInfo(){
        System.out.println(this.name);
        System.out.println(this.age);
    }
}

public class Main {
    public static void main(String[] args) {

        Student s1 = new Student("Varun",23);
        Student s2 = new Student(s1);
        s2.printInfo();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Note:

Primitive types are passed by value → Changes in function dont affect original
Objects are passed by reference → Changes in function affect original object

-----------------------------------------------------------------------------------------------------------------------------------------

Access Modifiers:

1: Public:
    Accessible from any class in any package.

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
    The ability of an object to behave in multiple forms.

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
Method overriding allows a subclass to provide a different implementation of a method that is already defined in its parent class.
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

    public class Dog extends Animal {
        @Override
        public void makeSound() {
            System.out.println("Woof");
        }
    }

    Animal cat = new Cat();
    Animal dog = new Dog();

    cat.makeSound(); // Calls Cat's makeSound() method
    dog.makeSound(); // Calls Dog's makeSound() method

-----------------------------------------------------------------------------------------------------------------------------------------

INHERITANCE:
    Reusing properties and methods from a parent class in a child class.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Single Level Inheritance:
    In Single Level Inheritance there is only 1 base class and 1 parent class.
Ex:
    class Animal {
        // ...
    }

    class Dog extends Animal {
        // ...
    }

-----------------------------------------------------------------------------------------------------------------------------------------

2: Multilevel Inheritance:
    In multilevel inheritance there is 1 class extends another class and then another class extends the 2nd class forming
    a chain of inheritance.

Ex:
    class Animal {
        // ...
    }

    class Dog extends Animal {
        // ...
    }

    class Breed extends Dog{
        // ...
    }

-----------------------------------------------------------------------------------------------------------------------------------------

3: Multiple Inheritance:    
    In Multiple Inheritance 1 class can extends 2 classes or more.
    In java we dont have multiple inheritance but we can acheive it through Interfaces.

Ex:
    interface Walks {
        void walk();
    }

    interface Swims {
        void swim();
    }

    class Human implements Walks, Swims {
        public void walk() {
            // implementation
        }

        public void swim() {
            // implementation
        }
    }

-----------------------------------------------------------------------------------------------------------------------------------------

4: Hierarchical Inheritance:
    In Hierarchical Inheritance multiple class extends 1 single class 
    1 parent class and multiple child classes.

Ex:
    class Animal {
        // ...
    }

    class Dog extends Animal {
        // ...
    }

    class Cat extends Animal{
        // ...
    }

-----------------------------------------------------------------------------------------------------------------------------------------

ENCAPSULATION:
    Binding data and methods together while hiding internal implementation.

Key Concepts of Encapsulation

Private fields → cannot be accessed directly.
Public getters/setters → controlled access of private feilds.
Data Hiding → Other classes cannot modify data directly, preventing unintended changes.
Better Control → You can validate, restrict, or modify behavior when getting or setting values.

-----------------------------------------------------------------------------------------------------------------------------------------

Super():
    It is used to call the parent class constructor.
    You cannot access private variables of parent class if they are private then how you gonna initialize them
    You can use Super() to call the constructor of the parent class to initialize it 
    You can also access parent variables using super.name.

-----------------------------------------------------------------------------------------------------------------------------------------

Reference to parent class with creating child class object:
Parent p1 = new Child():

You can access parent methods
You can access parent variables
You cannot access child methods 
You cannot access child vairables
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

-----------------------------------------------------------------------------------------------------------------------------------------

Difference betweem == and .equals():

==:
    Used on both primitives and objects.
    For primitives -> compares values.
    For objects    -> compares references.

equals():
    A method in Object class.
    Not used for primitives.
    It Can be overridden to compare values.
    It checks reference like == with objects 

-----------------------------------------------------------------------------------------------------------------------------------------