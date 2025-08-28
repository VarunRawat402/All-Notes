--------------------------------------------------------------------------------------------------------------------------------------------
ResponseEntity:
--------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity is a class used to create a HTTP Response, including:
    { Status code, Headers. Body }

--------------------------------------------------------------------------------------------------------------------------------------------

New ResponseEntity<>():
Manually creating a new ResponseEntity object to get full control over headers, status and Body.

Ex:
//Created a HTTP Response with body and status
ResponseEntity<String> response = new ResponseEntity<>("Success", HttpStatus.OK);

//Created a HTTP Response with body, headers, and status
HttpHeaders headers = new HttpHeaders();
headers.add("Custom-Header", "Value");
ResponseEntity<String> responseWithHeaders = new ResponseEntity<>("Hello", headers, HttpStatus.CREATED);

--------------------------------------------------------------------------------------------------------------------------------------------

ResponseEntity Static Helper Methods:
For standarnd and more readable responses.

Ex:
Returns 200 status with body:
ResponseEntity.ok("Body")

Returns custom status with body:
ResponseEntity.status(HttpStatus.CREATED).body("Created")	

Returns 201 Created status with location header:
ResponseEntity.created(URI.create("/resource/1")).body(obj)

Returns 204 status no body:
ResponseEntity.noContent().build()

--------------------------------------------------------------------------------------------------------------------------------------------
Status Code:
--------------------------------------------------------------------------------------------------------------------------------------------

2xx( Successfull ):

200 : Body is returned
201 : New resource is created
204 : Requests is successfull but there is no body

--------------------------------------------------------------------------------------------------------------------------------------------

3xx ( Redirection ):
Further action needs to be taken by the client to complete the request

--------------------------------------------------------------------------------------------------------------------------------------------

4xx ( Error ):
Malformed Request or Authentication Issues:

400 : Bad Request : Invalid Syntax or client side Issues
401 : Unauthorized request : Needs Authentication
403 : Forbidden : Client does not have the permission to use this resource

--------------------------------------------------------------------------------------------------------------------------------------------

5xx ( Server Error ):

500 : Internal Server error : Issue with server : Server could not handle the request
502 : Bad Gateway : 
503 : Service Unavailable : Server is unable to handle the request

--------------------------------------------------------------------------------------------------------------------------------------------
