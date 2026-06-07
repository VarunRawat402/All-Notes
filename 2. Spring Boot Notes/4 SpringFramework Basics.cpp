-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Framework Concepts:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Dependency Injection Types:

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Constructor Injection ( Best ):
    → Dependency passed when object is created using constructor
    → Dependency is mandatory, cant create object without it
    → Easy to test (pass mock in constructor)
    → Circular dependency caught at startup

Ex:
@Service
class UserService {
    private final UserRepository userRepository ;

    UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }
}

Mocking in Unit Testing:

// in test → just pass mock through constructor
UserRepository mockRepo = mock(UserRepository.class);
UserService service = new UserService(mockRepo); // ✅ easy

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Setter Injection:
    → Object created first, dependency set after via setter
    → Dependency is optional
    → Use when dependency not always required

Ex:
@Service
class UserService {
    private UserRepository userRepository ;

    @Autowired
    void setRepo(UserRepository repo) {
        this.repo = repo;
    }
}

Mocking in Unit Testing:

// in test → you CAN call setter manually
UserService service = new UserService();
service.setRepo(mockRepo); // ✅ works technically

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Feild Injection ( Worst ):
    → Spring injects directly into field via reflection
    → Hard to test, private field, cant pass mock
    → Dont use in production

Ex:
@Service
class UserService {
    public UserRepository userRepository ;

    @Autowired
    private UserRepository repo;   // private field, no constructor, no setter
}

Mocking in Unit Testing:

// in test → how do you set repo?
UserService service = new UserService();
service.repo = mockRepo; // ❌ private field, can't access directly

-----------------------------------------------------------------------------------------------------------------------------------------------------

@PostConstruct (Executed After Bean Creation):
    → Run methods automatically after the bean is created and dependencies are injected.
    → Used for Initialization, Resource setup

@PreDestroy (Executed Before Bean Destruction):
    → Runs before the bean is removed from the Spring context.
    → Used for cleanup, closing connections

-----------------------------------------------------------------------------------------------------------------------------------------------------
@Qualifer vs @Primary:
-----------------------------------------------------------------------------------------------------------------------------------------------------

@Primary:
    → Default bean when multiple beans of same type exist
    → Used automatically unless another bean is chosen explicitly

@Qualifier:
    → Manually select a specific bean by name
    → Overrides @Primary.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
@Component/@Service/@Repository:
    → the default bean name is the class name with lowercase first letter.
@Bean:
    → the default name is the method name.

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------
Types of Bean Scopes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Singleton Scope (Default):
    → Only one instance of the bean is created and shared.
    → Used : Service , Repository, Controller 

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Prototype Scope:
    → New instance every request
    → Spring does NOT manage the lifecycle (you must handle destruction).

Used:
    → A service which is new everytime you access it
    → Coupon Generator ( whenever u access it creates a new one )

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Request Scope (For Web Applications):
    → New instance per HTTP request

Used:
    → Handling data specific to an HTTP request, such as request logging.
    →  Whenever that request is fetched you can perform actions on that new request )

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Session Scope (For Web Applications):
    → One instance per user session

Used:
    ShoppingCart:
    → (You have an shopping cart so a new shopping cart is made per user and it
    → will be same for same user and different for different user )

-----------------------------------------------------------------------------------------------------------------------------------------------------

5: Application Scope (For Web Applications):
    → One instance per web application
    → Shared across all users

Used:
    → Global config
    → Caching

-----------------------------------------------------------------------------------------------------------------------------------------------------
