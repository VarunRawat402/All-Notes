--------------------------------------------------------------------------------------------------------------------------------
Unit Testing:
--------------------------------------------------------------------------------------------------------------------------------

AAA Pattern:

Arrange → set up data, mocks, environment
Act     → call the method being tested
Assert  → verify the result is correct

--------------------------------------------------------------------------------------------------------------------------------

Repository Testing Steps:

1. Save entity → verify returned object is not null
2. Check auto-generated ID is not null
3. Fetch using findById() or findAll() → confirm it exists
4. Compare stored field values with expected values

--------------------------------------------------------------------------------------------------------------------------------

@SpringBootTest:
    → Loads ENTIRE Spring context
    → (controllers, services, repos, security, config)
    → Used for integration testing.
    → Slower → everything loads

--------------------------------------------------------------------------------------------------------------------------------

@DataJpaTest:
    → Loads JPA layer only (@Entity + repositories)
    → Does NOT load services, controllers, security
    → Uses in-memory H2 database by default
    → Faster → only whats needed

--------------------------------------------------------------------------------------------------------------------------------

@AutoConfigureTestDatabase:
    → Controls which database is used in @DataJpaTest.

@DataJpaTest        //Use Real DB
@AutoConfigureTestDatabase(replace = Replace.NONE)

@DataJpaTest        //Use H2
@AutoConfigureTestDatabase(connection = EmbeddedDatabaseConnection.H2)

--------------------------------------------------------------------------------------------------------------------------------

Basic Comparisons:

1: assertEquals(expected, actual)          // values are equal
2: assertNotEquals(unexpected, actual)     // values are not equal
3: assertSame(obj1, obj2)                  // same object reference
4: assertNotSame(obj1, obj2)               // different object reference

--------------------------------------------------------------------------------------------------------------------------------

Boolean + Null Checks:

1: assertTrue(condition)
2: assertFalse(condition)
3: assertNull(actual)
4: assertNotNull(actual)

--------------------------------------------------------------------------------------------------------------------------------

Collections & Iterables

1: assertIterableEquals(expected, actual)          // same elements same order
2: assertLinesMatch(expectedLines, actualLines)

--------------------------------------------------------------------------------------------------------------------------------

Exception Testing:

1: assertThrows(ExpectedException.class, () -> method());

// capture exception and verify message
2: Exception ex = assertThrows(IllegalArgumentException.class,() -> service.method(null));
   assertEquals("Parameter cannot be null", ex.getMessage());

--------------------------------------------------------------------------------------------------------------------------------