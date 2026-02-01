--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Caching in Spring Boot using Redis:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Manual Caching (RedisTemplate):

1: Add Redis dependency in pom.xml
2: Configure Redis in application.properties
3: Create RedisTemplate with proper serializers
4: Create a cache repository for cache operations
5: Use cache in service layer

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:

@Bean
public RedisTemplate<String, Object> redisTemplate(RedisConnectionFactory redisConnectionFactory) {

    RedisTemplate<String, Object> template = new RedisTemplate<>();
    template.setConnectionFactory(redisConnectionFactory);

    // Key serializers
    template.setKeySerializer(new StringRedisSerializer());
    template.setHashKeySerializer(new StringRedisSerializer());

    // Value serializers (JSON)
    template.setValueSerializer(jsonRedisSerializer());
    template.setHashValueSerializer(jsonRedisSerializer());

    // Enable Redis transactions (optional)
    template.setEnableTransactionSupport(true);

    return template;
}


@Repository
public class UserCacheRepository {

    @Autowired
    private RedisTemplate<String, Object> redisTemplate;

    private static final String USER_KEY_PREFIX = "usr::";

    private String getKey(String username) {
        return USER_KEY_PREFIX + username;
    }

    public void set(User user) {
        String key = getKey(user.getUsername());
        redisTemplate.opsForValue().set(key, user, 24, TimeUnit.HOURS);
    }

    public User get(String username) {
        String key = getKey(username);
        return (User) redisTemplate.opsForValue().get(key);
    }

    public void delete(String username) {
        redisTemplate.delete(getKey(username));
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Declarative Caching:

1: Add Redis dependency
2: Configure Redis in application.properties
3: Enable caching in the main class using @EnableCaching.
4: Create a configuration class to define RedisConnectionFactory, RedisCacheManager, and RedisCacheConfiguration.
5: Use caching annotations

RedisConnectionFactory:
    → hostname, port etc are configured.
    → Automatically created if configured in application.properties
    → If not setup manually

RedisCacheConfiguration:
    → Defines cache settings such as TTL, key prefix, and serializers.

RedisCacheManager:
    → Uses RedisConnectionFactory and RedisCacheManager manage redis
    → Used internally when you apply annotations like @Cacheable.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:

//Redis Cache Manager:
//Use RedisConnectionFactory and RedisCacheConfiguration to set the connection and cache settings.
@Bean
public RedisCacheManager cacheManager(RedisConnectionFactory redisConnectionFactory) {
    return RedisCacheManager.builder(redisConnectionFactory)
            .cacheDefaults(cacheConfiguration())
            .transactionAware()
            .build();
}

//RedisCacheConfiguration:
//Use it to configure the cache settings- time to live (TTL), key prefix, serialization etc.
private RedisCacheConfiguration cacheConfiguration() {
    return RedisCacheConfiguration.defaultCacheConfig()
            .entryTtl(Duration.ofMinutes(30)) // Default TTL
            .disableCachingNullValues()
            .serializeKeysWith(RedisSerializationContext.SerializationPair
                    .fromSerializer(new StringRedisSerializer()))
            .serializeValuesWith(RedisSerializationContext.SerializationPair
                    .fromSerializer(jsonRedisSerializer()));
}


//RedisConnectionFactory:
//Use this if properties are not set in the application.properties file.
//It is used to set the port, host, and other connection properties.
@Bean
public RedisConnectionFactory redisConnectionFactory() {
    LettuceConnectionFactory factory = new LettuceConnectionFactory();
    factory.setHostName("localhost");
    factory.setPort(6379);
    factory.setTimeout(Duration.ofSeconds(30));
    return factory;
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Redis Configuration Properties Using Application.properties:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Boot auto-configures:
    RedisConnectionFactory, RedisCacheManager, RedisTemplate

spring.data.redis.host=localhost                            //Basic Redis connection
spring.data.redis.port=6379
spring.data.redis.timeout=30s

spring.data.redis.password=redisPassword                    //If Redis requires authentication

spring.data.redis.ssl.enabled=true                          //SSL (cloud Redis)

spring.data.redis.lettuce.pool.max-active=16                //Most companies tune this.
spring.data.redis.lettuce.pool.max-idle=8
spring.data.redis.lettuce.pool.min-idle=4
spring.data.redis.lettuce.pool.max-wait=5s

spring.cache.type=redis                                     //Enable Caching (NO Java code needed)

spring.cache.redis.time-to-live=30m                         //Global default TTL

spring.cache.redis.key-prefix=app-name::                    //Key prefix (VERY IMPORTANT)
spring.cache.redis.use-key-prefix=true

spring.cache.redis.cache-null-values=false                  //Null value handling

spring.cache.redis.key-serializer=org.springframework.data.redis.serializer.StringRedisSerializer                           //Serialization
spring.cache.redis.value-serializer=org.springframework.data.redis.serializer.GenericJackson2JsonRedisSerializer

spring.cache.cache-names=users,orders,products              //Cache Names

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DEV Configuration:

application-dev.properties:
spring.data.redis.host=localhost
spring.data.redis.port=6379
spring.cache.redis.time-to-live=10m

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PROD Configuration:

application-prod.properties:
spring.data.redis.host=prod-redis.internal
spring.data.redis.port=6380
spring.data.redis.password=${REDIS_PASSWORD}
spring.cache.redis.time-to-live=1h
spring.data.redis.ssl.enabled=true

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Secrets via:
    Env variables
    Vault
    Kubernetes secrets

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------