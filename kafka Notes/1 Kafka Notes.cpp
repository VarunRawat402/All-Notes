------------------------------------------------------------------------------------------------------------------------------------------------
KAFKA Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

Kafka is used to send, store, and process data in real time between systems asynchronously.

Problems Before Kafka ( Using REST API calls ):
    Blocking calls (service waits for response)
    Tight coupling between services
    Data loss if receiver service is down


Advantages of Kafka:
1. Handles millions of messages per second
2. Easy to scale by adding more brokers.
3. Messages are stored on disk and replicated across multiple brokers.
4. Fault Tolerance: (data replicated)
5. Loose coupling between services
6: Communicate asynchronously

------------------------------------------------------------------------------------------------------------------------------------------------

Core Concepts:

Producer -              Sends messages to Kafka topics.
Consumer -              Reads messages from Kafka topics.
Topic -                 A category where messages are stored.
Partition -             A topic is divided into partitions for parallel processing.
Broker -                A Kafka server that stores topics and handle message requests.
Cluster -               A group of Kafka brokers working together for scalability and fault tolerance.
Zookeeper -             Manages Kafka brokers, leader election, and metadata.
Offset -                A unique ID assigned to each message in a partition.
Consumer Group -        A group of consumers that consume messages from one or more topics.
Replication Factor -    The number of copies of each partition maintained across different brokers for fault tolerance.
Leader -                The broker responsible for handling read/write requests for a partition.
Follower -              A replica of a partition that stays in sync with the leader.

------------------------------------------------------------------------------------------------------------------------------------------------

Zookeeper:

Manages Kafka brokers (keeps track of which brokers are alive).
Manages leader election
Stores metadata (e.g., topic configurations, ACLs).

Kafka cannot work without Zookeeper (at least in older versions).
In newer versions (Kafka 3.0+), Zookeeper is being replaced by Kafka KRaft mode.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Connect
Kafka Connect is used to move data between Kafka and external systems without writing custom code.
It allows you to ingest (source) and export (sink) data seamlessly.

Key Components
Connector -         A plugin that defines how to interact with an external system (e.g., MySQL, Elasticsearch).
Source Connector -  Pulls data into Kafka from an external system.
Sink Connector -    Pushes data out of Kafka to an external system.
Worker -            The process that runs the connectors, handling data movement.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Streams
Kafka Streams is a Java library for processing Kafka data from Kafka topics. 
It allows you to transform, filter, aggregate, and join data streams using a simple API.

Key Features
Real-time processing -  Processes data as it arrives.
Fault-tolerant -        Ensures reliability even in case of failures.
Scalability -           Distributes workloads across multiple instances.

Basic Kafka Streams Workflow
Read data from a Kafka topic.
Process the data (transform, filter, aggregate, etc.).

Kafka Topic:
Producers send messages to a topic, and consumers read from it.
Messages are stored in topic

Kafka Partition:
A topic is divided into multiple partitions for parallel processing.

------------------------------------------------------------------------------------------------------------------------------------------------

Normal Partitioning :
If no key is provided, Kafka randomly assigns messages to partitions.
Good for even distribution of messages.

Key Bases Partitioning :
If a producer sends a message with a key ("userId"), 
Messages with the same key always go to the same partition.
Useful when order matters

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Offset:

A consumer offset is a unique ID assigned to each message in a partition.
It is used to track which message consumer has read in a Kafka topic.
Stored in internal topic: __consumer_offsets
Updated by Kafka broker

------------------------------------------------------------------------------------------------------------------------------------------------

Offset Management:

Automatic (Default Behavior)
Kafka commits offset automatically
enable.auto.commit=true

Manual Offset Management
Developers can manually commit offsets (enable.auto.commit=false).
Useful when ensuring messages are processed successfully before committing.

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Group:

A Consumer Group is a group of consumers who do same operation and work together to process a Kafka topic.

1 consumer can read multiple partitions
1 partition can be read by only one consumer in same group
2 consumers of same group reading same partition → duplicate work

Key Point:
Each Consumer group has its own offset Value means 
If consumer group A has read till 5 messages, its offset id will be 5
If Consumer grpup B Starts reading from same topic, its offset will be 0 not 5
Consumer group manages the offset not the individual consumers.

------------------------------------------------------------------------------------------------------------------------------------------------

Commit Log:
A commit log is an append-only file in disk where Kafka stores messages in order.
New messages are always appended at the end.
Messages are never modified or deleted manually
Consumers read from the log based on offsets.

Ex:
Offset  Message
0       Order101
1       Order102
2       Order103


------------------------------------------------------------------------------------------------------------------------------------------------

Segments:
Kafka splits log in segments
When a segment reaches a size, a new segment is created.

------------------------------------------------------------------------------------------------------------------------------------------------

Retention Policy:

Time-Based Retention (Default)
    Delete messages after X time

Size-Based Retention
    Delete when log size exceeds limit

Kafka deletes entire segments, not individual messages.
If a segment contains messages beyond the retention period, Kafka deletes it.

Ex:
If some messages in the segments are older than expiry time but some are not then 
it waits until all messages in the segment exceed the expiry period, then deletes the entire segment.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Cluster:
It is a group of kakfa brokers 

//Create Multiple Brokers
1: Create multiple server.properties
2: Change:
    broker.id
    port
    log.dirs
3: Start brokers

------------------------------------------------------------------------------------------------------------------------------------------------

Leader:

Replication factor = 2
    Means topic is replicated on 2 brokers

Ex:
User-Topic, replication factor = 2, partition = 2
user-topic is replicated on 2 brokers with 2 partitions
Partition 1: Broker 1 (Leader), Broker 2 (Follower)
Partition 2: Broker 2 (Leader), Broker 1 (Follower)

Producer sends data to only Leader
Leader:
    Writes data
    Replicates to followers
    Confirms write from followers
Without a leader, producer would have to write to multiple brokers, slowing everything down!

------------------------------------------------------------------------------------------------------------------------------------------------

ISR (In-Sync Replicas):
    Replicas that are fully in sync with the leader

Only replicas in ISR:
    Receive data
    Can become leader

If a follower:
    Is slow
    Stops responding
    → Kafka removes it from ISR

Why ISR Matters
    Prevents data loss
    Ensures only up-to-date replicas become leader
    Improves reliability during broker failure

------------------------------------------------------------------------------------------------------------------------------------------------
