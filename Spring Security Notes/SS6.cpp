----------------------------------------------------------------------------------------------------------------------------------------
JWT TOKEN IN SS6:
----------------------------------------------------------------------------------------------------------------------------------------

Dependency:

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-security</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-oauth2-resource-server</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jpa</artifactId>
        </dependency>
    </dependencies>

----------------------------------------------------------------------------------------------------------------------------------------

Application.properties:

spring:
  security:
    oauth2:
      resourceserver:
        jwt:
          # For HS256 (symmetric)
          secret-key: ${JWT_SECRET:mySuperSecretKeyThatIsAtLeast32CharactersLong!12345}
          # Or for RS256 (asymmetric - recommended for production):
          # private-key: classpath:private.pem
          # public-key: classpath:public.pem

jwt:
  access-token-expiration: 900 # 15 minutes in seconds
  refresh-token-expiration: 604800 # 7 days in seconds

logging:
  level:
    com.example.jwt: DEBUG

----------------------------------------------------------------------------------------------------------------------------------------

JWT Config ( Encoder and Decoder)

@Configuration
public class JwtConfig {

    @Value("${spring.security.oauth2.resourceserver.jwt.secret-key}")
    private String jwtSecret;

    /**
     * WHAT IT DOES: Creates JWT encoder for generating tokens
     * SS6: Uses NimbusJwtEncoder with secret key
     */
    @Bean
    public JwtEncoder jwtEncoder() {
        SecretKey key = new SecretKeySpec(jwtSecret.getBytes(), "HmacSHA256");
        return new NimbusJwtEncoder(new ImmutableSecret<>(key));
    }

    /**
     * WHAT IT DOES: Creates JWT decoder for validating tokens
     * SS6: Uses NimbusJwtDecoder with secret key
     */
    @Bean
    public JwtDecoder jwtDecoder() {
        SecretKey key = new SecretKeySpec(jwtSecret.getBytes(), "HmacSHA256");
        return NimbusJwtDecoder.withSecretKey(key).build();
    }
}

----------------------------------------------------------------------------------------------------------------------------------------

Security Config:

@Configuration
@EnableWebSecurity
@EnableMethodSecurity(prePostEnabled = true)
public class SecurityConfig {

    @Autowired
    private final JwtAuthFilter jwtAuthFilter;

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())
            .cors(cors -> cors.configure(http))
            
            .authorizeHttpRequests(authz -> authz
                .requestMatchers("/api/auth/**", "/public/**", "/health").permitAll()
                .requestMatchers("/api/admin/**").hasRole("ADMIN")
                .requestMatchers("/api/user/**").hasAnyRole("USER", "ADMIN")
                .anyRequest().authenticated()
            )
            
            .oauth2ResourceServer(oauth2 -> oauth2
                .jwt(jwt -> jwt.jwtAuthenticationConverter(jwtAuthenticationConverter()))
            )
            
            .sessionManagement(session -> session
                .sessionCreationPolicy(SessionCreationPolicy.STATELESS)
            )
            
            .addFilterBefore(jwtAuthFilter, UsernamePasswordAuthenticationFilter.class);

        return http.build();
    }

    @Bean
    public JwtAuthenticationConverter jwtAuthenticationConverter() {
        JwtGrantedAuthoritiesConverter authoritiesConverter = new JwtGrantedAuthoritiesConverter();
        authoritiesConverter.setAuthorityPrefix("ROLE_");
        authoritiesConverter.setAuthoritiesClaimName("roles");
        
        JwtAuthenticationConverter jwtConverter = new JwtAuthenticationConverter();
        jwtConverter.setJwtGrantedAuthoritiesConverter(authoritiesConverter);
        jwtConverter.setPrincipalClaimName("sub");
        
        return jwtConverter;
    }
}

----------------------------------------------------------------------------------------------------------------------------------------

JWT Util and Service:

@Service
@RequiredArgsConstructor
public class JwtService {

    private final JwtEncoder jwtEncoder;
    private final JwtDecoder jwtDecoder;
    
    @Value("${jwt.access-token-expiration:900}")
    private long accessTokenExpiration;
    
    @Value("${jwt.refresh-token-expiration:604800}")
    private long refreshTokenExpiration;

    //Function to create JWT or Refresh token
    private String generateToken(UserDetails userDetails, long expirationSeconds, String tokenType) {

        Instant now = Instant.now();
        Instant expiry = now.plusSeconds(expirationSeconds);

        //Extract User roles
        var roles = userDetails.getAuthorities().stream()
                .map(GrantedAuthority::getAuthority)
                .collect(Collectors.toList());

        //Build JWT claim using JwtClaimSet
        JwtClaimsSet claims = JwtClaimsSet.builder()
                .issuer("my-application")
                .subject(userDetails.getUsername())
                .audience(Arrays.asList("web-app", "mobile-app"))
                .issuedAt(now)
                .expiresAt(expiry)
                .claim("roles", roles)
                .claim("type", tokenType)
                .build();

        // JwtEncoder automatically signs the claim with the configured private key (RS256)
        Jwt encodedJwt = jwtEncoder.encode(JwtEncoderParameters.from(claims));
        
        return encodedJwt.getTokenValue();
    }

    //Validate and parse the token
    public Jwt validateAndParseToken(String token) {
        try {

            // JwtDecoder automatically verifies signature and expiration
            Jwt jwt = jwtDecoder.decode(token);
            return jwt;

        } catch (JwtException e) {
            throw new RuntimeException("Invalid JWT token: " + e.getMessage(), e);
        }
    }

    //Create JWT Token 
    public String generateAccessToken(UserDetails userDetails) {
        return generateToken(userDetails, accessTokenExpiration, "access");
    }

    //Create Refresh Token
    public String generateRefreshToken(UserDetails userDetails) {
        return generateToken(userDetails, refreshTokenExpiration, "refresh");
    }

    //Extract Username from jwt token
    public String extractUsername(String token) {
        Jwt jwt = validateAndParseToken(token);
        return jwt.getSubject();
    }

    //Extract user roles from jwt token
    public List<String> extractRoles(String token) {
        Jwt jwt = validateAndParseToken(token);
        return jwt.getClaim("roles");
    }

    //Create new JWT token from Refresh token
    public String refreshAccessToken(String refreshToken, UserDetails userDetails) {
        if (!isRefreshToken(refreshToken)) {
            throw new RuntimeException("Invalid refresh token");
        }
        
        // Validate the user still exists and is active
        if (!userDetails.isEnabled()) {
            throw new RuntimeException("User account is disabled");
        }
        
        return generateAccessToken(userDetails);
    }

    //Check if token is refresh token or not
    public boolean isRefreshToken(String token) {
        try {
            Jwt jwt = validateAndParseToken(token);
            return "refresh".equals(jwt.getClaim("type"));
        } catch (Exception e) {
            return false;
        }
    }
}

class JwtValidationException extends RuntimeException {
    public JwtValidationException(String message) {
        super(message);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------

JWT Filter:

@Component
@RequiredArgsConstructor
public class JwtAuthFilter extends OncePerRequestFilter {

    private static final Logger logger = LoggerFactory.getLogger(JwtAuthFilter.class);
    private final JwtService jwtService;
    private final CustomUserDetailsService userDetailsService;

    //Function to extract JWT token from header
    private String extractTokenFromRequest(HttpServletRequest request) {
        String bearerToken = request.getHeader("Authorization");
        
        if (StringUtils.hasText(bearerToken) && bearerToken.startsWith("Bearer ")) {
            return bearerToken.substring(7);
        }
        
        // Also check for token in query parameter (for WebSocket, etc.)
        String queryToken = request.getParameter("token");
        if (StringUtils.hasText(queryToken)) {
            return queryToken;
        }
        
        return null;
    }

    //Function to Check additional user validation
    private boolean isUserValid(UserDetails userDetails) {
        return userDetails.isEnabled() && 
               userDetails.isAccountNonLocked() && 
               userDetails.isAccountNonExpired() && 
               userDetails.isCredentialsNonExpired();
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, 
                                  HttpServletResponse response, 
                                  FilterChain filterChain)
            throws ServletException, IOException {

        try {
            String jwtToken = extractTokenFromRequest(request);
            
            if (StringUtils.hasText(jwtToken)) {            //If token is present
                
                //extractUsername() validates the token and return the username
                String username = jwtService.extractUsername(jwtToken);     
                logger.debug("✅ Token validated for user: {}", username);
                
                if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {
                    UserDetails userDetails = userDetailsService.loadUserByUsername(username);
                    
                    // Additional security checks
                    if (isUserValid(userDetails)) {

                        //create the authentication token and set the user as authenticated
                        UsernamePasswordAuthenticationToken authentication = 
                            new UsernamePasswordAuthenticationToken(userDetails,null,userDetails.getAuthorities());

                        authentication.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
                        SecurityContextHolder.getContext().setAuthentication(authentication);
                    } else {
                        logger.warn("🚫 User account invalid: {}", username);
                    }
                }
            }
            
        } catch (Exception e) {
            logger.error("💥 JWT Authentication failed for {}: {}", requestUri, e.getMessage());
        }

        filterChain.doFilter(request, response);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------