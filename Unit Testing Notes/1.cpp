--------------------------------------------------------------------------------------------------------------------------------
Unit Testing:
--------------------------------------------------------------------------------------------------------------------------------

Flow of Testing:
AAA Pattern ( Arrange Act Assert )

Multiple Verification level of Repository:

1: Check saved Operation ( saved or not ) ( null or not )
2: Verify Id Generation
3: Confirm Existance in Database by fetching the data
4: Check feild values are correct or not

--------------------------------------------------------------------------------------------------------------------------------

@SpringBootTest:

This annotation tells Spring Boot to start the full application context for the test.
It loads everything: configuration, beans, services, repositories, controllers, etc.

--------------------------------------------------------------------------------------------------------------------------------

@DataJpaTest:

This annotation is specialized for JPA tests.
It only loads: @Entity classes, Spring Data JPA repositories.
It does not load controllers, services, security, etc.
By default, it uses an in-memory database (H2)


@AutoConfigureTestDatabase:
Used with @DataJpaTest to control what database gets used.
By default, Spring uses inMemory H2 Database
With this annotation you can tell spring to use the configured DB

@DataJpaTest        //Uses Real DB
@AutoConfigureTestDatabase(replace = Replace.NONE)

@DataJpaTest        //Used TempH2
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