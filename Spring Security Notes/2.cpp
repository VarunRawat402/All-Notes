----------------------------------------------------------------------------------------------------------------------------------------
Spring Security:
----------------------------------------------------------------------------------------------------------------------------------------

Basic Authentication:
    Basic Authentication is a simple authentication mechanism where the client sends 
    the username and password in the Authorization header of every HTTP request.

Disadvantages:
The username and password are sent with every HTTP request.
Increases the risk of exposure if HTTPS is not used.

----------------------------------------------------------------------------------------------------------------------------------------

Note:
Basic Authentication is vulnerable to MITM (Man-in-the-Middle) attacks if sent over HTTP.
The credentials are just Base64 encoded, not encrypted.
Since Basic Authentication relies only on username and password, adding OTPs or security tokens is difficult.

----------------------------------------------------------------------------------------------------------------------------------------

MITM (Man in the middle):

How MITM Attacks Work?
    The attacker positions themselves between the user and the target server.
    They capture the data exchanged between the two parties.
    The attacker can read sensitive information such as login credentials, credit card details, or personal data
    The attacker can modify the communication to redirect users, send fake responses, or install malware.

----------------------------------------------------------------------------------------------------------------------------------------

CSRF (Cross-Site Request Forgery):

How CSRF attacks Works?
    The user logs into a website (e.g., a banking site) and remains authenticated (session is active).
    The attacker sends an email or posts a link:
    If the user clicks the link while logged into the bank site, the browser automatically includes the session cookie, making the request valid.
    The bank server processes the request, assuming it was made by the user.
    Since the user is already authenticated, the request is executed with their credentials.

How CSRF Token validation works:
    Spring Security generates a CSRF token when the session starts.
    For HTML forms, Spring automatically adds a hidden CSRF token field.
    For JavaScript/AJAX, the frontend reads the CSRF token from cookies and includes it in headers.
    The server validates the CSRF token before processing requests.
    If the CSRF token is missing or incorrect, the request is blocked.

Note:
Used when you send the authentication credentials in cookies to protect csrf attacks
Jwt token is sent in custom headers so csrf is not needed ( Disable csrf ).

----------------------------------------------------------------------------------------------------------------------------------------

CORS (Cross-Origin Resource Sharing):
It is a security rule in web browsers.
It blocks requests from a different domain to protect your data.
Browsers by default dont allow a website to request data from another websites server.
So Inorder to resource sharing we need to implements CORS.

Local Configuration:

@CrossOrigin(origins = "http://frontend.com") 
@RestController
public class MyController {
    @GetMapping("/data")
    public String getData() {
        return "Hello, CORS!";
    }
}

Global Configuration:

@Configuration
public class CorsConfig {
    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                registry.addMapping("/**") // Allow all URLs
                        .allowedOrigins("http://example.com") // Allow only example.com
                        .allowedMethods("GET", "POST"); // Allow GET & POST
            }
        };
    }
}

----------------------------------------------------------------------------------------------------------------------------------------

Encoding:
    Convert data from one form to another
    Does not need key or password
    Not used for security
    Is reversible
    Usecase : Streaming or compression of data

Hashing:
    Convert data into hash ( string )
    Not reversible
    Usecase : Security
    You created a password it was hashed and stored
    You verify the password by hashing it again and matching the stored hash

Encryption:
    Encoding data using key or password
    Need key or password to decrypt
    Ex : RSA
    You used a key and encryption to encrypt the text
    You used same key and decryption to decrypt the text

----------------------------------------------------------------------------------------------------------------------------------------

JWT ( Json Web Token ):
JWT (JSON Web Token) is used for secure authentication in Spring Boot applications. 
It is a token that holds user information and is used to verify identity without storing session data on the server.

How JWT Works in Spring Boot?
User Logs In → Sends username & password
If valid, it generates a JWT token and sends it back to the client.
Client Stores JWT → Usually in local storage or cookies ( cookies more secure )
Client Sends JWT on Every Request → Sent in Authorization: Bearer <token> header
Server Validates JWT → Extracts user info & grants access

----------------------------------------------------------------------------------------------------------------------------------------

Symmetric Encryption:
Uses one secret key for both encryption and decryption.
If someone gets the key, they can decrypt the data.
Fast but less secure because the same key is shared.

Asymmetric Encryption:
Uses two keys:
    Public key → Encrypts data
    Private key → Decrypts data
Even if someone gets the public key, they cannot decrypt without the private key.
More secure but slower than symmetric encryption.

----------------------------------------------------------------------------------------------------------------------------------------

SaveAll():
    User1 and User3 have same email address so user1 and user2 will get saved but when it will try
	to save User3 it will fail and rollback other saved users too due to its Transactional behavior

Code:
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

		userRepository.saveAll(Arrays.asList(user1,user2,user3));
	}

----------------------------------------------------------------------------------------------------------------------------------------

Save():
	We are saving users one by one so user1 and user2 will get saved and 
	user3 will give error due to which application wont start, so you can
	use try catch to handle the Exception.
	
Code:
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

----------------------------------------------------------------------------------------------------------------------------------------
