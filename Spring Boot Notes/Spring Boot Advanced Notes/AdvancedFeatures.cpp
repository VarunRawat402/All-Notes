--------------------------------------------------------------------------------------------------------------------------------------------
Advanced Rest API Features:
--------------------------------------------------------------------------------------------------------------------------------------------

1: Documentation ( REST API ):

Documentation is done so that consumers know how to use the API properly
Open API automatically generates the API Documentation for all the APIs of the application
and we can see them on the swagger ui URL.

Swagger UI : Swagger tool to visualize and interact with your rest API
    ( URL : localhost:8080/swagger-ui.html)

Dependency:
    <dependency>
    <groupId>org.springdoc</groupId>
    <artifactId>springdoc-openapi-starter-webmvc-ui</artifactId>
    <version>2.7.0</version>
    </dependency>

--------------------------------------------------------------------------------------------------------------------------------------------
    
2: Content Negotiation ( REST API ):

Content Negotiation allows a Spring Boot REST API to serve responses in different formats (JSON, XML, etc.) based on client requests.
With this dependency spring boot will automatically parse the data into the XML 
Add this request Headers:
    Accept : application/xml

Dependency:
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-xml</artifactId>
    </dependency>

--------------------------------------------------------------------------------------------------------------------------------------------

3: Internationalization (i18n):

Spring Boot supports internationalization (i18n) using messages.properties files. 
This allows you to provide different translations for messages based on the users locale.
Request Headers:
Accept-Language : en,nl,fr

Steps:
1: Create messages.properties file for different Languages
    ( path : src/main/resources)
    Ex:
        messages.properties : 
            goodMorning.message=Good Morning
        messages_fr.properties : 
            goodMorning.message=Bonjour!

2: Use these properties using MessageSource in Controller:
    //Message source will fetch the message.properties file based on the 
    //Request header : Accept-Language from the client

Code:
    @Autowired
    MessageSource messageSource;

    @GetMapping("/hello")
    public String helloWorldIn18(){
        Locale locale = LocaleContextHolder.getLocale();
        return messageSource.getMessage("goodMorning.message",null,"Default Message",locale);
    }

--------------------------------------------------------------------------------------------------------------------------------------------

4: Spring Boot Actuator:

Spring Boot Actuator provides production-ready features to monitor and manage applications without modifying the code.
It exposes various endpoints to check application health, metrics, environment properties, and more.

Dependency:
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>

Application.properties:
management.endpoints.web.exposure.include=*

--------------------------------------------------------------------------------------------------------------------------------------------


