--------------------------------------------------------------------------------------------------------------------------------
Testing of Student Service Layer using Mockito
--------------------------------------------------------------------------------------------------------------------------------

@ExtendWith(MockitoExtension.class)
public class StudentServiceTest {

    @Mock                   //Mocking the Repository
    private StudentRepository studentRepositoryMock;

    @InjectMocks            //Injecting the Mock Repository in Service-+

    private StudentService studentService;

    //Initializing the mock students here so every function can use it
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

        studentRepositoryMock.save(varun);
        studentRepositoryMock.save(nandini);
    }

    //Check Addition
    @Test
    public void checkAddition(){
        int answer = studentService.addition(1,2);
        assertThat(answer).isEqualTo(3);
    }

    //Check Multiplication
    @Test
    public void checkMultplication(){
        int answer = studentService.mult(10,25);
        assertEquals(250,answer);
    }

    //Check if student is getting fetched or not using ID
    @Test
    public void getStudentById(){
        when(studentRepositoryMock.findById(1)).thenReturn(Optional.of(varun));
        Student s1 = studentService.getStudentById(1);
        assertNotNull(s1);
    }

    //Check if the username is getting fetchec correctly
    @Test
    public void validateUsername(){
        when(studentRepositoryMock.findById(1)).thenReturn(Optional.of(varun));
        String name = studentService.getUserName(1);
        assertEquals("varun",name);
    }

    //Check if course is getting fetched correctly
    @Test
    public void validateCourse(){
        when(studentRepositoryMock.findById(1)).thenReturn(Optional.of(varun));
        String course = studentService.getCourse(1);
        assertEquals("Btech",course);
    }
}
