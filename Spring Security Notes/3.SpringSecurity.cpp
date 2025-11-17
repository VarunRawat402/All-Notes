-------------------------------------------------------------------------------------------------------------
New Spring Security Configs ( Security Filter Chain ):
-------------------------------------------------------------------------------------------------------------

Features:

Component based Configuration, Not inheritance
Lambda DSL, Cleaner Syntax, No more .and()
Multiple Filter chains
RequestMatchers() instead of antMatchers()
Oath2 and JWT First class supports
Easier to mock SecurityFilterChain than Override methods

-------------------------------------------------------------------------------------------------------------

Authorization:

Code:
    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                .csrf(csrf -> csrf.disable()) // Explicitly disable CSRF
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
    In this we hardcode the credentials and store in the InMemory of application

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

User Based Authentication:
    In this we fetch the user from the database and validate it


//User Entity:
public class User implements UserDetails {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String username;
    private String password;

    //join user and role table in new common table
    @ManyToMany
    @JoinTable(
            name = "user_roles",
            joinColumns = @JoinColumn(name = "user_id"),
            inverseJoinColumns = @JoinColumn(name = "roles_id")
    )
    private Set<Role> roles = new HashSet<>();

    @OneToOne(mappedBy = "user")
    private Student student;
}

//Role Entity:
Role:
    Roles are not hardcoded in variables, Make a Db for all the roles
    Roles and User are in many to many relationship so, we create common table for them

public class Role {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String name;
}

//Student Entity:
Student:
    Student is mapped to user in one to one relationship
    Student is the owning entity because we are saving student and user will 
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