-----------------------------------------------------------------------------------------------------------------------
Spring Boot Basics
-----------------------------------------------------------------------------------------------------------------------

Inversion Of Control:

→ Instead of you managing the lifecycle of beans, Spring creates and manages them.
→ @Component → Spring automatically creates a bean of that class.
→ All auto-created beans are stored inside the IoC Container.
→ Objects created manually using new are not stored in the IoC Container, so Spring cannot inject them.

-----------------------------------------------------------------------------------------------------------------------

Dependency Injection:
→ DI allows us to use beans created by Spring anywhere in the application.
→ If Spring did not create an object, then that object is not available for injection.

----------------------------------------------------------------------------------------------------------------------

Why Main() is static:

→ main() is static so JVM can call it immediately, without creating any object.
→ If it were not static:
    → JVM would need to create an object, but it would not know which constructor to call.

----------------------------------------------------------------------------------------------------------------------

Command line runner :

→ It is an interface
→ It lets you run code after spring application context is fully started
→ @Override the run() method in CommandLineRunner

Main():
→ You cannot use autowired fields + access beans + repo, service, controller etc
→ It is static and runs before spring creates beans, load configs, autowire dependency


----------------------------------------------------------------------------------------------------------------------

Singleton Class:
    → A singleton class is a class that allows only one instance

Code:
public class Customer {

    private static Customer customer;
    private final int id;
    private final String name;

    private Customer(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public static synchronized Customer getCustomer(int id, String name) {
        if (customer == null) {
            customer = new Customer(id, name);
        }
        return customer;
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

How to use Logger:

Option 1:
    → private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    → logger.info("This is an info message");
    → Controller is the class name.

Option 2:
    → Use @Slf4j on top of the class
    → log.info("message");

----------------------------------------------------------------------------------------------------------------------