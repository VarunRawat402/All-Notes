------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Framework Concepts:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Container vs Spring Context (IoC Container):

Spring Container: 
Core mechanism that creates and manages beans.

Spring Context (ApplicationContext):
A more advanced and feature-rich type of Spring container. Supports:
    Event handling
    AOP
    Internationalization
    Property management

So ApplicationContext = Container + extra features.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Qualifer vs @Primary:

@Primary ( Default Bean Selection )
Default bean when multiple beans of the same type exist.
Works unless another bean is explicitly chosen using @Qualifier.

@Qualifier ( Choosing a Specific Bean )
Used to select a specific bean when multiple beans exist. 
Overrides @Primary.

Note:
If the bean is created via @Component/@Service/@Repository, the default bean name is the class name with lowercase first letter.
If the bean is created via @Bean in a configuration class, the default name is the method name.

Ex:
interface Vehicle {
    void drive();
}

@Component
@Primary  
class Car implements Vehicle {
    public void drive() {
        System.out.println("Car is driving...");
    }
}

@Component
class Bike implements Vehicle {
    public void drive() {
        System.out.println("Bike is driving...");
    }
}

@Service
class TransportService {
    private final Vehicle vehicle;

    // No @Qualifier used, so Spring picks @Primary bean (Car)
    public TransportService(Vehicle vehicle) {
        this.vehicle = vehicle;
    }

    public void startJourney() {
        vehicle.drive();
    }
}

@Service
class TransportService {
    private final Vehicle vehicle;

    public TransportService(@Qualifier("bike") Vehicle vehicle) {
        this.vehicle = vehicle;
    }

    public void startJourney() {
        vehicle.drive();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

POJO VS Java Bean VS Spring Bean:

POJO (Plain Old Java Object)
Simple java class with no restrictions
getter + setter + methods + private variables are optional
No dependencies on spring framework

Ex:
    public class Car {
        private String brand;
        
        public Car(String brand) {
            this.brand = brand;
        }
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Java Bean:

A Java Bean is a special type of POJO with these rules:
Private feilds + public getters & setters + no argument constructor is must
Serializable (optional)

Ex:
    public class Person implements Serializable { // Optional for Java Bean
        private String name;
    
        public Person() {}
    
        public String getName() {
            return name;
        }
    
        public void setName(String name) {
            this.name = name;
        }
    }
    
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Bean:
Can be pojo or java bean
Needs to be managed by spring using @Component annotation

Ex:
    @Component  // Marks this as a Spring Bean
    public class Car {
        public void drive() {
            System.out.println("Car is moving...");
        }
    }


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DI ( Dependency Injection Type ):

1: Constructor Injection ( Best )
Dependencies are passed via the constructor.
    Supports Immutability and Testability
    Ensures dependency injection when object is created
    Immutability - dependencies should be final 
    Testability  - Easier for unit testing

Ex:
    @Service
    class Car {
        private final CarRepository carRepository;

        public Car(Engine engine) {
            this.engine = engine;
        }
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2: Setter Injection:
    Injects dependencies using setteer function
    Used when dependency are not always needed and only injects when required
    Cons: Object can be created without dependency + can fail at runtime
    Dev sometime forgets to call the dependencies
    Feilds cannot be final 

Ex:
    @Service
    class Car {
        private Engine engine;

        @Autowired
        public void setEngine(Engine engine) {
            this.engine = engine;
        }

        public void drive() {
            engine.start();
            System.out.println("Car is moving...");
        }
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: Feild Injection ( Worst ):
    @Autowired is used to inject dependencies
    Cons: Make testing harder
    Uses @Autowired directly on the field, making it impossible to create an instance without Springs help.
    If you create car object manually, dependency will not be injected in the object making testing harder
    Gives null pointer exception

Ex:
@Service
class Car {
    @Autowired
    private Engine engine; // Field Injection

    public void drive() {
        engine.start();
        System.out.println("Car is moving...");
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Types of Bean Scopes:

Singleton Scope (Default):

Only one instance of the bean is created and shared.
Spring manages the lifecycle.
Used : Service , Repository, Controller 

Ex:
    @Component
    @Scope("singleton")  // Default scope (can be omitted)
    class SingletonBean {
        public SingletonBean() {
            System.out.println("✅ SingletonBean Created!");
        }
    }

    SingletonBean bean1 = context.getBean(SingletonBean.class);
    SingletonBean bean2 = context.getBean(SingletonBean.class);

    System.out.println(bean1 == bean2); // ✅ True (same instance)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Prototype Scope:
A new instance is created each time it is requested.
Spring does NOT manage the lifecycle (you must handle destruction).
Used:
A service which is new everytime you access it
Coupon Generator ( whenever u access it creates a new one )

Code:
    PrototypeBean bean1 = context.getBean(PrototypeBean.class);
    PrototypeBean bean2 = context.getBean(PrototypeBean.class);

    System.out.println(bean1 == bean2); // ❌ False (different instances)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Request Scope (For Web Applications):
A new instance is created for each HTTP request.
Available only in Spring Web Applications.
Used :
Handling data specific to an HTTP request, such as request logging.
( Whenever that request is fetched you can perform actions on that new request )

Code:
@Component
@RequestScope  // Or use @Scope("request")
class RequestBean {
    public RequestBean() {
        System.out.println("🌍 New RequestBean Created!");
    }
}

@RestController
public class TestController {
    private final RequestBean requestBean;

    public TestController(RequestBean requestBean) {
        this.requestBean = requestBean;
    }

    @GetMapping("/test")
    public String test() {
        return "Request Bean: " + requestBean;
    }
}

O/P: 
🌍 New RequestBean Created!  // For first request
🌍 New RequestBean Created!  // For second request

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Session Scope (For Web Applications):
One instance per user session.
Useful for storing user-specific data (e.g., authentication, User Details ).
Used:
ShoppingCart:
(You have an shopping cart so a new shopping cart is made per user and it
will be same for same user and different for different user )

Application Scope (For Web Applications):
One instance per web application (shared across requests & sessions).
Useful for global application settings or caching.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference Between Session and Singleton:
Problem: 
Shared Cart for All Users
    With @Singleton, there is only one instance of ShoppingCart in the entire application.

    Example of Unexpected Behavior
    User A adds "Shoes" → The singleton ShoppingCart instance stores ["Shoes"].
    User B adds "Watch" → The same ShoppingCart instance is used → The cart now contains ["Shoes", "Watch"].
    User A views their cart → Sees User B's items too!
    User C adds "Laptop" → Now all users see ["Shoes", "Watch", "Laptop"]

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Difference Between Session and Prototype:
Problem: Cart Data Will Not Persist
With @Prototype, the shopping cart will reset on every request, so users will lose previously added items.

Example of Unexpected Behavior
User A calls /add-to-cart?item=Shoes

A new ShoppingCart instance is created.
"Shoes" is added to this cart.
User A calls /add-to-cart?item=Watch

A new ShoppingCart instance is created again.
"Watch" is added, but "Shoes" is lost.
User A views /cart

Instead of ["Shoes", "Watch"], they see only the last added item or an empty cart.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@PostContruct vs @PreConstruct:

@PostConstruct (Executed After Bean Creation)
Runs automatically after the bean is created and dependencies are injected.
Typically used for initialization logic, like setting up resources or preloading data.
Runs only once per bean lifecycle.
When Spring creates DatabaseService, it automatically calls init().

Code:
@Component
public class DatabaseService {
    
    @PostConstruct  // Executes after the bean is created
    public void init() {
        System.out.println("🔄 Database connection initialized...");
    }
}

@PreDestroy (Executed Before Bean Destruction)
Runs before the bean is removed from the Spring context.
Typically used for cleanup logic, like closing database connections or releasing resources.
Runs only once before the bean is destroyed.
Example: Closing a Database Connection
When the application shuts down, Spring calls cleanup() to release resources properly.

Code:
@Component
public class DatabaseService {
    
    @PreDestroy  // Executes before the bean is destroyed
    public void cleanup() {
        System.out.println("❌ Closing database connection...");
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Real Application Example:

@Component
public class EmailService {
    
    private EmailClient client;

    @PostConstruct
    public void setup() {
        client = new EmailClient();
        client.connect();
        System.out.println("📧 Email service is ready to send emails.");
    }

    @PreDestroy
    public void shutdown() {
        client.disconnect();
        System.out.println("📴 Email service is shutting down.");
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
