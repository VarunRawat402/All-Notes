------------------------------------------------------------------------------------------------------------------------------
Centralized Configuration:
------------------------------------------------------------------------------------------------------------------------------

A Config Server allows all microservices to fetch their configuration from a single centralized location (Git or local folder). 
This avoids manually updating configuration in each service.

How to setup the Centralized Configuration:

Config Server:
    A dedicated Spring Boot application that exposes configuration stored in Git (remote/local).

1: Dependecies:
    <dependency>
        <groupId>org.springframework.cloud</groupId>
        <artifactId>spring-cloud-config-server</artifactId>
    </dependency>


2: Annotations:
    @SpringBootApplication
    @EnableConfigServer
    public class ConfigServerApplication {
        public static void main(String[] args) {
            SpringApplication.run(ConfigServerApplication.class, args);
        }
    }

3: Application properties:
    server.port=8888
    spring.application.name=config-server
    spring.cloud.config.server.git.uri=https://github.com/your-repo/configurations          //Git url
    spring.cloud.config.server.git.clone-on-start=true                                  

------------------------------------------------------------------------------------------------------------------------------

Config Client:

1: Dependecies:
    //Spring Cloud Config Client
    <dependency>
        <groupId>org.springframework.cloud</groupId>
        <artifactId>spring-cloud-starter-config</artifactId>
    </dependency>

2: Application properties:
    spring.application.name=service1
    spring.config.import=optional:configserver:http://localhost:8888               //url of the Config server

------------------------------------------------------------------------------------------------------------------------------

Practical Setup (Using Git Repo):

Goal: Load config from Git using Config Server, and Limit Service fetches its config through the server.

1. Git Repo Setup:

Create a folder named git-config.
Inside it, create the file limit-ms.properties.
(The file name must match the microservice name: spring.application.name=limit-ms)
Run:
    git init
    git add .
    git commit -m "Initial config"

2: Config Server Setup (Local Git Path)
spring.cloud.config.server.git.uri=file:///C:/Users/User/Desktop/CentralizedConfigMS/git-localconfig-repo

Note: Even on Windows, forward slashes must be used in the URI.

------------------------------------------------------------------------------------------------------------------------------

Instead of using Git, configurations can be loaded from the project itself:

In the microservice:
spring.config.import=optional:classpath:/config/

Place your config files inside:
src/main/resources/config/

------------------------------------------------------------------------------------------------------------------------------