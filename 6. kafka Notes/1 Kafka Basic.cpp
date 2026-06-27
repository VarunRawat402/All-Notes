-----------------------------------------------------------------------------------------------------------------------------------------------------
KAFKA Notes:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Used to send, store, process data between systems asynchronously

Problems without Kafka (REST calls):
    → Synchronous → sender waits for receiver → blocking
    → Tight coupling → services depend directly on each other
    → Data loss → if receiver is down → message gone

-----------------------------------------------------------------------------------------------------------------------------------------------------

Advantages of Kafka:

→ Async communication    → sender doesnt wait
→ Loose coupling         → services dont know about each other
→ High throughput        → millions of messages per second
→ Fault tolerant         → messages replicated across brokers
→ Persistent storage     → messages stored on disk, not lost
→ Easy to scale          → add more brokers as load grows

-----------------------------------------------------------------------------------------------------------------------------------------------------

Core Concepts:

Producer          → sends messages to Kafka topics
Consumer          → reads messages from Kafka topics

Topic             → category/channel where messages are stored
Partition         → topic split into partitions enables parallel processing

Broker            → Kafka server that stores topics + handles requests
Cluster           → group of brokers working together 

Zookeeper         → manages brokers, leader election, metadata

Consumer Group    → group of consumers sharing work → each partition read by one consumer in group
Replication Factor→ number of copies of each partition across brokers → fault tolerance

Leader            → broker that handles all reads/writes for a partition
Follower          → broker that replicates data from leader → takes over if leader fails

-----------------------------------------------------------------------------------------------------------------------------------------------------

Zookeeper:

→ Tracks which brokers are alive
→ Manages leader election (picks new leader if current fails)
→ Stores metadata (topic configs, ACLs)
→ Deprecated in Kafka 3.0+ → replaced by Kafka Raft (KRaft)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Connect
    → Move data between Kafka and external systems
    → No need to write custom producer/consumer code

Key Components

Source Connector → MySQL → Kafka
Sink Connector   → Kafka → Elasticsearch
Connector        → defines what system to connect to
Worker           → process that runs connectors + handles data movement

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Streams
    → Process + transform data INSIDE Kafka using Java
    → filter, transform, aggregate, join streams in real time
    → No separate processing cluster needed → runs as Java app

-----------------------------------------------------------------------------------------------------------------------------------------------------

Normal Partitioning :
    → If no key is provided, Kafka randomly assigns messages to partitions.
    → Good for even distribution of messages.
    → Order NOT guaranteed across partitions

Key Bases Partitioning :
    → If a producer sends a message with a key ("userId"), 
    → Messages with the same key always go to the same partition in same order.
    → Use when order matters for related messages

-----------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Offset:
    → It is a position of a consumer in a Kafka partition
    → It is used to track upto which message consumer has read in a Kafka partition.
    → Stored in Kafka internal topic: __consumer_offsets
    → If a consumer restarts, resumes from last committed offset
    → If a consumer crashes, another consumer in same group takes over from last offset

Consumer commits offset → Broker stores it → Consumer Group manages it

-----------------------------------------------------------------------------------------------------------------------------------------------------

Offset Management:

1. Auto commit:
    → Kafka commits offsets automatically
    → enable.auto.commit=true
    → Commits before processing done → message loss on crash

2. Manual commit (recommended):
    → You commit AFTER message is successfully processed
    → enable.auto.commit=false
    → consumer.commitSync()  → waits for confirmation, slower but safe
    → consumer.commitAsync() → doesnt wait, faster but less safe

When to use:
    Auto   → simple use cases, okay with rare duplicates
    Manual → critical data, must ensure processed before committing

-----------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Group:
    → A Consumer Group is a group of consumers who do same operation and work together to process a Kafka topic.

→ 1 consumer can read multiple partitions
→ 1 partition can be read by only one consumer in same group
→ 2 consumers of same group reading same partition → duplicate work

-----------------------------------------------------------------------------------------------------------------------------------------------------

Commit Log:
    → Each partition is an append-only log
    → New messages always added at end
    → Messages never modified or deleted manually

-----------------------------------------------------------------------------------------------------------------------------------------------------

Segments:
    → Partition split into segment files on disk
    → New segment created when current reaches size limit
    → Kafka reads/writes to active segment

-----------------------------------------------------------------------------------------------------------------------------------------------------

Retention Policy:

Time-Based Retention (Default)
    → Delete messages after X time

Size-Based Retention
    → Delete when log size exceeds limit

→ Kafka deletes entire segments, not individual messages.
→ If a segment contains messages beyond the retention period, Kafka deletes it.

Ex:
→ If some messages in the segments are older than expiry time but some are not then 
→ It waits until all messages in the segment exceed the expiry period, then deletes the entire segment.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Cluster:
    → Group of Kafka brokers
    → Provides scalability + fault tolerance

Setup:

1. Create separate server.properties for each broker
2. Change per broker:
    broker.id  → unique ID for each broker
    port       → unique port for each broker
    log.dirs   → unique log directory for each broker
3. Start each broker separately

Why multiple brokers:
    → Partitions distributed across brokers → parallel processing
    → Replicas on different brokers → if one broker fails → others take over

-----------------------------------------------------------------------------------------------------------------------------------------------------

Leader:
    → Handles ALL reads + writes for a partition
    → Replicates data to followers
    → Producer sends data to leader ONLY → leader distributes to followers
    → Without leader → producer would write to all brokers → slow

Replication Factor = 2 → partition copied on 2 brokers

Example (replication=2, partitions=2):
    Partition 1 → Broker 1 (Leader), Broker 2 (Follower)
    Partition 2 → Broker 2 (Leader), Broker 1 (Follower)

-----------------------------------------------------------------------------------------------------------------------------------------------------

ISR (In-Sync Replicas):
    → Set of replicas fully caught up with leader
    → Only ISR members can become new leader if current leader fails

Kafka removes replica from ISR if:
    → Too slow to replicate
    → Stops responding

If a follower:
    → Is slow
    → Stops responding
    → Kafka removes it from ISR

Why ISR matters:
    → Prevents data loss → only up-to-date replica becomes leader
    → Guarantees reliability during broker failure
    → If follower behind on data becomes leader → messages lost 
    → ISR prevents this

-----------------------------------------------------------------------------------------------------------------------------------------------------
