-----------------------------------------------------------------------------------------------------------------------------------------------------
AOP (Aspect Oriented Programming):
-----------------------------------------------------------------------------------------------------------------------------------------------------

AOP:
    → Separates common/repeated logic from service logic
    → Write once → apply everywhere automatically
    → Ex: Logging, Transactions, Auditing, Metrics

-----------------------------------------------------------------------------------------------------------------------------------------------------
AOP Terminology:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Advice:
    → The actual code you want to run
    → ex: logger.info("Method executing");

Pointcut:
    → Expression that decides WHERE advice runs
    → ex: @Before("execution(* com.example.service.UserService.*(..))")
    → runs before ALL methods in UserService

Aspect:
    → Advice + Pointcut combined in one class
    → @Aspect annotation marks it

JoinPoint:
    → Metadata of the method being intercepted
    → joinPoint.getSignature().getName() → method name
    → joinPoint.getArgs()                → method arguments
    → joinPoint.getTarget()              → class it belongs to

-----------------------------------------------------------------------------------------------------------------------------------------------------
Important AOP Annotations:
-----------------------------------------------------------------------------------------------------------------------------------------------------

@Before         → runs BEFORE method          → use for: logging, security checks
@After          → runs AFTER method           → use for: cleanup (runs always)
@AfterReturning → runs if method SUCCEEDS     → use for: capture/log return value
@AfterThrowing  → runs if method THROWS       → use for: error logging

Code Example:

@Aspect
@Configuration
@Slf4j
public class LoggingAspect {

    @Before("execution(* com.example.service.UserService.*(..))")
    public void logBefore(JoinPoint jp) {
        log.info("BEFORE: {}", jp.getSignature().getName());
    }

    @After("execution(* com.example.service.UserService.*(..))")
    public void logAfter(JoinPoint jp) {
        log.info("AFTER: {}", jp.getSignature().getName());
    }

    @AfterReturning(
        value = "execution(* com.example.service.UserService.getUserById(..))",
        returning = "result")
    public void logAfterReturning(JoinPoint jp, Object result) {
        log.info("RETURNED: {}", result);
    }

    @AfterThrowing(
        value = "execution(* com.example.service.UserService.*(..))",
        throwing = "ex")
    public void logAfterThrowing(JoinPoint jp, Throwable ex) {
        log.error("EXCEPTION: {}", ex.getMessage());
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

@Around annotation:
    → Most powerful advice → wraps entire method execution
    → Use: run before + after, modify args, change return value, handle exceptions
    → Must call jp.proceed() → actually executes the real method
    → Whatever you return here → thats what caller gets
    → jp.proceed() not called → real method never executes

-----------------------------------------------------------------------------------------------------------------------------------------------------

Example 1: Calculate Execution Time:

@Around("execution(* com.example.service.UserService.*(..))")
public Object logExecutionTime(ProceedingJoinPoint jp) throws Throwable {
    long start = System.currentTimeMillis();
    Object result = jp.proceed();               // execute real method
    long end = System.currentTimeMillis();
    log.info("{} took {} ms", jp.getSignature().getName(), end - start);
    return result;                              // return original result
}

Example 2: Modify Return Value:

@Around("execution(* com.example.service.UserService.getUserById(..))")
public Object modifyReturnValue(ProceedingJoinPoint jp) throws Throwable {
    Object result = jp.proceed();               // execute real method
    return result * 10;                         // return modified result
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Common Pointcuts (Avoid Repetition):
    → To avoid repeating long package paths in every aspect
    → Create and define pointcuts in one class.

public class CommonPointCutClass {

    // All methods in User-Service class
    @Pointcut("execution(* com.example.service.UserService.*(..))")
    public void serviceLayer1() {}
}

public class LoggingAspect {

    @Before("com.example.Spring_AOP.CommonPointCutClass.serviceLayer1()")
    public void logBefore(JoinPoint joinPoint) {
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Custom Annotation:
    → You want AOP on selected methods only, not entire package or Entire Service

-----------------------------------------------------------------------------------------------------------------------------------------------------

Step 1: Create Annotation:

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface Loggable {}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Step 2: Pointcut Using Annotation:

@Pointcut("@annotation(com.example.Loggable)")
public void loggableMethods() {}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Step 3: Aspect Logic:

public class LoggingAspect {

    @Before("com.example.CommonPointCutClass.loggableMethods()")
    public void logStarting() {
        //
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Step 4: Use Annotation:

@Service
public class UserService {

    @Loggable
    public void getUser() {}

    public void updateUser() {}         // Not logged
}

-----------------------------------------------------------------------------------------------------------------------------------------------------