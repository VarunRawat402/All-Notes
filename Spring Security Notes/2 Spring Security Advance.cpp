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
      • HTML forms: Token added as hidden field.
      • JavaScript/AJAX: Token read from cookies and sent in headers.
      • Server validates token before processing.
      • Missing/incorrect token blocks the request.

    - Note:
      • CSRF protection is needed when authentication uses cookies.
      • JWT tokens are sent in custom headers, so CSRF is usually disabled.

----------------------------------------------------------------------------------------------------------------------------------------

4. CORS (Cross-Origin Resource Sharing):
    - Browser security feature that blocks cross-domain requests unless explicitly allowed.

- Local Configuration Example:

    @CrossOrigin(origins = "http://frontend.com")
    @RestController
    public class MyController {
          @GetMapping("/data")
          public String getData() {
              return "Hello, CORS!";
          }
    }

- Global Configuration Example:

    @Configuration
    public class CorsConfig {
          @Bean
          public WebMvcConfigurer corsConfigurer() {
                return new WebMvcConfigurer() {
                    @Override
                    public void addCorsMappings(CorsRegistry registry) {
                          registry.addMapping("/**")
                                    .allowedOrigins("http://example.com")
                                    .allowedMethods("GET", "POST");
                    }
                };
          }
    }

----------------------------------------------------------------------------------------------------------------------------------------

5. Encoding vs Hashing vs Encryption:
    - Encoding:
      • Converts data to another format.
      • Reversible, not secure.
      • Used for data transfer formats.

    - Hashing:
      • Converts data to a hash string; not reversible.
      • Used for password storage.
      • Passwords are hashed and stored; verification by hashing input and comparing.

    - Encryption:
      • Uses keys to encrypt and decrypt data.
      • Reversible with correct key.
      •   Used for secure communication (TLS, RSA, AES).

----------------------------------------------------------------------------------------------------------------------------------------

6. JWT (JSON Web Token):
    - Used for secure authentication in Spring Boot.
    - How it works:
      • User logs in → server validates credentials.
      • Server generates JWT and sends it to the client.
      • Client stores JWT (local storage/cookies).
      • Client sends JWT in the Authorization: Bearer <token> header.
      • Server validates JWT and grants access.

----------------------------------------------------------------------------------------------------------------------------------------

7. Symmetric vs Asymmetric Encryption:
  - Symmetric Encryption:
    • Same secret key used for encryption and decryption.
    • Fast but less secure if key leaks.

  - Asymmetric Encryption:
    • Uses public key (encrypt) and private key (decrypt).
    • More secure (public key can be shared, private key kept secret).
    • Slower than symmetric encryption.
    • Used in HTTPS handshakes and JWT signing.

----------------------------------------------------------------------------------------------------------------------------------------

8. saveAll() vs save() in Spring Data JPA:

- saveAll():
  • Saves list of entities in a single transaction.
  • If one entity fails (e.g., duplicate email), entire transaction rolls back.
  • Example:
      User1 and User2 saved, User3 fails (duplicate email) → all rolled back.

  Example Code:
        @Override
        public void run(String... args) throws Exception {
              User user1 = User.builder()
                        .email("varun@gmail.com")
                        .password(passwordEncoder.encode("varun123"))
                        .build();

              User user2 = User.builder()
                        .email("arun@gmail.com")
                        .password(passwordEncoder.encode("arun123"))
                        .build();

              User user3 = User.builder()
                        .email("varun@gmail.com")
                        .password(passwordEncoder.encode("varun123"))
                        .build();

              userRepository.saveAll(Arrays.asList(user1, user2, user3));
        }

- save():
  • Saves each entity individually.
  • If one fails, previous saves remain unaffected.
  • Handle errors using try-catch.

  Example Code:
        @Override
        public void run(String... args) throws Exception {
              User user1 = User.builder()
                        .name("varun")
                        .email("varun@gmail.com")
                        .password(passwordEncoder.encode("varun123"))
                        .authority("dev")
                        .build();

              User user2 = User.builder()
                        .name("arun")
                        .email("arun@gmail.com")
                        .password(passwordEncoder.encode("arun123"))
                        .authority("qa")
                        .build();

              User user3 = User.builder()
                        .name("varun")
                        .email("varun@gmail.com")
                        .password(passwordEncoder.encode("varun123"))
                        .authority("dev")
                        .build();

              userRepository.save(user1);
              userRepository.save(user2);
              userRepository.save(user3);
        }

---------------------------------------------------------------------------------------------------------------------------------------
HTTP vs HTTPS:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTP:

HyperText Transfer Protocol
Its the fundamental set of rules for transferring data between your browser and website ( server )
Transfers data in plain text.
Defaut Port : 80

The Problem with HTTP:
Because the data is not encrypted, its vulnerable to several attacks:

Eavesdropping: Anyone on the same Wi-Fi network (like at a coffee shop) or your Internet Service Provider can easily see everything youre sending and receiving.
Man-in-the-Middle (MitM) Attacks: A hacker can intercept the communication between you and the website, potentially stealing your data or even altering the information being sent (like changing a bank account number during a transfer).
No Verification: HTTP does not verify the identity of the website you are connecting to. You might think youre on yourbank.com, but you could be on a fake site designed to look like it.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS:

HyperText Transfer Protocol Secure.
Its the secure version of HTTP. It does everything HTTP does, but it adds a critical layer of security.
HTTP + TLS encryption.
Defaut Port : 443

The Three Key Pillars of HTTPS (What TLS Provides):

Encryption: This scrambles the data being sent back and forth. Even if someone intercepts it, they see only a jumbled mess of random characters. 
Only your browser and the website's server have the secret keys to encrypt and decrypt the data.

Data Integrity: 
This ensures that the data sent is not tampered with during transit. 
TLS provides a way to detect if any data has been altered or corrupted. 
If a single character is changed, the connection will fail.

Authentication: This proves that you are communicating with the intended website and not an imposter. 
This is done using SSL/TLS Certificates. These are digital "passports" issued by trusted third-party companies called Certificate Authorities (CAs). 
Your browser checks this certificate to confirm the website's identity.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How HTTPS Works (The "Handshake" Simplified):

When you connect to an HTTPS website (e.g., https://www.google.com), a secure connection is established in a quick process called a "handshake":
Hello and Certificate: Your browser says "hello" to the server. The server responds with its SSL Certificate to prove its identity.
Key Exchange: Your browser checks the certificate. If its valid and trusted, it uses the public key inside the certificate to agree on a new, temporary secret key with the server.
Secure Communication: Now, both your browser and the server use that temporary secret key to encrypt and decrypt all future communication for that session.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------




