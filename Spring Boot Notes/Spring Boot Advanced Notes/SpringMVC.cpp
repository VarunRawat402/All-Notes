------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MVC in Spring (Spring MVC)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring MVC (Model-View-Controller) is a framework within the Spring boot starter web dependency that helps build web applications. 

It separates concerns into three components:
    Model Represents the data and business logic.
    View Handles the UI (User Interface).
    Controller Manages user requests and updates the model and view.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How Spring MVC Works (Flow):

    Client Sends Request → The user sends a request.
    DispatcherServlet Receives Request → This is the front controller that manages request handling.
        Identifies correct controller based on URL and executes it.
        It is auto configured in the application
    Controller Processes Request → The request is passed to a controller, which processes it using services and the model.
    View→ The controller returns view and model, and Spring resolves the correct view (JSP, Thymeleaf, etc.).
    Response Sent to Client → The final webpage is rendered and displayed to the user.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Jackson in Spring Boot
Spring Boot automatically configures Jackson as the default JSON serializer/deserializer
Converts the json to object and vice versa as per need.

What is HttpMessageConverters?
Converts HTTP request/response bodies between JSON, XML, and Java objects.
This means when you send/receive JSON in a REST API, Jackson performs the actual conversion, 
but Spring uses HttpMessageConverter to trigger Jackson.

Important Status code:

200: success
201: created
204: no content
400: UnAuthorized
401: Bad Request
404: Resource Not found
500: Server Error

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Framework vs. Spring MVC vs. Spring Boot

What It Is?	
    Core framework for Java applications	
    A module inside Spring for web apps	
    A tool to make Spring development easier

Purpose	
    Provides dependency injection, transaction management, AOP, etc.	
    Helps build web applications (like Servlets but simpler)	
    Auto-configures everything in Spring to reduce setup time

Setup Required	
    Manual configuration (XML or Java-based)	
    Requires configuring DispatcherServlet, ViewResolvers, etc.	
    Almost no configuration needed (uses defaults)

Web Application Support?	
    Not specific to web apps	
    Yes, used for building web apps	
    Yes, auto-configures Spring MVC

Uses Spring Core?	
    Yes	
    Yes (built on Spring Framework)	
    Yes (built on Spring MVC)

Embedded Server?	
    No	
    No	
    Yes (Tomcat, Jetty, Undertow)

Configuration Style	
    XML-based or Java-based (@Configuration)	
    Java-based (@Controller, @RestController)	
    Annotations + auto-config (@SpringBootApplication)

REST API Support?	
    No built-in support	
    Yes, using @RestController	
    Yes, automatically set up

Startup Speed	
    Slow (manual configuration)	
    Moderate (requires setup)	
    Fast (auto-configured)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------