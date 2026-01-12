-------------------------------------------------------------------------------------------------------------------------------
Abstraction:
    Hides unnecessary implementation details and exposes only essential features.
    Helps in structure, code reusability, and security.

-------------------------------------------------------------------------------------------------------------------------------

1: Abstract Classes (abstract keyword) :

    abstract + normal + static methods
    instance + static variables
    Can have a constructor
    Multiple inheritance not supported
    Cannot create object of absrtact class

2: Interfaces (interface keyword) :

    abstract + default + static methods 
    Variables are public static final (constants)
    Cannot have a constructor
    Multiple Inheritance Supported

-------------------------------------------------------------------------------------------------------------------------------

When to Use Abstract Class vs Interface:

1: Use Abstract Class When:
    You want to share code among closely related classes
    You have common properties/attributes for subclasses
    You want to provide some default method implementations

Example:
    Animal → abstract class, with name field and run() method
    Subclasses Dog and Cat inherit common behavior
    Key Rule: Abstract class = “is-a” relationship + shared implementation

2: Use Interface When:
    You want to define a contract without implementation
    Classes are unrelated but should implement common behavior
    You want multiple inheritance
    You want to allow flexible design and loose coupling

Example:
    PaymentMethod → interface
    CreditCard and UPI implement interface → Cart can work with any payment type
    Key Rule: Interface = “can-do” relationship + multiple inheritance

-------------------------------------------------------------------------------------------------------------------------------

Abstract Class Code:

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

Animal a1 = new Animal("Shiro");                    //ERROR, Cannot create object of abstract class

Dog dog = new Dog("PetDog", "Golden Retriever");
dog.eat();                                          // PetDog is eating
dog.run();                                          // I am running
Animal.fly();                                       // I am flying

-------------------------------------------------------------------------------------------------------------------------------

Interface Code:

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

Car c = new Car();
c.start();                                  // Car is starting
c.stop();                                   // Vehicle is stopping
Vehicle.service();                          // Vehicle is being serviced

-------------------------------------------------------------------------------------------------------------------------------

Note:
If Interface A has method fun() and Interface B extends A with greet(),
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

Without Interface → Tight Coupling

Cart depends directly on all payment classes
Adding a new payment type → need to modify Cart → bad design

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

All payment types implement PaymentMethod
Cart depends only on interface, not on concrete classes
Adding new payment types → no changes to Cart

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

Best Practice — Constructor Injection
    Pass the payment method once in constructor, reuse in all methods

class Cart {
    PaymentMethod paymentMethod;

    Cart(PaymentMethod paymentMethod) {
        this.paymentMethod = paymentMethod;
    }

    void doPayment() {
        paymentMethod.pay();
    }
}

// Usage
Cart cart = new Cart(new CreditCard());
cart.doPayment();  // Uses the same payment method


-----------------------------------------------------------------------------------------------------------------------------------------
