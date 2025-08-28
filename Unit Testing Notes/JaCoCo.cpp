--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

To use this we need to add plugin in the pom.xml

PLUGIN:

<plugin>
    <groupId>org.jacoco</groupId>
    <artifactId>jacoco-maven-plugin</artifactId>
    <version>0.8.11</version> <!-- Use latest version -->
    <executions>
        <!-- Ensures JaCoCo runs during the test phase -->
        <execution>
            <id>prepare-agent</id>
            <goals>
                <goal>prepare-agent</goal>
            </goals>
        </execution>
        <!-- Generates the report after tests run -->
        <execution>
            <id>generate-report</id>
            <phase>test</phase> <!-- Runs after 'test' phase -->
            <goals>
                <goal>report</goal>
            </goals>
        </execution>
    </executions>
</plugin>

--------------------------------------------------------------------------------------------------------------------------------

Other JaCoCo Counters

You can also use these metrics:

Counter	Measures
LINE	% of executable lines covered (most common).
BRANCH	% of decision branches (e.g., if/else, switch) covered.
METHOD	% of methods executed.
CLASS	% of classes loaded during tests.

--------------------------------------------------------------------------------------------------------------------------------

mvn clean spring-boot:run

Compiles the code
Starts the Spring Boot application
You dont need to manually run the main() method — Spring Boot handles it

--------------------------------------------------------------------------------------------------------------------------------

mvn clean test

Compiles both:

src/main/java (your main app code)
src/test/java (your test classes)

Runs all tests using the maven-surefire-plugin.
Does not create a .jar or run the app — its focused purely on testing.
Just compile and test the code, without packaging it.

--------------------------------------------------------------------------------------------------------------------------------

mvn clean verify

Runs clean, compiles, tests, and then runs the verify phase.

The verify phase is typically used to:
Generate test coverage reports like JaCoCo
Validate code quality rules (e.g., PMD, Checkstyle)
Run integration tests (if configured)

--------------------------------------------------------------------------------------------------------------------------------

Imp:
Learn testing exceptions and errors using assertThrows