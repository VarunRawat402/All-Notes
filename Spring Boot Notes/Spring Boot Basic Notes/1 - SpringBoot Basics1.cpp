-----------------------------------------------------------------------------------------------------------------------
Lecture 1: Spring Boot Basics
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

-----------------------------------------------------------------------------------------------------------------------

How to use Logger:

Option 1:

    private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    logger.info("This is an info message");
    Controller is the class name.

Option 2:

    Use @Slf4j on top of the class
    log.info("message");

----------------------------------------------------------------------------------------------------------------------

Command line runner :

It is an interface
It lets u run code after spring application context is fully started
You need to override the run() method in CommandLineRunner

Main():
It is static and runs before spring creates beans, load configs, autowire dependency
You cannot use autowired fields + access beans + repo, service, controller etc

Uses:
Insert initial data
Run setup scripts

----------------------------------------------------------------------------------------------------------------------

ModelMapper:
Used to map fields from one class to another. Useful when entity classes and response DTOs differ.

Example:
Two classes → Student and StudentResponse.
We fetch a Student entity but want to return a StudentResponse in the API.

Student student = repository.findById(id).get();
StudentResponse studentResponse = modelMapper.map(student, StudentResponse.class);

----------------------------------------------------------------------------------------------------------------------

Circular Dependency:

Code:

Book Class:
public class Book{

    private int id;
    private String name;
    private int cost

    @ManyToOne
    @JoinColumn
    @JsonIgnore
    private Author author;
}

Author Class:
public class Author{

    private int id;
    private String name;
    private String email;

    @OneToMany(mappedBy="author",fetch=FetchType.EAGER);
    private List<Book> booklist
}

While returning a Book, it tries to fetch the Author.
While fetching Author, it tries to fetch the bookList.
This causes circular dependency in JSON serialization, not in Spring beans.

Ways to break the loop:

    1: @JsonIgnore: We will put it on Author and It will ignore the author while collecting data.
    2: @JsonIgnore("bookList") : It will go to the author and collect all data except bookList.


----------------------------------------------------------------------------------------------------------------------
Mapping DTOs (MapStruct() ) :
----------------------------------------------------------------------------------------------------------------------

Dependency:

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

Interface:
Create an Interface with @Mapper() annotation 
Create an abstract method taking Student and Returning StudentResponse, Mapper will automatically implement this

@Mapper(componentModel = "spring")
public interface StudentMapper {
    
    StudentResponse toStudentResponse(Student student);
}

2: If Feilds names are different you can mention it here

@Mapper(componentModel = "spring")
public interface StudentMapper {
 
    @Mapping(target = "username", source = "name")
    @Mapping(target = "department", source = "dept")
    @Mapping(target = "createdDate", expression = "java(java.time.LocalDate.now())")
    StudentResponse toStudentResponse(Student student);
}

----------------------------------------------------------------------------------------------------------------------