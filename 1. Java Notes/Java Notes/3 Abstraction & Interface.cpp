-----------------------------------------------------------------------------------------------------------------------------------------------------
Abstraction:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Abstract Classes (abstract keyword) :

    → normal + static + abstract methods
    → instance + static variables
    → constructor
    → Multiple inheritance not supported
    → Cannot override static methods
    → Can override abstract and default methods

2: Interfaces (interface keyword) :

    → default + static + abstract  
    → static final variables
    → Cannot have a constructor
    → Multiple Inheritance Supported
    → Cannot override static methods
    → Can override abstract and default methods

-----------------------------------------------------------------------------------------------------------------------------------------------------

When to Use Abstract Class vs Interface:

1: Use Abstract Class When:
    → You want to provide base functionality + shared state
    → You want to give default implementations for all subclassses
    → You want constructors

Example:
    → Animal → abstract class, with name field and run() method
    → Subclasses Dog and Cat inherit common behavior

2: Use Interface When:
    → You want to define a contract without implementation
    → You want to provide common behavior for subclasses
    → You want loose coupling

Example:
    → PaymentMethod → interface
    → CreditCard and UPI implement interface → Cart can work with any payment type

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
→ If Interface A has method fun() and Interface B extends A with greet(),
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

-----------------------------------------------------------------------------------------------------------------------------------------------------
Tight Coupling vs Loose Coupling
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Without Interface → Tight Coupling

→ PaymentService depends directly on all payment classes
→ Adding a new payment type → need to modify PaymentService → bad design

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

class PaymentService {
    void doPayment(CreditCard c) { 
        c.pay(); 
    }
    void doPayment(UPI u) { 
        u.pay(); 
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

With Interface → Loose Coupling:

→ All payment types implement PaymentMethod
→ PaymentService depends only on interface, not on concrete classes
→ Adding new payment types → no changes to PaymentService

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

class PaymentService {

    private PaymentMethod paymentMethod;

    void doPayment() {
        paymentMethod.pay();
    }
}

//Run Time Polymorphism
PaymentService paymentService = new PaymentService(new CreditCard());
paymentService.doPayment();

PaymentService paymentService = new PaymentService(new UPI());
paymentService.doPayment();

-----------------------------------------------------------------------------------------------------------------------------------------------------