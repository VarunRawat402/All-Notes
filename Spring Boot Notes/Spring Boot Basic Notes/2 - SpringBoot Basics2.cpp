-----------------------------------------------------------------------------------------------------------------------
Lecture 2: Spring Boot Basics
-----------------------------------------------------------------------------------------------------------------------

How to use Logger:
private static Logger logger = LoggerFactory.getLogger(Controller.class);
Controller is a class name

or 

@Slf4j annotation on top of the class
Then use log.info("message");

----------------------------------------------------------------------------------------------------------------------

Command line runner :

Main function is a static function so we cannot use any service, Repository etc in main as they are non-static
CommandLineRunner helps us run the non static function at the start of the application

public class Demo implements CommandLineRunner{

    @Autowired
    AuthorRepository ar;

    public static void main(String[] args){

    }

    @Override
    public void run(String[] args) throws Exception{

    }
}

-----------------------------------------------------------------------------------------------------------------------

Inversion Of Control:
Instead of you managing the Lifecycle of the object yourself, spring will do it for you.

@Component = The spring will create bean/object of any classes which have component annotation directly or indirectly.
Object created by spring automatically will be stored in the IOC Container for us to use
Object created by us manually using new keyword will not be stored in the Container.

-----------------------------------------------------------------------------------------------------------------------

Dependency Injection:
It is a process to use a bean/object of some class to use wherever we want in whole Application
if spring didnt create an object there is no object in the Container to use.
So Dependency Injection is Dependable to IOC.

-----------------------------------------------------------------------------------------------------------------------

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

When we fetch the book Details it will fetch the id, name and cost with no problem
But to fetch the author it will go to the author table then it tries to fetch the bookList and then
it will go to the Book again making this a circular loop called circular dependency.

To break that infinite loop we have many things:

    1: @JsonIgnore: We will put it on Author and It will ignore the author while collecting data.
    2: @JsonIgnore("bookList") : It will go to the author and collect all data except bookList.


----------------------------------------------------------------------------------------------------------------------
