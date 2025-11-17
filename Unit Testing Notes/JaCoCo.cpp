--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

Implementation:

Add JaCoCo dependency
Add JaCoCo Maven plugin

--------------------------------------------------------------------------------------------------------------------------------

PLUGIN:

<plugin>
    <groupId>org.jacoco</groupId>
    <artifactId>jacoco-maven-plugin</artifactId>
    <version>0.8.11</version> <!-- Latest version recommended -->
    <executions>
        
        <!-- Attach JaCoCo agent before tests run -->
        <execution>
            <id>prepare-agent</id>
            <goals>
                <goal>prepare-agent</goal>
            </goals>
        </execution>

        <!-- Generate coverage report after tests -->
        <execution>
            <id>generate-report</id>
            <phase>test</phase>
            <goals>
                <goal>report</goal>
            </goals>
        </execution>

    </executions>
</plugin>

--------------------------------------------------------------------------------------------------------------------------------

Counter	Measures:

LINE	% of executable lines covered (most common).
BRANCH	% of decision branches (e.g., if/else, switch) covered.
METHOD	% of methods executed.
CLASS	% of classes loaded during tests.

--------------------------------------------------------------------------------------------------------------------------------

`mvn clean spring-boot:run`

What it does:

Deletes target/
Compiles source code
Starts the Spring Boot application (embedded Tomcat/Jetty/Undertow)
Runs the app and keeps it alive until you stop it (Ctrl + C)

It does not run unit tests
Only runs the application for development purposes

--------------------------------------------------------------------------------------------------------------------------------

`mvn clean test`

What it does:

Deletes target/
Compiles main and test source code
Executes all unit tests in src/test/java
Stops once testing is complete

Console test results (pass/fail)
Coverage reports (JaCoCo)
Surefire reports

--------------------------------------------------------------------------------------------------------------------------------

`mvn clean verify`

Runs clean, compiles, tests, and then runs the verify phase.

The verify phase is typically used to:
Generating coverage reports (JaCoCo)
Code quality checks (Checkstyle, PMD)
Running integration tests (if configured)

--------------------------------------------------------------------------------------------------------------------------------

Imp:
Learn exception testing using assertThrows() for more robust test cases.

--------------------------------------------------------------------------------------------------------------------------------