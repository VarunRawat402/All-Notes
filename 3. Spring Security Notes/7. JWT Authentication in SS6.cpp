-----------------------------------------------------------------------------------------------------------------------------------------------------
JWT TOKEN IN SS6:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Nimbus:
    → Spring Security 6 uses Nimbus for jwt implementation
    → JwtEncoder and JwtDecoder are Interfaces
    → Nimbus is underlying implementation 

Nimbus Supports:
    → OAuth2 Server
    → Production Grade Security
    → Standard level JWT Validation
    → Key Rotation
    → RSA / HMAC Algo

Dependency:
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-oauth2-resource-server</artifactId>
    </dependency>

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Config ( Encoder and Decoder)
    → Configure JwtEncoder & JwtDecoder with secret key

@Configuration
public class JwtConfig {

    @Value("${spring.security.oauth2.resourceserver.jwt.secret-key}")
    private String jwtSecret;

    @Bean
    public JwtEncoder jwtEncoder() {
        SecretKey key = new SecretKeySpec(jwtSecret.getBytes(), "HmacSHA256");
        return new NimbusJwtEncoder(new ImmutableSecret<>(key));
    }

    @Bean
    public JwtDecoder jwtDecoder() {
        SecretKey key = new SecretKeySpec(jwtSecret.getBytes(), "HmacSHA256");
        return NimbusJwtDecoder.withSecretKey(key).build();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

    //Create JWT Token, called by Login API
    public String generateAccessToken(UserDetails userDetails) {
        return generateToken(userDetails, accessTokenExpiration, "access");
    }

    //create JWT token with claims
    private String generateToken(UserDetails userDetails, long expirationSeconds, String tokenType) {

        Instant now = Instant.now();
        Instant expiry = now.plusSeconds(expirationSeconds);

        var roles = userDetails.getAuthorities().stream().map(GrantedAuthority::getAuthority).collect(Collectors.toList());

        JwtClaimsSet claims = JwtClaimsSet.builder()
                .issuer("my-application")
                .subject(userDetails.getUsername())
                .audience(Arrays.asList("web-app", "mobile-app"))
                .issuedAt(now)
                .expiresAt(expiry)
                .claim("roles", roles)
                .claim("type", tokenType)
                .build();

        Jwt jwt = jwtEncoder.encode(JwtEncoderParameters.from(claims));
        return jwt.getTokenValue();

    }

    //Validate and parse token
    public Jwt validateAndParseToken(String token) {
        try {
            Jwt jwt = jwtDecoder.decode(token);
            return jwt;
        } catch (JwtException e) {
            throw new RuntimeException("Invalid JWT token: " + e.getMessage(), e);
        }
    }

    //Create Refresh Token, called by API
    public String generateRefreshToken(UserDetails userDetails) {
        return generateToken(userDetails, refreshTokenExpiration, "refresh");
    }

    //Extract Username
    public String extractUsername(String token) {
        Jwt jwt = validateAndParseToken(token);
        return jwt.getSubject();
    }

    //Extract user roles
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

-----------------------------------------------------------------------------------------------------------------------------------------------------

JWT Filter:

public class JwtAuthFilter extends OncePerRequestFilter {

    private final JwtService jwtService;
    private final CustomUserDetailsService userDetailsService;

    private boolean isUserValid(UserDetails userDetails) {
        return userDetails.isEnabled() && 
               userDetails.isAccountNonLocked() && 
               userDetails.isAccountNonExpired() && 
               userDetails.isCredentialsNonExpired();
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {

        try {

            String authHeader = request.getHeader("Authorization");
            String jwtToken = null;
            String username = null;

            if (StringUtils.hasText(authHeader) && authHeader.startsWith("Bearer ")) {
                jwtToken = bearerToken.substring(7);
                username = jwtService.extractUsername(jwtToken);     
            }

            if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {

                    UserDetails userDetails = userDetailsService.loadUserByUsername(username);

                    if (isUserValid(userDetails)) {
                        UsernamePasswordAuthenticationToken authentication =  new UsernamePasswordAuthenticationToken(userDetails,null,userDetails.getAuthorities());
                        authentication.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
                        SecurityContextHolder.getContext().setAuthentication(authentication);
                    } else {
                        logger.warn("User account invalid: {}", username);
                    }
            }
        } catch (Exception e) { logger.error("JWT Authentication failed for {}: {}", requestUri, e.getMessage());}
        filterChain.doFilter(request, response);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

