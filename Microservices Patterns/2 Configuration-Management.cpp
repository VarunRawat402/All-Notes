------------------------------------------------------------------------------------------------------------------------------
Configuration Management Patterns:
------------------------------------------------------------------------------------------------------------------------------

→ It handle how microservices manage configuration, secrets in a dynamic, distributed environment.
→ Microservices run independently in multiple environments (dev, QA, prod)
→ Configuration may change frequently (URLs, DB credentials, feature flags)
→ Hardcoding configs → inflexible, error-prone, and insecure

A. Externalized Configuration:
    Move configs out of the service code
    Store in config files, environment variables, or config servers

B. Secrets Management:
    Sensitive data (DB passwords, API keys) must be secured
    Avoid storing in config files or code
    AWS Secrets Manager
    Kubernetes Secrets

C. Centralized Configuration:
    One central config source for all service 
    Services fetch configs at startup (or dynamically)
    Spring Cloud Config Server + Git backend

D. Dynamic Configuration Refresh:
    Services can reload configuration at runtime without redeploy
    Useful for feature flags, timeouts, endpoints

Code:
    @RefreshScope
    @Component
    public class PaymentServiceConfig {
        @Value("${payment.url}")
        private String paymentUrl;
    }

------------------------------------------------------------------------------------------------------------------------------
Centralized Configuration Implementation:
------------------------------------------------------------------------------------------------------------------------------

→ All microservices fetch configuration from one central place
→ Config is stored in Git (recommended) or local folder
→ Changes config without redeploying all services

------------------------------------------------------------------------------------------------------------------------------

1: Config Server:
    Reads configuration from Git / local
    Exposes config via HTTP endpoints

1: Add spring cloud config server Dependecy:
2: Annotate application with @EnableConfigServer:

3: Application properties:
    server.port=8888
    spring.application.name=config-server
    spring.cloud.config.server.git.uri=https://github.com/your-repo/configurations          //URL to fetch config from
    spring.cloud.config.server.git.clone-on-start=true                                  

------------------------------------------------------------------------------------------------------------------------------

Config Client
    Fetches configuration from Config Server on startup

1: Add spring cloud starter config

2: Application properties:
    spring.application.name=user-service
    spring.config.import=optional:configserver:http://localhost:8888                        //URL of the config server

------------------------------------------------------------------------------------------------------------------------------

Configuration File Naming and Profiles:
    → user-service.properties
    → user-service-dev.properties
    → user-service-prod.properties

Active Profile ( Client Side ):
spring.profiles.active=dev              //Config Server will load user-service-dev.properties

------------------------------------------------------------------------------------------------------------------------------

Practical Setup (Using Git Repo):

1: Create git-config folder, create user-service.properties config file
    git-config/                 
    └── limit-ms.properties

2: Initial Git:
    git init
    git add .
    git commit -m "Initial config"

3: Config Server property:
spring.cloud.config.server.git.uri=file:///C:/Users/User/Desktop/git-config

------------------------------------------------------------------------------------------------------------------------------

Instead of using Git, configurations can be loaded from the project itself:

In the microservice:
spring.config.import=optional:classpath:/config/

Place your config files inside:
src/main/resources/config/

------------------------------------------------------------------------------------------------------------------------------