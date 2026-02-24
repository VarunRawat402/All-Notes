-----------------------------------------------------------------------------------------------------------------------------------------------------
Jwt Implementation using JJWT:
-----------------------------------------------------------------------------------------------------------------------------------------------------

JJWT: 
    → It is a library, java JWT
    → Used to create and parse token
    → External Library, used before SS6

Jwts:
    → It is a util class
    → Provides Builder & Parser to create and validate tokens
    → Jwts.builder() → "Create JWT"
    → Jwts.parser() → "Read & validate JWT"

-----------------------------------------------------------------------------------------------------------------------------------------------------

User Entity:
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String username;
    private String password;
    private List<String> roles;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

UserService:

public class UserService {

    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;

    public boolean saveNewUser(User user) {
        try {
            user.setPassword(passwordEncoder.encode(user.getPassword()));
            user.setRoles(Arrays.asList("USER"));
            userRepository.save(user);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public List<User> getAll() {return userRepository.findAll();}

    public User findByUserName(String username) {return userRepository.findByUsername(username);}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

UserServiceImplementation:

public class UserDetailsServiceImpl implements UserDetailsService {

    private finalUserRepository userRepository;

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        User user = userRepository.findByUsername(username);
        if (user != null) {
            return org.springframework.security.core.userdetails.User.builder()
                    .username(user.getUsername())
                    .password(user.getPassword())
                    .roles(user.getRoles().toArray(new String[0]))
                    .build();
        }
        throw new UsernameNotFoundException("User not found with username: " + username);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Util ( Extracting datas and creating tokens ):

public class JwtUtil {

    //Generate key
    private static final String SECRET_KEY = "TaK+HaV^uvCHEFsEVfypW#7g9^k*Z8$V";
    private final SecretKey signingKey = Keys.hmacShaKeyFor(SECRET_KEY.getBytes());

    //Parse and validate token (signature + expiration automatically checked)
    private Claims extractAllClaims(String token) {
        return Jwts.parser()
                .verifyWith(signingKey)
                .build()
                .parseSignedClaims(token)
                .getPayload();
    }

    //Extract username
    public String extractUsername(String token) {
        return extractAllClaims(token).getSubject();
    }

    //Validate token (if no exception -> valid)
    public boolean validateToken(String token) {
        try {
            extractAllClaims(token);
            return true;
        } catch (JwtException | IllegalArgumentException e) {
            return false;
        }
    }

    // Generate token
    public String generateToken(String username) {
        return Jwts.builder()
                .subject(username)
                .issuedAt(new Date())
                .expiration(new Date(System.currentTimeMillis() + 1000 * 60 * 50))
                .signWith(signingKey)
                .compact();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Filter ( Validate the Token and grant access ):

public class JwtFilter extends OncePerRequestFilter {           //OncePerRequestFilter : Pass the request only one time
   
    private final UserDetailsService userDetailsService;
    private final JwtUtil jwtUtil;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws ServletException, IOException {

        String authorizationHeader = request.getHeader("Authorization");
        String username = null;
        String jwt = null;

        //Extract token and username from header
        if (authorizationHeader != null && authorizationHeader.startsWith("Bearer ")) {
            jwt = authorizationHeader.substring(7);
            username = jwtUtil.extractUsername(jwt);
        }

        if (username != null && jwtUtil.validateToken(jwt)) {

            UserDetails userDetails = userDetailsService.loadUserByUsername(username);

                //validates the user with userdetails
                UsernamePasswordAuthenticationToken auth = new UsernamePasswordAuthenticationToken(userDetails, null, userDetails.getAuthorities());

                //set extra details
                auth.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

                //set the user as authenticated in security context
                SecurityContextHolder.getContext().setAuthentication(auth);
        }
        chain.doFilter(request, response);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Spring Security (Authorization and Authentication):

@Configuration
@EnableWebSecurity
@RequiredArgsConstructor
public class SpringSecurity {


    private final UserDetailsServiceImpl userDetailsService;
    private final PasswordEncoder passwordEncoder;
    private final JwtFilter jwtFilter;

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        return http
                .authorizeHttpRequests(request -> request
                        .requestMatchers("/public/**").permitAll() // Open access to public endpoints
                        .requestMatchers("/user/**").hasRole("USER") // Requires authentication
                        .requestMatchers("/admin/**").hasRole("ADMIN") // Only allows users with 'ADMIN' role
                )
                .csrf(AbstractHttpConfigurer::disable) // Disable CSRF protection
                .addFilterBefore(jwtFilter, UsernamePasswordAuthenticationFilter.class) // Add your custom JWT filter before the default UsernamePasswordAuthenticationFilter
                .build();
    }

    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration auth) throws Exception {
        return auth.getAuthenticationManager();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Public Controller ( creating token / adding user ):

@RestController
@RequestMapping("/public")
@Slf4j
@RequiredArgsConstructor
public class PublicController {

    private final AuthenticationManager authenticationManager;
    private final UserDetailsServiceImpl userDetailsService;
    private final UserService userService;\
    private final JwtUtil jwtUtil;

    //Create the user and store in the DB with username and password
    @PostMapping("/signup")
    public void signup(@RequestBody User user) {
        userService.saveNewUser(user);
    }

    //Client sends the username and password to validate himself and creates the token
    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody User user) {
        try{
            authenticationManager.authenticate(new UsernamePasswordAuthenticationToken(user.getUsername(), user.getPassword()));
            String token = jwtUtil.generateToken(user.getUsername());
            return new ResponseEntity<>(token, HttpStatus.OK);
        }catch (Exception e){
            log.error("Exception occurred while createAuthenticationToken ", e);
            return new ResponseEntity<>("Incorrect username or password", HttpStatus.BAD_REQUEST);
        }
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------