----------------------------------------------------------------------------------------------------------------------------------------
Mockito:
----------------------------------------------------------------------------------------------------------------------------------------

Mockito:
    → Framework for unit testing 
    → replaces real dependencies with mocks
    → Tests run in-memory → no real DB, HTTP, or external service calls
    → Isolates the class you're testing from its dependencies

----------------------------------------------------------------------------------------------------------------------------------------

What to mock:

→ Repository     → instead of hitting real DB
→ RestTemplate, FeignClient, WebClient → instead of real API calls
→ AWS SDK, payment gateways, email/SMS services

----------------------------------------------------------------------------------------------------------------------------------------

MOCKITO Annotations:

1: @ExtendWith(MockitoExtension.class) 
    → enables Mockito in test class

2: @Mock           
    → creates a mock object of a class/interface

3: @InjectMocks    
    → creates real instance + injects all @Mock into it

4: @MockBean       
    → replaces a Spring Bean with mock (used in controller tests)

----------------------------------------------------------------------------------------------------------------------------------------

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
    → Configures MockMvc automatically
    → Used to test controllers without starting a real server

MockMvc:
    → Sends HTTP requests (GET, POST, PUT, DELETE)  without starting real server
    → Verifies status, response body, headers
    → Validates JSON serialization/deserialization

@MockBean:
    → Replaces a Spring Bean with a mock during tests
    → Used mostly in controller tests

----------------------------------------------------------------------------------------------------------------------------------------

@Test
void testGetStudent() throws Exception {

    // mock service response
    when(studentService.getStudentById(1L)).thenReturn(new Student(1L, "John Doe"));

    // send GET request and verify response
    mockMvc.perform(get("/students/1"))
        .andExpect(status().isOk())
        .andExpect(jsonPath("$.name").value("John Doe"));

    // verify service method was actually called
    verify(studentService).getStudentById(1L);
}

----------------------------------------------------------------------------------------------------------------------------------------

verify():
    → Confirms a method was actually called during the test
    → Can check call count and parameters
    verify(studentService).getStudentById(1L);        // called once
    verify(studentService, times(2)).getStudentById(1L); // called twice

----------------------------------------------------------------------------------------------------------------------------------------

