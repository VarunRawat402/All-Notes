--------------------------------------------------------------------------------------------------------------------------------
Complete Testing code for Testing a student Object in Repository:
--------------------------------------------------------------------------------------------------------------------------------

@DataJpaTest
@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)
class StudentRepositoryTest {

    @Autowired
    StudentRepository studentRepository;

    private Student varun;
    private Student nandni;

    @BeforeEach
    void saveStudent(){

        varun = Student.builder()
                .name("varun")
                .course("Btech")
                .age(24)
                .build();

        nandni = Student.builder()
                .name("nandni")
                .course("Taxation")
                .age(24)
                .build();

        studentRepository.save(varun);
        studentRepository.save(nandni);
    }

    @Test
    public void checkIfGlobalStudentIsSaved(){

        //Fetching the Students
        Optional<Student> saved1 = studentRepository.findById(1);
        Optional<Student> saved2 = studentRepository.findById(2);

        //Checking saved Data
        assertNotNull(saved1);
        assertNotNull(saved2);
        assertNull(saved1.get(),"Saved1 Student should be empty");
    }

    @Test
    public void idGenerationOfStudents(){

        //Creating the student
        Student s1 = Student.builder().name("nikhil").course("Btech").age(24).build();
        Student s2 = Student.builder().name("Arun").course("EEE").age(31).build();

        //saving them in Repo
        Student save1 = studentRepository.save(s1);
        Student save2 = studentRepository.save(s2);

        //Checking if temp Students are saved successfully or not
        assertNotNull(save1);
        assertNotNull(save2);

        //Checking if the id is null
        assertThat(save1.getId()).isNotNull();
        assertThat(save2.getId()).isNotNull();

        //Checking if the id is as expected
        assertThat(save1.getId()).isEqualTo(3);
        assertThat(save2.getId()).isEqualTo(4);
    }

    @Test
    public void checkFeildValues(){
        assertThat(varun.getAge()).isEqualTo(24);
        assertThat(nandni.getCourse()).isEqualTo("Taxation");
        assertThat(varun.getName()).isNotBlank();
    }

}