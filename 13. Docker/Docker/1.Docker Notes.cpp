----------------------------------------------------------------------------------------------------------------------------------------------
Docker Notes:
----------------------------------------------------------------------------------------------------------------------------------------------

Image:

→ A Docker Image is a packaged application.
→ Application code + Runtime Environment + Libraries + Dependencies
→ It ensures app runs the same everywhere

----------------------------------------------------------------------------------------------------------------------------------------------

Container:
    → It is a running instance of image
    → It is used to run the application

----------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

1: Create docker file 
2: mvn clean install                    //create jar files
3: docker build -t <image-name> .       //build image
4: docker run -it <image-name>          //run image

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Container Commands:

'docker run -it <image>'            → Create + start container
'docker container ls'               → List running containers
'docker container ls -a'            → List running + stopped containers
'docker start <container>'          → Start stopped container
'docker stop <container>'           → Stop running container
'docker logs <container>'           → Show container logs
'docker rm <container>'             → Remove container
'docker exec -it <container> <shell>'   → Enter running container
    
----------------------------------------------------------------------------------------------------------------------------------------------

Docker Images Commands:

'docker images'                   → Lists local images
'docker pull <image>'             → Download image from Docker Hub
'docker build -t <image> <path>'  → Build image from Dockerfile
'docker image rm <image>'         → Delete image
'docker inspect <image>'          → Show image metadata
'docker tag <source_image> <new_image>:<tag>'   → Create new tag for image

----------------------------------------------------------------------------------------------------------------------------------------------

Build Docker Image - Spring Boot:

1: Create docker file
2: Create jar files
3: Build docker image
4: Run docker image

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Archietecture:

Docker CLI:
    → Used to run docker commands
    → Sends requests to Docker Daemon via REST API

Docker Daemon:
    → Background service 
    → Core working component

    Responsible for:
        → build + run image
        → manage volumne + network
        → pull + push image

Docker Engine:
    → docker cli + docker daemon + REST APIs

----------------------------------------------------------------------------------------------------------------------------------------------

Workflow Example:

Command : 'docker run nginx'

CLI → Sends request to Docker Daemon
Daemon → Checks if image exists locally
If not → Pulls from Docker Hub
Daemon → Allocates storage + network
Daemon → Starts container process
Daemon → Returns container ID / status
CLI → Prints result in terminal

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Volumes:

→ Container data is temporary
→ Container stops / crashes / removed → data is lost
→ Persistent storage managed by Docker
→ MySQL container recreated → data still exists

→ Multiple containers can use the same volume
→ Used for shared logs + uploads + data

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Volume Implementation:

'docker volume create mysql-data'
    → creates a Docker-managed volume

'docker run --name mysql-db -v mysql-data : /var/lib/mysql mysql:8.0'
    → MySQL stores data in /var/lib/mysql

'docker volume inspect mysql-data'
    → display volume meta-data

'docker volume ls'
    → show all volumes

----------------------------------------------------------------------------------------------------------------------------------------------

Regular Folder Bind (Bind Mounts): 
    → Connect Host folder to container folder
    → Data stored directly on host machine
    → Container writes → saved in host folder
    → Not managed by Docker
    → Used for dev + testing

Implementation:

1: Create folder on host machine
2: Bind folder to the container
3: 'docker run --name mysql -v <host-folder> : <var/lib/mysql> Mysql.0'

----------------------------------------------------------------------------------------------------------------------------------------------

Network:
    → Used to communicate between containers
    → Use container names instead of IP address
    → Isolated from external system

----------------------------------------------------------------------------------------------------------------------------------------------

Bridge Network (Default):
    'docker run --network=bridge ubuntu'

→ Use internal IPs to communicate
→ Containers are isolated from host
→ Port-mapping is required
→ Provides good security.

----------------------------------------------------------------------------------------------------------------------------------------------

Host Network:
    'docker run --network=host ubuntu'

→ Containers use host network
→ No Port-mapping
→ Better performance but Less isolation

----------------------------------------------------------------------------------------------------------------------------------------------

None Network:
    'docker run --network=none ubuntu'

→ No network connectivity.
→ Cannot communicate with Host or other containers

----------------------------------------------------------------------------------------------------------------------------------------------

Custom Network:

→ Use container names to communicate
→ Better isolation than default bridge

'docker create network lbms-network -d bridge'
    → Creates user-defined bridge network

'docker run --network=lbms-network user-service'
    → Run container in custom network

----------------------------------------------------------------------------------------------------------------------------------------------

Port Mapping:

→ Your application runs on application port, 8000
→ When your application runs inside container, you cannot directly use the port
→ You need to map the application port to host port to use it

'docker run -it -p 6000:8000 user-service:latest'
    → App port    - 8000
    → Host port   - 6000

----------------------------------------------------------------------------------------------------------------------------------------------

Environmental variables:
    → Used to configure application properties at runtime

'docker run -it -e key=value <application-name>'

Ex:
    → server.port=${PORT}
    → docker run -it -e PORT=8000 user-service
    → Port value is passed at runtime

----------------------------------------------------------------------------------------------------------------------------------------------

Basic Logging and monitoring:

'docker logs <container_name_or_id>'
    → show container logs

'docker logs -t <container_name_or_id>'
    → show logs with timestamps

'docker stats <container_name_or_id>'
    → show container cpu, memory usage

'docker inspect <container_name_or_id>'
    → show container json meta-data

'docker top <container_name_or_id>'
    → shows processes running inside container

----------------------------------------------------------------------------------------------------------------------------------------------

Docker compose:
    Run and configure all the services together instead of one by one

Without docker compose:
    Manually build and run image for each service 1 by 1


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

Docker Ignore:
    → Works like .gitignore
    → Excludes files during build
    → Smaller image + fast re-builds

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Multi-Stage Builds:
    → Use multiple FROM statements in a single Dockerfile. 
    → Each FROM = new stage
    → You copy only required files to final stage

Advantages:
    → Small image size

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Hub:
    → Used to store and manage docker images
    → public + private properties

Login:

'docker login -u varun402'
    → username → varun402

----------------------------------------------------------------------------------------------------------------------------------------------

Push Image to Docker Hub:

1: Login in docker hub
2: Tag the image with username/image-name

Commands:

'docker build -t varun402/user-service:latest .'    → tag image
'docker push varun402/user-service:latest'          → push image

----------------------------------------------------------------------------------------------------------------------------------------------

Local Setup (Without Docker):

When you connect to MySQL using localhost:
    → spring.datasource.url=jdbc:mysql://localhost:3306/lbms
    → localhost → Your machine where mysql is running
    → App connects directly to local MySQL

Problem in Docker:

→ Inside a container
→ localhost → container itself, not your host machine
→ Containers are isolated
→ So, Spring Boot container cannot find MySQL using localhost

Solution — Shared Docker Network:
    → Run both MySQL and Spring Boot containers in the same custom Docker network.
    → Use container names to communicate instead of localhost.
    → spring.datasource.url=jdbc:mysql://mysql-db:3306/lbms

----------------------------------------------------------------------------------------------------------------------------------------------

Run Two application in same network:

'docker create network student-app-network -d bridge'       
    → create custom network

'docker run -d --name mysql-db --network student-app-network mysql:8.0'
    → run mysql in custom network

'docker run -d --name student-app --network student-app-network student-app'
    → run spring boot app in same network

----------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot + MySQL (Docker Compose Setup):
----------------------------------------------------------------------------------------------------------------------------------------------

version: '3.8'
services:

  mysql-db:
    image: mysql:8.0
    container_name: mysql-db
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword123
      MYSQL_DATABASE: ecommerce_db
    ports:
      - "3306:3306"
    volumes:
      - mysql_data:/var/lib/mysql
    networks:
      - app-network

  spring-boot-app:
    build: .
    container_name: spring-boot-app
    ports:
      - "8080:8080"
    environment:
      DB_HOST: mysql-db
      DB_NAME: ecommerce_db
      DB_USER: app_user
      DB_PASS: apppassword123
    depends_on:
      - mysql-db
    networks:
      - app-network

volumes:
  mysql_data:

networks:
  app-network:
    driver: bridge

----------------------------------------------------------------------------------------------------------------------------------------------

Flow:

1: mysql-db service starts first
    → MySQL initializes with your DB, username, and password.

2: spring-boot-app starts next
    → Reads environment variables
    → Connects to MySQL via hostname mysql-db
    → Runs migrations or schema updates 
3: Data persists inside the named volume mysql_data.

----------------------------------------------------------------------------------------------------------------------------------------------