------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Configuration Management Patterns:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Microservices run independently in multiple environments (dev, QA, prod)
→ Configuration may change frequently (URLs, DB credentials, feature flags)
→ Hardcoding configs → inflexible, error-prone

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Centralized Configuration:
    → All Services will fetch configs from config server dynamically
    → Spring Cloud Config Server + Git backend


2. Secrets Management:
    → Avoid storing Sensitive data in config files or code
    → Sensitive data must be secured
    → AWS Secrets Manager / Kubernetes Secrets / Docker env

Code:
    @RefreshScope
    @Component
    public class PaymentServiceConfig {
        @Value("${payment.url}")
        private String paymentUrl;
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Centralized Configuration Implementation:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

→ All microservices fetch configuration from 1 config server
→ Config is stored in Git (recommended) or local folder

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Config Server:
    → Reads configuration from Git / local

1: Add spring cloud config server Dependecy:
2: Annotate application with @EnableConfigServer:

3: Application properties:
    server.port=8888
    spring.application.name=config-server
    spring.cloud.config.server.git.uri=https://github.com/your-repo/configurations          //URL to fetch config from
    spring.cloud.config.server.git.clone-on-start=true                                  

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Config Client
    → Fetches configuration from Config Server on startup

1: Add spring cloud starter config

2: Application properties:
    spring.application.name=user-service
    spring.config.import=optional:configserver:http://localhost:8888                        //URL of the config server

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Configuration File Naming and Profiles:
    → user-service.properties
    → user-service-dev.properties
    → user-service-prod.properties

Active Profile(Service):
spring.profiles.active=dev              //Config Server will load user-service-dev.properties

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------------------------------------------------