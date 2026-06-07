-----------------------------------------------------------------------------------------------------------------------------------------------------
User-Based Authentication:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Basic Authentication Flow:

→ Client combines username + password → encodes in Base64

→ "varun:pass123" → Base64 → YWRtaW46c2VjcmV0
→ Authorization: Basic YWRtaW46c2VjcmV0

→ BasicAuthenticationFilter intercepts request → decodes Base64 → gets username + password
→ Creates UsernamePasswordAuthenticationToken → passes to AuthenticationManager → Authenticates the user

Note:
    → Base64 is NOT encryption → anyone can decode it
    → Always use HTTPS with Basic Auth → otherwise credentials exposed in transit

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

Authorization Configuration:

Code:
    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())                   // Explicitly disable CSRF
            .authorizeHttpRequests(auth -> auth
                    .requestMatchers("/admin/**").hasRole("ADMIN")
                    .requestMatchers("/user/**").hasRole("USER")
                    .anyRequest().authenticated()
            )
            .formLogin(withDefaults())
            .httpBasic(Customizer.withDefaults());
            .logout(withDefaults());

        return http.build();
    }

-----------------------------------------------------------------------------------------------------------------------------------------------------

User-Based Authentication:
    → Validates user from the Database
    → Needs to implement UserDetails and UserDetailsService

-----------------------------------------------------------------------------------------------------------------------------------------------------

public class User implements UserDetails {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String username;
    private String password;

    //join user and role table in new common table
    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(
            name = "user_roles",
            joinColumns = @JoinColumn(name = "user_id"),
            inverseJoinColumns = @JoinColumn(name = "role_id")
    )
    private Set<Role> roles;

    @OneToOne(mappedBy = "user")
    private Student student;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Role:
    → Roles are not hardcoded, Make a table for all the roles
    → Roles and User are in many to many relationship so, we create common table for them

public class Role {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Student:
    → Student is mapped to user in one to one relationship
    → Student is the owning entity because we are saving student and user will be automatically saved

public class Student{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn
    private User user;

}

-----------------------------------------------------------------------------------------------------------------------------------------------------

UserService:

public class UserService implements UserDetailsService {
    private final UserRepository userRepository;

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return userRepository.findByUsername(username);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------