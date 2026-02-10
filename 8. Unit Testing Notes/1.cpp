--------------------------------------------------------------------------------------------------------------------------------
Unit Testing:
--------------------------------------------------------------------------------------------------------------------------------

Flow of Testing:
    AAA = Arrange → Act → Assert

Arrange     → Set up data, mocks, and environment
Act         → Write tests 
Assert      → Verify tests

--------------------------------------------------------------------------------------------------------------------------------

Repository Testing - Steps:

1: Check Save Operation
    → Ensure save() returns a non-null entity.

2: Verify ID Generation
    → Verify auto-generated ID is not null.

3: Confirm Existence in Database
    → Fetch the entity using findById() or findAll().

4: Validate Field Values
    → Compare stored values with expected values.

--------------------------------------------------------------------------------------------------------------------------------

@SpringBootTest:

→ Starts the entire Spring Boot application context
Loads:
    → Controllers
    → Services
    → Repositories
    → Security
    → Configuration
→ Used for integration testing.

--------------------------------------------------------------------------------------------------------------------------------

@DataJpaTest:

→ Used for JPA layer testing only
Loads:
    → @Entity
    → JPA repositories
→ Does not load services, controllers, security, etc.
→ Uses in-memory H2 database by default.

--------------------------------------------------------------------------------------------------------------------------------

@AutoConfigureTestDatabase:
    → Controls which database is used in @DataJpaTest.

Use real configured DB:

@DataJpaTest        //Use Real DB
@AutoConfigureTestDatabase(replace = Replace.NONE)

@DataJpaTest        //Use H2
@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)

--------------------------------------------------------------------------------------------------------------------------------

Basic Comparisons:

assertEquals(expected, actual);
assertNotEquals(unexpected, actual);

assertSame(expectedObject, actualObject);
assertNotSame(unexpectedObject, actualObject);

--------------------------------------------------------------------------------------------------------------------------------

Boolean & Null Checks   

assertTrue(condition);
assertFalse(condition);

assertNull(actual);
assertNotNull(actual);

--------------------------------------------------------------------------------------------------------------------------------

Collections & Iterables

assertIterableEquals(expectedIterable, actualIterable);
assertLinesMatch(expectedLines, actualLines);

--------------------------------------------------------------------------------------------------------------------------------

Exception Testing (Preferred Way):

assertThrows(ExpectedException.class, () -> method());

Capture Exception & Verify Message:

Exception ex = assertThrows(IllegalArgumentException.class,
    () -> service.method(null)
);

assertEquals("Parameter cannot be null", ex.getMessage());

--------------------------------------------------------------------------------------------------------------------------------