--------------------------------------------------------------------------------------------------------------------------------
Junit 4 and Junit 5 Annotations:
--------------------------------------------------------------------------------------------------------------------------------

@Disabled               : Disables a test method or Class.

@Test                   : Marks a method as a test case.

@BeforeEach             : Runs before each test method (JUnit 5).

@AfterEach              : Runs after each test method

@BeforeAll              : Runs once before all tests (must be static).

@AfterAll               : Runs once after all tests (must be static).

@DisplayName            : Sets a custom readable name for a test.

@ParameterizedTest      : Marks a test that runs multiple times with different inputs.

@ValueSource            : Provides simple literal values (ints, strings, etc.).

@CsvSource              : Provides inline CSV values for multi-argument tests.

@CsvFileSource          : Loads CSV data from a file.

@Timeout                : Fails the test if it exceeds the given time limit.

--------------------------------------------------------------------------------------------------------------------------------

Database Testing Annotations:

In SpringBootTest, If you make changes in the DB, It will stay in the DB
In DataJpaTest, If you make changes in DB, it will get rollbacked after every test

In SpringBootTest, rollback does not happen, So If you want rollback you can use @Transactional annotation
In DataJpaTest, rollback happens automatically So If you want to persist the data you can use @Commit annotation

@Transactional:
Rolls back DB changes after the test completes.
Used when you want SpringBootTest to behave like DataJpaTest regarding rollback.

@Commit : 
Disables rollback and commits DB changes.
Useful for multi-step DB tests where next tests depend on persisted data.

@Sql : 
Executes SQL scripts before test execution.
Script may contain inserts, deletes, schema setup, etc.

--------------------------------------------------------------------------------------------------------------------------------

Parameterized Tests:
Tests that run the same logic with different inputs automatically. 

--------------------------------------------------------------------------------------------------------------------------------

1: Basic Value Injection (For simple values):

Ex:

@ParameterizedTest
@ValueSource(ints = {2,5,6,8,10})
public void isEven(int num){
    assertThat(num%2==0).isTrue();
}

@ParameterizedTest
@ValueSource(strings = {"","varun","arun"})
public void isEven(String s){
    assertThat(s).isNotBlank();
}

--------------------------------------------------------------------------------------------------------------------------------

2: CSV Inputs (For multiple parameters):

@ParameterizedTest
@CsvSource({"3,9", "4,16", "5,25"})
void testSquare(int input, int expected) {
    assertEquals(expected, input * input);
}

--------------------------------------------------------------------------------------------------------------------------------

3: From Files (For large datasets)

@ParameterizedTest
@CsvFileSource(resources = "/testdata.csv")
void testNumberWords(int num, String word) {
    assertEquals(word, convertToWord(num));
}

--------------------------------------------------------------------------------------------------------------------------------

Question:

Check if all the given names is present in the DB or not:

@ParameterizedTest
@ValueSource(strings = {"varun","nandni"})
public void checkUserNames(String name){
    List<Student> l1 = studentRepository.findAll();
    
    assertTrue(l1.stream()
    .anyMatch(student -> student.getName().equals(name))
    ,"Student with name"+name+"did not found");
}

--------------------------------------------------------------------------------------------------------------------------------

Test if these usernames are present in repository or not:

@ParameterizedTest
@CsvSource({
    "varun","arun","shiro"
})
public void nameTest(String name){
    assertNotNull(userRepository.findByUsername(name));
}

--------------------------------------------------------------------------------------------------------------------------------

Differnce between JUNIT4 and JUNIT5:

JUNIT4:
    Single Monolithic Library
    Uses @Before, @After, @BeforeClass, @AfterClass.
    Uses @Ignore to disable tests.tests
    Parameterized tests require external runners.

JUNIT5:
    Combination of Platform, Jupiter, and Vintage.
    Uses @BeforeEach, @AfterEach, @BeforeAll, @AfterAll.
    Uses @Disabled.
    Built in ParameterizedTest

--------------------------------------------------------------------------------------------------------------------------------







