--------------------------------------------------------------------------------------------------------------------------------------------
JWT Implementation:
--------------------------------------------------------------------------------------------------------------------------------------------

Steps to Implement JWT Token:

1: create the sign in key using hash Algorithm
2: create the jwt token using jwts.builder() with custom claims
3: validate and parse the token using jwts.parser()
4: validate the username and expiration date of token
5: login with username and password and validate the user, then create the token
6: create jwtAuthFilter to get the token from header, validate the token and make the user authenticated

--------------------------------------------------------------------------------------------------------------------------------------------

JWT util:

jwts is a library used to create and validate the JWT token

To create the token:
    jwts.builder() is used to create the token 
    add custom claims, subject, issuedAt, expiration, then sign the token and build it

To validate and parse the token:
    jwts.parser() is used to parse the token
    verify the token with sign in key
    parse the claims and get the payload, which is jwt claims

To get expiration, username, claims you can use parse function:

--------------------------------------------------------------------------------------------------------------------------------------------

User Model:

public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    private String username;
    private String password;
    private List<String> roles;
}

--------------------------------------------------------------------------------------------------------------------------------------------

UserService:

@Service
@RequiredArgsConstructor
public class UserService {


    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;

   //Add user in the Repository
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

    public List<User> getAll() {
        return userRepository.findAll();
    }
    public User findByUserName(String username) {
        return userRepository.findByUsername(username);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

UserServiceImplementation:

@Service
@RequiredArgsConstructor
public class UserDetailsServiceImpl implements UserDetailsService {

    private finalUserRepository userRepository;

    //Fetch the user from repository and validate it
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

--------------------------------------------------------------------------------------------------------------------------------------------

Spring Security (Authorization and Authentication):

@Configuration
@EnableWebSecurity
@RequiredArgsConstructor
public class SpringSecurity {


    private final UserDetailsServiceImpl userDetailsService;
    private final PasswordEncoder passwordEncoder;
    private final JwtFilter jwtFilter;

    //SecurityFilterChain for authorization of request
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

    //This verifies the user if it's valid or not with the help of loadUserByUsername()
    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration auth) throws Exception {
        return auth.getAuthenticationManager();
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

JWT Util ( Extracting datas and creating tokens ):

@Component
public class JwtUtil {


    //Secret Key in String
    private String SECRET_KEY = "TaK+HaV^uvCHEFsEVfypW#7g9^k*Z8$V";

    //String key converted into SecretKey object using Algorithm
    private SecretKey getSigningKey() {
        return Keys.hmacShaKeyFor(SECRET_KEY.getBytes());
    }

    //validate and parse the token
    private Claims extractAllClaims(String token) {
        return Jwts.parser()
                .verifyWith(getSigningKey())
                .build()
                .parseSignedClaims(token)
                .getPayload();
    }

    //Extract Username from token
    public String extractUsername(String token) {
        Claims claims = extractAllClaims(token);
        return claims.getSubject();
    }

    //Check if token Expired
    private Boolean isTokenExpired(String token) {
        return extractAllClaims(token).getExpiration().before(new Date());
    }

    //Check if token is valid or not
    public Boolean validateToken(String token) {
        return !isTokenExpired(token);
    }

    //Create claims and token
    public String generateToken(String username) {
        Map<String, Object> claims = new HashMap<>();
        return createToken(claims, username);
    }

    //Create the token using claims and key
    private String createToken(Map<String, Object> claims, String subject) {
        return Jwts.builder()
                .claims(claims)
                .subject(subject)
                .header().empty().add("typ","JWT")
                .and()
                .issuedAt(new Date(System.currentTimeMillis()))
                .expiration(new Date(System.currentTimeMillis() + 1000 * 60 * 50)) // 50 minutes expiration time
                .signWith(getSigningKey())
                .compact();
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

JWT Filter ( Validate the Token and grant access ):

@Component
@RequiredArgsConstructor
public class JwtFilter extends OncePerRequestFilter {           //OncePerRequestFilter : Pass the request only one time
   
    private final UserDetailsService userDetailsService;
    private final JwtUtil jwtUtil;

    //This will be automatically called to validate the user through token
    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws ServletException, IOException {

        //Extract header from request
        String authorizationHeader = request.getHeader("Authorization");
        String username = null;
        String jwt = null;

        //Extract the token if header is not null and starts with bearer
        //Extract username from the token
        if (authorizationHeader != null && authorizationHeader.startsWith("Bearer ")) {
            jwt = authorizationHeader.substring(7);
            username = jwtUtil.extractUsername(jwt);
        }

        //If username is not null fetch the user from repository
        //Validate the token
        //If token is valid set the user as authenticated user
        if (username != null) {
            UserDetails userDetails = userDetailsService.loadUserByUsername(username);
            if (jwtUtil.validateToken(jwt)) {

                //Creates a UsernamePasswordAuthenticationToken with user details
                //This object is used to validate the user by passing username, password and roles
                //Since we already validated the user we will use it to make the user authenticated
                UsernamePasswordAuthenticationToken auth = new UsernamePasswordAuthenticationToken(userDetails, null, userDetails.getAuthorities());

                //Extracts extra details (IP address, session ID) from HttpServletRequest.
                //Set all the extracted details in the auth object
                auth.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

                //Sets the user as authenticated in the spring security context
                //Now this user can act as a authenticated user
                SecurityContextHolder.getContext().setAuthentication(auth);
            }
        }
        //Pass the request to the next filter chain
        chain.doFilter(request, response);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

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
            authenticationManager.authenticate(
                    new UsernamePasswordAuthenticationToken(user.getUsername(), user.getPassword()));
            String token = jwtUtil.generateToken(user.getUsername());
            return new ResponseEntity<>(token, HttpStatus.OK);
        }catch (Exception e){
            log.error("Exception occurred while createAuthenticationToken ", e);
            return new ResponseEntity<>("Incorrect username or password", HttpStatus.BAD_REQUEST);
        }
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------