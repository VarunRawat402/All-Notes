-------------------------------------------------------------------------------------------------------------
New Spring Security Configs ( Security Filter Chain ):
-------------------------------------------------------------------------------------------------------------

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
            .logout(withDefaults());

        return http.build();
    }

-------------------------------------------------------------------------------------------------------------

InMemory Authorization:
    → No need to implement UserDetails or UserDetailsService for in memory authentication
    → Hardcode the credentials 
    → Used for testing

Code:
    @Bean
    public UserDetailsService userDetailsService(){

        UserDetails admin = User.withUsername("varun")
                .password(passwordEncoder().encode("1234")).roles("ADMIN").build();

        UserDetails user = User.withUsername("arun")
                .password(passwordEncoder().encode("1234")).roles("USER").build();

        return new InMemoryUserDetailsManager(admin,user);
    }

------------------------------------------------------------------------------------------------------------------------------------------------------

Database-Based Authentication:
    → Validates user from the Database
    → Needs to implement UserDetails and UserDetailsService


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

Role:
    → Roles are not hardcoded, Make a table for all the roles
    → Roles and User are in many to many relationship so, we create common table for them

public class Role {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
}

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

//User Service:
UserService:
public class UserService implements UserDetailsService {
    private final UserRepository userRepository;

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return userRepository.findByUsername(username);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------