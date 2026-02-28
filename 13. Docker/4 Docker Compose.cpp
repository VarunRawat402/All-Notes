----------------------------------------------------------------------------------------------------------------------------------------------
Docker compose:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Run and configure all the services together instead of one by one

Without docker compose:
    → Manually build and run image for each service 1 by 1


Common Docker Compose Commands:

'docker compose up'
    → start containers, build image if missing

'docker compose up --build'
    → force re-build of image everytime

'docker compose down'
    → stop and removes containers + network + vol

'docker compose ps'
    → show running containers

'docker compose logs'
    → show logs 

'docker compose logs user-service'
    → show user-service logs

'docker compose stop user-service'
    → stop specific service

'docker compose restart user-service'
    → restart specific service

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Compose File for SpringBoot:

build           → Builds image from Dockerfile
image           → Pulls image from Docker Hub
depends_on      → Starts service after another service
networks        → Enables internal communication
environment     → Sets environment variables

----------------------------------------------------------------------------------------------------------------------------------------------
Code:
----------------------------------------------------------------------------------------------------------------------------------------------

version: '3.7'   
services:

  currency-exchange:
    build: ./CurrencyExchange
    ports:
      - "8000:8000"
    networks:
      - currency-network
    depends_on:
      - discovery-service

  currency-conversion:
    build: ./CurrencyConversion
    ports:
      - "8100:8100"
    networks:
      - currency-network
    depends_on:
      - discovery-service

  discovery-service:
    build: ./Discovery-Service
    ports:
      - "8761:8761"
    networks:
      - currency-network

networks:
  currency-network:

----------------------------------------------------------------------------------------------------------------------------------------------

Caching:

→ Docker reads Dockerfile line by line
→ Each line can be cached

On rebuild:
    → Unchanged line  → reused
    → Changed line    → that layer + all below it rebuild

Example:

    FROM openjdk:17
    COPY pom.xml .
    RUN mvn dependency:go-offline
    COPY src ./src
    RUN mvn clean package
    CMD ["java", "-jar", "app.jar"]

If src/ changes:
    → COPY src ./src → rebuilt
    → All steps below → rebuilt

Best Practice:
    → Rarely change first
        → Base image + Dependencies

    → Frequent change last:
        → Source code

----------------------------------------------------------------------------------------------------------------------------------------------