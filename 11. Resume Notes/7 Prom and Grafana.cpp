------------------------------------------------------------------------------------------------------------------------------------------------
PROM AND GRAFANA:
------------------------------------------------------------------------------------------------------------------------------------------------

Prometheus Implementation:

1: Add Prometheus & Actuator dependency:
2: Enable Actuator Endpoints in application.properties:
3: Create Prometheus config file (prometheus.yml):

------------------------------------------------------------------------------------------------------------------------------------------------

Prometheus Config File:

global:
  scrape_interval: 15s

scrape_configs:
  - job_name: "spring-boot-app"
    metrics_path: "/actuator/prometheus"
    static_configs:
      - targets:
          - "host.docker.internal:8080"
        labels:
          application: "Spring boot Service"

-----------------------------------------------------------------------------------------------------------------------------------------------

Actuator Endpoint:
  management.endpoints.web.exposure.include=*

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