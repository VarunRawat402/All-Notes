--------------------------------------------------------------------------------------------------------------------------------------------
KAFKA IN PROJECT:
--------------------------------------------------------------------------------------------------------------------------------------------

Producer and Consumer Properties:
    This is used to configure the properties for kafka producer and consumer
    You configure the bootstrap server, serializer, deserializer, groupId, mappings etc

Properties getProducerProperties() {

    Properties properties = new Properties();
    
    properties.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092,localhost:9093,localhost:9094");
    properties.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class.getName());
    properties.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, "org.springframework.kafka.support.serializer.JsonSerializer");
    
    // Automatically add type information in headers for automatic conversion during deserialization
    properties.put("spring.json.add.type.headers", "true"); // Add type information in headers
    properties.put("spring.json.type.mapping", 
        "userEvent:com.company.events.UserEvent, " +
        "orderEvent:com.company.events.OrderEvent, " +
        "paymentEvent:com.company.events.PaymentEvent");

    return properties;
}

Properties getConsumerProperties(String groupId) {

    Properties properties = new Properties();
    
    properties.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092,localhost:9093,localhost:9094");
    properties.put(ConsumerConfig.GROUP_ID_CONFIG, groupId);
    properties.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class.getName());
    properties.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, "org.springframework.kafka.support.serializer.JsonDeserializer");
    
    // Trusted packages
    // Coming json data can be mapped or deserialized to these packages only
    properties.put("spring.json.trusted.packages", 
        "com.company.events,com.company.dto,com.company.models");
    
    // It converts the incoming json automatically to the respective class object based on the header value
    properties.put("spring.json.type.mapping", 
        "userEvent:com.company.events.UserEvent, " +
        "orderEvent:com.company.events.OrderEvent, " +
        "paymentEvent:com.company.events.PaymentEvent");
    
    // Default type for fallback
    // when no header is present or header value doesn't match any mapping, it will convert to this class object
    properties.put("spring.json.value.default.type", "com.company.events.BaseEvent");
    
    return properties;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Prodcuer and Consumer Factory:
    It is used to create the producer and consumer instance using the properties configured above
    ProducerFactory is an interface in kafka

ProducerFactory getProducerFactory(){
    return new DefaultKafkaProducerFactory(getProperties());
}

ConsumerFactory getConsumerFactory(){
    return new DefaultKafkaConsumerFactory(getCProperties());
}

--------------------------------------------------------------------------------------------------------------------------------------------

Kafka Template:
    This is used to send the message to the kafka topic, error handling etc.
    You need to initialize the kafka template with the ProducerFactory instance

    @Bean
    KafkaTemplate<String, String> getKafkaTemplate(){
        return new KafkaTemplate(getProducerFactory());
    }

bin/kafka-console-consumer --topic user_created --bootstrap-server localhost:9092 --help

--------------------------------------------------------------------------------------------------------------------------------------------

Note:
    @KafkaListener("user-create", groupId = "grp123")
    public void updateWalletsForTxn(String msg) throws ParseException, JsonProcessingException {

@KafkaListener annotation is used on top of the function which we want to run automatically when msg is produced on the 
group we mention in the annotation.
Whenever any message is produced in the topic "user-create" create function will run and that msg is passed as 
a parameter to the function

--------------------------------------------------------------------------------------------------------------------------------------------

Conversion of Java Object to JSON object:
    In order to send the data to kafka you need to convert it to correct json format
    This is needed when you dont have automatic conversion of json to object
    When you dont initialize type header in the producer and consumer properties

Created a json Object with and put details we want to send to the listener
    JSONObject jsonObject = new JSONObject();
    jsonObject.put("userId", user.getId());
    jsonObject.put("phoneNumber", user.getPhoneNumber());
    jsonObject.put("identifierValue", user.getIdentifierValue());
    jsonObject.put("userIdentifier", user.getUserIdentifier());

Sent the message( Json Object ) to the topic USER_CREATION_TOPIC
Anyone who wants to listen to that msg and take the values can take it
    kafkaTemplate.send("user-create",objectMapper.writeValueAsString(jsonObject));

--------------------------------------------------------------------------------------------------------------------------------------------

Automaic Deserialization of message to DTO :
    It is used to configure how message will automatically deserialized to correct DTO based on topic and headers

Scenario 1:
Each topic gets only 1 type of DTO model

There are 2 topics user and order
user topic gets UserDTO object, order topic gets OrderDTO object
So, header type is not needed because we know which topic gets which object

@KafkaListener(topics = "user", groupId = "grp1")
public void listenUserTopic(UserDTO user) {
    // Process UserDTO object
}
kafka Listeneres will automatically convert the json to UserDTO object based on the function parameter

Scenario 2:
Each topic gets multiple type of DTO model
There is 1 topic user-event which gets userCreated, userUpdated, userDeleted DTOs all to the same topic
So, header type is needed because we dont know which dto object is coming for event topic

Code:

configProps.put(JsonDeserializer.TYPE_MAPPINGS, 
    "userCreation:com.example.dto.UserCreationEvent," +    // You chose "userCreation"
    "userUpdate:com.example.dto.UserUpdateEvent," +        // You chose "userUpdate"  
    "userDelete:com.example.dto.UserDeleteEvent");         // You chose "userDelete"

You need to explicitly map this in consumer and prodcuer
userCreation is header name can be anything with path to the class it maps to
userCreation is sent as header so consumer can identity which class this json needs to be mapped with
using this header name

--------------------------------------------------------------------------------------------------------------------------------------------
How to consume mesasges using kafka listener for both Scenario:
--------------------------------------------------------------------------------------------------------------------------------------------

Scenario 1:

2 topics : user-create and order-placed
In user-create, userDto will be send to save the user
In order-placed, orderDto will be send to save the order
2 kafka listeners will be there on the method to process usercreate and orderplaced

@kafkaListener(topic="user-create")
public void userCreate(UserDto userDto){

}

@kafkaListener(topic="order-placed")
public void orderPlaced(OrderDto orderDto){

}

--------------------------------------------------------------------------------------------------------------------------------------------

Scenario 2:
1 topic, user-event
In this topic both userDto and orderDto will be send to save user and order
When topic is same for different tasks and different data
We use kafkaListener on class level
Based on header value it will call the respective method

@Service
@KafkaListener(topics = "business-events-topic")
public class BusinessEventsConsumer {
    
    // Handler for UserCreatedEvent - Save User
    @KafkaHandler
    public void handleUserCreated(UserCreatedEvent event) {
        userService.saveUser(event);
    }
    
    // Handler for OrderCreatedEvent - Process Order
    @KafkaHandler
    public void handleOrderCreated(OrderCreatedEvent event) {
        orderService.saveOrder(event);
    }

    // Fallback for unknown event types
    @KafkaHandler(isDefault = true)
    public void handleUnknown(Object event) {
        System.err.println("❌ Unknown event type: " + event.getClass().getSimpleName());
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Flow:

Kafka Message Arrives
        ↓
JsonDeserializer reads header: __TypeId__ = "user_created"
        ↓
Checks TYPE_MAPPINGS: "user_created" → UserCreatedEvent.class
        ↓
Creates UserCreatedEvent instance from JSON
        ↓
Spring looks for @KafkaHandler methods that accept UserCreatedEvent parameter
        ↓
Finds: handleUserCreated(UserCreatedEvent event)
        ↓
Calls THAT specific method with the typed object

--------------------------------------------------------------------------------------------------------------------------------------------