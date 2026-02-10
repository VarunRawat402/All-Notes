--------------------------------------------------------------------------------------------------------------------------------
Junit 4 and Junit 5 Annotations:
--------------------------------------------------------------------------------------------------------------------------------

@Disabled               : Disables a test method or Class.

@Test                   : Marks a method as a test case.

@BeforeEach             : Runs before each test method.

@AfterEach              : Runs after each test method

@BeforeAll              : Runs once before all tests (static).

@AfterAll               : Runs once after all tests (static).

@DisplayName            : Sets a custom readable name for a test.

@ParameterizedTest      : Marks a test that runs multiple times with different inputs.

@ValueSource            : Provides simple literal values (ints, strings, etc.).

@CsvSource              : Provides inline CSV values for multi-argument tests.

@CsvFileSource          : Loads CSV data from a file.

@Timeout                : Fails the test if it exceeds the given time limit.

--------------------------------------------------------------------------------------------------------------------------------

Database Testing Annotations:

→ In @SpringBootTest, If you make changes in the DB, It will stay in the DB
→ If you want to rollback changes in @SpringBootTest you can use @Transactional

→ In @DataJpaTest, If you make changes in DB, it will get rollbacked after every test
→ If you dont want to rollback changes you can use @Commit annotation

--------------------------------------------------------------------------------------------------------------------------------

Parameterized Tests:
    → Tests that run the same logic with different inputs automatically. 

--------------------------------------------------------------------------------------------------------------------------------

1: Single Parameter (ValueSource):

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

3: File-Based Parameters (CsvFileSource):

@ParameterizedTest
@CsvFileSource(resources = "/testdata.csv")
void testNumberWords(int num, String word) {
    assertEquals(word, convertToWord(num));
}

--------------------------------------------------------------------------------------------------------------------------------

1: Check if all the given names is present in the DB or not:

@ParameterizedTest
@ValueSource(strings = {"varun","nandni"})
public void checkUserNames(String name){
    List<Student> l1 = studentRepository.findAll();

    assertTrue(l1.stream().anyMatch(student -> student.getName().equals(name)) ,"Student with name"+name+"did not found");
}

--------------------------------------------------------------------------------------------------------------------------------

2: Test if these usernames are present in repository or not:

@ParameterizedTest
@CsvSource({
    "varun","arun","shiro"
})
public void nameTest(String name){
    assertNotNull(userRepository.findByUsername(name));
}

--------------------------------------------------------------------------------------------------------------------------------
