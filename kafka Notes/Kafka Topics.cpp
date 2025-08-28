--------------------------------------------------------------------------------------------------------------------------------------------
Create Kafka Topic in Spring Boot:
--------------------------------------------------------------------------------------------------------------------------------------------

Topic with 1 partition and 1 replica
@Bean
public NewTopic paymentTopic() {
    return TopicBuilder.name("payment-topic")
    .build();
}

Topic with customized partitions and replicas
@Bean
public NewTopic shipmentTopic() {
    return TopicBuilder.name("shipment-topic")
    .partitions(2)
    .replicas(3)
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