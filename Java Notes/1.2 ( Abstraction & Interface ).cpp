-------------------------------------------------------------------------------------------------------------------------------
Abstraction:

Abstraction is used to hide unnecessary details and only shows essential features.
It is used to provide structure, Code Reusability and security

-------------------------------------------------------------------------------------------------------------------------------

How to Achieve Abstraction in Java?

1: Abstract Classes (abstract keyword) :

    Can have abstract + normal + static methods
    Can have instance + static variables
    Can have a constructor
    Multiple Inheritance Not supported

2: Interfaces (interface keyword) :

    Can have abstract + default + static methods 
    Only public static final (constants)
    Cannot have a constructor
    Multiple Inheritance Supported (A class can implement multiple interfaces)

-------------------------------------------------------------------------------------------------------------------------------

Abstract Class Code:

abstract class Animal {

    String name;
    static int price = 1000;

    Animal(String name){    //Constructor
        this.name=name;
    }

    abstract void eat()     //abstract method

    void run(){             //Normal method
        System.out.println("I am running");
    }

    static void fly(){      //static method
        System.out.println("I am flying");
    }

}

public class Dog extends Animal{

    String breed;

    //using super to call the constructor to initialize the name 
    Dog(String name,String breed) {
        super(name);
        this.breed=breed;
        this.age=age;
    }

    //Override the eat method of abstract class
    @Override
    void eat(){
        System.out.println( name + " is barking");
    }
}
    
Dog dog = new Dog("PetDog", "Golden Retreiver");
dog.eat()           //Dog is barking
dog.run();          //I am running
Animal.fly();       //I am flying

-------------------------------------------------------------------------------------------------------------------------------

Interface Code:

interface Vehicle {

    //abstract method
    void start(); 

    //default method (has implementation)
    default void stop() {
        System.out.println("Vehicle is stopping");
    }

    //static method
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
Interface A has one abstract method fun()
Interface B has one abstract method greet() and extends interface A
Student class implements interface B need to implement both fun() and greet() methods

interface A{
    void fun();
}

interface B extends A{
    void greet();
}

class Student implements B{

    fun(){
        //Implementation of fun
    }

    greet(){
        //Implementation of greet
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Example of Loose and Tight Coupling using Interface:
In this example we have 2 payment methods CreditCard and UPI
Cart class is responsible for doing payment using these payment methods

-----------------------------------------------------------------------------------------------------------------------------------------

Without Interface:

In Cart class we had to make 2 doPayment() method for 2 payment types.
Now if we have 10 payment types we will have to make 10 doPayment() methods beacause cart class is dependent on all the payment types
Everytime we add a new payment type we have to change the Cart class which is not good practice
This is known as Tight Coupling

Ex:

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

public class Cart {

    void doPayment(CreditCard creditCard){
        creditCard.pay();
    }

    void doPayment(UPI upi){
        upi.pay();
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

With Interface:

Every payment type implements singe interface PaymentMethod
Cart class takes PaymentMethod interface in the doPayment method
This makes Cart class dependent on PaymentMethod interface not all the payment types
This is known as Loose Coupling
Now If we have to add new payment types we dont need to change anything in the Cart class

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

public class Cart {

    void doPayment(PaymentMethod paymentMethod){
        paymentMethod.pay();
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
The best practice is to add payment method in the constructor of the Cart class
So, we dont need to pass the payment method for every cart function
Ex: If cart had 5 function with payment we had to :
c1.doPayment(c1);
c1.doPlaceOrder(c1);
c1.doCancelOrder(c1);

with constructor we can pass the payment method once while creating cart object.

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
