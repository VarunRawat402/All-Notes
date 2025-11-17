--------------------------------------------------------------------------------------------------------------------------------
Unit Testing:
--------------------------------------------------------------------------------------------------------------------------------

Flow of Testing (AAA Pattern):

Arrange → Set up data, mocks, and environment
Act → Execute the logic or method being tested
Assert → Verify expected results

--------------------------------------------------------------------------------------------------------------------------------

Repository Verification Steps:

1: Check Save Operation
    Ensure the entity is saved (not null).

2: Verify ID Generation
    Confirm ID is generated automatically (if applicable).

3: Confirm Existence in Database
    Fetch the saved record and ensure it exists.

4: Validate Field Values
    Check whether stored values match expected values.

--------------------------------------------------------------------------------------------------------------------------------

@SpringBootTest:

Starts the full Spring Boot application context during testing.
Loads everything: configuration, beans, services, repositories, controllers, etc.
Used for integration testing.

--------------------------------------------------------------------------------------------------------------------------------

@DataJpaTest:

This annotation is used for JPA tests.
It only loads: @Entity classes, JPA repositories.
Does not load services, controllers, security, etc.
Uses in-memory H2 database by default.


@AutoConfigureTestDatabase:
Controls which database is used in @DataJpaTest.
Without configuration → defaults to H2

Use real configured DB:

@DataJpaTest        //Use Real DB
@AutoConfigureTestDatabase(replace = Replace.NONE)

@DataJpaTest        //Use TempH2
@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)

--------------------------------------------------------------------------------------------------------------------------------

Junit5 Assertions:

Basic Comparisons:

assertEquals(expected, actual);
assertNotEquals(unexpected, actual);
assertSame(expectedObject, actualObject);
assertNotSame(unexpectedObject, actualObject);

--------------------------------------------------------------------------------------------------------------------------------

Boolean Conditions:

assertTrue(condition);
assertFalse(condition);
assertNull(actual);
assertNotNull(actual);

--------------------------------------------------------------------------------------------------------------------------------

Collections/Iterables:

assertIterableEquals(expectedIterable, actualIterable);
assertLinesMatch(expectedLines, actualLines);

--------------------------------------------------------------------------------------------------------------------------------

Advanced:

assertThrows(ExpectedException.class, () -> method());
assertTimeout(Duration.ofSeconds(2), () -> operation());
assertAll("group", 
    () -> assertEquals(1, x),
    () -> assertEquals(2, y)
);

--------------------------------------------------------------------------------------------------------------------------------

Exception Testing:
// Clear exception assertion
Exception e = assertThrows(NullPointerException.class, 
    () -> obj.method(null));
assertEquals("Parameter cannot be null", e.getMessage());

--------------------------------------------------------------------------------------------------------------------------------