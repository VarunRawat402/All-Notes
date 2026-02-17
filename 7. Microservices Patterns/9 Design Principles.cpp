------------------------------------------------------------------------------------------------------------------------
Design Principles:
------------------------------------------------------------------------------------------------------------------------

SOLID Principles:

1: S - Single Responsibility:
    → A class should have only one reason to change.
    → User service should contain only user-related logic.
    → Different service for Email and GenerateReport
    → Easy Testing and Maintainence

class UserService {
    void saveUser(User u) { }
    void sendEmail(User u) { }
    void generateReport() { }
}

------------------------------------------------------------------------------------------------------------------------

2: O - Open Closed Principle:
    → Open for extension, closed for modification.
    → Useful when multiple strategies/types perform the same action.

Example:
    → Do not use multiple if statements for different types in service class
    → If you use multiple if statements for each type, service must change for every new type.
    → Instead depend on an interface and add new implementations.
    → Add new class, not modify old class.

interface Payment {
    void pay();
}

class UpiPayment implements Payment {}
class CardPayment implements Payment {}

------------------------------------------------------------------------------------------------------------------------

3: L - Liskov Substitution Principle:
    → Child object must be safely usable wherever parent object is expected without breaking behavior.
    → If class B extends A, then you should be able to use B anywhere A is expected — and everything should still work correctly.

Example:
    → Bad Design

class Bird {
    void fly() {
        System.out.println("Bird can fly");
    }
}

class Penguin extends Bird {
    void fly() {
        throw new RuntimeException("Penguins cannot fly");
    }
}

Bird b = new Penguin();
b.fly();   // crashes

------------------------------------------------------------------------------------------------------------------------

4: I - Interface Segregation Principle:
    → Clients should not be forced to implement unused methods.
    → Avoid large “god” interfaces.
    → Prefer small, focused interfaces.

------------------------------------------------------------------------------------------------------------------------

5: D - Dependency Inversion Principle:
    → Dependency Injection
    → Loose coupling 
    → Easy mocking and testing

class OrderService {
    Payment payment;
    OrderService(Payment payment) { 
        this.payment = payment; 
    }
}

------------------------------------------------------------------------------------------------------------------------

DRY Principle:
    → Dont Repeat Yourself
    → Avoid duplicating logic in multiple places.
    → Commonly done using utility/helper methods or classes.

Example:
    → Creating one method and re-using it everywhere 

class OrderService {

    public double addTax(double price) {
        double tax = price * 0.18;
        return price + tax;
    }

    public double calculateTotal(double price) {
        return addTax(price);
    }

    public double calculateInvoice(double price) {
        return addTax(price);
    }
}

------------------------------------------------------------------------------------------------------------------------

COMPOSITION OVER INHERITANCE:
    → Prefer using objects inside a class (composition) instead of extending a class (inheritance) to reuse behavior.
    → Avoids tight coupling
    → Easy Debugging
    → Avoid inheritance
    → Can swap behavior at runtime

Example:
    → Instead of extending payment strategy use strategy object
    → Changes behavior of different strategy at run time

class OrderService {
    private PaymentStrategy strategy;
}

------------------------------------------------------------------------------------------------------------------------
