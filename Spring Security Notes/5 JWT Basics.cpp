---------------------------------------------------------------------------
Spring Security & JWT Notes
---------------------------------------------------------------------------

JWT BEST PRACTICES AND IMPLEMENTATION:

1: Use Strong Signing Algorithms
	Avoid weak secrets with HS256.
	Prefer RS256 / ES256 (asymmetric) for production.

2: Never hardcode secrets, Use environment variables, Vault, or cloud secret managers.
3: Access tokens: 5-15 minutes, Use refresh tokens for long-term access.
4: Logging JWTs can expose tokens if logs are leaked.
5: Avoid sensitive info in jwt token

---------------------------------------------------------------------------

JWT (JSON Web Token):
- Structure: header.payload.signature
- Stateless: No session storage on the server.
- Validation is entirely based on the token.

---------------------------------------------------------------------------
Spring Security Filter Chain:
- addFilterBefore(customFilter, UsernamePasswordAuthenticationFilter.class) 
    → place your JWT filter before default authentication.

---------------------------------------------------------------------------
Filters:
- Filter: Intercepts HTTP requests/responses before they reach the servlet.
- OncePerRequestFilter: Ensures the filter runs once per request, even during internal forwards.

---------------------------------------------------------------------------
Filter Methods:
- doFilter()        → implement your logic.
- chain.doFilter()  → passes request/response to the next filter or controller.

---------------------------------------------------------------------------
JWT Claims:
- Standard claims include:
    - sub → username (subject)
    - exp → expiration timestamp
    - Custom claims

---------------------------------------------------------------------------
Token Generation:
1. Authenticate username and password.
2. Create claims map for custom info.
3. Use Jwts.builder() to create token

---------------------------------------------------------------------------
Extracting Claims:
- Use Jwts.parserBuilder() with secret key (HS256) or public key (RS256).
- Parse token → returns a Claims object.
- Extract values like username, expiration, custom fields.  

---------------------------------------------------------------------------
JWT Validation:
    - Extract claims from the token.
    - Get the expiration date from claims.
    - If expiration date is before the current date, the token is expired.
    - If expiration date is after the current date, the token is valid.

---------------------------------------------------------------------------
JWT Validation in doFilter():
1. Get the "Authorization" header from the request.
2. Extract the token from the header.
3. Extract the username from the token.
4. Validate the JWT token using JWT utilities.
5. If valid:
    - Create a UsernamePasswordAuthenticationToken.
    - Set user details and roles, marks user as authenticated.
    - Add the user as a verified user in the Spring Security context.
    - Pass the request and response to the next filter using chain.doFilter().

---------------------------------------------------------------------------