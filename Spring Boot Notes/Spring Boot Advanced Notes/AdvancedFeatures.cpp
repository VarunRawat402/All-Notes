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
    Spring Boot Actuator provides tools for monitoring and managing a running application.

It exposes endpoints for:
    health
    metrics
    environment
    beans
    logs
    mappings

1: Add the Dependency:

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>

2: Expose the points:
    Application.properties:
    management.endpoints.web.exposure.include=*

--------------------------------------------------------------------------------------------------------------------------------------------


