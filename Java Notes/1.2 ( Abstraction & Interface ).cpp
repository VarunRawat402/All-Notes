-------------------------------------------------------------------------------------------------------------------------------
Abstraction:

Abstraction is used to hide unnecessary details and only shows essential features.
It is used to provide structure, Code Reusability and security

-------------------------------------------------------------------------------------------------------------------------------

How to Achieve Abstraction in Java?

1: Abstract Classes (abstract keyword) :

    Can have abstract, normal, static methods
    Can have instance, static variables
    Can have a constructor
    Multiple Inheritance Not supported

2: Interfaces (interface keyword) :

    Can only have abstract methods (before Java 8), but can have default and static methods from Java 8+.
    Only public static final (constants)
    Cannot have a constructor
    Multiple Inheritance Supported (A class can implement multiple interfaces)

-------------------------------------------------------------------------------------------------------------------------------

Abstract Class Code:

abstract class Animal {

    //Instance variable in abstract class
    String name;
    static int price = 1000;

    //Constructor
    Animal(String name){
        this.name=name;
    }

    //abstract method
    abstract void eat(){
    }

    //normal method
    void run(){
        System.out.println("I am running");
    }

    //static method
    static void fly(){
        System.out.println("I am flying");
    }

}

public class Dog extends Animal{

    //Dog instance variables
    String breed;
    int age;

    //Passing values of name, breed and age of dog
    //using super to call the constructor to initialize the name 
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
dog.run();
Animal.fly();

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

Note:
If B interface is extending A Interface
A has fun() method, B has greet() method
Class Student implementing B interface have to override both fun() and greet() methods

interface A{
    void fun();
}

interface B extends A{
    void greet();
}

class Student implements B{
    fun(){

    }
    greet(){
        
    }
}

-------------------------------------------------------------------------------------------------------------------------------

What is the need of interface or abstraction:
    Loose Coupling and Reusability of Code:

This is an example of multiple payment class methods
which are used to make payment through Cart class

-----------------------------------------------------------------------------------------------------------------------------------------

Now for 2 payment methods we needed to create 2 doPayment methods
This is known as tight Coupling
If we in future have to have 2 more payment methods
Then we have to change the Cart class do right which have nothing to with Payemnt methods classes
With Interface you can remove this tight coupling

Ex:

Shopping Cart:
public class Cart {

    void doPayment(CreditCard creditCard){
        creditCard.pay();
    }

    void doPayment(UPI upi){
        upi.pay();
    }
    
}

public class CreditCard{
    public void pay() {
        System.out.println("Payment is done by creditCard");
    }
}

public class UPI{
    public void pay() {
        System.out.println("Payment is done by UPI Id");
    }
}

Main:
public static void main(String[] args) {
    
    CreditCard c1 = new CreditCard();
    UPI u1 = new UPI();
    
    Cart cart1 = new Cart();
    cart1.doPayment(c1);
    cart1.doPayment(u1);
}

-----------------------------------------------------------------------------------------------------------------------------------------

In Cart Method there is only 1 method for payment method now due to interface
Now this doPayment method is dependent on interface not all the classes implementing the interface
So If in future we have to add new payment methods we can create it and implement the interface
No need to change anything in the Cart class


public class Cart {
    void doPayment(PaymentMethod paymentMethod){
        paymentMethod.pay();
    }
}

public interface PaymentMethod {
    void pay();
}

public class CreditCard implements PaymentMethod{
    @Override
    public void pay() {
        System.out.println("Payment is done by creditCard");
    }
}

public class UPI implements PaymentMethod{
    @Override
    public void pay() {
        System.out.println("Payment is done by UPI Id");
    }
}


Main:

public class HelloApplication {
	public static void main(String[] args) {

		CreditCard c1 = new CreditCard();
		UPI u1 = new UPI();
		
		Cart cart1 = new Cart();
		cart1.doPayment(c1);
		cart1.doPayment(u1);
	
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------

Note:
The best practice to add payment method is to add like dependency Injection in constructor
So you dont need to provide the payment method everytime you have to do something
Lets say you have to use payment method in different functions too then you have to provide the payment method there too
Instead you can define it once and use anywhere in the class

Ex:

public class Cart {

    PaymentMethod paymentMethod;

    Cart(PaymentMethod paymentMethod){
        this.paymentMethod = paymentMethod
    }

    void doPayment(){
        paymentMethod.pay();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------
