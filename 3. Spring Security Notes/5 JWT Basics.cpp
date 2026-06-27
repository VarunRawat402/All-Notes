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

JWT filter:
    → addFilterBefore(JwtFilter, UsernamePasswordAuthenticationFilter.class) 
    → place your JWT filter before default authentication.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Filter Methods:
→ doFilter()        → implement your logic.
→ chain.doFilter()  → passes request/response to the next filter or controller.

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Validation:

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