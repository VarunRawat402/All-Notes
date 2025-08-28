--------------------------------------------------------------------------------------------------------------------------------------------
What is a Scheduler?
--------------------------------------------------------------------------------------------------------------------------------------------

A scheduler allows you to run code at fixed times or intervals—like a cron job.

What is a Cron Expression?
A cron expression defines tine when a job should run

Enable Scheduling in Spring
    @EnableScheduling
    @SpringBootApplication
    public class MyApp { ... }

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