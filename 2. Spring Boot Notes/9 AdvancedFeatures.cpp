-----------------------------------------------------------------------------------------------------------------------------------------------------
Advanced Rest API Features:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Spring Boot Actuator:
    → Provides production-ready endpoints to monitor and manage your app
    → Use cases: health checks, metrics, logs, thread dumps, DB status

Setup:
    1. Add dependency: spring-boot-starter-actuator
    2. management.endpoints.web.exposure.include=*   // expose all endpoints

-----------------------------------------------------------------------------------------------------------------------------------------------------

Common Endpoints:
    /actuator/health    → app health status (UP/DOWN, DB status)
    /actuator/info      → app info (from application.properties)
    /actuator/env       → environment properties
    /actuator/metrics   → JVM memory, CPU, HTTP requests, GC stats
    /actuator/beans     → all Spring beans loaded

-----------------------------------------------------------------------------------------------------------------------------------------------------

Secure Actuator Endpoints (Production):

→ Expose only what you need:
    management.endpoints.web.exposure.include=health,metrics
    management.endpoint.health.show-details=when_authorized

→ Restrict access to ADMIN only:
    .requestMatchers("/actuator/**").hasRole("ADMIN")

⚠️ Never expose all endpoints (*) in production
   → /actuator/env exposes secrets, /actuator/beans exposes internals

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: SCHEDULER:
    → Runs code automatically at fixed intervals or specific times
    → Enable with @EnableScheduling annotation on main class
    → @EnableScheduling must be on main class, else @Scheduled won't work

Cron Expression (6 fields):

second  minute  hour  day-of-month  month  day-of-week
    0      15     10       *           *        ?
→ Runs at 10:15 AM every day

-----------------------------------------------------------------------------------------------------------------------------------------------------

Every day at 10:15 AM:
    @Scheduled(cron = "0 15 10 * * ?")
    public void dailyTask() { }

Every Sunday at 9 AM:
    @Scheduled(cron = "0 0 9 * * SUN")
    public void weeklyTask() { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

fixedRate:
    → use when: task must run on strict schedule regardless of execution time
    runs at: 0s, 5s, 10s, 15s → doesnt care how long method took
    ex: fetch live stock prices every 5s

Ex:
    @Scheduled(fixedRate = 5000)
    public void task() { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

fixedDelay:
    → use when: next run should wait for current to finish
    → ex: DB cleanup → dont start new cleanup before old one finishes
    → runs at: 0s, 8s, 16s → waits 5s AFTER method finishes

Ex:
    @Scheduled(fixedDelay = 5000)
    public void task() { }

-----------------------------------------------------------------------------------------------------------------------------------------------------