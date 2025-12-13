------------------------------------------------------------------------------------------------------------------------------------------------
Redis Cache Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

1. @Cacheable:
Caches the result of a method. 
If the method is called again with the same parameters, the cached value is returned instead of executing the method.

value = name of the cache
key = key of the cache 
value = data fetched from the database

@Cacheable(value = "users", key = "#id")
public User getUserById(Long id) {
    // This method will only execute if the user is not in cache
    return userRepository.findById(id).orElse(null);
}

------------------------------------------------------------------------------------------------------------------------------------------------

2. @CachePut:
Updates the cache with the method result. 
The method is always executed, and the result is put into cache.
When updating or saving data, so cache stays in sync with DB.

@CachePut(value = "users", key = "#user.id")
public User updateUser(User user) {
    return userRepository.save(user);
}

------------------------------------------------------------------------------------------------------------------------------------------------

3. @CacheEvict:

Removes an entry from the cache.
Deleting data or when cached data becomes stale.

@CacheEvict(value = "users", key = "#id")
public void deleteUser(Long id) {
    userRepository.deleteById(id);
}

beforeInvocation = true → Evicts cache before method execution (useful if the method throws exception).

------------------------------------------------------------------------------------------------------------------------------------------------
