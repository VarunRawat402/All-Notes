--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

Implementation:

Add jacoco dependencies
Add jacoco plugin

--------------------------------------------------------------------------------------------------------------------------------

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

Counter	Measures:

LINE	% of executable lines covered (most common).
BRANCH	% of decision branches (e.g., if/else, switch) covered.
METHOD	% of methods executed.
CLASS	% of classes loaded during tests.

--------------------------------------------------------------------------------------------------------------------------------

mvn clean spring-boot:run

What it does:

Deletes the target folder.
Compiles your applications source code.
Starts the embedded web server (Tomcat, Jetty, or Undertow).
Runs your full Spring Boot application so you can interact with it, e.g., access http://localhost:8080.
The process keeps running until you manually stop it with Ctrl+C.

It typically does not run your unit tests (src/test/java) by default. Its primary job is to run the application.

--------------------------------------------------------------------------------------------------------------------------------

mvn clean test:

What it does:

Deletes the target folder.
Compiles your applications source code (src/main/java).
Compiles your test code (src/test/java).
Runs all the tests found in src/test/java.
Stops the process after running the tests. It does not package your application or run it.

You will see the test results in the console (pass/fail) and detailed reports (like from JaCoCo or Surefire) will be generated in the target directory.

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

--------------------------------------------------------------------------------------------------------------------------------