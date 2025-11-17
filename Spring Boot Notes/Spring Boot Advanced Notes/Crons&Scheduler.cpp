    --------------------------------------------------------------------------------------------------------------------------------------------
What is a Scheduler?
--------------------------------------------------------------------------------------------------------------------------------------------

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