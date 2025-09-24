----------------------------------------------------------------------------------------------------------------------------------------
Spring Security: Key Concepts and Explanations
----------------------------------------------------------------------------------------------------------------------------------------

1. Basic Authentication:
    - Mechanism: Client sends username and password in the Authorization header of every HTTP request.
    - Disadvantages:
      • Credentials are sent with every request, increasing exposure risk if HTTPS is not used.
      • Vulnerable to MITM (Man-in-the-Middle) attacks over HTTP.
      • Credentials are only Base64 encoded (not encrypted).
      • Difficult to add extra security (like OTPs or tokens).

----------------------------------------------------------------------------------------------------------------------------------------

2. MITM (Man-in-the-Middle) Attacks:
    - How it works:
      • Attacker intercepts communication between user and server.
      • Can read sensitive data (login credentials, credit card info, etc.).
      • May modify communication (redirect, send fake responses, install malware).

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
    - Purpose: Browser security feature that blocks requests from different domains.
    - To allow sharing, CORS must be configured.

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
      • Converts data to another format (not for security).
      • No key/password needed; reversible.
      • Use case: Data streaming, compression.

    - Hashing:
      • Converts data to a hash string; not reversible.
      • Use case: Security (e.g., storing passwords).
      • Passwords are hashed and stored; verification by hashing input and comparing.

    - Encryption:
      • Uses a key/password to encode data; requires key to decrypt.
      • Use case: Secure communication (e.g., RSA).
      • Data is encrypted with a key and decrypted with the same or another key.

----------------------------------------------------------------------------------------------------------------------------------------

6. JWT (JSON Web Token):
    - Used for secure authentication in Spring Boot.
    - How it works:
      • User logs in with credentials.
      • Server validates and generates JWT token, sends to client.
      • Client stores JWT (local storage/cookies).
      • Client sends JWT in Authorization: Bearer <token> header on each request.
      • Server validates JWT and grants access.

----------------------------------------------------------------------------------------------------------------------------------------

7. Symmetric vs Asymmetric Encryption:
    - Symmetric Encryption:
      • One secret key for both encryption and decryption.
      • Fast, but less secure if key is leaked.

    - Asymmetric Encryption:
      • Uses public key (for encryption) and private key (for decryption).
      • More secure (public key can be shared, private key kept secret).
      • Slower than symmetric encryption.

----------------------------------------------------------------------------------------------------------------------------------------

8. saveAll() vs save() in Spring Data JPA:
    - saveAll():
      • Saves a list of users in a single transaction.
      • If any user fails (e.g., duplicate email), the entire operation rolls back.
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
      • Saves users one by one.
      • If a user fails, previous users remain saved.
      • Use try-catch to handle exceptions for individual saves.

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