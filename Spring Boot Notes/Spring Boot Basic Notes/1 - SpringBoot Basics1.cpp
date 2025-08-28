-----------------------------------------------------------------------------------------------------------------------
Lecture 1: Spring Boot Basics
-----------------------------------------------------------------------------------------------------------------------

NETWORK CALL: 
    Client sends a request to the server over the network and server sends the response
    You can see all the network calls in the network tab in inspect of website

-----------------------------------------------------------------------------------------------------------------------

User -> FrontEnd -> Network Call -> Server -> Servelets -> Controller Class/path -> Function/Logic
Function/Logic (returned the response) -> Servelets -> FrontEnd -> User

-----------------------------------------------------------------------------------------------------------------------

Logs:
    There are different types of logs:
    These logs are in descending order in terms of severeness.
    Error -> Warning -> Info -> Debug -> Trace 

-----------------------------------------------------------------------------------------------------------------------

There cannot be 2 similar APIs 
APIs are simialr when the "HTTP Method" and "Path" are same for both APIs

Ex- 
@GetMapping("/book")
public String getName(){
    return name;
}

@GetMapping("/book")
public int getId(){
    return id;
}

-----------------------------------------------------------------------------------------------------------------------