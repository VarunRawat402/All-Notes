------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Spring Framework Concepts:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Container (IoC Container):
    Creates beans
    Manages bean lifecycle
    Injects dependencies

Spring Context (ApplicationContext):
    Advanced form of Spring Container:
    Includes:
        Event handling
        AOP support
        Internationalization (i18n)
        Property & profile management

So ApplicationContext = Container + extra features.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Dependency Injection Types:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: Constructor Injection ( Best )
Dependencies are passed via the constructor at object creation.
    Ensures dependency are injected when object is created
    Immutability - dependencies should be final 
    Testability  - Easier for unit testing

Ex:
@Service
class Car {

    private final Engine engine;
    public Car(Engine engine) {
        this.engine = engine;
    }
}


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2: Setter Injection:
    Dependency injected later
    Used when dependency is optional
    Can cause runtime errors without dependency
    Feilds cannot be final 

Ex:
@Service
class Car {
    private Engine engine;

    @Autowired
    public void setEngine(Engine engine) {
        this.engine = engine;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: Feild Injection ( Worst ):
    @Autowired is used to inject dependencies
    Hard to test
    No immutability
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

@PostConstruct (Executed After Bean Creation)
    Run methods automatically after the bean is created and dependencies are injected.

Used for:
    Initialization
    Resource setup

@PreDestroy (Executed Before Bean Destruction)
    Runs before the bean is removed from the Spring context.

Used for:
    Cleanup
    Closing connections

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
@Qualifer vs @Primary:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Primary:
    Default bean when multiple beans of same type exist
    Used automatically unless another bean is chosen explicitly

@Qualifier:
    Explicitly chooses which bean to inject
    Overrides @Primary.

Note:
@Component/@Service/@Repository → the default bean name is the class name with lowercase first letter.
@Bean                           → the default name is the method name.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example:
    Bean Name : debitPaymentService & creditPaymentService
    Bean Type : PaymentService

interface PaymentService {void pay();}

@Primary
public class DebitPaymentService implements PaymentService {
    public void pay() {System.out.println("Paid using Debit Card");}
}

public class CreditPaymentService implements PaymentService {
    public void pay() {System.out.println("Paid using Credit Card");}
}

@Service
class TransportService {

    @Autowired                              //Spring injects DebitPaymentService
    private PaymentService paymentService;
}

@Service
class TransportService {

    @Autowired
    @Qualifier("creditService")             //Spring injects CreditPaymentService
    private PaymentService paymentService;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Types of Bean Scopes:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Singleton Scope (Default):
    Only one instance of the bean is created and shared.
    Used : Service , Repository, Controller 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Prototype Scope:
    New instance every request
    Spring does NOT manage the lifecycle (you must handle destruction).

Used:
    A service which is new everytime you access it
    Coupon Generator ( whenever u access it creates a new one )

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Request Scope (For Web Applications):
    New instance per HTTP request

Used:
    Handling data specific to an HTTP request, such as request logging.
    ( Whenever that request is fetched you can perform actions on that new request )

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Session Scope (For Web Applications):
    One instance per user session

Used:
    ShoppingCart:
    (You have an shopping cart so a new shopping cart is made per user and it
    will be same for same user and different for different user )

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Application Scope (For Web Applications):
    One instance per web application
    Shared across all users

Used:
    Global config
    Caching

------------------------------------------------------------------------------------------------------------------------------------------------------------------------