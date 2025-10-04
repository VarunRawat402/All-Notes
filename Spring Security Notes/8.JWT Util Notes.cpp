---------------------------------------------------------------------------
Spring Security & JWT Notes
---------------------------------------------------------------------------

JWT BEST PRACTICES AND IMPLEMENTATION:

1: Use Strong Signing Algorithms
	Avoid HS256 with weak keys 
	Recommended: RS256 or ES256 (asymmetric cryptography)

2: Dont hardcode the secrets, use Environmental variables
3: Set short expiration times
4: NEVER log JWT tokens
5: Dont store sensitive data in JWT payload

---------------------------------------------------------------------------
JWT (JSON Web Token):
- Structure: header.payload.signature
- Stateless: No need to store user-specific data on the server.

---------------------------------------------------------------------------
Spring Security Filter Chain:
- addFilterBefore: Allows adding custom filters (e.g., JWT filters) before standard Spring Security filters.

---------------------------------------------------------------------------
Filters:
- Filter: Intercepts HTTP requests and responses before they reach the servlet.
- OncePerRequestFilter: A filter that runs only once per HTTP request.

---------------------------------------------------------------------------
Filter Methods:
- doFilter: Override this method to provide custom filtering logic.
- chain.doFilter(): Passes the request and response to the next filter or servlet in the chain.

---------------------------------------------------------------------------
JWT Claims:
- Standard claims include:
    - sub: Username (subject)
    - exp: Expiration date
    - Custom data as needed

---------------------------------------------------------------------------
Token Generation:
1. Authenticate username and password.
2. Create claims for custom data.
3. Use Jwts.builder() to:
    - Set claims, username, issue date, expiration date, headers.
    - Sign the token with a secret key.

---------------------------------------------------------------------------
JWT Validation:
- Check if the token is expired:
    - Extract claims from the token.
    - Get the expiration date from claims.
    - If expiration date is before the current date, the token is expired.
    - If expiration date is after the current date, the token is valid.

---------------------------------------------------------------------------
Extracting Claims:
- Use jwts.parser to create a parser.
- Set the secret key for verification.
- Parse the token to get the JWT object.
- Extract the payload (claims) from the object.

---------------------------------------------------------------------------
JWT Validation in doFilter():
1. Get the "Authorization" header from the request.
2. Extract the token from the header.
3. Extract the username from the token.
4. Validate the JWT token using JWT utilities.
5. If valid:
    - Create a UsernamePasswordAuthenticationToken.
    - Set user details and roles; mark user as authenticated.
    - Add the user as a verified user in the Spring Security context.
    - Pass the request and response to the next filter using chain.doFilter().


---------------------------------------------------------------------------