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

SpringBootTest:

It is used to load the spring application context, Without it no bean will be Initialized and no server will be started
Tests the ENTIRE application

--------------------------------------------------------------------------------------------------------------------------------

DataJpaTest:

It is same as @SpringBootTest but it is used to test the Jpa Repository without loading the entire application context
Tests ONLY JPA components
Uses embedded DB (H2 by default)	

Annotation:

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