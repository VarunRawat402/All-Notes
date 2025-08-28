-------------------------------------------------------------------------------------------------------------------------------
Abstraction:

Abstraction is used to hide unnecessary details and only shows essential features.
Improves code reusability and security.
-------------------------------------------------------------------------------------------------------------------------------

How to Achieve Abstraction in Java?

1: Abstract Classes (abstract keyword) :

    Can have both abstract and normal methods.
    Can have instance variables
    Can have a constructor
    Multiple Inheritance Not supported

2: Interfaces (interface keyword) :

    Can only have abstract methods (before Java 8), but can have default and static methods from Java 8+.
    Only public static final (constants)
    Cannot have a constructor
    Supported (A class can implement multiple interfaces)

-------------------------------------------------------------------------------------------------------------------------------

Abstract Class Code:

abstract class Animal {

    //Instance variable in abstract class
    String name;

    //Constructor
    Animal(String name){
        this.name=name;
    }

    //abstract method
    abstract void eat(){
    }

}

public class Dog extends Animal{

    //Dog instance variables
    String breed;
    int age;

    //Passing animal's name dog's breed and age in dogs constructor
    //Super calls the parent class contructor
    //In order to use Dog we have to implement Parent class object first
    Dog(String name,String breed, int age) {
        super(name);
        this.breed=breed;
        this.age=age;
    }

    //Implemented the method from abstract class
    void eat(){
        System.out.println( name + " is barking");
    }
}
    
Dog dog = new Dog("PetDog", "Golden Retreiver" ,3);
dog.eat()           //Dog is barking

-------------------------------------------------------------------------------------------------------------------------------

Interface Code:

interface Vehicle {

    // Abstract method
    void start(); 

    // Default method (has implementation)
    default void stop() {
        System.out.println("Vehicle is stopping");
    }

    // Static method (called using interface name)
    static void service() {
        System.out.println("Vehicle is being serviced");
    }
}

class Car implements Vehicle {
    public void start() {
        System.out.println("Car is starting");
    }
}

public class Main {
    public static void main(String[] args) {

        Car c = new Car();
        c.start();
        c.stop(); // ✅ Calling default method
        Vehicle.service(); // ✅ Calling static method
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Use Abstract Class When:
    You need instance variables	
    You need constructors	
    You want partial implementation	

Use an interface when:
    You want multiple inheritance (Java allows a class to implement multiple interfaces).
    You dont need instance variables or constructors.
    You need pure abstraction (no method implementations except default or static methods).

-------------------------------------------------------------------------------------------------------------------------------


