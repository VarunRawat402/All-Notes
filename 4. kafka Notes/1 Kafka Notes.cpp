------------------------------------------------------------------------------------------------------------------------------------------------
KAFKA Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

→ Kafka is used to send, store, and process data in real time between systems asynchronously.

Problems Before Kafka ( Using REST API calls ):
    → Synchronous communication / Blocking calls
    → Tight coupling between services
    → Data loss if receiver service is down


Advantages of Kafka:
1. Handles millions of messages per second
2. Easy to scale by adding more brokers.
3. Messages are stored on disk and replicated across multiple brokers.
4. Fault Tolerance: (data replicated)
5. Loose coupling between services
6: Communicate asynchronously

------------------------------------------------------------------------------------------------------------------------------------------------

Core Concepts:

Producer -              → Sends messages to Kafka topics.
Consumer -              → Reads messages from Kafka topics.
Topic -                 → A category where messages are stored.
Partition -             → A topic is divided into partitions for parallel processing.
Broker -                → A Kafka server that stores topics and handle message requests.
Cluster -               → A group of Kafka brokers working together for scalability and fault tolerance.
Zookeeper -             → Manages Kafka brokers, leader election, and metadata.
Consumer Group -        → A group of consumers that consume messages from topics.
Replication Factor -    → The number of copies of each partition maintained across different brokers for fault tolerance.
Leader -                → The broker who writes the message and replicates to followers.
Follower -              → The broker who replicates data from the leader.

------------------------------------------------------------------------------------------------------------------------------------------------

Zookeeper:

→ Manages Kafka brokers (keeps track of which brokers are alive).
→ Manages leader election
→ Stores metadata (e.g., topic configurations, ACLs).

→ Zookeeper is depricated in newer versions of Kafka.
→ In newer versions (Kafka 3.0+), Kafka Raft is used.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Connect
    → It is used to send data from external systems to kafka and from kafka to external systems.
    → MySQL → Kafka → Elasticsearch
    → Eliminates the need to write custom producer/consumer code

Key Components
Connector           →  Defines what system to connect to
Source Connector    →  External system → Kafka
Sink Connector      →  Kafka → External system
Worker              →  The process that runs the connectors, handling data movement.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Streams
    → It is used to process data inside Kafka using Java
    → It allows you to transform, filter, aggregate, and join data using a simple API.

------------------------------------------------------------------------------------------------------------------------------------------------

Normal Partitioning :
    → If no key is provided, Kafka randomly assigns messages to partitions.
    → Good for even distribution of messages.

Key Bases Partitioning :
    → If a producer sends a message with a key ("userId"), 
    → Messages with the same key always go to the same partition in same order.
    → Useful when order matters

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Offset:
    → It is a position of a consumer in a Kafka partition
    → It is used to track upto which message consumer has read in a Kafka partition.
    → Stored in Kafka internal topic: __consumer_offsets
    → If a consumer restarts, it can resume from last committed offset.
    → If a consumer crashes, another consumer in the same group can take over from the last committed offset.
    → Consumer commits the Offset
    → Broker stores the Offset
    → Consumer Group manages the Offset

------------------------------------------------------------------------------------------------------------------------------------------------

Offset Management:

1. Auto commit:
    → Kafka commits offsets automatically
    → enable.auto.commit=true

2. Manual commit (recommended):
    → Developers can manually commit offsets (enable.auto.commit=false).
    → Useful when ensuring messages are processed successfully before committing.
    → consumer.commitSync();
    → consumer.commitAsync();

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Group:
    → A Consumer Group is a group of consumers who do same operation and work together to process a Kafka topic.

→ 1 consumer can read multiple partitions
→ 1 partition can be read by only one consumer in same group
→ 2 consumers of same group reading same partition → duplicate work

------------------------------------------------------------------------------------------------------------------------------------------------

Commit Log:
    → Each partition is basically a commit log.
    → New messages are always appended at the end.
    → Messages are never modified or deleted manually

------------------------------------------------------------------------------------------------------------------------------------------------

Segments:
    → Each partition is divided into segments.
    → Kafka stores messages in segments which is a actual disk file.
    → When a segment reaches a size, a new segment is created.

------------------------------------------------------------------------------------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Cluster:
    → It is a group of kakfa brokers 

//Create Multiple Brokers
1: Create multiple server.properties
2: Change:
    broker.id
    port
    log.dirs
3: Start brokers

------------------------------------------------------------------------------------------------------------------------------------------------

Leader:
    → Writes data
    → Replicates to followers
    → Confirms write from followers

→ Without a leader, producer would have to write to multiple brokers, slowing everything down!
→ Producer sends data to only Leader
Replication factor = 2
    → Means topic is replicated on 2 brokers

Ex:
User-Topic, replication factor = 2, partition = 2
user-topic is replicated on 2 brokers with 2 partitions
Partition 1: Broker 1 (Leader), Broker 2 (Follower)
Partition 2: Broker 2 (Leader), Broker 1 (Follower)

------------------------------------------------------------------------------------------------------------------------------------------------

ISR (In-Sync Replicas):
    → Replicas that are fully in sync with the leader

Only replicas in ISR:
    → Receive data
    → Can become leader

If a follower:
    → Is slow
    → Stops responding
    → Kafka removes it from ISR

Why ISR Matters
    → Prevents data loss
    → Ensures only up-to-date replicas become leader
    → Improves reliability during broker failure

------------------------------------------------------------------------------------------------------------------------------------------------
