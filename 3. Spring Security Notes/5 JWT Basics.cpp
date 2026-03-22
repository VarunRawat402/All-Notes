-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Security & JWT Notes
-----------------------------------------------------------------------------------------------------------------------------------------------------

Flow of JWT Authentication:

Client  → sends username and password 
Backend → Validates credentials → returns JWT
Client  → Calls secured APIs using jwt 
Backend → Extract token from header → validate token

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT BEST PRACTICES AND IMPLEMENTATION:

1: Use Strong Signing Algorithms
	→ Weak secrets      → HS256.
	→ Strong secrets    → RS256 / ES256

2: Expiration time : 5-15 min
3: Avoid sensitive info in jwt token

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Structure:

1: header       → Signing algorithm(HS256/RS256) & Token Type(JWT)
2: Payload      → Sub, name, role, iat, expiration, custom data
3: Signature    → Used to verify token 

-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Security Filter Chain:
→ addFilterBefore(customFilter, UsernamePasswordAuthenticationFilter.class) 
    → place your JWT filter before default authentication.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Filter Methods:
→ doFilter()        → implement your logic.
→ chain.doFilter()  → passes request/response to the next filter or controller.

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Validation in doFilter():
1. Get the "Authorization" header from the request.
2. Extract the token from the header.
3. Extract the username from the token.
4. Validate the JWT token using JWT utilities.
5. If valid:
    → Create a UsernamePasswordAuthenticationToken.
    → Set user details and roles, marks user as authenticated.
    → Add the user as a verified user in the Spring Security context.
    → Pass the request and response to the next filter using chain.doFilter().

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT and Refresh Token Flow:

Client sends username + password
Server validates and generates jwt + refresh token
Jwt token is return to the client
refresh token is stored in httpOnly cookie in the browser 
that cookie is automatically sent with request
You can also set the path of the cookie : path : /auth, means it will get sent on paths starting with auth/
Server extracts the refresh token from the cookie + validates it and generate new access token and returns it
Client sends same request again with new access token

-----------------------------------------------------------------------------------------------------------------------------------------------------