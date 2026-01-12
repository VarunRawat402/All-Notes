--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

JaCoCo (Java Code Coverage) is a tool used to measure how much of your Java code is executed during tests.

It helps you:
    Identify untested code
    Improve test quality
    Enforce minimum coverage in CI/CD pipelines

Implementation Steps:

Add JaCoCo Maven Plugin
Run tests using Maven
Generate coverage report
View HTML report from target/site/jacoco/index.html

--------------------------------------------------------------------------------------------------------------------------------
JaCoCo Maven Plugin Configuration

<plugin>
    <groupId>org.jacoco</groupId>
    <artifactId>jacoco-maven-plugin</artifactId>
    <version>0.8.11</version>
    <executions>

        <!-- Attach JaCoCo agent before tests -->
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

Coverage Counters (Metrics):

LINE	% of executable lines covered (most common).
BRANCH	% of decision branches (e.g., if/else, switch) covered.
METHOD	% of methods executed.
CLASS	% of classes loaded during tests.

--------------------------------------------------------------------------------------------------------------------------------

Maven Commands & Behavior:

'mvn clean spring-boot:run'

What it does:
    Deletes target/
    Compiles source code
    Starts Spring Boot application
    Runs embedded server (Tomcat/Jetty)
    Keeps application running

Important:
    ❌ Does NOT run unit tests
    ❌ Does NOT generate JaCoCo reports

Used only for local development

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean test'

What it does:
    Deletes target/
    Compiles main + test code
    Runs all unit tests (src/test/java)
    Stops after tests complete

Output:
    Console test results
    JaCoCo coverage report
    Surefire reports

Most common command for coverage

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean verify'

What it does:
    Runs clean
    Compiles code
    Executes unit tests
    Executes verify phase

Verify phase is used for:
    JaCoCo coverage validation
    Code quality checks (Checkstyle, PMD)
    Integration tests (if configured)

--------------------------------------------------------------------------------------------------------------------------------

Imp:
Learn exception testing using assertThrows() for more robust test cases.

--------------------------------------------------------------------------------------------------------------------------------