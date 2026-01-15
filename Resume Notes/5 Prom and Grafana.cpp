------------------------------------------------------------------------------------------------------------------------------------------------
PROM AND GRAFANA:
------------------------------------------------------------------------------------------------------------------------------------------------

1. CPU Metrics
    CPU usage (%)
    CPU cores used
    CPU usage per container / pod

How to explain:
    CPU metrics indicate how much processing application consumes.
    High CPU usage can signal heavy load or inefficient processing.

Safe example line:
    We monitored CPU usage to ensure the service was not over-consuming processor resources.

------------------------------------------------------------------------------------------------------------------------------------------------

2. Memory Metrics
Metrics you see:
    Memory usage (MB/GB)
    Memory limit vs used memory
    JVM heap usage (for Spring Boot)

How to explain:
    Memory metrics show how much RAM the application consumes. Monitoring this helps detect memory leaks or applications nearing their memory limits.
    Safe example line:
    “Memory usage was tracked to ensure the application stayed within allocated limits.”

------------------------------------------------------------------------------------------------------------------------------------------------

3. Application (Basic) Metrics

These come from the application itself.
Common ones you can say:
    Request count
    Response time / latency
    Error count (4xx / 5xx)
    Application uptime
How to explain:
    Application metrics help understand how the service behaves under load, such as how many requests it handles and how quickly it responds.

------------------------------------------------------------------------------------------------------------------------------------------------

//Consumer Service Configuration of Kafka:
//This is used to map the kafka json event to java class automatically
//Json data coming with typeId = txncreation will be mapped to TxnCreation class
//Json data coming with typeId = usercreation will be mapped to UserCreation class
spring.kafka.consumer.properties.spring.json.type.mapping = txncreation:com.example.wallet.wallet.kafkaUtil.TxnCreation,usercreation:com.example.wallet.wallet.kafkaUtil.UserCreation


//Producer Service Configuration of Kafka:
//This is used to set the typeId while sending json data to kafka topic
//This will automatically add typeId = txnupdate in the json data
spring.kafka.producer.properties.spring.json.type.mapping=txnupdate:com.example.wallet.wallet.kafkaUtil.TxnUpdate

------------------------------------------------------------------------------------------------------------------------------------------------