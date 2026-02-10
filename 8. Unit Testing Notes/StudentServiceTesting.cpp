--------------------------------------------------------------------------------------------------------------------------------
Testing Student Service Layer using Mockito:
--------------------------------------------------------------------------------------------------------------------------------

Purpose:
    → Test Service layer in isolation
    → Replace Repository with mock
    → No database, no Spring context, pure unit test

@ExtendWith(MockitoExtension.class)
public class StudentServiceTest {

    @Mock                                                           //Mocking the Repository
    private StudentRepository studentRepositoryMock;

    @InjectMocks                                                    //Injecting the Mock Repository in Service-+
    private StudentService studentService;

    private Student varun;
    private Student nandini;

    //This will create the students before each test so we dont have to create manually in each test
    @BeforeEach
    void initializeStudentsToTest(){
        varun = Student.builder()
                .name("varun")
                .course("Btech")
                .age(24)
                .build();

        nandini = Student.builder()
                .name("nandini")
                .course("Taxation")
                .age(24)
                .build();
    }

    //Test 1: Fetch Student by ID
    @Test
    void getStudentById() {

        when(studentRepositoryMock.findById(1)).thenReturn(Optional.of(varun));
        Student student = studentService.getStudentById(1);

        assertNotNull(student);
        assertEquals("varun", student.getName());
    }

    //Test 2: Validate Course
    @Test
    void validateCourse() {

        when(studentRepositoryMock.findById(1)).thenReturn(Optional.of(varun));
        String course = studentService.getCourse(1);

        assertEquals("Btech", course);
    }
}

--------------------------------------------------------------------------------------------------------------------------------