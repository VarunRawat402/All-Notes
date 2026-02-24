--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

What is Code Coverage:
    It tells how much % of your code executed during tests

JaCoCo:
    It is a tool to measure code coverage

It helps you:
    → Identify untested code
    → Improve test quality
    → Enforce minimum coverage in CI/CD pipelines

--------------------------------------------------------------------------------------------------------------------------------

How do you improve code coverage when build fails due to low coverage:
    
1: Check Coverage report
2: Find uncovered code
3: Write unit tests for that code with edge cases
4: Re-run build

--------------------------------------------------------------------------------------------------------------------------------

What is Maven Build:

It is a process where maven
    → Reads pom.xml
    → Download Dependencies
    → Compiles Code
    → Run unit tests
    → Package application into JAR
    → Stores in target/

--------------------------------------------------------------------------------------------------------------------------------

Implementation Steps:

→ Add JaCoCo Maven Plugin
→ Run tests using Maven
→ Generate coverage report
→ View HTML report from target/site/jacoco/index.html

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

Line Coverage    : % of executable lines covered (most common).
Branch Coverage  : % of decision branches (e.g., if/else, switch) covered.
Method Coverage  : % of methods executed.
Class Coverage   : % of classes loaded during tests.

--------------------------------------------------------------------------------------------------------------------------------

Maven Lifecycle:
    validate → compile → test → package → verify → install → deploy

clean → Deletes old build and target/ files

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean test'
    → Deletes target/
    → Compiles code
    → Runs unit tests (src/test/java)

Output:
    → Console test results
    → JaCoCo coverage report
    → Surefire reports

You only want to run tests quickly

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean verify'
    → Deletes target/
    → Compiles code
    → Runs unit tests
    → package the application into JAR
    → runs additional checks (integration tests, quality plugins, coverage checks)

Use when:
→ CI pipeline validation
→ need full build checks before install

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean install':
    → Deletes target/
    → Compiles code
    → Run unit test
    → package the application into JAR
    → runs additional checks (integration tests, quality plugins, coverage checks)
    → stores it in local repo

Why install matters:
    → other local projects can use this artifact as dependency

Use when:
→ Use shared libraries
→ dependency reuse locally

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean spring-boot:run'
    → Deletes target/
    → Compiles code
    → starts the Spring Boot app

Use when:
→ local development
→ No unit test runs
→ quick app run without building jar

--------------------------------------------------------------------------------------------------------------------------------