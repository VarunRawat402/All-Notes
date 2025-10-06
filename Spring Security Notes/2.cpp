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
HTTP vs HTTPS:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTP:

HyperText Transfer Protocol
Its the fundamental set of rules for transferring data between your browser and website ( server )
It sends all information—your passwords, credit card numbers, messages—in plain text.
Defaut Port : 80

The Problem with HTTP:
Because the data is not encrypted, its vulnerable to several attacks:

Eavesdropping: Anyone on the same Wi-Fi network (like at a coffee shop) or your Internet Service Provider can easily see everything youre sending and receiving.
Man-in-the-Middle (MitM) Attacks: A hacker can intercept the communication between you and the website, potentially stealing your data or even altering the information being sent (like changing a bank account number during a transfer).
No Verification: HTTP does not verify the identity of the website you are connecting to. You might think youre on yourbank.com, but you could be on a fake site designed to look like it.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS:

HyperText Transfer Protocol Secure
Its the secure version of HTTP. It does everything HTTP does, but it adds a critical layer of security.
It uses encryption protocols called TLS (Transport Layer Security), formerly known as SSL, to protect the data.
Defaut Port : 443

The Three Key Pillars of HTTPS (What TLS Provides):

Encryption: This scrambles the data being sent back and forth. Even if someone intercepts it, they see only a jumbled mess of random characters. 
Only your browser and the website's server have the secret keys to encrypt and decrypt the data.

Data Integrity: This ensures that the data sent is not tampered with during transit. 
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

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------]\

Cascade:

cascade will always be added on the saving side
If you are saving student and want user to be saved automatically then you need to add cascade on student entity at user attribute
If you are saving user and want student to be saved automatically then you need to add cascade on user entity at student attribute

Ex:

public class User{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String username;
    private String password;

    private List<String> roles = new ArrayList<>();
}

public class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
    private int age;

    @OneToOne(cascade = CascadeType.PERSIST)    //cascade is in the student entity because we are saving student and want user to be saved automatically
    @JoinColumn
    private User user;

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------]\



