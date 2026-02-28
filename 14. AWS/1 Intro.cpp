------------------------------------------------------------------------------------------------------------------------------------------------------------
AWS Intro:
------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS Tools:

1: EC2 → Virtual computer to run your Spring Boot jar file

2: IAM → Security manager (who can access what)

3: S3 → Online storage for files (images, PDFs, backups)

4: RDS → Managed database (like MySQL/PostgreSQL without installing)

5: CloudWatch → App monitoring & logs

6: Secrets Manager → Store passwords safely (not in code)

7: Elastic Beanstalk → Auto-deploy tool (just upload jar, AWS handles setup)

8: Lambda → Run small code pieces without servers (background tasks)

9: SQS → Message queue (for async tasks like sending emails)

10: AWS SDK → Set of Libraries that lets you use AWS Services directly from code

------------------------------------------------------------------------------------------------------------------------------------------------------------

IAM:
    → It controls permission of Users and Machines to access on AWS Services

Users:
    → Individual people
    → You / your teammate
    → Gets username and password for AWS Console login
    → Gets AccessKey and SecretKey for CLI / AWS SDK to use AWS Services on local

Groups:
    → Team departments
    → Developers, Admins
    → Give permissions to groups and add users to these groups instead of giving each user permissions

Roles:
    → Temporary permissions for apps/services or users
    → EC2 uses roles to access temporary permission to perform actions on AWS Services
    → Automatically refreshed and gets new permissions before old expires
    → Users can temporarily assume Role to perform actions by switching to Role

Policy:
    → Permissions to access resources
    → read / write from S3 Bucket

Note:
→ In production EC2 uses IAM Role to access AWS Services
→ No SecretKey or AccessKey is required

→ Developers use username and password to login in AWS Console
→ Use SecretKey and AccessKey to perform actions on AWS services from local 

------------------------------------------------------------------------------------------------------------------------------------------------------------

EC2:
    → It is a virtual machine to run your application

Core Components:

1: Instance         → The virtual computer where application runs
2: Instance-Type    → CPU/RAM specs (t3.micro / m5.large / r5.large)
3: AMI              → Operating System ( Windows/ Linux DVD/ MacOS )
4: EBS Volume       → Virtual hard disk ( Hard disk / SSD )
5: Security Group   → Firewall rules of who can connect to EC2
6: Key Pair         → SSH login key to connect to EC2 instance

→ Public Ip changes after stop/start
→ Use ElasticIp or FixedIp

→ Allow SSH traffic:  You can connect to instance using SSH
→ Allow HTTP Traffic: You can connect to instance using HTTP / Browser

SSH : It is a protocol used to securely connect to a remote computer over network

How to connect to EC2 Instance:
    1: Using Key-Pair:
    2: AWS Console to connect

------------------------------------------------------------------------------------------------------------------------------------------------------------

Run Spring Boot Application in EC2 Instance:

1: Create EC2 Instance and expose SSH, HTTP and Springboot port
2: Create SpringBoot Jar files
3: Copy jar file snapshot to EC2 Instance
4: Install Java in EC2 Instance
5: Run Application in background using Jar snapshot

------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS SECRET MANAGER:

→ It is used to store username, passwords, auth tokens or any sensitive configurations securely and encrypted
→ Values are not added in the code it is passed at runtime using secret manager
→ Only services which has IAM role can access secrets so better security control

Naming Convention:
/application-name/environment/service
/springboot-ecommerce/prod/database

------------------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot application uses secrets:

1: You can pass secrets as env variables using Docker 
2: You can pass secrets as env variables using k8s secret config file 
3: You can use AWS Secret Client to fetch secrets using Secret manager
4: You can pass secrets as env variables using AWS Secret manager

------------------------------------------------------------------------------------------------------------------------------------------------------------

Inject MYSQL username and password using AWS SDK:

# Use environment variables (no hardcoded values!)
spring.datasource.username=${DB_USERNAME}
spring.datasource.password=${DB_PASSWORD}
spring.datasource.url=jdbc:mysql://${DB_HOST}:3306/${DB_NAME}

@Component
public class SecretLoader {
    
    @PostConstruct
    public void loadSecrets() {
        // Get secret from AWS
        AWSSecretsManager client = AWSSecretsManagerClientBuilder.defaultClient();
        String secret = client.getSecretValue(new GetSecretValueRequest()
                .withSecretId("/springboot-app/db")).getSecretString();
        
        // Parse JSON
        JsonNode json = new ObjectMapper().readTree(secret);
        
        // Set as System environment variables (available to entire app)
        System.setProperty("DB_USERNAME", json.get("username").asText());
        System.setProperty("DB_PASSWORD", json.get("password").asText());
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------



