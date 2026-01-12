------------------------------------------------------------------------------------------------------------------------------------------------
Redis Interview Questions:
------------------------------------------------------------------------------------------------------------------------------------------------

What is Redis:
Redis is an in-memory data store that can be used as a database, cache, and message broker.

------------------------------------------------------------------------------------------------------------------------------------------------

Why Redis is fast:

In-memory storage:
Redis stores all data in RAM, not on disk. 
Accessing memory is thousands of times faster than disk.

Single-threaded: 
Redis uses a single-threaded, non-blocking I/O model
so there is no context switching overhead, making reads/writes extremely fast.

Efficient data structures: 
Redis supports optimized structures like Strings, Hashes, Lists, Sets, Sorted Sets
which allow operations to run in O(1) or O(log N) time.

Pipelining & batching: 
Redis can handle multiple commands in a single request, reducing network round-trips.

------------------------------------------------------------------------------------------------------------------------------------------------

Redis data structures:

Strings: 
    Cache small objects, counters, tokens, feature flags.

Hashes: 
    Store complex objects like user profiles or cart items.

Lists: 
    Implement queues for background jobs, notifications.

Sets / Sorted Sets: 
    Leaderboards, unique collections, real-time analytics.

Hash Example:
Map<String, Object> user = Map.of("name", "Varun", "age", 25);
redisTemplate.opsForHash().putAll("user:1001", user);

List Example:
redisTemplate.opsForList().rightPush("queue:orders", orderId);
String orderId = (String) redisTemplate.opsForList().leftPop("queue:orders");

------------------------------------------------------------------------------------------------------------------------------------------------

Difference between String and Hash in Redis:

String: 
Stores one value per key.
Caching simple values like session IDs, JWT tokens, feature flags.

Hash:
Stores map or object 
Store user profiles, shopping cart contents, product information.

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Caching Patterns:
Storing frequently accessed data in memory using different patterns for handling cache hits, misses, updates, and expiration.

1: Cache-Aside (Lazy Loading):
Application checks Redis first  →  if key not found   →  fetch from DB  →  populate Redis.

2: Read-Through:
Cache automatically loads from DB on a cache miss

3: Write-Through:
Writes go to both DB and cache simultaneously.

4: Write-back:
Writes go to cache first  →  Redis asynchronously updates the DB later

5: Time-to-Live (TTL):
Cache entries expire automatically after a set time to prevent stale data.

6: Cache Eviction:
Old or less-used keys are removed automatically when memory is full.

------------------------------------------------------------------------------------------------------------------------------------------------

RDB (Redis Database Backup / Snapshotting):

Creates snapshots of the entire dataset at intervals ( every 5 minutes )
Saves to a .rdb file on disk.
Fast for loading large datasets, compact storage.
If Redis crashes, you restore the last snapshot; data between snapshots may be lost.

AOF (Append-Only File):

Appends every write command to a log file (.aof)
On restart, Redis replays the log to reconstruct the dataset.
Slower than RDB, but more durable.

Redis is in-memory, so without RDB/AOF, all data is lost on restart.
RDB: Good for backups, fast startup, minimal performance impact.
AOF: Good for high durability, ensures almost no data loss.
Combination: Many production systems use both RDB + AOF for speed + durability.

Example:
In an e-commerce Spring Boot app:
    Product catalog and less critical data → RDB snapshots.
    Shopping carts, orders, payments → AOF for near-zero data loss.

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Replication:
Copying data from one Redis server (master) to one or more Redis servers (slaves/replicas).

Master handles writes, replicates data to replicas.
Master sends data updates to replicas asynchronously.
Replicas can serve read requests, reducing load on the master.
When a new replica joins, master sends a full snapshot (RDB) first, then streams incremental updates.

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Sentinel:
Continuously monitors Redis master and replicas.

If the master fails:
    Promotes one replica to master automatically.
    Updates other replicas to follow the new master.
    Notifies client applications of the new master address.
    Provides high availability without manual intervention.

Without Sentinel, you have to manual connect to redis master or redis replica
If that specific replica crashes, then data is lost and you need to manually configure again

With Sentinel, You connect to redis and master node through sentienl automatically
Configure reads from replicas using LettuceConnectionFactory
If master fails, it will automatically update to the current master

@Bean
public LettuceConnectionFactory redisConnectionFactory() {
    RedisSentinelConfiguration sentinelConfig = new RedisSentinelConfiguration()
            .master("mymaster")
            .sentinel("127.0.0.1", 26379)
            .sentinel("127.0.0.1", 26380)
            .sentinel("127.0.0.1", 26381);

    LettuceClientConfiguration clientConfig = LettuceClientConfiguration.builder()
            .readFrom(ReadFrom.REPLICA_PREFERRED) // read from replicas if available
            .build();

    return new LettuceConnectionFactory(sentinelConfig, clientConfig);
}

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Locks:
Redis locks are mechanisms to prevent multiple processes or threads from accessing the same resource simultaneously

SET key value NX PX timeout
    NX ensures the key is set only if it doesnt exist (atomic operation).
    EX sets a TTL so the lock auto-expires if the process crashes.


Prevents race conditions in distributed applications.
Ensures mutual exclusion for critical sections
Avoids duplicate processing when multiple instances of a service run concurrently.

Give me example where we use redis locks and how its used 

------------------------------------------------------------------------------------------------------------------------------------------------\

Redis Pub Sub:

Publisher sends messages to a channel.
All subscribers connected at that moment receive the message.
No persistence / No Replay
Messages sent while a subscriber is offline are lost.
Very low latency (<1ms), works entirely in memory.

------------------------------------------------------------------------------------------------------------------------------------------------\

How do you protect DB when Redis is down:
When Redis goes down, the cache layer is unavailable, and all requests may hit the database directly.

Serve DB data safely without crashing the app.
Limit requests to DB per user
Use Ciruit Breaker pattern to avoid overwhelming DB

------------------------------------------------------------------------------------------------------------------------------------------------

Cache Double Delete Strategy:

T1: UPDATE user (uncommitted)
T2: SELECT user → A
T1: COMMIT
T1: DELETE cache
T2: PUT A in cache  ❌ (AFTER delete)

So Delete cache 2 times:

@Transactional
public void updateUser(User user) {
    userRepo.save(user);          // 1. DB update
    redisTemplate.delete(key);    // 2. First delete

    Executors.newSingleThreadScheduledExecutor()
        .schedule(() -> redisTemplate.delete(key),
                  500, TimeUnit.MILLISECONDS); // 3–4
}

------------------------------------------------------------------------------------------------------------------------------------------------

