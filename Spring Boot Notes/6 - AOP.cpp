------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AOP:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AOP separates common logic from business logic.
    → Logging
    → Transactions
    → Auditing
    → Metrics

How AOP Works (Simple Flow)
    → Aspect    → Common code 
    → Pointcut  → path where it should run 
    → Spring AOP runs this automatically.

Types of AOP Tools:

1: Spring AOP:
    → Most commonly used
    → Works only on Spring Beans Class

2: AspectJ:
    → Fully featured AOP framework
    → Works on any Java class

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Basic AOP Example (Logging):
    → write Logs before every method of UserService

@Configuration
@Aspect
@Slf4j
public class LoggingAspect {

    @Before("execution(* com.example.service.UserService.*(..))")
    public void logMethod() {
        logger.info("Method called...");
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AOP Terminology:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Compile-Time Concepts:

1: Advice: 
    → The actual code you want to run
    → logger.info("Method executing");


2: PointCut:
    → Expression that decides where code runs
    → @Before("execution(* com.example.service.UserService.*(..))")

3: Aspect:
    → Combination of Advice + Pointcut

4: Weaver
    → The framework that applies the advice to matching pointcuts.
    → This process is called Weaving.

5: JoinPoint:
    → Gives us the metadata of the original method

From JoinPoint you can get:
    → joinPoint.getSignature().getName()
    → joinPoint.getArgs()
    → joinPoint.getTarget()

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Important AOP Annotations:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Before: 
    → Runs Before method  
    → (Logging, security)

@After: 
    → uns after method
    → (Cleanup)

@AfterReturning: 
    → Runs if method returns successfully	
    → (Capture result value)

@AfterThrowing: 
    → Runs if method throws exception	
    → (Error logging)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code For All the Annotations:

@Aspect
@Configuration
public class LoggingAspect {

    @Before("execution(* com.example.service.UserService.*(..))")
    public void logBefore(JoinPoint jp) {
        logger.info("BEFORE: {}", jp.getSignature().getName());
    }

    @After("execution(* com.example.service.UserService.*(..))")
    public void logAfter(JoinPoint jp) {
        logger.info("AFTER: {}", jp.getSignature().getName());
    }

    @AfterReturning(value = "execution(* com.example.service.UserService.getUserById(..))", returning = "result"
    )
    public void logAfterReturning(JoinPoint jp, Object result) {
        logger.info("RETURNED: {}", result);
    }

    @AfterThrowing(value = "execution(* com.example.service.UserService.*(..))", throwing = "ex"
    )
    public void logAfterThrowing(JoinPoint jp, Throwable ex) {
        logger.error("EXCEPTION: {}", ex.getMessage());
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Around Annotations ( @Around ):

Most powerful advice because it:
    → Runs before and after
    → Can modify arguments
    → Can change return value
    → Can handle exceptions

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example 1 : Calculate Execution Time:

Code:
@Around("execution(* com.example.service.UserService.*(..))")
public Object logExecutionTime(ProceedingJoinPoint jp) throws Throwable {

    long start = System.currentTimeMillis();            //start time
    Object result = jp.proceed();                       //execute method
    long end = System.currentTimeMillis();              //end time

    logger.info("{} took {} ms",
            jp.getSignature().getName(),
            end - start);

    return result;
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example 2: Modify Return Value:
    → We can access the result and modify it
    → value return here, will return by the actual method

@Around("execution(* com.example.service.UserService.getUserById(..))")
public Object modifyReturnValue(ProceedingJoinPoint joinPoint) throws Throwable {

    Object result = joinPoint.proceed();
    return result*10;                               //Modified result value
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Custom Annotation:
    → You want AOP on selected methods only, not entire package or Entire Service

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 1: Create Annotation:

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface Loggable {}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 2: Pointcut Using Annotation:

@Pointcut("@annotation(com.example.Loggable)")
public void loggableMethods() {}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 3: Aspect Logic:

public class LoggingAspect {

    @Before("com.example.CommonPointCutClass.loggableMethods()")
    public void logStarting() {
        //
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 4: Use Annotation:

@Service
public class UserService {

    @Loggable
    public void getUser() {}

    public void updateUser() {}         // Not logged
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------