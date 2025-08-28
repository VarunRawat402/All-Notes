------------------------------------------------------------------------------------------------------------------------------------------------
KAFKA Notes:
------------------------------------------------------------------------------------------------------------------------------------------------

Apache Kafka is a distributed messaging system that allows applications to send, store
and process real-time data streams efficiently.

Ex:
If 1 million request is coming to an API it is going to overload and less fault torence will be there
With kafka in between those million request will get distributed between multiple servers.

------------------------------------------------------------------------------------------------------------------------------------------------

Core Concepts:

Producer -              Sends messages (events) to Kafka topics.
Consumer -              Reads messages from Kafka topics.
Topic -                 A category where messages are published.
Partition -             A topic is divided into partitions for parallel processing.
Broker -                A Kafka server that stores and manages message streams.
Cluster -               A group of Kafka brokers working together.
Zookeeper -             Manages Kafka brokers, leader election, and metadata.
Offset -                A unique ID assigned to each message in a partition.
Consumer Group -        A group of consumers that share the workload of reading messages from a topic.
Replication Factor -    The number of copies of data across brokers for fault tolerance.
Leader -                The broker responsible for handling read/write requests for a partition.
Follower -              A replica of a partition that stays in sync with the leader.

------------------------------------------------------------------------------------------------------------------------------------------------

Zookeeper:
Zookeeper is a distributed coordination service developed by Apache.

Why is Zookeeper used in Kafka?
Manages Kafka brokers (keeps track of which brokers are alive).
Handles leader election for partitions.
Stores metadata (e.g., topic configurations, ACLs).
Ensures fault tolerance and synchronization between nodes.

🔹 Kafka cannot work without Zookeeper (at least in older versions).
🔹 In newer versions (Kafka 3.0+), Zookeeper is being replaced by Kafka KRaft mode.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Connect
Kafka Connect is a tool for fetching external data from (like databases, message queues, or cloud services) 
with Kafka without writing custom code. It allows you to ingest (source) and export (sink) data seamlessly.

Key Components
Connector -         A plugin that defines how to interact with an external system (e.g., MySQL, Elasticsearch).
Source Connector -  Pulls data into Kafka from an external system.
Sink Connector -    Pushes data out of Kafka to an external system.
Worker -            The process that runs the connectors, handling data movement.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Streams
Kafka Streams is a Java library for processing and analyzing real-time data streams from Kafka topics. 
It allows you to transform, filter, aggregate, and join data streams using a simple API.

Key Features
Real-time processing -  Processes data as it arrives.
Fault-tolerant -        Ensures reliability even in case of failures.
Scalability -           Distributes workloads across multiple instances.

Basic Kafka Streams Workflow
Read data from a Kafka topic.
Process the data (transform, filter, aggregate, etc.).

------------------------------------------------------------------------------------------------------------------------------------------------

🟢 INSTALLATION COMMANDS

zookeeper-server-start.bat ..\..\config\zookeeper.properties        //To Start the Zookeeper
kafka-server-start.bat ..\..\config\server.properties               //To Start the broker

//Create Topic 
kafka-topics.bat --create --topic my-topic --bootstrap-server localhost:9092 --replication-factor 1 --partitions 3

//Create Producer and Consumer
kafka-console-producer.bat --broker-list localhost:9092 --topic my-topic
kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic my-topic --from-beginning

------------------------------------------------------------------------------------------------------------------------------------------------

🟢 SEND MESSAGES WITH KEYS

zookeeper-server-start.bat ..\..\config\zookeeper.properties
kafka-server-start.bat ..\..\config\server.properties

kafka-topics.bat --create --topic foods --bootstrap-server localhost:9092 --replication-factor 1 --partitions 4
kafka-console-producer.bat --broker-list localhost:9092 --topic foods --property "key.separator=-" --property "parse.key=true"
kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic foods --from-beginning -property "key.separator=-" --property "print.key=false"

//Hello is key and Varun is value ( Seperated by - as mentioned in the command )
Ex:
Hello-Varun
Hello-Arun
Bye-Priti

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Topic:
It is a topic where messages are stored. Producers send messages to a topic, and consumers read from it.

Kafka Partition:
A topic is divided into partition where messages are stored.
Ex: Like Book Almirah is a topic and shelves are partition

------------------------------------------------------------------------------------------------------------------------------------------------

Normal Partitioning :
If no key is provided, Kafka randomly assigns messages to partitions.
Good for even distribution of messages.

Key Bases Partitioning :
If a producer sends a message with a key ("user"), 
Messages with the same key always go to the same partition.
Useful when order matters

------------------------------------------------------------------------------------------------------------------------------------------------

Consumers and Parallel Processing:

1 partition can be read by only 1 consumer in a consumer group.
1 Consumer can read multiple partition in a consumer group.
If you have more consumers than partitions, some consumers stay idle.
If you have fewer consumers than partitions, each consumer reads multiple partitions.

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Offset:
A consumer offset is a unique ID assigned to each message in a partition.

It is used to track which message consumer has read in a Kafka topic.
Kafka remembers where each consumer left off using offsets.
Kafka stores offsets in a built in topic: "__consumer_offsets".
"__consumer_offsets" it is not meant to read and write by clients
It gets updated by kafka broker to reflect the position of each consumer in each partition.

Ex:
If there are 4 messages produced then each message has unique offset id 
So If a consumer read till 3rd message and crashed kafka will store the offset id as 3 and when consumer
gets restarted, It will read based of the last offset value which is after 3

------------------------------------------------------------------------------------------------------------------------------------------------

Automatic (Default Behavior)
Kafka automatically commits offsets after reading messages (enable.auto.commit=true).
If a consumer restarts, Kafka resumes from the last committed offset.

Manual Offset Management
Developers can manually commit offsets (enable.auto.commit=false).
Useful when ensuring messages are processed successfully before committing.

------------------------------------------------------------------------------------------------------------------------------------------------

Consumer Group:

A Consumer Group is a collection of consumers working together to process a Kafka topic.

1 consumer can read from 3 partition
2 consumers can also read from 3 partition
3 consumers can also read from 3 partitition 1 consumer for each partition ( Best )

Key Point:
Each Consumer group has its own offset Value means 
If consumer Group A has read till 5 messages so its offset id should be 6
But If Consumer B Starts reading fresh from same topic it will not start with 6 but with 0.
Consumer group manages the offset not the individual consumers.

------------------------------------------------------------------------------------------------------------------------------------------------

Commit Log:
A commit log is an append-only file where Kafka stores messages in order.
New messages are always appended at the end.
Messages are never modified or deleted manually

Consumers read from the log based on offsets.
Ex: File
Offset  Message
0       Order #101
1       Order #102
2       Order #103
3       Order #104
...

------------------------------------------------------------------------------------------------------------------------------------------------

Segments:
Kafka splits a commit log into smaller files called segments to improve performance.
Each partition consists of multiple segment files.
When a segment reaches a size or time limit, a new segment is created.
We can define the size of the segments.

Ex:
If commit log file has 9 messages it will create 3 segement files each consist of 3 messages 

------------------------------------------------------------------------------------------------------------------------------------------------

Retention Policy:
Kafka does not delete messages immediately after they are consumed. Instead, it follows a retention policy.
Kafka deletes entire segments, not individual messages.
If a segment contains messages beyond the retention period, Kafka deletes it.

Ex:
If some messages in the segments are older than expiry time but some are not then 
it waits until all messages in the segment exceed the expiry period, then deletes the entire segment.


Time-Based Retention (Default)
Messages are deleted after a certain time.

Size-Based Retention
Messages are deleted when the total log size exceeds a limit.

------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Cluster:
It is a group of kakfa brokers 

How to create multiple kafka brokers:

1: Create 3 server properties files for 3 brokers
2: In each server file change the ID , port and the log file name
3: Then create 3 brokers in cmd

------------------------------------------------------------------------------------------------------------------------------------------------

Replication Factor:
If topic has 3 Replication factor
It means every partition of that topic is replicated 3 times in 3 different brokers
Replication factor should be equal to or less than the Brokers

------------------------------------------------------------------------------------------------------------------------------------------------

Leader:
Every topic is replicated in every broker which means
Every partition is replicated in every broker too
So, 1 broker is leader of 1 partition 

Ex:
I created 3 brokers with different ports
I created a topic in all 3 servers with replication factor 3 and partition factor 3
It means topic is created on all 3 servers
So, All 3 brokers have topic food with 3 partition
So, Every broker is a leader of 1 partition each
Lets say B1 is a leader of P1, B2 -> P2 and B3 -> P3
So if a message is produced in P1 partition then first it will get stored in broker1 then it 
will get replicated in other 2
Same as if message is produced on P2 then it will get first stored on B2.

Why Leaders are Important:

Producer sends data to Leader (Broker-1). 
Leader writes the message to disk.
Leader replicates data to Followers (Broker-2 & Broker-3).
Followers acknowledge back to the leader.
Leader confirms to the producer that the message is stored.
Without a leader, every producer would have to write to multiple brokers, slowing everything down!

------------------------------------------------------------------------------------------------------------------------------------------------

ISR (In-Sync Replicas):
Kafka has a concept called ISR (In-Sync Replicas) to make sure followers dont fall too far behind.

✅ ISR = Followers that are up-to-date with the leader.
✅ Only ISR followers can become the new leader if the leader fails.
✅ If a follower falls behind too much, Kafka removes it from ISR.

------------------------------------------------------------------------------------------------------------------------------------------------