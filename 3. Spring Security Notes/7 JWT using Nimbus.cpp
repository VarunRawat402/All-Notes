-----------------------------------------------------------------------------------------------------------------------------------------------------
JWT TOKEN IN SS6:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Nimbus:
    → Spring Security 6 uses Nimbus for jwt implementation
    → Spring native + less code
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

    //To create JWT token, called by Login API
    public String generateAccessToken(UserDetails userDetails) {
        return generateToken(userDetails, accessTokenExpiration, "access");
    }

    //To create Refresh token, called by Login API
    public String generateRefreshToken(UserDetails userDetails) {
        return generateToken(userDetails, refreshTokenExpiration, "refresh");
    }

    //Generate JWT / Refresh Token
    private String generateToken(UserDetails userDetails, long expirationSeconds, String tokenType) {

        Instant now = Instant.now();
        Instant expiry = now.plusSeconds(expirationSeconds);
        List<String> roles = userDetails.getAuthorities().stream().map(GrantedAuthority::getAuthority).collect(Collectors.toList());

        JwtClaimsSet claims = JwtClaimsSet.builder()
                .subject(userDetails.getUsername())
                .issuedAt(now)
                .expiresAt(expiry)
                .claim("roles", roles)
                .claim("type", tokenType)
                .build();

        Jwt jwt = jwtEncoder.encode(JwtEncoderParameters.from(claims));
        return jwt.getTokenValue();
    }

    //Validate + Parse Token
    public Jwt validateAndParseToken(String token) {
        try {
            Jwt jwt = jwtDecoder.decode(token);
            return jwt;
        } catch (JwtException e) {
            throw new RuntimeException("Invalid JWT token: " + e.getMessage(), e);
        }
    }

    //Extract Username
    public String extractUsername(String token) {
        Jwt jwt = validateAndParseToken(token);
        return jwt.getSubject();
    }

    //Extract Roles
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


-----------------------------------------------------------------------------------------------------------------------------------------------------