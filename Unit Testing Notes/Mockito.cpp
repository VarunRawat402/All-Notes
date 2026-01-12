----------------------------------------------------------------------------------------------------------------------------------------
Mockito:
----------------------------------------------------------------------------------------------------------------------------------------

Mockito is used for unit testing where dependencies are replaced with mocks to isolate and test a single class.

Mocks:
    Run in-memory
    Avoid slow I/O operations (DB, HTTP calls, external services)
    Help simulate edge cases like null values, errors, and exceptions

----------------------------------------------------------------------------------------------------------------------------------------
Mockito Uses:
----------------------------------------------------------------------------------------------------------------------------------------

Mockito Uses:

Databases: 
    Mock Repository classes instead of hitting a real DB

APIs / Web Services: 
    Mock RestTemplate, FeignClient, WebClient

Third-Party Services: 
    Mock AWS SDK, payment gateways, SMS/email services

----------------------------------------------------------------------------------------------------------------------------------------

MOCKITO Annotations:
    Mockito provides annotations to reduce boilerplate code.

@Mock           → Creates mock object
@InjectMocks    → Injects mocks into the class under test


Student Service Test (Using Annotations):

@ExtendWith(MockitoExtension.class)
public class StudentServiceTest {

    @Mock
    private StudentRepository studentRepositoryStub;

    @InjectMocks
    private StudentService studentService;

    @Test
    void testSuccessfulTest() {
        when(studentRepositoryStub.findById(1))
            .thenReturn(Optional.of(new Student(1, "Varun Rawat")));

        String name = studentService.getName(1);
        assertEquals("Varun Rawat", name);
    }

    @Test
    void testFailedTest() {
        when(studentRepositoryStub.findById(1))
            .thenReturn(Optional.of(new Student(1, "Varun Rawat")));

        String name = studentService.getName(1);
        assertNotEquals("Varun", name);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------

Testing Controller Layer APIs:

@AutoConfigureMockMvc:
    Configures MockMvc automatically
    Used to test controllers without starting a real server

MockMvc:
    Sends HTTP requests (GET, POST, PUT, DELETE)
    Verifies status, response body, headers
    Validates JSON serialization/deserialization

@MockBean:
    Replaces a Spring Bean with a mock during tests
    Used mostly in controller tests

----------------------------------------------------------------------------------------------------------------------------------------

Code:

@Test
public void testGetStudent() throws Exception {

    when(studentService.getStudentById(1L)).thenReturn(new Student(1L, "John Doe"));
    
    mockMvc.perform(get("/students/1")).andExpect(status().isOk()).andExpect(jsonPath("$.name").value("John Doe"));
    
    verify(studentService).getStudentById(1L);
}

verify():
    Ensures a method was called
    Can verify call count and parameters

----------------------------------------------------------------------------------------------------------------------------------------

