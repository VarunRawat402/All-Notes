--------------------------------------------------------------------------------------------------------------------------------
Complete Repository Testing - Student Entity
--------------------------------------------------------------------------------------------------------------------------------

Purpose:
    → Test JPA Repository layer only
    → Uses in-memory H2 database
    → Each test runs in transaction + auto rollback


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

    //Test 1: Check if Students Are Saved in DB 
    @Test
    void checkIfStudentsAreSaved() {

        Optional<Student> saved1 = studentRepository.findById(varun.getId());
        Optional<Student> saved2 = studentRepository.findById(nandni.getId());

        assertTrue(saved1.isPresent());
        assertTrue(saved2.isPresent());
    }

    //Test 2: ID Generation Check
    @Test
    public void idGenerationOfStudents(){

        Student s1 = Student.builder().name("Eren").course("Btech").age(24).build();
        Student s2 = Student.builder().name("Grisha").course("Btech").age(31).build();

        Student save1 = studentRepository.save(s1);
        Student save2 = studentRepository.save(s2);

        assertThat(save1.getId()).isNotNull();
        assertThat(save2.getId()).isNotNull();

    }

    //Test 3: Validate Field Values
    @Test
    void checkFieldValues() {

        assertThat(varun.getAge()).isEqualTo(24);
        assertThat(nandni.getCourse()).isEqualTo("Taxation");
        assertThat(varun.getName()).isNotBlank();
    }
}

--------------------------------------------------------------------------------------------------------------------------------