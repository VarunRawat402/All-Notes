-----------------------------------------------------------------------------------------------------------------------
Spring Boot Basics
-----------------------------------------------------------------------------------------------------------------------

Inversion Of Control:

Instead of you managing the lifecycle of objects, Spring creates and manages them.
@Component → Spring automatically creates an object (bean) of that class.
All auto-created beans are stored inside the IoC Container.
Objects created manually using new are not stored in the IoC Container, so Spring cannot inject them.

-----------------------------------------------------------------------------------------------------------------------

Dependency Injection:
DI allows us to use beans created by Spring anywhere in the application.
If Spring did not create an object, then that object is not available for injection.
DI completely depends on IoC, because IoC must create and store the object first.

----------------------------------------------------------------------------------------------------------------------

Why Main() is static:

main() is static so JVM can call it immediately, without creating any object.
If it were not static:
    JVM would need to create an object, but it would not know which constructor to call.
    That would create a circular problem.

----------------------------------------------------------------------------------------------------------------------

Command line runner :

It is an interface
It lets u run code after spring application context is fully started
@Override the run() method in CommandLineRunner

Main():
It is static and runs before spring creates beans, load configs, autowire dependency
You cannot use autowired fields + access beans + repo, service, controller etc

----------------------------------------------------------------------------------------------------------------------

Singleton Class:
A singleton class is a class that allows only one instance of itself to be created and provides a global access point to that instance.

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
    If the class implements Cloneable, clone() can produce a new instance.

Fix:
    Override clone() and prevent cloning:
    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }

Serialization:
    Serialization creates a new object during deserialization.

    Implement readResolve() to return the original instance:
    private Object readResolve() {
        return INSTANCE;
    }

----------------------------------------------------------------------------------------------------------------------

How to use Logger:

Option 1:

    private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    logger.info("This is an info message");
    Controller is the class name.

Option 2:

    Use @Slf4j on top of the class
    log.info("message");

----------------------------------------------------------------------------------------------------------------------

Mapping DTOs:
    MapStruct() is used to map DTOs

1: Dependency:

<dependencies>
    <!-- MapStruct Runtime -->
    <dependency>
        <groupId>org.mapstruct</groupId>
        <artifactId>mapstruct</artifactId>
        <version>1.5.5.Final</version>
    </dependency>

    <!-- Lombok -->
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <version>1.18.32</version>
        <scope>provided</scope>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <version>3.11.0</version>
            <configuration>
                <annotationProcessorPaths>
                    <!-- Lombok -->
                    <path>
                        <groupId>org.projectlombok</groupId>
                        <artifactId>lombok</artifactId>
                        <version>1.18.32</version>
                    </path>

                    <!-- MapStruct Processor -->
                    <path>
                        <groupId>org.mapstruct</groupId>
                        <artifactId>mapstruct-processor</artifactId>
                        <version>1.5.5.Final</version>
                    </path>

                    <!-- Lombok + MapStruct Binding -->
                    <path>
                        <groupId>org.projectlombok</groupId>
                        <artifactId>lombok-mapstruct-binding</artifactId>
                        <version>0.2.0</version>
                    </path>
                </annotationProcessorPaths>
            </configuration>
        </plugin>
    </plugins>
</build>


----------------------------------------------------------------------------------------------------------------------

2: Interface:

Create an Interface with @Mapper() annotation 
Create an abstract method taking Student and Returning StudentResponse, Mapper will automatically implement this

@Mapper(componentModel = "spring")
public interface StudentMapper {
    
    StudentResponse toStudentResponse(Student student);
}

3: If Feilds names are different you can mention it here

@Mapper(componentModel = "spring")
public interface StudentMapper {
 
    @Mapping(target = "username", source = "name")
    @Mapping(target = "department", source = "dept")
    @Mapping(target = "createdDate", expression = "java(java.time.LocalDate.now())")
    StudentResponse toStudentResponse(Student student);
}

----------------------------------------------------------------------------------------------------------------------