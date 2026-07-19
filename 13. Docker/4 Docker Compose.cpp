----------------------------------------------------------------------------------------------------------------------------------------------
Docker compose:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Configure + Run all the services in one file
→ Without it → manually build + run + network each application one by one

----------------------------------------------------------------------------------------------------------------------------------------------

Common Commands:

'docker compose up'                         → start all services, build image if missing
'docker compose up --build'                 → force rebuild images every time
'docker compose down'                       → stop + remove containers, networks, volumes
'docker compose ps'                         → show running containers
'docker compose logs'                       → show logs for all services
'docker compose logs user-service'          → show logs for specific service
'docker compose stop user-service'          → stop specific service
'docker compose restart user-service'       → restart specific service

----------------------------------------------------------------------------------------------------------------------------------------------\

Docker Compose File (Key Fields):

build           → build image from local Dockerfile
image           → pull image from Docker Hub
ports           → map host:container ports
depends_on      → start this service AFTER another service
networks        → which network this service joins
environment     → environment variables passed at runtime

----------------------------------------------------------------------------------------------------------------------------------------------
Code:
----------------------------------------------------------------------------------------------------------------------------------------------

version: '3.7'
services:

    discovery-service:                    //start first, others depend on it
        build: ./Discovery-Service
        ports:
            - "8761:8761"
        networks:
            - currency-network

        currency-exchange:
        build: ./CurrencyExchange
        ports:
            - "8000:8000"
        networks:
            - currency-network
        depends_on:
            - discovery-service              //waits for discovery to start

    currency-conversion:
        build: ./CurrencyConversion
        ports:
            - "8100:8100"
        networks:
            - currency-network
        depends_on:
            - discovery-service

networks:
    currency-network:                    //all services share this network

----------------------------------------------------------------------------------------------------------------------------------------------

Caching:

→ Docker reads Dockerfile line by line
→ Each line is a layer and cached after first build
→ Unchanged layer → reused from cache → faster build
→ Changed layer → that layer + everything below → rebuilt

FROM openjdk:17
COPY pom.xml .
RUN mvn dependency:go-offline    → cached if pom.xml unchanged ✅
COPY src ./src
RUN mvn clean package            → rebuilt if src/ changes
CMD ["java", "-jar", "app.jar"]

Best Practice:

→ Rarely change first
    → Base image + Dependencies

→ Frequent change last:
    → Source code

----------------------------------------------------------------------------------------------------------------------------------------------