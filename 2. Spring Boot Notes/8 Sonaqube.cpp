-----------------------------------------------------------------------------------------------------------------------------------------------------
SONARQUBE:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. SonarLint:
    → IDE plugin to check issues while coding
    → Issues like: bugs, code smells, security hotspots.
    → No server required.
    → Can connect to sonarqube or sonarcloud for shared rules

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. SonarQube:
    → Installed on your own server.
    → Supports PR analysis, Quality Gates, historical trends.
    → Integrates with Jenkins, GitHub Actions, GitLab CI, etc.
    → IP Server : localhost:9000

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. SonarCloud:
    → Cloud-hosted SonarQube
    → No installation server or maintenance.
    → Tight integration with GitHub, GitLab, Bitbucket.
    → Free for public repositories, paid for private repositories.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Type of issues:

1: Bugs:
    → Logical errors that may cause runtime failures
    → Example: NullPointer risk, wrong conditions

2: Vulnerabilities
    → Security-related issues
    → Example: SQL injection, hardcoded credentials

3: Code Smells
    → Maintainability issues
    → Example: long methods, duplicated logic, unused variables

4: Code Coverage
    → Percentage of code covered by tests

5:Duplications
    → Duplicate blocks of code across files
    Shows:
        → Percentage duplicated
        → Exact duplicated lines

-----------------------------------------------------------------------------------------------------------------------------------------------------