-------------------------------------------------------------------------------------------------------------------------------
Abstraction:
-------------------------------------------------------------------------------------------------------------------------------

1: Abstract Classes (abstract keyword) :

    → normal + static + abstract methods
    → instance + static variables
    → constructor
    → Multiple inheritance not supported

2: Interfaces (interface keyword) :

    → default + static + abstract  
    → static final variables
    → Cannot have a constructor
    → Multiple Inheritance Supported

-------------------------------------------------------------------------------------------------------------------------------

When to Use Abstract Class vs Interface:

1: Use Abstract Class When:
    → You want to provide common code with subclasses
    → You want to provide common properties and attributes to subclasses
    → You want to write some default implementation for subclassses

Example:
    → Animal → abstract class, with name field and run() method
    → Subclasses Dog and Cat inherit common behavior

2: Use Interface When:
    → You want to define a contract without implementation
    → You want to provide common behavior for subclasses
    → You want to allow flexible design and loose coupling

Example:
    → PaymentMethod → interface
    → CreditCard and UPI implement interface → Cart can work with any payment type

-------------------------------------------------------------------------------------------------------------------------------
Abstract Class Code:
-------------------------------------------------------------------------------------------------------------------------------

abstract class Animal {

    String name;
    static int price = 1000;

    Animal(String name) {                       // Constructor
        this.name = name;
    }

    abstract void eat();                        // Abstract method

    public void run() {                         // Normal method
        System.out.println("I am running");
    }

    static void fly() {                         // Static method
        System.out.println("I am flying");
    }
}

class Dog extends Animal {

    String breed;

    Dog(String name, String breed) {
        super(name);
        this.breed = breed;
    }

    @Override
    void eat() {
        System.out.println(name + " is eating");
    }
}

Dog dog = new Dog("PetDog", "Golden Retriever");

-------------------------------------------------------------------------------------------------------------------------------
Interface Code:
-------------------------------------------------------------------------------------------------------------------------------

interface Vehicle {

    void start();                                           // Abstract method

    default void stop() {                                   // Default method
        System.out.println("Vehicle is stopping");
    }

    static void service() {                                 // Static method
        System.out.println("Vehicle is being serviced");
    }
}

class Car implements Vehicle {
    public void start() {
        System.out.println("Car is starting");
    }
}

-------------------------------------------------------------------------------------------------------------------------------

Note:
→ → If Interface A has method fun() and Interface B extends A with greet(),
→ Student class implementing B must implement both methods

interface A { void fun(); }
interface B extends A { void greet(); }

class Student implements B {

    public void fun(){ 
        /* implementation */ 
    }

    public void greet(){ 
        /* implementation */ 
    }
}

-------------------------------------------------------------------------------------------------------------------------------
Tight Coupling vs Loose Coupling
-------------------------------------------------------------------------------------------------------------------------------

→ Without Interface → Tight Coupling

→ Cart depends directly on all payment classes
→ Adding a new payment type → need to modify Cart → bad design

Ex:
class CreditCard { 
    void pay(){ 
        System.out.println("Payment by Credit Card");
    } 
}
class UPI { 
    void pay(){ 
        System.out.println("Payment by UPI"); 
    } 
}

class Cart {
    void doPayment(CreditCard c) { 
        c.pay(); 
    }
    void doPayment(UPI u) { 
        u.pay(); 
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

With Interface → Loose Coupling:

→ All payment types implement PaymentMethod
→ Cart depends only on interface, not on concrete classes
→ Adding new payment types → no changes to Cart

interface PaymentMethod { 
    void pay(); 
}

class CreditCard implements PaymentMethod {
    public void pay() { 
        System.out.println("Payment by Credit Card"); 
    }
}

class UPI implements PaymentMethod {
    public void pay() { 
        System.out.println("Payment by UPI"); 
    }
}

class Cart {
    void doPayment(PaymentMethod paymentMethod) {
        paymentMethod.pay();
    }
}

// Usage
Cart cart = new Cart();
cart.doPayment(new CreditCard());
cart.doPayment(new UPI());

-----------------------------------------------------------------------------------------------------------------------------------------