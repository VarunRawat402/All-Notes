--------------------------------------------------------------------------------------------------------------------------------------------
Create Kafka Topic in Spring Boot:
--------------------------------------------------------------------------------------------------------------------------------------------

// Topic with 1 partition and 1 replica

@Bean
public NewTopic paymentTopic() {
    return TopicBuilder.name("payment-topic")
    .build();
}

// Topic with customized partitions and replicas

@Bean
public NewTopic shipmentTopic() {
    return TopicBuilder.name("shipment-topic")
        .partitions(6)                              // ✅ Increased for throughput
        .replicas(3)                                // ✅ High availability
        .config("retention.ms", "604800000")        // ✅ 7 days retention
        .config("segment.bytes", "1073741824")      // ✅ 1GB segment size
        .config("cleanup.policy", "delete")         // ✅ Cleanup policy
        .config("compression.type", "snappy")       // ✅ Compression
        .config("max.message.bytes", "10485760")    // ✅ 10MB max message size
        .build();
}

--------------------------------------------------------------------------------------------------------------------------------------------
Send Messages to kafka Topics:
--------------------------------------------------------------------------------------------------------------------------------------------

Message Builder:

Message<OrderConfirmation> message = MessageBuilder
    .withPayload(orderConfirmation)
    .setHeader(TOPIC, "order-topic")
    .build();

kafkaTemplate.send(message);

Sending Multiple Payloads:

//Added 2 objects in map
Map<String, Object> payload = new HashMap<>();
payload.put("orderConfirmation", orderConfirmation);
payload.put("additionalInfo", someOtherData);

//Send the map 
Message<Map<String, Object>> message = MessageBuilder
    .withPayload(payload)
    .setHeader(TOPIC, "order-topic")
    .build();

--------------------------------------------------------------------------------------------------------------------------------------------