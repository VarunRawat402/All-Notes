--------------------------------------------------------------------------------------------------------------------------------------------
Kafka in Real Projects (Spring Boot)
--------------------------------------------------------------------------------------------------------------------------------------------

Producer & Consumer Properties:

These properties define how Kafka producers and consumers behave
    Broker connection
    Serialization / deserialization
    Consumer group
    Type mapping for automatic DTO conversion

Why type headers matter:
    They allow the consumer to know which Java class the JSON should be converted into.

--------------------------------------------------------------------------------------------------------------------------------------------
Kafka Configuration using Java Classes
--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Producer Configuration:

    Properties getProducerProperties() {

        Properties props = new Properties();

        props.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG,
                "localhost:9092,localhost:9093,localhost:9094");

        props.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG,
                StringSerializer.class);

        props.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG,
                JsonSerializer.class);

        // Add type info in headers (__TypeId__)
        props.put(JsonSerializer.ADD_TYPE_INFO_HEADERS, true);

        // Header → Class mapping
        props.put(JsonSerializer.TYPE_MAPPINGS,
            "userEvent:com.company.events.UserEvent," +
            "orderEvent:com.company.events.OrderEvent," +
            "paymentEvent:com.company.events.PaymentEvent");

        return props;
    }

--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Consumer Configuration:

    Properties getConsumerProperties(String groupId) {

        Properties props = new Properties();

        props.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG,
                "localhost:9092,localhost:9093,localhost:9094");

        props.put(ConsumerConfig.GROUP_ID_CONFIG, groupId);

        props.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG,
                StringDeserializer.class);

        props.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG,
                JsonDeserializer.class);

        // Security: allow deserialization only from trusted packages
        props.put(JsonDeserializer.TRUSTED_PACKAGES,
            "com.company.events,com.company.dto");

        // Same mapping as producer
        props.put(JsonDeserializer.TYPE_MAPPINGS,
            "userEvent:com.company.events.UserEvent," +
            "orderEvent:com.company.events.OrderEvent," +
            "paymentEvent:com.company.events.PaymentEvent");

        // Fallback type
        props.put(JsonDeserializer.VALUE_DEFAULT_TYPE,
                "com.company.events.BaseEvent");

        return props;
    }

--------------------------------------------------------------------------------------------------------------------------------------------

ProducerFactory & ConsumerFactory:

Factories create actual Kafka producers/consumers using the above properties.

@Bean
public ProducerFactory<String, Object> producerFactory() {
    return new DefaultKafkaProducerFactory<>(getProducerProperties());
}

@Bean
public ConsumerFactory<String, Object> consumerFactory() {
    return new DefaultKafkaConsumerFactory<>(getConsumerProperties("grp123"));
}

--------------------------------------------------------------------------------------------------------------------------------------------
Kafka Configuration Properties Using Application.properties 
--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Producer Configuration;

spring.kafka.producer.bootstrap-servers=localhost:9092,localhost:9093,localhost:9094

spring.kafka.producer.key-serializer=org.apache.kafka.common.serialization.StringSerializer
spring.kafka.producer.value-serializer=org.springframework.kafka.support.serializer.JsonSerializer

spring.kafka.producer.acks=all
spring.kafka.producer.retries=3
spring.kafka.producer.properties.linger.ms=5

spring.kafka.producer.properties.spring.json.add.type.headers=true

spring.kafka.producer.properties.spring.json.type.mapping=\
userEvent:com.company.events.UserEvent,\
orderEvent:com.company.events.OrderEvent,\
paymentEvent:com.company.events.PaymentEvent

--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Consumer Configuration:

spring.kafka.consumer.bootstrap-servers=localhost:9092,localhost:9093,localhost:9094
spring.kafka.consumer.group-id=grp123

spring.kafka.consumer.key-deserializer=org.apache.kafka.common.serialization.StringDeserializer
spring.kafka.consumer.value-deserializer=org.springframework.kafka.support.serializer.JsonDeserializer

spring.kafka.consumer.auto-offset-reset=earliest
spring.kafka.consumer.enable-auto-commit=true

spring.kafka.consumer.properties.spring.json.trusted.packages=\
com.company.events,com.company.dto

spring.kafka.consumer.properties.spring.json.type.mapping=\
userEvent:com.company.events.UserEvent,\
orderEvent:com.company.events.OrderEvent,\
paymentEvent:com.company.events.PaymentEvent

spring.kafka.consumer.properties.spring.json.value.default.type=\
com.company.events.BaseEvent

--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Template:
    KafkaTemplate is used to send the messages to kafka.
    You need to initialize the kafka template with the ProducerFactory instance

Handles:
    Serialization
    Retries
    Error handling
    Partitions & keys

@Bean
public KafkaTemplate<String, Object> kafkaTemplate() {
    return new KafkaTemplate<>(producerFactory());
}

kafkaTemplate.send("user-create", userEvent);

--------------------------------------------------------------------------------------------------------------------------------------------

KafkaListener (Consumer Side):

@KafkaListener(topics = "user-create", groupId = "user-consumer")
public void updateWallet(UserCreatedEvent event) {
    // Runs automatically when message arrives to user-create topic
}

Method is triggered automatically
Message is converted to DTO before method execution

--------------------------------------------------------------------------------------------------------------------------------------------

Automaic Deserialization of message to DTO :
    It is used to configure how message will automatically deserialized to correct DTO based on topic and headers

Scenario 1: One DTO per Topic (Most Common)

user topic  → UserDTO object
order topic → OrderDTO object
    No header needed
    kafka Listener will automatically convert the json to UserDTO object based on the function parameter

@KafkaListener(topics = "user-create")
public void userCreate(UserDto userDto) {
}

Scenario 2: Multiple DTOs in One Topic (Event-Driven):

user topic → userCreateDTO, userUpdateDTO, userDeleteDTO
    Header required
    Uses → __TypeId__

Code:
configProps.put(JsonDeserializer.TYPE_MAPPINGS, 
    "userCreation:com.example.dto.UserCreationEvent," +    //message with userCreation typeId will be mapped to userCreatedEvent DTO
    "userUpdate:com.example.dto.UserUpdateEvent," +        
    "userDelete:com.example.dto.UserDeleteEvent");         

--------------------------------------------------------------------------------------------------------------------------------------------
How to consume mesasges using kafka listener for both Scenario:
--------------------------------------------------------------------------------------------------------------------------------------------

Scenario 2: Kafka Listener on class level

1 Topic → business-events-topic
UserCreatedEvent & OrderCreatedEvent both will come
Based on header value it will call the respective method

@Service
@KafkaListener(topics = "business-events-topic")
public class BusinessEventsConsumer {

    @KafkaHandler
    public void handleUser(UserCreatedEvent event) {
        userService.save(event);
    }

    @KafkaHandler
    public void handleOrder(OrderCreatedEvent event) {
        orderService.save(event);
    }

    @KafkaHandler(isDefault = true)
    public void unknown(Object event) {
        System.out.println("Unknown event type");
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------
Kafka Topic Creation in Spring Boot
--------------------------------------------------------------------------------------------------------------------------------------------

Important prerequisite:

Topics are created only if:
    spring.kafka.admin.auto-create=true
    (or Kafka auto-topic creation is enabled on broker)

--------------------------------------------------------------------------------------------------------------------------------------------

Topic Create:

Why these configs matter:
    Partitions → consumer parallelism
    Replicas → fault tolerance
    Retention → how long data lives
    Compression → network efficiency
    Segment size → disk management

@Bean
public NewTopic shipmentTopic() {
    return TopicBuilder
            .name("shipment-topic")
            .partitions(6)                       // Throughput & parallelism
            .replicas(3)                         // High availability
            .config("retention.ms", "604800000") // 7 days
            .config("segment.bytes", "1073741824") // 1 GB
            .config("cleanup.policy", "delete")
            .config("compression.type", "snappy")
            .config("max.message.bytes", "10485760") // 10 MB
            .build();
}

--------------------------------------------------------------------------------------------------------------------------------------------
Sending Messages to Kafka:
--------------------------------------------------------------------------------------------------------------------------------------------

Using MessageBuilder (recommended):
    Clean
    Header-based routing
    Supports key, partition, timestamp

Message<OrderConfirmation> message =
        MessageBuilder
                .withPayload(orderConfirmation)
                .setHeader(KafkaHeaders.TOPIC, "order-topic")
                .build();

kafkaTemplate.send(message);

--------------------------------------------------------------------------------------------------------------------------------------------

Sending Multiple Objects (Map payload):

Map<String, Object> payload = new HashMap<>();
payload.put("orderConfirmation", orderConfirmation);
payload.put("additionalInfo", someOtherData);

Message<Map<String, Object>> message =
        MessageBuilder
                .withPayload(payload)
                .setHeader(KafkaHeaders.TOPIC, "order-topic")
                .build();

kafkaTemplate.send(message);

This works only if:
    Consumer uses JsonDeserializer
    Trusted packages are configured
    Consumer knows how to interpret the map

--------------------------------------------------------------------------------------------------------------------------------------------

Better practice in production:
    Create a wrapper DTO instead of raw Map.

class OrderEvent {
    private OrderConfirmation orderConfirmation;
    private AdditionalInfo additionalInfo;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Common Interview Clarifications:

Does Spring Boot always create topics:
    No, Only if KafkaAdmin is enabled and broker allows it

Is topic creation done by producers/consumers:
    No, Done by KafkaAdmin during application startup

Should topics be created in production apps:
    Usually NO, 
    Topics created via:
        Terraform
        Kafka CLI
        Platform team
        Application does not own infra

--------------------------------------------------------------------------------------------------------------------------------------------