---------------------------------------------------------------------------
Spring Security & JWT Notes
---------------------------------------------------------------------------

JWT BEST PRACTICES AND IMPLEMENTATION:

1: Use Strong Signing Algorithms
	Avoid HS256 with weak, short secrets.
	Prefer RS256 or ES256 for asymmetric signing.

2: Dont hardcode the secrets, Store private keys and secrets in environment variables or secret managers.
3: Set short expiration times -> Short-lived access tokens (5-15 minutes) -> Use refresh tokens for long-term authentication.
4: NEVER log JWT tokens, Logs can be leaked and tokens can be replayed.
5: Dont store sensitive data in JWT payload, JWT can be decoded easily even if signed.

---------------------------------------------------------------------------

JWT (JSON Web Token):
- Structure: header.payload.signature
- Stateless: No session storage on the server.
- Authentication is validated entirely using the token.

---------------------------------------------------------------------------
Spring Security Filter Chain:
- addFilterBefore() is used to insert custom filters (e.g., JWT authentication filter) 
    before Spring Security internal filters like UsernamePasswordAuthenticationFilter.

---------------------------------------------------------------------------
Filters:
- Filter: Intercepts HTTP requests/responses before they reach the servlet.
- OncePerRequestFilter: Interface, Ensures filtering logic runs once per request, even through internal forwards.

---------------------------------------------------------------------------
Filter Methods:
- doFilter: Override this method to provide custom filtering logic.
- chain.doFilter(): Forwards the request/response to the next filter or servlet.

---------------------------------------------------------------------------
JWT Claims:
- Standard claims include:
    - sub → username (subject)
    - exp → expiration timestamp
    - Additional custom claims can be added if needed (e.g., roles, userId).

---------------------------------------------------------------------------
Token Generation:
1. Authenticate username and password.
2. Create a claims map for custom data.
3. Use Jwts.builder() to:
    - Set claims, Set subject (username), issue date, expiration date, headers.
    - Sign with secret key or private key (RS256).

---------------------------------------------------------------------------
Extracting Claims:
- Use Jwts.parserBuilder() to create a JWT parser.
- Set secret key or public key (for RS256).
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
    - Set user details and roles; mark user as authenticated.
    - Add the user as a verified user in the Spring Security context.
    - Pass the request and response to the next filter using chain.doFilter().


---------------------------------------------------------------------------