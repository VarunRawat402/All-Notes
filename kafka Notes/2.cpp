KAFKA IN PROJECT:

--------------------------------------------------------------------------------------------------------------------------------------------

This is used to configure the kafka server configuration
Properties is a map in which we configure bootstrap server and key/value StringSerializer

    Properties getProperties(){
        Properties properties = new Properties();
        properties.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG,"localhost:9092");
        properties.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        properties.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        return properties;
    }

    Properties getCProperties(){
        Properties properties = new Properties();
        properties.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
        properties.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class);
        properties.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class);
        return properties;
    }

--------------------------------------------------------------------------------------------------------------------------------------------

This is used to create the instance of kafka producers
ProducerFactory is an interface in kafka
This creates the kafka producer using the kafka configuration in properties

    ProducerFactory getProducerFactory(){
        return new DefaultKafkaProducerFactory(getProperties());
    }

    ConsumerFactory getConsumerFactory(){
        return new DefaultKafkaConsumerFactory(getCProperties());
    }

--------------------------------------------------------------------------------------------------------------------------------------------

This is used to send/produce the message to the kafka topic, error handling etc.
You need to initialize the kafka template with the ProducerFactory then do operations using kafka template.

    @Bean
    KafkaTemplate<String, String> getKafkaTemplate(){
        return new KafkaTemplate(getProducerFactory());
    }

bin/kafka-console-consumer --topic user_created --bootstrap-server localhost:9092 --help

--------------------------------------------------------------------------------------------------------------------------------------------

Note:
    @KafkaListener(topics = CommonConstants.TRANSACTION_CREATION_TOPIC, groupId = "grp123")
    public void updateWalletsForTxn(String msg) throws ParseException, JsonProcessingException {

@KafkaListener annotation is used on top of the function which we want to run automatically when msg is produced on the 
group we mention in the annotation.
Whenever any message is produced in the topic TRANSACTION_CREATION_TOPIC create function will run and that msg is passed as 
a parameter to the function

--------------------------------------------------------------------------------------------------------------------------------------------

Created a json Object with and put details we want to send to the listener
    JSONObject jsonObject = new JSONObject();
    jsonObject.put("userId", user.getId());
    jsonObject.put("phoneNumber", user.getPhoneNumber());
    jsonObject.put("identifierValue", user.getIdentifierValue());
    jsonObject.put("userIdentifier", user.getUserIdentifier());

Sent the message( Json Object ) to the topic USER_CREATION_TOPIC
Anyone who wants to listen to that msg and take the values can take it
    kafkaTemplate.send(CommonConstants.USER_CREATION_TOPIC,
            objectMapper.writeValueAsString(jsonObject));
    }

--------------------------------------------------------------------------------------------------------------------------------------------