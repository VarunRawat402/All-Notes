----------------------------------------------------------------------------------------------------------------------------------------
Spring Security: Key Concepts and Explanations
----------------------------------------------------------------------------------------------------------------------------------------

1. Basic Authentication:

- Client sends username and password in the Authorization header with every request (Base64 encoded).
- Disadvantages:
  • Credentials are sent on every request → higher risk if HTTPS is not used.
  • Vulnerable to MITM attacks when used over HTTP.
  • Base64 is not encryption; easily decoded.
  • Difficult to add extra security (like OTPs or tokens).

----------------------------------------------------------------------------------------------------------------------------------------

2. MITM (Man-in-the-Middle) Attacks:

- How it works:
  • Attacker intercepts communication between user and server.
  • Can read sensitive data (login credentials, credit card info, etc.).
  • Can modify traffic (fake responses, redirection, malicious payloads).

----------------------------------------------------------------------------------------------------------------------------------------

3. CSRF (Cross-Site Request Forgery):

- How CSRF Attacks Work:
  • User logs into a site and stays authenticated.
  • Attacker tricks user into making a request (via email/link) while logged in.
  • Browser includes session cookie, making the request valid.
  • Server processes the request as if made by the user.

- CSRF Token Validation:
  • Spring Security generates a CSRF token per session.
  • HTML → Token added in hidden input
  • AJAX → Token added in header
  • Server validates token before processing.
  • Missing/incorrect token blocks the request.

- Note:
  • CSRF protection is needed when authentication uses cookies.
  • JWT tokens are sent in custom headers, so CSRF is usually disabled.

----------------------------------------------------------------------------------------------------------------------------------------

4. CORS (Cross-Origin Resource Sharing):\

- Browser blocks cross-domain requests unless explicitly allowed.
- Backend must explicitly allow frontend domain

- Local (Controller-level):

  @CrossOrigin(origins = "http://frontend.com")
  @RestController
  public class MyController {
        @GetMapping("/data")
        public String getData() {
            return "Hello, CORS!";
        }
  }

- Global Configuration:

  @Configuration
  public class CorsConfig {
      @Bean
      public WebMvcConfigurer corsConfigurer() {
          return new WebMvcConfigurer() {
              @Override
              public void addCorsMappings(CorsRegistry registry) {
                  registry.addMapping("/**")
                          .allowedOrigins("http://example.com")
                          .allowedMethods("GET","POST","PUT","DELETE");
              }
          };
      }
  }


----------------------------------------------------------------------------------------------------------------------------------------

5. Encoding vs Hashing vs Encryption:

- Encoding:
  • Converts data to another format.
  • Reversible, not secure.
  • Used for data transport.

- Hashing:
  • Converts data to a hash string
  • One-way (irreversible)
  • Passwords are hashed and stored

- Encryption:
  • Uses keys to encrypt and decrypt data.
  • Reversible with correct key.
  • Used for secure communication (TLS, RSA, AES).

----------------------------------------------------------------------------------------------------------------------------------------

6. JWT (JSON Web Token):

- How it works:
  • User logs in → server validates credentials.
  • Server generates JWT and sends it to the client.
  • Client stores JWT (local storage/cookies).
  • Client sends JWT in the Authorization: Bearer <token> header.
  • Server validates JWT and grants access.

----------------------------------------------------------------------------------------------------------------------------------------

7. Symmetric vs Asymmetric Encryption:

- Symmetric Encryption:
  • Same key for encrypt & decrypt
  • Fast but Key sharing is risky

- Asymmetric Encryption:
  • Public key → encrypt
  • Private key → decrypt
  • More secure (public key can be shared, private key kept secret).
  • Slower than symmetric encryption.
  • Used in TLS handshakes and JWT signing.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HTTP vs HTTPS:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTP:
HyperText Transfer Protocol
Plain text communication
Defaut Port : 80

The Problem with HTTP:
Because the data is not encrypted, its vulnerable to several attacks:

Eavesdropping: 
  Anyone on the same Wi-Fi network (like at a coffee shop) or your Internet Service Provider can easily see everything youre sending and receiving.

Man-in-the-Middle (MitM) Attacks: 
  A hacker can intercept the communication between you and the website, potentially stealing your data or even altering the information being sent (like changing a bank account number during a transfer).

No Verification: 
  HTTP does not verify the identity of the website you are connecting to. 
  You might think you are on yourbank.com, but you could be on a fake site designed to look like it.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS:
HyperText Transfer Protocol Secure.
Its the secure version of HTTP. It does everything HTTP does, but it adds a critical layer of security.
HTTP + TLS encryption.
Defaut Port : 443

The Three Key Pillars of HTTPS (What TLS Provides):

Encryption:
  Encrypt the data so attackers cannot read it 
  Only your browser and the website's server have the secret keys to encrypt and decrypt the data.

Data Integrity: 
  Data cannot be modified silently
  TLS provides a way to detect if any data has been altered or corrupted. 
  If a single character is changed, the connection will fail.

Authentication: 
  Verifies server identity using certificates
  This proves that you are communicating with the intended website and not an imposter. 
  This is done using SSL/TLS Certificates.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How HTTPS Works (The "Handshake" Simplified):

When you connect to an HTTPS website. A secure connection is established called a "handshake"

Browser → Server: Hello
Server → Browser: Certificate
Browser verifies certificate
Secure symmetric key established
Encrypted communication begins

If its valid and trusted, It uses the public key inside the certificate to agree on a new, temporary secret key with the server.
Secure Communication: Now, both your browser and the server use that temporary secret key to encrypt and decrypt all future communication for that session.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------




