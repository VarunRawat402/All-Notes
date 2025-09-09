--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to do caching the spring boot using redis:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Manual Caching:
1: Add redis dependency in the pom.xml
2: Add the redis configuration in the application.properties file
3: Create RedisTemplate bean to interact with the Redis server, and configure it
4: Crete a cacheRepository class to perform cache operations, like saving, retrieving, and deleting cache entries
5: Use the cacheRepository class in your service layer to cache data as needed

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
1: Add the dependency of redis in the pom.xml
2: Add the redis configuration in the application.properties file
3: Enable caching in your Spring Boot application by adding the @EnableCaching annotation to your main
4: Create a cacheConfig class to configure the RedisConnectionFactory, RedisCacheManager , RedisCacheConfiguration 
5: Use caching annotations like @Cacheable, @CachePut, and @CacheEvict on your service methods to manage caching automatically

RedisConnectionFactory:
It is used to create connections to the Redis server.
It is used to set the port, host, and other connection properties.
If the properties are set in the application.properties file, then it will automatically create the connection factory.
If you want to customize the connection, you can create a bean of RedisConnectionFactory in your configuration class.

RedisCacheConfiguration:
It is used to configure the cache settings- time to live (TTL), key prefix, serialization etc.
You can create a bean of RedisCacheConfiguration in your configuration class to customize the cache settings.

RedisCacheManager:
It is used to manager the cache operations.
It is used to create, update, and delete cache entries.
It takes RedisConnectionFactory and RedisCacheConfiguration as input parameters to set the connection and cache settings.
You can use @Cacheable, @CachePut, and @CacheEvict annotations to manage the cache operations automatically.

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