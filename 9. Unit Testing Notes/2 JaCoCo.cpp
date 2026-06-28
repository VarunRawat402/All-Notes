--------------------------------------------------------------------------------------------------------------------------------
JaCOCO:
--------------------------------------------------------------------------------------------------------------------------------

What is Code Coverage:
    → It tells how much % of your code executed during tests

JaCoCo:
    → It is a tool to measure code coverage
    → Identify untested code
    → Improve test quality
    → Enforce minimum coverage in CI/CD pipelines → build fails if below threshold

Report location: target/site/jacoco/index.html

--------------------------------------------------------------------------------------------------------------------------------

How to fix low coverage (build fails):

1. Check JaCoCo HTML report
2. Find uncovered code
3. Write unit tests covering those lines + edge cases
4. Re-run build

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

'mvn clean test':
    → Deletes target/ → compiles → runs unit tests only
    → Use when: just want to run tests quickly

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean verify'
    → Deletes target/ → compiles → runs tests → packages JAR
    → runs integration tests + quality checks + coverage checks
    → Use when: CI/CD pipeline validation

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean install':
    → Same as verify + stores JAR in local Maven repo (~/.m2)
    → Other local projects can use it as dependency
    → Use when: building shared libraries or reusing locally

--------------------------------------------------------------------------------------------------------------------------------

'mvn clean spring-boot:run'
    → Deletes target/ → compiles → starts Spring Boot app directly
    → No tests run, no JAR created
    → Use when: quick local development run

--------------------------------------------------------------------------------------------------------------------------------