--------------------------------------------------------------------------------------------------------------------------------------------
ResponseEntity:
--------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity is a class used to create a HTTP Response
    Including : { Body, Headers, Status code }

--------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity<>() Manually Creating:

You create a new ResponseEntity object when you want complete control.

Ex:
// Create a response with body + status
ResponseEntity<String> response = new ResponseEntity<>("Success", HttpStatus.OK);

// Create a response with body + headers + status
HttpHeaders headers = new HttpHeaders();
headers.add("Custom-Header", "Value");
ResponseEntity<String> responseWithHeaders = new ResponseEntity<>("Hello", headers, HttpStatus.CREATED);

--------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity Static Helper Methods:

Static builder methods make responses cleaner and more readable.

Examples:

// Returns 200 status with body:
ResponseEntity.ok("Body")

// Returns custom status with body:
ResponseEntity.status(HttpStatus.CREATED).body("Created")	

// Returns 201 Created status with location header:
ResponseEntity.created(URI.create("/resource/1")).body(obj)

// Returns 204 status no body:
ResponseEntity.noContent().build()

--------------------------------------------------------------------------------------------------------------------------------------------
HTTP Status Codes:
--------------------------------------------------------------------------------------------------------------------------------------------

2xx( Successfull ):

200 OK : Body is returned
201 Created : New resource is created
204 No Content : Requests is successfull but there is no body

--------------------------------------------------------------------------------------------------------------------------------------------

3xx ( Redirection ):
Client must take additional action (e.g., redirect).

--------------------------------------------------------------------------------------------------------------------------------------------

4xx ( Error ):
Malformed Request or Authentication Issues:

400 Bad Request : Invalid syntax or bad input
401 Unauthorized : Authentication required or invalid credentials
403 Forbidden : Client authenticated but not allowed to access resource
404 Not Found : Resource does not exist


--------------------------------------------------------------------------------------------------------------------------------------------

5xx ( Server Error ):

500 : Internal Server error : Issue with server : Server could not handle the request
502 : Bad Gateway : Server received invalid response from upstream service
503 : Service Unavailable : Server temporarily unable to handle request

--------------------------------------------------------------------------------------------------------------------------------------------
