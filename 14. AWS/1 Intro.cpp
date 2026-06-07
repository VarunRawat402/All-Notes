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

7: Lambda → Run small code pieces without servers (background tasks)

8: SQS → Message queue (for async tasks like sending emails)

9: AWS SDK → Set of Libraries that lets you use AWS Services directly from code

10: Elastic Beanstalk → Auto-deploy tool (just upload jar, AWS handles setup)

------------------------------------------------------------------------------------------------------------------------------------------------------------

IAM (Identity and Access Management):
    → It controls permission of Users and Machines to access on AWS Services

1: Users
    → Individual people (you, teammate, admin)
    → Long-term identity for humans

How developers authenticate:
    → AWS Console (browser): username + password
    → CLI / AWS SDK (local laptop): Access Key + Secret Key tied to that user

2: Groups
    → Team departments
    → Examples: Developers, Admins, DevOps
    → Attach Policy once to the group → every user in group gets same permissions
    → Easier than assigning policies to each user separately
    → Add/remove user from group to grant or revoke access

3: Roles
    → Temporary permissions for apps/services or users
    → EC2 uses roles to access temporary permission to perform actions on AWS Services
    → Automatically refreshed and gets new permissions before old expires
    → Users can temporarily assume Role to perform actions by switching to Role

4: Policy
    → JSON document that defines allowed or denied actions
    → Attached to User, Group, or Role

Examples:
    → Permission to read / write objects in a specific S3 bucket
    → Permission to get secrets from Secrets Manager

------------------------------------------------------------------------------------------------------------------------------------------------------------

EC2 (Elastic Compute Cloud):
    → Its a virtual machine to run your application

Core Components ( what you configure when creating an instance):

1: Instance
    → The actual virtual computer where your app runs

2: Instance-Type
    → How powerful the machine is (CPU + RAM)
    → Examples: t3.micro (small/cheap), m5.large, r5.large (bigger)

3: AMI (Amazon Machine Image)
    → Operating System
    → Examples: Windows / macos / linux

4: EBS Volume
    → Virtual hard disk attached ( HD / SSD )
    → Stores OS, jar, logs, files — data stays even if instance restarts

5: Security Group
    → Firewall: controls WHO can connect and on WHICH port
    → You must open ports explicitly or traffic is blocked

6: Key Pair
    → SSH login credentials (public key on EC2 + private key .pem file with you)
    → Used to securely log into the instance from your machine

------------------------------------------------------------------------------------------------------------------------------------------------------------

Networking & IP:

→ Every instance gets a Public IP (reachable from internet) and Private IP (internal AWS network)
→ Public IP changes when you STOP and START the instance again
→ Fix: attach Elastic IP (static/fixed public IP) so IP does not change after restart

SSH (Secure Shell):
    → It is used to securely connect to a remote computer over the network and run commands remotely

Security Group — common rules to allow:

→ SSH (port 22)   → So YOU can log into the server terminal (admin work: install Java, run jar)
→ HTTP (port 80)  → So users can open your app in a browser (no SSL)
→ HTTPS (port 443)→ Same as HTTP but encrypted (production)
→ Custom port     → Spring Boot default is 8080 — open this if app is not behind port 80/443

------------------------------------------------------------------------------------------------------------------------------------------------------------

How to connect to EC2 Instance:

1: Using Key-Pair (most common for developers)
    → Download .pem file when creating instance
    → Command: ssh -i key.pem ec2-user@<public-ip>

2: Using AWS Console
    → EC2 → Select instance → Connect → "EC2 Instance Connect" or "Session Manager"
    → Browser-based terminal, no manual ssh command needed

------------------------------------------------------------------------------------------------------------------------------------------------------------

Run Spring Boot Application on EC2 Instance (manual deploy flow):

1: Create EC2 Instance

2: Build Spring Boot jar on your local machine
    → mvn clean package → get .jar from target/

3: Copy jar file to EC2 Instance
    → Use scp with your .pem key, or upload via S3 then download on EC2

4: SSH into EC2 and install Java
    → Instance needs Java runtime to run the jar

5: Run application in background using jar
    → java -jar app.jar (use nohup or systemd so it keeps running after you disconnect SSH)

------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS Secrets Manager:

What it is:
    → It is used to store sensitive data securely and encrypted

What you store here:
    → Database username / password
    → API keys, auth tokens
    → Any sensitive config (JWT secret, third-party keys, etc.)

→ Values are NOT in source code → safer if repo is leaked
→ Secrets are injected at runtime
→ You can rotate/update passwords in AWS without redeploying code
→ Access is controlled via IAM — only allowed services/users can read secrets

Secret naming convention (organize by app + environment + service):

Format:  /application-name/environment/service
Example: 
    /springboot-ecommerce/prod/database
    → app name     → prod env  → database credentials

------------------------------------------------------------------------------------------------------------------------------------------------------------

How Spring Boot application can use secrets (4 ways):

1: Docker
    → Pass secrets as environment variables in docker run / docker-compose
    → Good for local or container deploy; secret value still comes from somewhere (env file, CI, etc.)

2: Kubernetes (k8s)
    → Store in k8s Secret config file → mount as env variables into pod
    → K8s manages secret inside cluster; separate from AWS Secrets Manager unless you sync them

3: AWS SDK (programmatic fetch — most "AWS native" for EC2/ECS)
    → App uses AWS Secrets Manager Client at startup
    → Fetches secret JSON from AWS → sets DB_USERNAME, DB_PASSWORD, etc.
    → Works because instance/task has IAM Role with secretsmanager:GetSecretValue permission

4: AWS Secrets Manager + environment variables (no SDK in app code)
    → AWS injects secret values as env vars on the service (e.g. ECS task definition, Lambda env)
    → Spring Boot reads ${DB_USERNAME} from environment — same as option 1 but source is AWS

------------------------------------------------------------------------------------------------------------------------------------------------------------

Example: Inject MySQL username and password using AWS SDK

Step 1 — application.properties (placeholders only, no real passwords):

    # Use environment variables (no hardcoded values!)
    spring.datasource.username=${DB_USERNAME}
    spring.datasource.password=${DB_PASSWORD}
    spring.datasource.url=jdbc:mysql://${DB_HOST}:3306/${DB_NAME}

Step 2 — Load secrets from AWS before Spring uses datasource (@PostConstruct runs early):

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

Flow in one line:
    App starts → SecretLoader fetches JSON from Secrets Manager → sets System properties
    → Spring resolves ${DB_USERNAME} / ${DB_PASSWORD} → connects to MySQL

------------------------------------------------------------------------------------------------------------------------------------------------------------



