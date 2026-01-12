------------------------------------------------------------------------------------------------------------------------------------------------
SpringBoot + Redis
------------------------------------------------------------------------------------------------------------------------------------------------

1. @Cacheable:
    Caches the result of a method. 
    If the method is called again with the same key, the cached value is returned instead of executing the method.

value   → Cache name
key     → Cache key
Cached value  → Method return value (usually DB data)

@Cacheable(value = "users", key = "#id")
public User getUserById(Long id) {
    // This method will only execute if the user is not in cache
    return userRepository.findById(id).orElse(null);
}

------------------------------------------------------------------------------------------------------------------------------------------------

2. @CachePut:
Always executes the method, and the result is put into cache.
Used when saving or updating data

@CachePut(value = "users", key = "#user.id")
public User updateUser(User user) {
    return userRepository.save(user);
}

------------------------------------------------------------------------------------------------------------------------------------------------

3. @CacheEvict:

Removes data from cache
Used when deleting data or when cache becomes stale

@CacheEvict(value = "users", key = "#id")
public void deleteUser(Long id) {
    userRepository.deleteById(id);
}

beforeInvocation = true:
    Cache removed before method runs
    Useful if method may throw an exception

------------------------------------------------------------------------------------------------------------------------------------------------
