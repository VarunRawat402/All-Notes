--------------------------------------------------------------------------------------------------------------------------------
Mockito:
--------------------------------------------------------------------------------------------------------------------------------

1: Tests should focus on one class (unit) without relying on real dependencies (e.g., databases, APIs, services).
Mockito replaces these dependencies with fake (mock) objects.

2: Check if a method was called, how many times, and with which arguments.

3: Mocks run in-memory, avoiding slow I/O operations (e.g., HTTP calls, DB queries).

4: Simulate rare scenarios (e.g., null returns, exceptions) without complex setups.

--------------------------------------------------------------------------------------------------------------------------------
Mockito Uses:
--------------------------------------------------------------------------------------------------------------------------------

Databases: Mock Repository classes to avoid real DB calls.
APIs/Web Services: Mock RestTemplate or FeignClient.
Third-Party Libraries: Mock classes from SDKs (e.g., AWS, Payment Gateways).

--------------------------------------------------------------------------------------------------------------------------------

MOCK:
How to mock the Data:

//This will return the Student object by their Id
//Used optional here coz mock functions returns in optional
Repository:
public interface StudentRepository extends JpaRepository<Student,Integer> {
    Optional<Student> findById(int id);
}

//This will fetch the student by the studentID using Repository 
//and returns the name of the student
Student Service:
@Service
public class StudentService {

    private final StudentRepository studentRepository;

    StudentService(StudentRepository studentRepository){
        this.studentRepository = studentRepository;
    }

    public String getName(int id){
        Student student = studentRepository.findById(id).orElse(null);
        return student.getName();
    }

}

--------------------------------------------------------------------------------------------------------------------------------

Student Service Test:
public class StudentServiceTest {

    //Created StudentRepository,StudentService instance 
    @Autowired
    StudentRepository studentRepositoryStub;
    @Autowired
    StudentService studentService;

    @BeforeEach
    void setup() {

        // Creating a stubbed StudentRepository using mock which will mock all the Respository functions
        studentRepositoryStub = mock(StudentRepository.class);

        //Initializing the studentService with stubRepository so we can use the stub data
        studentService = new StudentService(studentRepositoryStub);
    }

    //Testing the application
    //Now StudentService will use Stub Student Repository and whatever fake data it returns

    @Test
    void testFindStudentById() {
        String name  = studentService.getName(1);
        assertEquals("Varun Rawat", name); 

    }

    @Test
    void testFailedTest(){
        when(studentRepositoryStub.findById(1)).thenReturn(Optional.of(new Student(1, "Varun Rawat")));
        String name  = studentService.getName(1);
        assertNotEquals("Varun", name);
    }
}

--------------------------------------------------------------------------------------------------------------------------------

MOCKITO Annotations:
We can make mock testing more simple by using annotation
We can use @Mock to mock the Layer and @InjectMocks to inject the mock dependencies

Student Service Test:

@ExtendWith(MockitoExtension.class)
public class StudentServiceTest {

    @Mock
    private StudentRepository studentRepositoryStub;

    @InjectMocks
    private StudentService studentService;

    @Test
    void testSuccessfulTest() {
        when(studentRepositoryStub.findById(1)).thenReturn(Optional.of(new Student(1, "Varun Rawat")));
        String name  = studentService.getName(1);
        assertEquals("Varun Rawat", name);
    }

    @Test
    void testFailedTest(){
        when(studentRepositoryStub.findById(1)).thenReturn(Optional.of(new Student(1, "Varun Rawat")));
        String name  = studentService.getName(1);
        assertNotEquals("Varun", name);
    }
}

--------------------------------------------------------------------------------------------------------------------------------

Testing Controller Layer APIS:

@AutoConfigureMockMvc:
    Automatically configures a MockMvc instance for testing web layers
    Integration testing of controllers without the overhead of a real server

private MockMvc mockMvc
    Main testing utility for Spring MVC
    Send HTTP requests (GET, POST, PUT, DELETE)
    Verify responses (status, content, headers)
    Test JSON serialization/deserialization
    Validate controller behavior

@MockitoBean:
    Allows you to mock dependencies and define their behavior during tests

Code:

@Test
public void testGetStudent() throws Exception {
    // Arrange - set up mock behavior
    when(studentService.getStudentById(1L))
        .thenReturn(new Student(1L, "John Doe"));
    
    // Act & Assert - perform HTTP request and verify
    mockMvc.perform(get("/students/1"))
           .andExpect(status().isOk())
           .andExpect(jsonPath("$.name").value("John Doe"));
    
    // Verify mock interaction
    verify(studentService).getStudentById(1L);
}

verify():
    It is used to check weather this function gets called or not with given parameters

--------------------------------------------------------------------------------------------------------------------------------

