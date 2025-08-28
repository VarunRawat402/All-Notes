--------------------------------------------------------------------------------------------------------------------------------
Junit 4 and Junit 5 Annotations:
--------------------------------------------------------------------------------------------------------------------------------

@Disabled : This is used to disable the test 

@Test : Marks a method as a test case

@BeforeEach : Runs before each test method

@AfterEach : Runs after each test method

@BeforeAll : Runs once before all tests (static method)

@AfterAll :	Runs once after all tests (static method)

@DisplayName : Custom test name for reports

--------------------------------------------------------------------------------------------------------------------------------

Database Testing Annotations:

@Transactional : This is used to roll back all the DB changes after each test
Ex: If test1 changes something in DB then test2 might give weird failures

@Commit : Commits DB changes (disable rollback)
Normally, After every test Spring rolls back database change. @Commit disables this rollback.

@Sql : Executes SQL scripts before test
Create a SQL script with sql queries
This annotation will run that script before every test

@AutoConfigureTestDatabase : Control Which Database to Use

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