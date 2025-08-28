--------------------------------------------------------------------------------------------------------------------------------------------------------------------
Currency Project with Docker and Zipkin:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

1: Create the whole Project
2: Docker:

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

( Maven plug in Method )

1: Open Intellij Terminal

    ( Creating Images of Microservices )
2: Go inside each microservices folder and create jar files and image
    ( mvn spring-boot:build-image -DskipTests )

    ( Creating Container of Images and running )
3: Now you can run the docker images one by one and use the microservices 
4: Docker-compose File method:
    1: Creata a docker-compose.yaml file in the project folder
    2: Add the configs of every service with ports, image name, connections
    3: In cmd, Go to project folder and run
        ( docker-compose up)
    4: This will run all the docker images in the file
5:  Run the APIs and check on the Zipkin server for request tracing
    ( "http://localhost:9411/zipkin/" )

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

docker-compose.yaml:

version: '3.7'

services:

  CurrencyExchange:
    image: varun/currencymsv1-currencyexchange:0.0.1-SNAPSHOT
    ports:
      - "8000:8000"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka
      MANAGEMENT.ZIPKIN.TRACING.ENDPOINT: http://zipkin-server:9411/api/v2/spans


  CurrencyConversion:
    image: varun/ccv1:0.0.1-SNAPSHOT
    ports:
      - "8100:8100"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka
      MANAGEMENT.ZIPKIN.TRACING.ENDPOINT: http://zipkin-server:9411/api/v2/spans


  Api-Gateway:
    image: varun/apiv1:0.0.1-SNAPSHOT
    ports:
      - "9765:9765"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka
      MANAGEMENT.ZIPKIN.TRACING.ENDPOINT: http://zipkin-server:9411/api/v2/spans


  Discovery-Service:
    image: varun/dsv1:0.0.1-SNAPSHOT
    ports:
      - "8761:8761"
    networks:
      - currency-network

  zipkin-server:
    image: openzipkin/zipkin:2.23
    ports:
      - "9411:9411"
    networks:
      - currency-network
    restart: always #Restart if there is a problem starting up

networks:
  currency-network:

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
