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

        //Created s1 using parameterized constructor
        Student s1 = new Student("Varun",23);
        //Created s2 using copy constructor
        Student s2 = new Student(s1);
        s2.printInfo();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Note:

Primitive values are passed as value in the function, changes in function wont affect the real value
Objects are passed by reference in the function, changes in the function will affect the real value

-----------------------------------------------------------------------------------------------------------------------------------------

Access Modifiers:

1: Public:
    If any variable/methods is public then any class can access that in same package and different package too.

2: Protected:
    If any variable/methods is protected then any class can acess that in same package but in order to access that in different pacakge it needs to be
    the subclass of the varaible/methods's class.

3: Private:
    If any varaible/method is private then no one can access that even in same package.

4: Default:
    If any varaible/method is Default then any class can access that varaible in the same package but no one can access that in diff package.

-----------------------------------------------------------------------------------------------------------------------------------------

How to access Private varaibles:
    By using getters and setters we can allow users to access private variables by the functions we provide to them.
    and they can only those things what we are allowing them to do using the functions.

Ex:
    class Student{

        public String name;
        //No one can access pass directly
        private String pass;

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

POLYMORPHISM: ( Many Forms )
When we do same thing with differnt approaches that is called polymorphism.

It allows objects to be treated as instances of their parent class rather than their actual class. 
Polymorphism is acheived through 2 types.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Method Overloading ( Compile time Polymorphism ):
When we create multiple functions with same name but differentiate them with no. of parameters that is called method Overloading.

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
Taking properties and methods of another class into one class is called inheritance.

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

Binding of data and methods to single unit is called Encapsulation.
It is the practice of hiding the internal details of a class and only exposing necessary functionality.

Key Concepts of Encapsulation

Private Fields → Variables (data) are marked as private to prevent direct access.
Public Getter and Setter Methods → These methods allow controlled access to private fields.
Data Hiding → Other classes cannot modify data directly, preventing unintended changes.
Better Control → You can validate, restrict, or modify behavior when getting or setting values.

-----------------------------------------------------------------------------------------------------------------------------------------

