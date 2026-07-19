----------------------------------------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------------------------------------

AWS Secrets Manager:
    → Stores sensitive data securely and encrypted in AWS
    → Values never in source code → safe even if repo is leaked
    → Secrets injected at runtime → update without redeploying
    → Access controlled via IAM → only allowed services can read

What to store:
    → DB username/password
    → JWT secret, API keys, auth tokens
    → Any sensitive config

Naming convention:
    Format  → /app-name/environment/service
    Example → /springboot-ecommerce/prod/database

----------------------------------------------------------------------------------------------------------------------------------------------

4 Ways Spring Boot Can Use Secrets:

1. Docker:
    → Pass secrets as env variables in docker run / docker-compose
    → Good for local/container deploy

2. Kubernetes:
    → Store in k8s Secret config → mount as env variables into pod
    → k8s manages secrets inside cluster

3. AWS SDK (most AWS-native for EC2/ECS):
    → App fetches secret from Secrets Manager at startup using SDK
    → Works because EC2/ECS has IAM Role with secretsmanager:GetSecretValue permission
    → Most common approach for Spring Boot on AWS

4. AWS Injects as Env Variables:
    → AWS injects secret values directly as env vars (ECS task, Lambda)
    → Spring Boot reads ${DB_USERNAME} from environment → no SDK needed

----------------------------------------------------------------------------------------------------------------------------------------------

AWS SDK Example (Fetch at startup):

Step 1 → application.properties (placeholders only):
    spring.datasource.username=${DB_USERNAME}
    spring.datasource.password=${DB_PASSWORD}
    spring.datasource.url=jdbc:mysql://${DB_HOST}:3306/${DB_NAME}

Step 2 → fetch secret before Spring uses datasource:
    @Component
    public class SecretLoader {

        @PostConstruct
        public void loadSecrets() {
            // fetch secret JSON from AWS
            AWSSecretsManager client = AWSSecretsManagerClientBuilder.defaultClient();
            String secret = client.getSecretValue(
                new GetSecretValueRequest()
                    .withSecretId("/springboot-app/db"))
                .getSecretString();

            // parse JSON
            JsonNode json = new ObjectMapper().readTree(secret);

            // set as system properties → Spring resolves ${DB_USERNAME} etc
            System.setProperty("DB_USERNAME", json.get("username").asText());
            System.setProperty("DB_PASSWORD", json.get("password").asText());
        }
    }

Flow:
    App starts → SecretLoader fetches JSON from AWS
    → sets system properties → Spring resolves ${DB_USERNAME}/${DB_PASSWORD}
    → connects to MySQL ✅

----------------------------------------------------------------------------------------------------------------------------------------------