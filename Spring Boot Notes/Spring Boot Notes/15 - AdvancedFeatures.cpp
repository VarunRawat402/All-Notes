--------------------------------------------------------------------------------------------------------------------------------------------
Advanced Rest API Features:
--------------------------------------------------------------------------------------------------------------------------------------------

1: Content Negotiation ( REST API ):
    Content Negotiation allows a Spring Boot REST API to return responses in different formats (JSON, XML, etc.) depending on what the client asks for.

// Spring Boot (with the proper dependency) will automatically convert the response to XML.
If the client sends:
    Accept: application/xml

// Spring Boot already supports JSON by default. Adding this dependency adds XML support.
<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-xml</artifactId>
</dependency>


--------------------------------------------------------------------------------------------------------------------------------------------

2: Internationalization (i18n):
    Internationalization (i18n) allows your API to return messages in different languages based on the clients locale.

Client sends a language preference using:
    Accept-Language: en, fr, nl

Steps:
1: Create messages.properties file for different Languages ( path : src/main/resources):
   
// Spring Boot automatically picks the file based on the locale.
Ex:
    messages.properties : 
        goodMorning.message=Good Morning
    messages_fr.properties : 
        goodMorning.message=Bonjour!

2. Use MessageSource in the Controller:
    LocaleContextHolder fetches the locale from the request header.

Code:
    @Autowired
    MessageSource messageSource;

    @GetMapping("/hello")
    public String helloWorldIn18(){
        Locale locale = LocaleContextHolder.getLocale();
        return messageSource.getMessage("goodMorning.message",null,"Default Message",locale);
    }

--------------------------------------------------------------------------------------------------------------------------------------------

3: Spring Boot Actuator:

It provides production-ready features to monitor and manage your application.
It exposes built-in endpoints that give insights into your apps health, metrics, environment, and more.
Monitor Application health (DB up or down)
Gather metrics (memory, CPU, HTTP requests, GC)
Check logs and thread dumps
Integrate with monitoring tools (Prometheus, Grafana, ELK, etc.)

1: Add the Dependency:

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>

2: Expose the points:
    Application.properties:
    management.endpoints.web.exposure.include=*

--------------------------------------------------------------------------------------------------------------------------------------------
4: What is a Scheduler?

A scheduler allows you to run code automatically at fixed intervals or specific times.
This works like cron jobs in Linux but inside a Spring Boot application.

Cron Expression:
A cron expression defines the exact time a scheduled job should run.

Spring uses 6 fields:
    - second minute hour day-of-month month day-of-week
    - Example: 0 15 10 * * ? → Runs at 10:15 AM every day.

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


