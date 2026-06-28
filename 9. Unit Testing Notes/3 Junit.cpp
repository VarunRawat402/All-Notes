--------------------------------------------------------------------------------------------------------------------------------
Junit 4 and Junit 5 Annotations:
--------------------------------------------------------------------------------------------------------------------------------

@Test               → marks method as a test case
@Disabled           → skips test method or entire class

@BeforeEach         → runs before EACH test method
@AfterEach          → runs after EACH test method
@BeforeAll          → runs ONCE before all tests    (must be static)
@AfterAll           → runs ONCE after all tests     (must be static)

@DisplayName        → sets readable custom name for test
@Timeout            → fails test if it exceeds given time limit

--------------------------------------------------------------------------------------------------------------------------------

Parameterized Test Annotations:

@ParameterizedTest  → marks test to run multiple times with different inputs
@ValueSource        → single value per run (ints, strings etc)
@CsvSource          → multiple values per run (inline CSV)
@CsvFileSource      → multiple values loaded from CSV file

--------------------------------------------------------------------------------------------------------------------------------

DB Testing Behavior:

@SpringBootTest → changes persist in DB after test
    → add @Transactional to rollback changes after each test

@DataJpaTest → automatically rolls back after each test
    → add @Commit if you want changes to persist

--------------------------------------------------------------------------------------------------------------------------------

Parameterized Tests:
    → Tests that run the same logic with different inputs automatically. 

--------------------------------------------------------------------------------------------------------------------------------

1: Single Value (ValueSource):

@ParameterizedTest
@ValueSource(ints = {2,5,6,8,10})
public void isEven(int num){
    assertThat(num%2==0).isTrue();
}

@ParameterizedTest
@ValueSource(strings = {"varun","arun"})
void isNotBlank(String s) {
    assertThat(s).isNotBlank();
}

--------------------------------------------------------------------------------------------------------------------------------

2: Multilevel Parameter (CsvSource):

@ParameterizedTest
@CsvSource({"3,9", "4,16", "5,25"})
void testSquare(int input, int expected) {
    assertEquals(expected, input * input);
}

--------------------------------------------------------------------------------------------------------------------------------

3: Values from CSV file (CsvFileSource):

@ParameterizedTest
@CsvFileSource(resources = "/testdata.csv")
void testNumberWords(int num, String word) {
    assertEquals(word, convertToWord(num));
}

--------------------------------------------------------------------------------------------------------------------------------

4. Check if names exist in DB:

@ParameterizedTest
@ValueSource(strings = {"varun", "nandni"})
void checkUserNames(String name) {
    List<Student> students = studentRepository.findAll();
    assertTrue(students.stream()
        .anyMatch(s -> s.getName().equals(name)),
        "Student with name " + name + " not found");
}

--------------------------------------------------------------------------------------------------------------------------------

5. Check if usernames exist in repository:

@ParameterizedTest
@CsvSource({"varun", "arun", "shiro"})
void nameTest(String name) {
    assertNotNull(userRepository.findByUsername(name));
}

--------------------------------------------------------------------------------------------------------------------------------
