--------------------------------------------------------------------------------------------------------------------------------
Junit 4 and Junit 5 Annotations:
--------------------------------------------------------------------------------------------------------------------------------

@Disabled               : This is used to disable the test 

@Test                   : Marks a method as a test case

@BeforeEach             : Runs before each test method

@AfterEach              : Runs after each test method

@BeforeAll              : Runs once before all tests (static method)

@AfterAll               : Runs once after all tests (static method)

@DisplayName            : Custom test name for reports

@ParameterizedTest      : Marks a test as parameterized.

@ValueSource            : Provides literal values (ints, strings, etc.)

@CsvSource              : Provides inline CSV values.

@CsvFileSource          : Provides CSV data from a file.

@Timeout                : Fails a test if takes longer than given time

--------------------------------------------------------------------------------------------------------------------------------

Database Testing Annotations:

In SpringBootTest, If you make changes in the DB, It will stay in the DB
In DataJpaTest, If you make changes in DB, it will get rollbacked after every test

In SpringBootTest, rollback does not happen, So If you want rollback you can use @Transactional annotation
In DataJpaTest, rollback happens automatically So If you want to persist the data you can use @Commit annotation

@Transactional:
This is used to rollback all the changes from the DB which are done in the tests
So, other tests dont get affected by changed data

@Commit : Commits DB changes (disable rollback)
It is used to persist the changes in the DB for multi test scenarios

@Sql : Executes SQL scripts before test
Create a SQL script with sql queries
This annotation will run that script before every test

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
    Before, After,  BeforeClasss, AfterClass
    Ignore to disable tests
    External Runner ( for parameterzied tests )

JUNIT5:
    Composed of 3 things, Platform, Jupitor, Vintage
    BeforeEach, AfterEach,  BeforeAll, AfterAll
    Disabled
    Built in ParameterizedTest

--------------------------------------------------------------------------------------------------------------------------------







