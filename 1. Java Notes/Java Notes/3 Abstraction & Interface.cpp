-----------------------------------------------------------------------------------------------------------------------------------------------------
Abstraction:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Abstract Classes (abstract keyword) :

    → Contains normal + static + abstract methods
    → Contains instance + static variables
    → Contains constructor to initialize instance variables
    → Multiple inheritance not supported
    → Can override abstract + default methods
    → Cannot override static methods
   

2: Interfaces (interface keyword) :

    → Contains default + static + abstract methods
    → Contains only static final variables
    → Cannot have a constructor
    → Multiple Inheritance Supported
    → Can override abstract and default methods
    → Cannot override static methods
   
-----------------------------------------------------------------------------------------------------------------------------------------------------

When to Use Abstract Class vs Interface:

1: Use Abstract Class When:
    → You want to provide partial implementation + state
    → "IS A" relationship (Dog IS an Animal)

2: Use Interface When:
    → You want to define a contract without implementation
    → "CAN DO" relationship (Bird CAN fly, Airplane CAN fly)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
→ If Interface A has method fun()
→ Interface B extends A with greet(),
→ Class C implementing B must implement both methods

-----------------------------------------------------------------------------------------------------------------------------------------------------
Tight Coupling
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
Loose Coupling
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