-----------------------------------------------------------------------------------------------------------------------------------------------------
Lecture 1: SPRING SECURITY
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Authentication:
    → Verifies WHO you are
    → Validates username + password OR JWT token

2. Authorization:
    → Verifies WHAT you can access
    → Checks roles + authorities after authentication

-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Security Overview:

→ All APIs secured automatically
→ Default username = "user"
→ Random password printed in console
→ Session based auth applied automatically

-----------------------------------------------------------------------------------------------------------------------------------------------------

Session:
    1. User logs in with username + password
    2. Server validates credentials
    3. Server creates SESSION with user details in it
    4. Server generates unique JSESSIONID 
    5. JSESSIONID sent to client → stored in browser cookie
    6. Every request → browser sends JSESSIONID automatically
    7. Server looks up session using JSESSIONID → checks if user is authenticated or not
    
→ Session
    ├── JsessionId
    ├── username
    ├── roles
    ├── authenticated=true
    └── securityContext

-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Security Filter Chain:
    → A chain of security filters applied to every request
    → Placed between the DispatcherServlet and the Controller.

Key Components:

1. UsernamePasswordAuthenticationFilter:
    → Intercepts login requests         
    → Extracts username + password
    → Creates UsernamePasswordAuthenticationToken
    → Passes token to AuthenticationManager

2. AuthenticationManager:
    → Receives the token
    → Delegates to AuthenticationProvider for actual validation

3. AuthenticationProvider:
    → Validates credentials
    → Returns authenticated object with UserDetails + authorities

4. Authentication Object:
    → Principal   → UserDetails
    → Credentials → null after auth (cleared for security)
    → Roles       → what you can access

-----------------------------------------------------------------------------------------------------------------------------------------------------

Security Context:
    → Stores authentication + authorization data for the current request
    → Accessed via SecurityContextHolder

Common Uses:

1. Get current logged-in user:
    SecurityContextHolder.getContext().getAuthentication().getName();

2. Check user role:
    SecurityContextHolder.getContext().getAuthentication()
        .getAuthorities().contains("ROLE_ADMIN");

-----------------------------------------------------------------------------------------------------------------------------------------------------

UsernamePasswordAuthenticationToken:
    → Used to represent authentication in two different stages

-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Not Yet Authenticated (Login Request):

→ Created with just username + password
→ authenticated = false
→ Sent to AuthenticationManager for validation

UsernamePasswordAuthenticationToken token = new UsernamePasswordAuthenticationToken(username, password);
Authentication result = authenticationManager.authenticate(token);

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. Already Authenticated (JWT Flow):

→ Created with UserDetails + null password + authorities
→ authenticated = true (3 args constructor = trusted)
→ Skips validation, set directly into SecurityContext

UsernamePasswordAuthenticationToken token = new UsernamePasswordAuthenticationToken(userDetails, null, userDetails.getAuthorities());
SecurityContextHolder.getContext().setAuthentication(token);

Key difference:
    2 args constructor → not authenticated → needs validation
    3 args constructor → already authenticated → trust and set directly

-----------------------------------------------------------------------------------------------------------------------------------------------------
How BcryptPassword Encoder works:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Hashing (storing password):

→ Generates random salt
→ Combines salt + raw password
→ Applies BCrypt algorithm → produces final hash → stored in DB

-----------------------------------------------------------------------------------------------------------------------------------------------------

Verification (login):

→ Extracts salt + cost factor from stored hash
→ Hashes incoming raw password with same salt + cost
→ Compares both hashes → match = authenticated ✅

-----------------------------------------------------------------------------------------------------------------------------------------------------