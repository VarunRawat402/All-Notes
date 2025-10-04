-----------------------------------------------------------------------------------------------------------------------------------------
Java OOPs:
-----------------------------------------------------------------------------------------------------------------------------------------

Destructor:
We dont have Destructor in the java because in java variables, methods etc etc are automatically removed/delete if they are
not having any value.

Constructor:
It is used to create an object of the class.
It has same name as the class.

-----------------------------------------------------------------------------------------------------------------------------------------

Default Constructor:
It is created automatically by the class if we dont initialize it.
It takes no parameters.
It is used to create objects of the class without assigning any values to the objects.

Parameterized Constructor:
It takes some parameters when creating an object of the class.
It is used to create an object of the class and take parameters and assign them to the objects.

Copy Constructor: 
It takes object as a parameter and create a new object with same values as the object we are passing
It is used to make duplicate objects.

Constructor Chaining:
When you create an object of the child class then constructor of parent class will gets call first then child
class's constructor will be called.

Constructor Overloading:
When you have mutliple constructors with same name but they are taking different values and assigning

public class Student {
    private String name;
    private int age;

    public Student(){};

    public Student(String name){
        this.name = name;
    }

    public Student(String name , int age){
        this.name = name;
        this.age = age;
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Ex:

class Student{
    String name;
    int age;

    //Default Constructor
    Student(){

    }

    //Parameterized Constructor
    Student(String name, int age){
        this.name = name;
        this.age = age;
    }

    //Constructor Overloading
    Student(String name){
        this.name = name;
    }

    //Copy Constructor
    Student(Student original){
        this.name = original.name;
        this.age = original.age;
    }

    //Function to print the object info
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
    Any class can access that in any package

2: Protected:
    Any class can acess that in same package 
    To access in diff package the class should be inherited ( subclass )

3: Private:
    No one can access that even in same package.

4: Default:
    Any class can access that varaible in the same package
    No one can access that in diff package.

-----------------------------------------------------------------------------------------------------------------------------------------

How to access Private varaibles:
    By using getters and setters we can allow users to access private variables by the functions we provide to them.
    and they can only those things what we are allowing them to do using the functions.

Ex:
    class Student{

        public String name;
        private String pass;                //No one can access pass directly

        //we made a func to get the pass so user can use this function to get the pass the way i am allowing it
        public String getPass(){
            return this.pass;        
        }

        //we made a func to set the pass so user can use this function to set the pass the way i am allowing it
        public void setPass(String pass){
            this.pass = pass;
        }
    }

    public class Main {
        public static void main(String[] args) {

            Student s1 = new Student();
            s1.name = "Varun Rawat";
            s1.setPass("Dev1ce402@");
            String pass = s1.getPass();
            System.out.println(pass);
        }
    }

-----------------------------------------------------------------------------------------------------------------------------------------

POLYMORPHISM: ( Many Forms )
Ability of objects to take many forms

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
The decision on which method to call is made at runtime based on the actual type of the object.

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
Taking properties and methods of parent class into one class is called inheritance.

There are 4 types of Inheritance.

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

Binding data and methods together, hiding internal implementation.

Key Concepts of Encapsulation

Private Fields → Variables (data) are marked as private to prevent direct access.
Public Getter and Setter Methods → These methods allow controlled access to private fields.
Data Hiding → Other classes cannot modify data directly, preventing unintended changes.
Better Control → You can validate, restrict, or modify behavior when getting or setting values.

-----------------------------------------------------------------------------------------------------------------------------------------

Why use private vairables in the class when you provide getters and setters to change it and access it:

1: Control ( Validation ):
    With anyone accessing the data directly can change the value to nonsensical value too
    If age is public, User can set it to -120, and the code will allow it
    Using setter you can validate the age and if its out of bound you can throw exception

2: Maintaining Internal Consistency:
    Sometimes changing one feild might require change in another feild
    So using setter you can validate the change in the feid and based on that change the another feild
    But if user can directly access the things he may or might forget to change in the second which can cause inconsitentcy

3: Read Only write:
    If you dont want to change something and is for Read only like userId,
    You can provide getter only not setters

-----------------------------------------------------------------------------------------------------------------------------------------

Super():
    It is used to call the constructor of the parent class
    You cannot access instance variables of parent class if they are private then how you gonna initialize them
    You can use Super() to call the constructor of the parent class to initialize it 
    You can access parent class variables using it, Ex: super.name, will give you parent name

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
    It is the root class of all the classes

hashCode():
    Returns a unique integer value of the object
    used in HashMap, HashTable, HashSet
    Unique value is not guranteed, coz some objects can have same hashCode due to hash collisions
    If a.equals(b) is true then Hashcode of a and b should be same
    If equals() methods is overriden the hashcode methods should also be written to make it equal 

equals():
    If used with object it checks the reference of the objects
    Overriden in String, Integer class to check the values not reference

toString():
    It is used to return the String representation of Object


Finalize():
    It is called automatically by the GC when object is destroyed
    It is used for cleanup Functions

-----------------------------------------------------------------------------------------------------------------------------------------

Difference betweem == and .equals():

==:
    It is a comparator
    It is used with both primitives and Objects
    It checks value with primitives
    It checks the reference of the object with objects

equals():
    It is a method in object class
    It is not used with primitives only with objects
    It can be overriden to have custom logic of checking equality
    It checks reference like == with objects 
    It checks value with String, Integer like classes because it is overriden in those classes that way

-----------------------------------------------------------------------------------------------------------------------------------------