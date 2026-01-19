------------------------------------------------------------------------------------------------------------------------------------------------
Redis Interview Questions:
------------------------------------------------------------------------------------------------------------------------------------------------

What is Redis:
→ In-memory data store
→ Used as database, cache, and message broker

------------------------------------------------------------------------------------------------------------------------------------------------

Why Redis is fast:

In-memory storage:
→ Data stored in RAM (not disk)
→Accessing memory is thousands of times faster than disk.

Single-threaded: 
→ Single-threaded, non-blocking I/O
→ No context switching
→ Very fast reads & writes

Efficient data structures: 
→ Redis supports optimized structures like Strings, Hashes, Lists, Sets, Sorted Sets
→ Operations run in O(1) or O(log N)

Pipelining & batching: 
→ Redis can handle multiple commands in a single request, reducing network round-trips.

------------------------------------------------------------------------------------------------------------------------------------------------

Redis data structures:

Strings: 
→ Cache small values
→ Counters, tokens, feature flags

Hashes: 
→ Store objects / maps
→ User profiles, cart items

Lists: 
→ Queues
→ Background jobs, notifications

Sets / Sorted Sets: 
→ Unique values, rankings
→ Leaderboards, analytics

Hash Example:
Map<String, Object> user = Map.of("name", "Varun", "age", 25);
redisTemplate.opsForHash().putAll("user:1001", user);

List Example:
redisTemplate.opsForList().rightPush("queue:orders", orderId);
String orderId = (String) redisTemplate.opsForList().leftPop("queue:orders");

------------------------------------------------------------------------------------------------------------------------------------------------

Difference between String and Hash in Redis:

String: 
→ One value per key
→ Session IDs, JWT tokens, flags

Hash:
→ Multiple fields per key
→ User profiles, cart data, product info

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Caching Patterns:

1: Cache-Aside (Lazy Loading):
Application checks Redis first  →  if key not found   →  fetch from DB  →  populate Redis.
It is implemented by manually putting and getting the cache in method

2: Read-Through:
Cache automatically loads from DB on a cache miss
It is implemented using @Cacheable annotation

3: Write-Through:
Writes go to both DB and cache simultaneously.

4: Write-back:
Writes go to cache first  →  Redis asynchronously updates the DB later

5: Time-to-Live (TTL):
Cache entries expire automatically after a set time to prevent stale data.

6: Cache Eviction:
Old or less-used keys are removed automatically when memory is full.

------------------------------------------------------------------------------------------------------------------------------------------------

→ Redis is in-memory
→ Without persistence → all data lost on restart

RDB (Redis Database Backup / Snapshotting):

Creates snapshots of the entire dataset at intervals ( every 5 minutes )
Saves to a .rdb file on disk.
Fast for loading large datasets, compact storage.
If Redis crashes, you restore the last snapshot; data between snapshots may be lost.

AOF (Append-Only File):

Appends every write command to a log file (.aof)
On restart, Redis replays the log to reconstruct the dataset.
Slower than RDB, but more durable.

------------------------------------------------------------------------------------------------------------------------------------------------

RDB: 
    → Good for backups
    → Fast restart
    → Minimal performance impact
    → Some data loss possible

AOF:
    → Logs every write operation
    → High durability
    → Near-zero data loss
    → Slight performance overhead

Combination: Many production systems use both RDB + AOF for speed + durability.

RDB + AOF (Production Best Practice):
→ RDB → fast recovery
→ AOF → strong durability

Example (E-commerce App):
→ Product catalog / less critical data → RDB
→ Cart, orders, payments → AOF

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Replication:
    Copies data from master → replicas

How it works:
→ Master handles all writes
→ Replicates data to replicas asynchronously
→ Replicas handle read requests → reduces master load

New replica joining:
→ Master sends full RDB snapshot
→ Then streams incremental updates

------------------------------------------------------------------------------------------------------------------------------------------------

Redis Sentinel:
    Continuously monitors master & replicas

If the master fails:
→ Promotes a replica to master automatically
→ Reconfigures other replicas
→ Notifies clients of new master
→ No manual intervention required
    Promotes one replica to master automatically.
    Updates other replicas to follow the new master.
    Notifies client applications of the new master address.
    Provides high availability without manual intervention.

→ Manual master/replica configuration
→ On failure → downtime + reconfiguration

→ With Sentinel, You connect to redis and master node through sentienl automatically
→ Configure reads from replicas using LettuceConnectionFactory
→ If master fails, it will automatically update to the current master

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
    Used to prevent multiple threads from accessing the same resource simultaneously

Command:
→ SET key value NX PX timeout

Meaning:
→ NX → set only if key does not exist (atomic)
→ PX / EX → TTL → lock auto-expires if process crashes

→ Prevents race conditions in distributed applications.
→ Ensures mutual exclusion for critical sections
→ Avoids duplicate processing when multiple instances of a service run concurrently.

------------------------------------------------------------------------------------------------------------------------------------------------\

Redis Pub Sub:

→ Publisher sends messages to a channel.
→ All subscribers connected at that moment receive the message.
→ No persistence / No Replay
→ Messages sent while a subscriber is offline are lost.
→ Very low latency (<1ms), works entirely in memory.

------------------------------------------------------------------------------------------------------------------------------------------------\

How do you protect DB when Redis is down:
    When Redis goes down, the cache layer is unavailable, and all requests may hit the database directly.

→ Serve DB data safely (fallback logic)
→ Rate limit requests per user
→ Circuit Breaker pattern → prevent DB overload

------------------------------------------------------------------------------------------------------------------------------------------------

Cache Double Delete Strategy:
    Prevents stale cache after DB update

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

