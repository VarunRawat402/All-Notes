------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AOP:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Definition:
Spring AOP allows you to separate cross-cutting concerns from the main business logic.

Cross-cutting concerns = features needed across multiple modules (logging, security, transactions, performance monitoring, etc.).
Instead of writing the same code in every class, AOP lets you define these concerns once and apply them automatically wherever needed.

How AOP Works
    Write the common logic as an Aspect
    Define Pointcuts to specify where the aspect should run
    The AOP Weaver injects this behavior into the target methods at runtime

Types of AOP Tools:

1: Spring AOP:
Most commonly used
Works only on Spring Beans

2: AspectJ:
Fully featured AOP framework
Works on any Java class

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

@Configuration
@Aspect
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    // Applied before any method inside UserService
    @Before("execution(* com.example.Spring_AOP.Services.UserService.*(..))")
    public void logMethod() {
        logger.info("Method called...");
    }
}


-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AOP Terminology:

Compile-Time Concepts:

1: Advice: 
The code you want to execute (logging, authentication, validation, etc.).
logger.info("Method executing: {}", joinPoint);


2: PointCut:
An expression that defines where the advice should run.
Example: 
intercept all methods inside UserService:
@Before("execution(* com.example.Spring_AOP.Services.UserService.*(..))")


3: Aspect:
A combination of ( Advice + Pointcut ).

4: Weaver
The framework that applies the advice to matching pointcuts.
This process is called Weaving.

Runtime Concept:

1: JoinPoint:
Represents the specific method execution where the advice is applied.

From JoinPoint you can get:
    joinPoint.getSignature()
    joinPoint.getSignature().getName()
    joinPoint.getArgs()
    joinPoint.getTarget()

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Important Annotations:

@Before	: Runs before method execution   ( Logging, security checks )

@After: Runs after method execution (regardless of success/failure)	(Final cleanup, auditing)

@AfterReturning: Runs only if method returns successfully	(Capture return value)

@AfterThrowing: Runs if method throws exception	(Error logging / compensation logic)
Code For All the Annotations:

@Aspect
@Configuration
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    @Before("execution(* com.example.service.UserService.*(..))")
    public void logBefore(JoinPoint joinPoint) {
        logger.info("BEFORE: {}", joinPoint.getSignature().getName());
    }

    @After("execution(* com.example.service.UserService.*(..))")
    public void logAfter(JoinPoint joinPoint) {
        logger.info("AFTER: {}", joinPoint.getSignature().getName());
    }

    @AfterReturning(
        value = "execution(* com.example.service.UserService.getUserById(..))",
        returning = "result"
    )
    public void logAfterReturning(JoinPoint joinPoint, Object result) {
        logger.info("AFTER RETURNING: {} - Result: {}", joinPoint.getSignature().getName(), result);
    }

    @AfterThrowing(
        value = "execution(* com.example.service.UserService.*(..))",
        throwing = "ex"
    )
    public void logAfterThrowing(JoinPoint joinPoint, Throwable ex) {
        logger.error("AFTER THROWING: {} - Exception: {}", joinPoint.getSignature().getName(), ex.getMessage());
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Around Annotations:

Most powerful advice because it:
    Runs before and after the method
    Can modify arguments
    Can change return values
    Can handle exceptions
    Gives full control through ProceedingJoinPoint

Example 1: Log Execution Time

Code:
@Aspect
@Configuration
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    @Around("execution(* com.example.service.UserService.*(..))")
    public Object logExecutionTime(ProceedingJoinPoint joinPoint) throws Throwable {

        long start = System.currentTimeMillis();                    //Start the time
        logger.info("START: {}", joinPoint.getSignature().getName());
        Object result = joinPoint.proceed();                        //Execute the Method
        long end = System.currentTimeMillis();                      //End the time

        logger.info("END: {} - Time: {} ms", joinPoint.getSignature().getName(), end - start);      //Log the time taken

        return result;
    }
}


Example 2: Modify Return Value:
    We can access the result and modify it

@Around("execution(* com.example.service.UserService.getUserById(..))")
public Object modifyReturnValue(ProceedingJoinPoint joinPoint) throws Throwable {
    Object result = joinPoint.proceed();
    logger.info("Original result: {}", result);

    return "result*2";               // override original value
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Common Point Cut:
To avoid repeating long package paths in every aspect
Create and define pointcuts in one class.

How to Implement:
We Create a CommonPointCutClass:
We define PointCuts in this class
We use these PointCuts methods in the Aspect class by using their path

public class CommonPointCutClass {

    // Bean-level pointcut (any bean name containing 'Service')
    //IOC container will have all the beans like service so it will intercept all the methods of those beans
    @Pointcut("bean(*Service*)")
    public void serviceLayer() {}

    // Package-level pointcut ( all methods in Services package and sub-packages )
    @Pointcut("execution(* com.example.Spring_AOP.Services..*(..))")
    public void serviceLayer1() {}
}

Aspect Class:

@Aspect
@Configuration
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    @Before("com.example.Spring_AOP.CommonPointCutClass.serviceLayer1()")
    public void logBefore(JoinPoint joinPoint) {
        logger.info("BEFORE: {} - {}", joinPoint.getSignature().getName(), System.currentTimeMillis());
    }

    @AfterReturning(
        value = "com.example.Spring_AOP.CommonPointCutClass.serviceLayer1()",
        returning = "result"
    )
    public void logAfterReturning(JoinPoint joinPoint, Object result) {
        logger.info("AFTER: {}", result);
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Custom Annotation:
Till now we learned how to use PointCut on packages,Class and method
Lets say I want to use a PointCut on 10 different methods how can I do it.

1: Give 10 different paths:
    @Pointcut("execution(* Services.UserService.getUser(..)) || 
            execution(* Services.StudentService.getStudent(..)) || 
            execution(* Services.PaymentService.processPayment(..)) || 
            execution(* Services.AdminService.deleteUser(..))")
    public void specificMethods() {}

2: Use Naming Convention:
All the methods that start with loggable will get intercepted in Services package
But lets just say our methods dont have the same naming conventions
@Pointcut("execution(* Services..loggable*(..))")
public void loggableMethods() {}

3: Custom Annotations ( Most Imp )
We will make a custom annotation 
We will pass the path of the annotation in the PointCut
We will pass that PointCut path on the @Before @After methods with logic(Aspect)
We will use that annotation on methods we want to be intercepted

Annotation Class code:
    @Retention(RetentionPolicy.RUNTIME)
    @Target(ElementType.METHOD)
    public @interface Loggable {}

CommonPoint Class code:
    @Pointcut("@annotation(com.example.Spring_AOP.Loggable)")
    public void loggableMethods() {}

Aspect Class Code:
    @Before("com.example.Spring_AOP.CommonConfig.loggableMethods()")
    public void logStarting(){
        logger.info("Method is executed");
    }

Service class code:
    @Service
    public class UserService {
        @Loggable
        public void getUser() {}

        public void updateUser() {}  // Not logged
    }

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------