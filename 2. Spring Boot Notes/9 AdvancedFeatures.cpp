--------------------------------------------------------------------------------------------------------------------------------------------
Advanced Rest API Features:
--------------------------------------------------------------------------------------------------------------------------------------------

1: Content Negotiation ( REST API ):
    → Used to return response in different formats ( JSON, XML, etc ) based on client request.
    → Client specifies the desired format using the Accept header.

Accept: application/json
Accept: application/xml

How It Works in Spring Boot
    → Spring Boot supports JSON by default.
    → To support XML, you must add an XML message converter.

Spring automatically:
    → Reads Accept header
    → Chooses the correct converter (JSON/XML)
    → Serializes the response

Dependency (XML Support):
<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-xml</artifactId>
</dependency>

@GetMapping(value = "/user", produces = { "application/json", "application/xml" })
public User getUser() {
    return new User(1, "Varun");
}

--------------------------------------------------------------------------------------------------------------------------------------------

2: Spring Boot Actuator:

Actuator provides production-ready features to monitor and manage applications.
    → Health monitoring (DB up or down)
    → Metrics collection (memory, CPU, HTTP requests, GC)
    → Check logs and thread dumps (Debugging)
    → Integrate with monitoring tools (Prometheus, Grafana, ELK, etc.)

1: Add the Dependency:

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>

2: Expose the points:
    Application.properties:
    management.endpoints.web.exposure.include=*

Common Actuator endpoints:

/actuator/health    : Shows application health (up, down, details)
/actuator/info	    : Displays arbitrary info properties (from application.properties)
/actuator/env	    : Exposes environment properties
/actuator/metrics	: Lists available metrics (like jvm.memory.used, http.server.requests)
/actuator/beans	    : Displays all Spring Beans

How do you expose actuator endpoints securely:
    management.endpoints.web.exposure.include=health,metrics
    management.endpoint.health.show-details=when_authorized
    .authorizeHttpRequests()
    .requestMatchers("/actuator/**").hasRole("ADMIN")

--------------------------------------------------------------------------------------------------------------------------------------------

3: What is a Scheduler?
    → A scheduler allows you to run code automatically at fixed intervals or specific time.

Cron Expression:
    → A cron expression defines the exact time a scheduled job should run.

Spring uses 6 fields:
    → second, minute, hour, day-of-month, month, day-of-week
    → Example: 0 15 10 * * ? → Runs at 10:15 AM every day.

Enable Scheduling in Spring:

@EnableScheduling
@SpringBootApplication
public class MyApp {
}

--------------------------------------------------------------------------------------------------------------------------------------------
Examples:

Fixed Rate (every 5 seconds)

@Scheduled(fixedRate = 5000)
public void runTask() {
    System.out.println("Runs every 5 seconds");
}

Every day at 10:15 AM
@Scheduled(cron = "0 15 10 * * ?")
public void dailyTask() {
    System.out.println("Runs at 10:15 AM every day");
}

Every Sun at 9 AM:
@Scheduled(cron = "0 0 9 * * SUN")
public void dailyTask() {
    System.out.println("Runs at 9:00 AM every SUN");
}

--------------------------------------------------------------------------------------------------------------------------------------------

