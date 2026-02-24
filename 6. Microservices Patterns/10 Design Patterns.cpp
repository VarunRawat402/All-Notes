------------------------------------------------------------------------------------------------------------------------
Design Patterns:
------------------------------------------------------------------------------------------------------------------------

SINGLETON PATTERN:
    → Only 1 instance of a class exists in the JVM and provides a global access point to it.
    → No inconsistent state
    → No multiple objects so no wasted memory/resources
    → Ex: DBConfigurer, Logger

Code:
public class DataStore {

    private static DataStore instance;

    private final List<String> items = Collections.synchronizedList(new ArrayList<>());

    private DataStore() {}

    public static synchronized DataStore getInstance(){
        if (instance == null) {
            instance = new DataStore();
        }
        return instance;
    }

    public List<String> getItems() {
        return Collections.unmodifiableList(items);
    }
}

----------------------------------------------------------------------------------------------------------------------

FACTORY PATTERN:
    → It uses Factory class to create objects of Concrete Types instead of using new directly in service class
    → Service class asks for objects from Factory Class
    → Used with Payment Types or Strategy Types
    → Removes Tight coupling to concrete classes
    → Removes If Else logic in Service class which vioaltes open/closed principle

public interface PaymentType {
    void process(double amount);
}

public class CreditCardPayment implements PaymentType {
    @Override
    public void process(double amount) {
        System.out.println("Processing credit card: $" + amount);
    }
}

public class PayPalPayment implements PaymentType {
    @Override
    public void process(double amount) {
        System.out.println("Processing PayPal: $" + amount);
    }
}

public class PaymentFactory {

    public static PaymentType createPayment(String type) {
        switch(type.toLowerCase()) {
            case "creditcard":  return new CreditCardPayment();
            case "paypal":      return new PayPalPayment();
            case "crypto":      return new CryptoPayment();
            default:            throw new IllegalArgumentException("Unknown payment type");
        }
    }
}

// No change in service class when adding new types
public class PaymentService {
    public void processPayment(String type, double amount) {
        PaymentType payment = PaymentFactory.createPayment(type);
        payment.process(amount);
    }
}

----------------------------------------------------------------------------------------------------------------------

Builder Pattern:
    → It is used to create complex objects step-by-step
    → Used when many fields exist / some are optional / constructor becomes too large
    → In Springboot @Builder annotation creates everything for you

Example:

public class User {

    private String name;
    private int age;
    private String email;

    private User(Builder b) {
        this.name = b.name;
        this.age = b.age;
        this.email = b.email;
    }

    public static class Builder {
        private String name;
        private int age;
        private String email;

        public Builder name(String n) {
            this.name = n;
            return this;
        }

        public Builder age(int a) {
            this.age = a;
            return this;
        }

        public Builder email(String e) {
            this.email = e;
            return this;
        }

        public User build() {
            return new User(this);
        }
    }
}


----------------------------------------------------------------------------------------------------------------------

Prototype Pattern:
    → Prototype pattern creates new objects by cloning an existing object instead of creating new from scratch
    → Creating object is expensive due to heavy initialization / preconfigured fields etc
    → If class have nested objects, use Deep Cloning

Example:

class Sheep implements Cloneable {

    String name;
    
    public Sheep clone() {
        try {
            return (Sheep) super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}

----------------------------------------------------------------------------------------------------------------------

Adapter Pattern:
    → It is used when we want to use an existing or third-party class but its methods dont match what my system expects. 
    → We create an adapter class that wraps it and translates the calls so both sides can work together

→ Our Payment gateway classes depends on PaymentGateway Interface for loose coupling
→ StripClient is 3rd party Class which we cannot modify and cannot change makeCharge(), So we used adapter pattern
→ to implement the makeCharge() in pay() so it can match our Design 

class StripeClient {
    public void makeCharge(int cents) {
        System.out.println("Stripe charged " + cents);
    }
}

interface PaymentGateway {
    void pay(double amount);
}

class StripeAdapter implements PaymentGateway {

    private StripeClient stripe;

    @Override
    public void pay(double amount) {
        stripe.makeCharge((int)(amount * 100));
    }
}

class PaymentService {

    private PaymentGateway paymentGateway;

    public void processPayment(double amount) {
        paymentGateway.pay(amount);
    }
}

public class Main {
    public static void main(String[] args) {

        PaymentGateway gateway = new StripeAdapter(stripeClient);
        PaymentService service = new PaymentService(gateway);
        service.processPayment(500.0);
    }
}

----------------------------------------------------------------------------------------------------------------------

DECORATOR PATTERN:
    → Decorator pattern adds multiple combinations of behavior to an object dynamically at runtime without modifying its original class.

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