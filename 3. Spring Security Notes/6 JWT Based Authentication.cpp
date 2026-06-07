-----------------------------------------------------------------------------------------------------------------------------------------------------
Jwt Implementation using JJWT:
-----------------------------------------------------------------------------------------------------------------------------------------------------

JWTS (jjwt library):
    → External library, more manual control.
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

    // Generate token
    public String generateToken(String username) {
        return Jwts.builder()
                .subject(username)
                .issuedAt(new Date())
                .expiration(new Date(System.currentTimeMillis() + 1000 * 60 * 50))
                .signWith(signingKey)
                .compact();
    }

    //Parse and validate token (signature + expiration automatically checked)
    private Claims extractAllClaims(String token) {
        return Jwts.parser()
                .verifyWith(signingKey)
                .build()
                .parseSignedClaims(token)
                .getPayload();
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

    //Extract username
    public String extractUsername(String token) {
        return extractAllClaims(token).getSubject();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Filter ( Validate the Token and grant access ):

public class JwtFilter extends OncePerRequestFilter {           //OncePerRequestFilter : Pass the request only one time
   
    private final UserDetailsService userDetailsService;
    private final JwtUtil jwtUtil;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws ServletException, IOException {

        try {
            String authHeader = request.getHeader("Authorization");
            String jwtToken = null;
            String username = null;

            if (StringUtils.hasText(authHeader) && authHeader.startsWith("Bearer ")) {
                jwtToken = authHeader.substring(7);
                username = jwtUtil.extractUsername(jwtToken);     
            }

            if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {

                // Load user details from DB using username extracted from JWT
                UserDetails userDetails = userDetailsService.loadUserByUsername(username);

                // Create authenticated token with userDetails + authorities (3 args = already authenticated, no need to validate again)
                UsernamePasswordAuthenticationToken authentication = new UsernamePasswordAuthenticationToken(userDetails, null, userDetails.getAuthorities());

                // Attach request metadata (IP address, session ID) to the authentication object
                authentication.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

                // Store authentication in SecurityContext → Spring now knows who the current user is
                SecurityContextHolder.getContext().setAuthentication(authentication);

            }
            
        } catch (Exception e) { 
            logger.error("JWT Authentication failed for {}: {}", requestUri, e.getMessage());
        }

        filterChain.doFilter(request, response);
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