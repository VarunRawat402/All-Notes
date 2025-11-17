-------------------------------------------------------------------------------------------------------------------------------
Abstraction:

Abstraction hides unnecessary implementation details and exposes only the essential features.
It helps in providing structure, improving code reusability, and increasing security.

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
    }

    //Override the eat method of abstract class
    @Override
    void eat(){
        System.out.println( name + " is eating");
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
        c.stop();                           // ✅ Calling default method
        Vehicle.service();                  // ✅ Calling static method
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Note:
If Interface A has an abstract method fun() and Interface B extends A and adds greet()
then Student must implement both methods.

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

Example of Tight Coupling vs Loose Coupling using Interfaces
Two payment types → CreditCard and UPI
Cart class is responsible for performing payment using these methods

-----------------------------------------------------------------------------------------------------------------------------------------

Without Interface → Tight Coupling

Cart must create separate doPayment() methods for each payment type
If we add 10 payment types → we must write 10 methods
Cart depends directly on all payment classes
Any new payment class requires updating Cart → bad design

Ex:

public class CreditCard {
    public void pay() {
        System.out.println("Payment is done by Credit Card");
    }
}

public class UPI {
    public void pay() {
        System.out.println("Payment is done by UPI");
    }
}

public class Cart {

    void doPayment(CreditCard creditCard) {
        creditCard.pay();
    }

    void doPayment(UPI upi) {
        upi.pay();
    }
}

Main:
public static void main(String[] args) {

    CreditCard c1 = new CreditCard();
    UPI u1 = new UPI();

    Cart cart = new Cart();
    cart.doPayment(c1);
    cart.doPayment(u1);
}

-----------------------------------------------------------------------------------------------------------------------------------------

With Interface → Loose Coupling:

All payment types implement a single interface PaymentMethod
Cart now depends only on PaymentMethod, not on every payment class
Adding new payment types → no change needed in Cart
This is the recommended flexible design

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

Note: Best Practice — Use Constructor Injection

Instead of passing payment method in every function call, pass it once in the constructor.

Without constructor injection (bad):
    cart.doPayment(c1);
    cart.doPlaceOrder(c1);
    cart.doCancelOrder(c1);


With constructor injection (good):

Ex:
public class Cart {

    PaymentMethod paymentMethod;

    Cart(PaymentMethod paymentMethod) {
        this.paymentMethod = paymentMethod;
    }

    void doPayment() {
        paymentMethod.pay();
    }
}

Cart cart = new Cart(new CreditCard());
cart.doPayment();                           // Uses the same payment method

-----------------------------------------------------------------------------------------------------------------------------------------
