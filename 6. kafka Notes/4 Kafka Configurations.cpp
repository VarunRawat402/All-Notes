-----------------------------------------------------------------------------------------------------------------------------------------------------
Kafka in Real Projects (Spring Boot)
-----------------------------------------------------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Producer Configuration;
-----------------------------------------------------------------------------------------------------------------------------------------------------

spring.kafka.producer.bootstrap-servers         = localhost:9092,localhost:9093,localhost:9094

spring.kafka.producer.key-serializer            = org.apache.kafka.common.serialization.StringSerializer
spring.kafka.producer.value-serializer          = org.springframework.kafka.support.serializer.JsonSerializer

spring.kafka.producer.acks                      = all
spring.kafka.producer.retries                   = 3
spring.kafka.producer.properties.linger.ms      = 5

spring.kafka.producer.properties.spring.json.add.type.headers = true

spring.kafka.producer.properties.spring.json.type.mapping=\
userEvent:com.company.events.UserEvent,\
orderEvent:com.company.events.OrderEvent,\
paymentEvent:com.company.events.PaymentEvent

-----------------------------------------------------------------------------------------------------------------------------------------------------
Kafka Consumer Configuration:
-----------------------------------------------------------------------------------------------------------------------------------------------------

spring.kafka.consumer.bootstrap-servers     = localhost:9092,localhost:9093,localhost:9094
spring.kafka.consumer.group-id              = grp123

spring.kafka.consumer.key-deserializer      = org.apache.kafka.common.serialization.StringDeserializer
spring.kafka.consumer.value-deserializer    = org.springframework.kafka.support.serializer.JsonDeserializer

spring.kafka.consumer.auto-offset-reset     = earliest
spring.kafka.consumer.enable-auto-commit    = true

spring.kafka.consumer.properties.spring.json.trusted.packages=\
com.company.events,com.company.dto

spring.kafka.consumer.properties.spring.json.type.mapping=\
userEvent:com.company.events.UserEvent,\
orderEvent:com.company.events.OrderEvent,\
paymentEvent:com.company.events.PaymentEvent

spring.kafka.consumer.properties.spring.json.value.default.type=\
com.company.events.BaseEvent

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Template:
    → KafkaTemplate is used to send messages to Kafka.

@Bean
public KafkaTemplate<String, Object> kafkaTemplate() {
    return new KafkaTemplate<>(producerFactory());
}

kafkaTemplate.send("user-create", userEvent);

-----------------------------------------------------------------------------------------------------------------------------------------------------

Message Builder:
    → More flexible way to send messages with headers, keys, partitions, timestamps.

Using MessageBuilder (recommended):
    → Clean
    → Header-based routing
    → Supports key, partition, timestamp

Message<OrderConfirmation> message =
        MessageBuilder
                .withPayload(orderConfirmation)
                .setHeader(KafkaHeaders.TOPIC, "order-topic")
                .build();

kafkaTemplate.send(message);

-----------------------------------------------------------------------------------------------------------------------------------------------------

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
    → Consumer uses JsonDeserializer
    → Trusted packages are configured
    → Consumer knows how to interpret the map

-----------------------------------------------------------------------------------------------------------------------------------------------------

Kafka Topic Creation in Spring Boot
    → spring.kafka.admin.auto-create=true
    → Kafka auto-topic creation is enabled on broker

Topic Create:

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

-----------------------------------------------------------------------------------------------------------------------------------------------------


