-----------------------------------------------------------------------------------------------------------------------------------------------------
Redis Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

What is Redis:
    → In-memory data storage
    → Can be used as:
        - Database
        - Cache
        - Message Broker

To connect Redis:
	→ redis-cli -h <host-name> -p <port> -a <password>

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why Redis is fast:

1. In-Memory Storage
    → Data is stored in RAM, not disk
    → Memory access is much faster than disk access

2. Single-Threaded Architecture
    → Single-threaded with non-blocking I/O
    → Fast read and write operations

3. Optimized Data Structures
    → Supports Strings, Hashes, Lists, Sets, Sorted Sets
    → Most operations run in O(1) or O(log N)

4. Pipelining & Batching
    → Multiple commands can be sent in one request
    → Reduces network round-trips
    → Improves performance

-----------------------------------------------------------------------------------------------------------------------------------------------------

When Redis Memory Is Full:

1. Increase memory or add Redis nodes
2. Evict existing keys using an eviction policy


Best Practice:
    → Always set an expiry (TTL) for cache
    → Expired keys are automatically removed

-----------------------------------------------------------------------------------------------------------------------------------------------------

Disadvantages:

1. Increased Startup Time
    → Redis loads data from disk into RAM on startup
    → Larger datasets take longer to load

2. Duplicate Storage
    → Same data exists in both RAM and disk

Example:
    → 1 GB data stored on disk
    → On startup, Redis loads it into RAM
    → Total storage used = 1 GB RAM + 1 GB Disk

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis data structures:

1. Strings
    → Store strings using keys
    → Used for counters, tokens, feature flags, cache values

2. Hashes
    → Store data as key-value pairs
    → Used for user profiles, cart data, product info

3. Lists
    → Ordered collection of values
    → Used for queues, background jobs, notifications

4. Sets / Sorted Sets
    → Store unique values
    → Used for leaderboards, rankings, analytics

Examples:

Hash:
Map<String, Object> user = Map.of("name", "Varun", "age", 25);
redisTemplate.opsForHash().putAll("user:1001", user);

List:
redisTemplate.opsForList().rightPush("queue:orders", orderId);
String orderId = (String) redisTemplate.opsForList().leftPop("queue:orders");

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference between String and Hash in Redis:

String: 
    → One value per key
    → Session IDs, JWT tokens, flags

Hash:
    → Multiple fields per key
    → User profiles, cart data, product info

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Caching Patterns:

1: Cache-Aside (Lazy Loading):
    → Check Redis first
    → If cache miss, fetch from DB and store in Redis
    → Application controls cache reads/writes
    → Can be implemented manually or using Spring Cache annotations
    → Redis Miss → DB → Redis → Response

2: Read-Through:
    → Application requests data from cache
    → On cache miss, cache automatically fetches from DB and updates Redis
    → Cache controls data loading
    → Cache Miss → Cache fetches from DB → Redis → Response

3: Write-Through:
    → Write to both Redis and DB at the same time

4: Write-back:
    → Write to Redis first
    → Redis updates DB asynchronously later
    → Faster writes but risk of data loss before DB update

5: Time-to-Live (TTL):
    → Keys expire automatically after a configured time

6: Cache Eviction:
    → Removes old/less-used keys when memory is full based on the configured eviction policy

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Memory:
    → Redis stores data in memory
    → Without persistence, all data is lost on restart

1: RDB (Redis Database Backup / Snapshotting):
    → Creates snapshots of the entire dataset at intervals
    → Stores snapshots in a .rdb file
    → Fast recovery and compact storage
    → Data written after the last snapshot may be lost

2: AOF (Append-Only File):
    → Logs every write operation in a .aof file
    → On restart, Redis replays the log to rebuild data
    → Higher durability than RDB
    → Slightly slower due to write logging

-----------------------------------------------------------------------------------------------------------------------------------------------------

RDB
    → Snapshot-based
    → Fast restart
    → Good for backups
    → Minimal performance impact
    → Some data loss possible

AOF
    → Logs every write
    → High durability
    → Near-zero data loss
    → Slight performance overhead

-----------------------------------------------------------------------------------------------------------------------------------------------------

Combination: 
    → RDB provides fast recovery
    → AOF provides strong durability
    → Commonly used together in production

Example:
→ Product catalog, reference data → RDB
→ Cart, orders, payments → AOF

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Replication:

How it works:
    → Leader handles all writes + reads
    → Data is replicated asynchronously to replicas
    → Replicas mainly handle read requests
    → Reduces load on the leader

Limitations:
    → Replication lag can occur
    → Recent writes may be lost if master fails before replication completes

New replica joining:
    → Master sends full RDB snapshot
    → Then streams incremental updates

Note:
    → Read critical data from master to avoid stale reads due to replication lag.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Sentinel:
    → Monitors master and replicas using heartbeats

If the master fails:
    → Promotes a replica to master
    → Reconfigures other replicas to follow the new master
    → Notifies clients of the new master address
    → No manual intervention required

Without Sentinel:
    → Manual failover and reconfiguration
    → Higher downtime

With Sentinel:
    → Applications connect through Sentinel
    → Sentinel automatically discovers the current master
    → Client configuration is updated automatically after failover

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Locks:
    → Used to ensure only one application instance accesses a shared resource at a time
    → Prevents race conditions in distributed systems

Benefits:
    → Prevents duplicate processing
    → Ensures only one service instance executes a critical operation
    → Useful in distributed applications with multiple service instances

-----------------------------------------------------------------------------------------------------------------------------------------------------

Redis Pub Sub:

→ Publisher sends messages to a channel
→ All subscribers currently connected receive the message
→ No persistence / No Replay
→ Messages sent while a subscriber is down are lost.
→ Very low latency (<1ms), works entirely in memory.

-----------------------------------------------------------------------------------------------------------------------------------------------------

When Redis Is Down:

Problem:
    → Cache becomes unavailable
    → Requests bypass cache and hit the DB directly
    → Can overload the database

Protection Strategies:
    → Fallback to DB reads
    → Rate limit requests
    → Use Circuit Breaker pattern to reduce DB pressure
    → Degrade non-critical features if needed

-----------------------------------------------------------------------------------------------------------------------------------------------------

Cache Double Delete Strategy:
    → Prevent stale data from being written back to cache after a DB update

Problem Scenario:

T1: Update user in DB
T2: Read old user data (before update is committed)
T1: Commit transaction
T1: Delete cache
T2: Writes old data back to cache 

Solution:
    → Delete cache immediately after DB update
    → Delete cache again after a short delay

-----------------------------------------------------------------------------------------------------------------------------------------------------

