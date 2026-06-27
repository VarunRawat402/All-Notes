-----------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot + Redis
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. @Cacheable:
    → Used for read operations
    → Cache hit  → Method not executed
    → Cache miss → Method executes and result is cached

@Cacheable(value = "users", key = "#id")
public User getUser(Long id) {
    return userRepository.findById(id);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. @CachePut:
    → Used for update operations
    → Method always executes
    → Cache is updated with the latest result

@CachePut(value = "users", key = "#user.id")
public User updateUser(User user) {
    return userRepository.save(user);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. @CacheEvict:
    → Removes data from cache
    → Used when data is deleted or becomes stale

@CacheEvict(value = "users", key = "#id")
public void deleteUser(Long id) {
    userRepository.deleteById(id);
}

beforeInvocation = true:
    Cache removed before method runs
    Useful if method may throw an exception

-----------------------------------------------------------------------------------------------------------------------------------------------------

4. @Caching:
    → Combines multiple cache operations
    → Useful when a method affects multiple caches

@Caching(
   evict = {
      @CacheEvict(value = "users", key = "#id"),
      @CacheEvict(value = "userList", allEntries = true)
   }
)
public void deleteUser(Long id) {
    userRepository.deleteById(id);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

5. @CacheConfig:
    → Defines common cache configuration at class level
    → Reduces repetition

@CacheConfig(cacheNames = "users")
@Service
public class UserService { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

6. Conditional Attributes:

1: Condition:
    → Cache only if condition is true
    → @Cacheable(value = "users", key = "#id", condition = "#id > 0")

2: unless:
    → Dont cache if condition is true
    → @Cacheable(value = "users", key = "#id", unless = "#result == null")

-----------------------------------------------------------------------------------------------------------------------------------------------------

