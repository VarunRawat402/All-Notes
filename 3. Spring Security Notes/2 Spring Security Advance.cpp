-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Security: Key Concepts and Explanations
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Basic Authentication:

→ Client sends username/password in the Authorization header
→ Server needs to store session data
→ less secure than jwt

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. MITM (Man-in-the-Middle) Attacks:

→ Attacker intercepts communication between user and server.
→ Client  →  Attacker  →  Server
→ Can read username/password, jwt token, session cookie, personal data
→ Use HTTPS, Certificate validation, VPN

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. CSRF (Cross-Site Request Forgery):

→ User logs in bank site, sessionId is stored in browser
→ User visits attacker site, attacker sent request to bank
→ Browser automatically adds sessionId, Bank think its valid
→ Money Transferred

→ Spring Security generates a CSRF token automatically per session.
→ Server validates token and session before processing.
→ Missing/incorrect token blocks the request.

→ Note:
  • CSRF protection is needed when authentication uses cookies.
  • With JWT token validation, CSRF protection is generally not required.

-----------------------------------------------------------------------------------------------------------------------------------------------------

4. CORS (Cross-Origin Resource Sharing):

→ Browser blocks requests to different origin by default
→ Server needs to allow browser by sending CORS Headers

@CrossOrigin(origins = "http://frontend.com")
@RestController
public class MyController {
      @GetMapping("/data")
      public String getData() {
          return "Hello, CORS!";
      }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Hashing:
• Data → Hash
• Irreversible
• Passwords are hashed and stored

-----------------------------------------------------------------------------------------------------------------------------------------------------

Encryption:
• Keys → Encrypt / Decrypt
• Reversible with correct key.
• Used for secure communication (TLS, JWT).

→ Symmetric Encryption:
  • Same key for encrypt / decrypt
  • Fast but Key sharing is risky

→ Asymmetric Encryption:
  • Public key → encrypt
  • Private key → decrypt
  • Slower than symmetric encryption.

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTTP:
  → Defaut Port : 80

The Problem with HTTP:
  → Data you are sending is not encrypted
  → Anyone on the same Wi-Fi network can easily see everything you are sending and receiving.
  → A hacker can intercept the communication between you and the website and can read all the sensitive details

No Verification: 
  → HTTP does not verify the server you are connected to
  → You could be on the fake site without knowing it

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS:
  → Its the secure version of HTTP. 
  → HTTP + TLS encryption.
  → Defaut Port : 443

Encryption:
  → Encrypt the data so attackers cannot read it 
  → Browser and server have the secret keys to encrypt / decrypt data

Security:
  → Attacker cannot modify the data 
  → TLS Checks if any data is corrupted or modified 
  → If a single character is changed, the connection will fail.

Working
  → Verifies server identity using certificates
  → This proves that you are communicating with the intended website and not an imposter. 
  → This is done using SSL/TLS Certificates.

-----------------------------------------------------------------------------------------------------------------------------------------------------

How HTTPS Works (The "Handshake" Simplified):

→ When you connect to an HTTPS website. 
→ A secure connection is established called a "handshake"

1: Browser → Server   : Hello
2: Server  → Browser  : Certificate
3: Browser verifies certificate
4: Secure symmetric key established
5: Encrypted communication begins

→ If its valid and trusted, It uses the public key inside the certificate to agree on a new, temporary secret key with the server.
→ Secure Communication: Now, both your browser and the server use that temporary secret key to encrypt and decrypt all future communication for that session.

-----------------------------------------------------------------------------------------------------------------------------------------------------




