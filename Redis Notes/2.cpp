--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to do caching the spring boot using redis:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Manual Caching:

1: Add redis dependency in the pom.xml
2: Add the redis configuration in the application.properties file
3: Create a RedisTemplate bean to interact with Redis and configure serializers.
4: Create a CacheRepository class to perform cache operations (save, get, delete).es
5: Use the repository class inside the service layer to store and retrieve cached data.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:

@Bean
public RedisTemplate<String, Object> redisTemplate(RedisConnectionFactory redisConnectionFactory) {
    RedisTemplate<String, Object> template = new RedisTemplate<>();
    template.setConnectionFactory(redisConnectionFactory);
    
    // Key serializer - String for all keys
    template.setKeySerializer(new StringRedisSerializer());
    template.setHashKeySerializer(new StringRedisSerializer());
    
    // Value serializer - JSON for better compatibility and security
    template.setValueSerializer(jsonRedisSerializer());
    template.setHashValueSerializer(jsonRedisSerializer());
    
    // Enable transaction support
    template.setEnableTransactionSupport(true);
    
    return template;
}

@Repository
public class UserCacheRepository {

    //Prefix value
    private final String USER_KEY_PREFIX = "usr::";

    @Autowired
    RedisTemplate<String,Object> redisTemplate;

    //Set user data in cache using RedisTemplate
    public void set(User user){
        String key = getKey(user.getUsername());
        redisTemplate.opsForValue().set(key,user,24, TimeUnit.HOURS);
    }

    //Get User data from cache using RedisTemplate
    public User get(String username){
        String key = getKey(username);
        return (User) redisTemplate.opsForValue().get(key);
    }

    //Create key with prefix
    public String getKey(String username){
        return USER_KEY_PREFIX+username;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Declarative Caching:

1: Add Redis dependency in pom.xml.
2: Add Redis configuration in application.properties.
3: Enable caching in the main class using @EnableCaching.
4: Create a configuration class to define RedisConnectionFactory, RedisCacheManager, and RedisCacheConfiguration.
5: Use caching annotations like @Cacheable, @CachePut, @CacheEvict on service methods.

RedisConnectionFactory:
Creates and manages connections to Redis.
If Redis host/port is set in application.properties, Spring auto-configures the factory.
If custom settings are required, define a bean manually.

RedisCacheConfiguration:
Defines cache settings such as TTL, key prefix, and serializers.
You can override the default configuration by exposing a bean.

RedisCacheManager:
Controls creation, update, and deletion of cache entries.
Takes RedisConnectionFactory and RedisCacheConfiguration as inputs.
Used internally when you apply annotations like @Cacheable.

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