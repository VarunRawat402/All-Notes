------------------------------------------------------------------------------------------------------------------------------
Centralized Configuration:
------------------------------------------------------------------------------------------------------------------------------

How to setup the Centralized Configuration:

Config Server:
    A centralized server that stores/fetch configuration properties from git

1: Dependecies:
    //Spring Cloud Config Server
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

Practical ( With GIT ):

Lets create a small application on Centralized Configurations:
We will Load configuration from git using Config server and then Limit service will fetch its config from server

Git Repo:
1: We created the folder "git-config" where we will store all our configuration ( same folder where MS are present )
2: We created limit service configuration "limit-ms.properties" 
    (make sure the name of the configuration file is same as the microservice name )
3: Then we did "git init" and added this file to the git

Config Server:

1: Configured the Config Server
    spring.cloud.config.server.git.uri=file:///C:/Users/User/Desktop/CentralizedConfigMS/git-localconfig-repo
    //Actual path had backward slashes but, we have to have forwards slashes here so, it can run

------------------------------------------------------------------------------------------------------------------------------

Practical ( With Local ):

//Loads the config properites from resources/config package
spring.config.import=optional:classpath:/config/

------------------------------------------------------------------------------------------------------------------------------