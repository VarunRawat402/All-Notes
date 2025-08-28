------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AOP:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Definition:
Spring AOP (Aspect-Oriented Programming) allows you to separate cross-cutting concerns/Common features from the main business logic.

Why Use AOP?
Some functionalities like logging, security, transaction management, performance,etc are needed across multiple modules in an application.
Instead of writing duplicate code in every class, AOP allows us to define them separately and apply them dynamically where needed.

How to Apply:
1: Implement the common features as an Aspect
2: Define point cuts to indicate where the aspect should be applied

Tools:

1: Spring AOP:
Not a complete AOP but very popular
Only works with spring beans

2: AspectJ:
Not that populare very less used
Can work on any java class

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

//We made a logMethod which logs something and used @Before which takes the service class path
Aspect Class:

@Configuration
@Aspect
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());
    //This will log before any method inside UserService executes.
    //com.example.Spring_AOP.Services.UserService.getUserById --> This will run on getUserById method only
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AOP Terminology:

Compile Time:

1: Advice: 
What code to execute ( logging, Authenticaion )
    logger.info("Method is Executing..................{}",joinPoint);

2: PointCut:
Expression that identifies methods that needs to be intercepted
All the Service class methods needs to be intercepted
    @Before("execution(* com.example.Spring_AOP.Services.UserService.*(..))")

3: Aspect:
Combination of Advice ( code ) and PointCut ( when to intercept) is called Aspect

4: Weaver
    Its the Framework which Implements AOP
    Its weaver job to execute the advice at pointcuts
    The whole process is called weaving

RunTime:

1: JoinPoint:
When pointcut is true and advice is executed, A specific instance of advice is called joinPoint.
JoinPoint helps get method details inside an aspect.
You can get :
    joinPoint.getSignature()
    joinPoint.getSignature().getName()
    joinPoint.getTarget()
    joinPoint.getArgs()

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Important Annotations:

@Before	: Before method execution   ( Logging, security checks )

@After: After method execution (regardless of success/failure)	( Cleanup, auditing) 

@AfterReturning: After method returns successfully	( Logging return value, caching results )

@AfterThrowing: If method throws an exception	( Error logging, rollback )

Code For All the Annotations:

@Aspect
@Configuration
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());+

    @Before("execution(* com.example.service.UserService.*(..))")
    public void logBefore(JoinPoint joinPoint) {
        logger.info("BEFORE execution: {}", joinPoint.getSignature().getName());
    }

    @After("execution(* com.example.service.UserService.*(..))")
    public void logAfter(JoinPoint joinPoint) {
        logger.info("AFTER execution: {}", joinPoint.getSignature().getName());
    }

    //Use the result and print it
    @AfterReturning(value = "execution(* com.example.service.UserService.getUserById(..))", returning = "result")
    public void logAfterReturning(JoinPoint joinPoint, Object result) {
        logger.info("AFTER RETURNING: {} - Result: {}", joinPoint.getSignature().getName(), result);
    }

    @AfterThrowing(value = "execution(* com.example.service.UserService.*(..))", throwing = "ex")
    public void logAfterThrowing(JoinPoint joinPoint, Throwable ex) {
        logger.error("AFTER THROWING: {} - Exception: {}", joinPoint.getSignature().getName(), ex.getMessage());
    }
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Around Annotations:

This is the most powerful type of advice in Spring AOP. It allows you to:
Execute before and after a method call.
Modify the methods arguments and return value.
Handle exceptions and apply additional behavior.
You can control when to execute the method

Ex 1:
Log Execution Time:
//UserService class gets called then @Around aspect will intercept
//I will log the info and do anything before calling the method
//I will call the method now
//I can log anything and modify result after executing the method

Code:
@Aspect
@Configuration
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    @Around("execution(* com.example.service.UserService.*(..))")
    public Object logExecutionTime(ProceedingJoinPoint joinPoint) throws Throwable {
        long start = System.currentTimeMillis();
        
        logger.info("START: {}", joinPoint.getSignature().getName());
        
        Object result = joinPoint.proceed();  // Execute the actual method
        
        long end = System.currentTimeMillis();
        logger.info("END: {} - Execution Time: {} ms", joinPoint.getSignature().getName(), (end - start));
        
        return result;  // Return the actual method result
    }
}


Ex 2:
Modifying Result
//We can access the result and modify it

@Around("execution(* com.example.service.UserService.getUserById(..))")
public Object modifyReturnValue(ProceedingJoinPoint joinPoint) throws Throwable {
    Object result = joinPoint.proceed();  // Execute method
    logger.info("Original result: {}", result);
    
    return "Modified Result";  // Change the return value
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Common Point Cut:
When we move the packages and services the path will get change and then we need to modify
the path in PointCuts in every method in aspect class
So we make a common class where PointCuts are defined and use that in aspect class so,
when we change the common class path it will get reflected automatically on every aspect method

How to Implement:
We Create a CommonPointCutClass:
We define PointCuts in this class
We use these PointCuts methods in the Aspect class by using their path

code:
//Purpose of this class is to make common PointCuts and use them in Main Aspect Class
public class CommonPointCutClass {

    //This will make all the methods intercepted whose class bean name has Service in it
    //Ex: UserService class bean name shouldbe userService so it will intercept all the methods in that class
    //This is on Bean level
    @Pointcut("bean(*Service*)")
    public void serviceLayer(){}

    //This is the path of the package we want to intercept methods of
    //This is Services package path so all the methods in all the services class of this package will get intercepted
    //This is Path level
    @Pointcut("execution(* com.example.Spring_AOP.Services..*(..))")
    public void serviceLayer1() {}
}

Aspect Class:

@Configuration
@Aspect
public class LoggingAspect {

    private Logger logger = LoggerFactory.getLogger(getClass());

    //This is the path of the CommonPointCutClass method serviceLayer1
    //So the all the methods will get intercepted of the path defined in serviceLayer1
    @Before("com.example.Spring_AOP.CommonPointCutClass.serviceLayer1()")
    public void logBefore(JoinPoint joinPoint) {
        logger.info("BEFORE execution: {} - {}", joinPoint.getSignature().getName(), System.currentTimeMillis());
    }

    @AfterReturning(value = "com.example.Spring_AOP.CommonPointCutClass.serviceLayer1()",returning = "result")
    public void logAfter(JoinPoint joinPoint,Object result) {
        logger.info("AFTER execution:  {}",result);
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