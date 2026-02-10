------------------------------------------------------------------------------------------------------------------------
Design Principles:
------------------------------------------------------------------------------------------------------------------------

SOLID Principles:

1: S - Single Responsibility:
    → A class should have only one reason to change.
    → User Service should not send mail and generate report
    → User service should contain methods related to user only
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
    → Used when you have multiple types or strategies to do 1 thing
    → Used to avoid changing stable codes
    → Add new features safely

Example:
    → Do not use multiple if statements for different types in service class
    → If you want to add new type, you need to change the service class
    → Instead use interface, with this you need to just create new class and give the logic 
    → No need to change the service class and modify the stable code

interface Payment {
    void pay();
}

class UpiPayment implements Payment {}
class CardPayment implements Payment {}

------------------------------------------------------------------------------------------------------------------------

3: L - Liskov Substitution Principle:
    → Child object must be usable in place of parent object without breaking behavior.
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
    → Clients should not be forced to implement methods they dont want to use
    → You should not create a GOD Interface with multiple methods 
    → Make small, focused interfaces instead of one big interface.

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
    → Avoid duplicating the same logic in multiple places.
    → Re-use the same logic everywhere
    → Real world - Util Classes

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

SINGLETON PATTERN:
    → A singleton class is a class that allows only one instance
    → Only one instance of a class is created and shared everywhere.
    → Control object creation + provide global access point.


Code:
public class DataStore {

    private static volatile DataStore instance;

    private final List<String> items = Collections.synchronizedList(new ArrayList<>());

    // private constructor
    private DataStore() {}

    public static DataStore getInstance() {
        if (instance == null) {
            synchronized (DataStore.class) {
                if (instance == null) {
                    instance = new DataStore();
                }
            }
        }
        return instance;
    }

    public void addItem(String item) {
        items.add(item);
    }

    public void removeItem(String item) {
        items.remove(item);
    }

    // unmodifiable read-only view
    // cannot change the list directly need to use methods provided
    public List<String> getItems() {
        return Collections.unmodifiableList(items);
    }
}

----------------------------------------------------------------------------------------------------------------------

How can a Singleton be broken (reflection, clone, serialization)

Clone:
    → If the class implements Cloneable, clone() can produce a new instance.
    → Override clone() and prevent cloning:

Serialization:
    → Serialization creates a new object during deserialization.

----------------------------------------------------------------------------------------------------------------------

FACTORY PATTERN:
    → It is a design pattern where you create a factory class to create objects instead of creating objects in the service class
    → Hides object creation logic from service class
    → It is used when you multiple types of implementation of an interface

public interface Payment {
    void process(double amount);
}

public class CreditCardPayment implements Payment {
    @Override
    public void process(double amount) {
        System.out.println("Processing credit card: $" + amount);
    }
}

public class PayPalPayment implements Payment {
    @Override
    public void process(double amount) {
        System.out.println("Processing PayPal: $" + amount);
    }
}

// Step 3: Factory
public class PaymentFactory {
    public static Payment createPayment(String type) {
        switch(type.toLowerCase()) {
            case "creditcard":
                return new CreditCardPayment();
            case "paypal":
                return new PayPalPayment();
            case "crypto":
                return new CryptoPayment();
            default:
                throw new IllegalArgumentException("Unknown payment type");
        }
    }
}

// Step 4: Client usage - Simple!
// No change in service class when adding new types
public class PaymentService {
    public void processPayment(String type, double amount) {
        Payment payment = PaymentFactory.createPayment(type);
        payment.process(amount);
    }
}

----------------------------------------------------------------------------------------------------------------------

Builder Pattern:
    → It is used to create complex objects step by step
    → It is used when object has so many parameters
    → It is used when you want to create object with different parameter combination
    → In Springboot @Builder annotation creates everything for you

Manual Implementation:

public class Computer {

    // Required parameters
    private final String CPU;
    private final String RAM;
    
    // Optional parameters
    private final String storage;
    private final String graphicsCard;
    private final boolean bluetooth;
    private final boolean wifi;
    
    // Private constructor (only Builder can create)
    private Computer(ComputerBuilder builder) {
        this.CPU = builder.CPU;
        this.RAM = builder.RAM;
        this.storage = builder.storage;
        this.graphicsCard = builder.graphicsCard;
        this.bluetooth = builder.bluetooth;
        this.wifi = builder.wifi;
    }
    
    public static class ComputerBuilder {

        // Required parameters
        private final String CPU;
        private final String RAM;
        
        // Optional parameters with defaults
        private String storage = "512GB SSD";
        private String graphicsCard = "Integrated";
        private boolean bluetooth = false;
        private boolean wifi = true;
        
        // Constructor for required parameters
        public ComputerBuilder(String CPU, String RAM) {
            this.CPU = CPU;
            this.RAM = RAM;
        }
        
        // Setter methods for optional parameters (return Builder for chaining)
        public ComputerBuilder storage(String storage) {
            this.storage = storage;
            return this;
        }
        
        public ComputerBuilder graphicsCard(String graphicsCard) {
            this.graphicsCard = graphicsCard;
            return this;
        }
        
        public ComputerBuilder bluetooth(boolean bluetooth) {
            this.bluetooth = bluetooth;
            return this;
        }
        
        public ComputerBuilder wifi(boolean wifi) {
            this.wifi = wifi;
            return this;
        }
        
        // Build method to create the final object
        public Computer build() {
            return new Computer(this);
        }
    }
    
    // Getters
    @Override
    public String toString() {
        return "Computer [CPU=" + CPU + ", RAM=" + RAM + ", storage=" + storage + 
               ", graphicsCard=" + graphicsCard + ", bluetooth=" + bluetooth + 
               ", wifi=" + wifi + "]";
    }
}

public class ComputerShop {
    public static void main(String[] args) {
        // Creating computers with different configurations
        
        // Basic computer
        Computer basic = new Computer.ComputerBuilder("i5", "8GB")
                            .build();
        
        // Gaming computer
        Computer gaming = new Computer.ComputerBuilder("i9", "32GB")
                            .storage("2TB NVMe SSD")
                            .graphicsCard("RTX 4090")
                            .bluetooth(true)
                            .build();
        
        // Office computer
        Computer office = new Computer.ComputerBuilder("i7", "16GB")
                            .wifi(true)
                            .build();
        
        System.out.println("Basic: " + basic);
        System.out.println("Gaming: " + gaming);
        System.out.println("Office: " + office);
    }
}

----------------------------------------------------------------------------------------------------------------------

Prototype Pattern:
    → Create new objects by cloning existing ones instead of using new.
    → When creating an object is expensive (database calls, network calls, complex calculations) and you need many similar objects.

Example:

// 1. Make class Cloneable
class Sheep implements Cloneable {
    String name;
    
    // 2. Override clone()
    public Sheep clone() {
        try {
            return (Sheep) super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}

// 3. Use it
Sheep original = new Sheep();
original.name = "Dolly";

Sheep clone = original.clone();  // Clone instead of creating new
clone.name = "Molly";

----------------------------------------------------------------------------------------------------------------------

DECORATOR PATTERN:
    → It is used to add new functionality to objects without altering their structure
    → It is used when there are multiple types and layers of 1 thing and you need to layer all together

Example
    Hotel Room Pricing Strategies:

// 1. Simple Interface
interface RoomPrice {
    double getPrice();
    String getDescription();
}

// 2. Base Room
class StandardRoom implements RoomPrice {
    public double getPrice() { return 100.00; }
    public String getDescription() { return "Standard Room"; }
}

// 3. Deluxe Room
class DeluxeRoom implements RoomPrice {
    public double getPrice() { return 150.00; }
    public String getDescription() { return "Deluxe Room"; }
}

// 4. FIRST STRATEGY: Surge Pricing (+20%)
class SurgePricing implements RoomPrice {
    private RoomPrice room;
    
    public SurgePricing(RoomPrice room) {
        this.room = room;
    }
    
    public double getPrice() {
        return room.getPrice() * 1.20;
    }
    
    public String getDescription() {
        return room.getDescription() + " (Peak Season)";
    }
}

// 5. SECOND STRATEGY: Holiday Pricing (+30%)
class HolidayPricing implements RoomPrice {
    private RoomPrice room;
    
    public HolidayPricing(RoomPrice room) {
        this.room = room;
    }
    
    public double getPrice() {
        return room.getPrice() * 1.30;
    }
    
    public String getDescription() {
        return room.getDescription() + " (Holiday)";
    }
}

// 6. THIRD STRATEGY: Last Minute Discount (-15%)
class LastMinuteDiscount implements RoomPrice {
    private RoomPrice room;
    
    public LastMinuteDiscount(RoomPrice room) {
        this.room = room;
    }
    
    public double getPrice() {
        return room.getPrice() * 0.85; // 15% off
    }
    
    public String getDescription() {
        return room.getDescription() + " (Last Minute Deal)";
    }
}

----------------------------------------------------------------------------------------------------------------------