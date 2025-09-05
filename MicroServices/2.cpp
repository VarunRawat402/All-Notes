------------------------------------------------------------------------------------------------------------------------------------------------------------------------
We can communicate through microservices using RestTemplate, WebClient, FeignClient
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REST TEMPLATE:
    RestTemplate is a synchronous client to perform HTTP requests

1: Synchronous Operations: 
        All operations performed using RestTemplate are synchronous, meaning the thread that executes the request will block until the response is returned.

2: Template Methods: 
        Offers several methods for different HTTP methods (getForObject, postForObject, exchange, etc.), which simplify the use of HTTP calls and reduce boilerplate code.

3: Error Handling: 
        Includes a default error handler that can be overridden to handle client and server errors according to specific requirements.

4: Data Conversion: 
        Automatically converts HTTP messages to and from Java objects based on converters and formatters. It supports a wide range of response body types and can be extended 
        to support additional types.

5: Interceptors: 
        Allows adding ClientHttpRequestInterceptors to modify requests and responses, e.g., for adding headers, logging request and response details, etc.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:
    RestTemplate restTemplate = new RestTemplate();
    //getForObject makes the get call to the provided uri and convert the object we got to the String class as mentioned in the method.
    String result = restTemplate.getForObject("http://example.com/api/resource", String.class);
    System.out.println(result);
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

While RestTemplate has been very effective and popular, it does not support non-blocking I/O operations,
which can be a limitation when dealing with large-scale applications or reactive programming.
RestTemplate has been deprecated in favor of WebClient, which supports both synchronous and asynchronous operations, along with reactive streams.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Thread:
Whenever a client makes a request to the server/application, A thread is responsible for processing a request and giving a response back
1 thread can process only 1 request and blocked by that request untill it is completed.

Ex:
A client made a request to the application so 1 thread is assigned to that request which will make the call to DB and get the response
from the DB and give the response to the client and after the client got the response that thread will deallocate themeselves.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RestTemplate is a blocking call

Spring Web flux is a non blocking call
Dependency name : Spring Boot started web flux

Feign Client is blocking by defualt but we can make it non blocking with customization

------------------------------------------------------------------------------------------------------------------------------------------------------------------------