-----------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot + Redis
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. @Cacheable:
    → Cache hit  → method NOT executed
    → Cache miss → method executed → result cached

@Cacheable(value = "users", key = "#id")
public User getUser(Long id) {
    return userRepository.findById(id);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. @CachePut:
    → Used for Update/write operations
    → Method always executes  →  Cache always updated

@CachePut(value = "users", key = "#user.id")
public User updateUser(User user) {
    return userRepository.save(user);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. @CacheEvict:
    → Removes data from cache
    → Used when deleting data or when cache becomes stale

@CacheEvict(value = "users", key = "#id")
public void deleteUser(Long id) {
    userRepository.deleteById(id);
}

beforeInvocation = true:
    Cache removed before method runs
    Useful if method may throw an exception

-----------------------------------------------------------------------------------------------------------------------------------------------------

4. @Caching:
    → Combine multiple cache actions
    → One method affects multiple caches
    → Deletes cache from both users and userList

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
    → Reduce repetition
    → Common cache name across service

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

