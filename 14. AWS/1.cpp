------------------------------------------------------------------------------------------------------------------------------------------------------------
AWS + SpringBoot
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

AWS S3 ( Simple Storage Service ):

1: Bucket:
    → Top-level folder (global unique name)

2: Object:
    → Actual File (with data + metadata)

3: Key:
    → Unique key / File path / location of object

4: Region:
    → Physical location of storage

Production:
    → Application connects to S3 automatically using IAM Role

Local:
    → Application needs AccessKey and SecretKey to access S3 
    → Use AWS CLI to configure AccessKey and SecretKey on machine so application can read it automatically
    → Set Environment variables in Laptop

------------------------------------------------------------------------------------------------------------------------------------------------------------

RDS:
    → It is used to run your Database on AWS 

Features:
→ Install Database software 
→ Apply patches and Updates
→ Automatic Backups 
→ Scale storage 
→ Failover strategy (if primary fails, backup takes over)

Configuration:

1: Database Type:
    → Mysql, PostgreSQL, Aurora

2: Version:
    → MySQL 8 / MySQL 5.7

3: Template:
    → AWS Pre-configured settings for different environments
    → Production: 
    → Dev/Test:
    → Free-Tier

4: Availability: 
    → SingleDB or Multi-AZ
    → AWS automatically creates backup of DB in different availability zones
    → If primary fails, backup takes over with 0 downtime

5: Storage:
    →20GB
    →50GB

6: Instance Type:
    → db.t3.micro
    → db.t3.medium

7: Connectivity:
    → VPC / Subnet / Public Access

→ VPC ( virtual private cloud ):
    → It is a private virtual network where you define your custom configurations
    → IP address range, Subnets, routing
    → Internet access, Security rules, Gateways

→ Subnet:
    → Smallet network inside VPC
    → Each subnet lives in one AZ
    → Public Subnet : Has route to Internet Gateway
    → Private Subnet : No Internet route
    → You create multiple subnets in multiple zones so if one fails, second is still running


8: Security Group: 
    → who can connect to RDS
    → Public : No
    → EC2 Instance : yes

9: Authentication:
    → username and password

10: Backup:
    → 7Days / 30Days

------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Boot RDS Settings:

→ Database: MySQL 8.0
→ Template: Production
→ Instance: db.t3.medium
→ Storage: 20GB gp3
→ Public Access: NO
→ Backup: 7 days
→ Password: YourStrongPassword123!

Spring Boot connection:
    → jdbc:mysql://database-1.xxx.us-east-1.rds.amazonaws.com:3306/yourdb

Connect to RDS using cmd:
    → mysql -h <endpoint> -P 3306 -u <username> -p

------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS LAMBDA:
    → lets you run code when triggered
    → In EC2 Instance, Application runs all the time even if nothing is getting processed
    → In Lambda, Code runs only when request comes or processing happening otherwise stops

Features & Limitations:
    1: Serverless → Runs your code without creating any server
    2: Pay only for the execution time
    3: Auto scales instantly
    4: Timeout limit is 15 minutes → if request takes longer than that, it will not be processed
    5: Memory up to 10 GB
    6: Code size up to 250 MB

Event Triggers:
    1: HTTP Request → API Gateway → Lambda
    2: File Upload → S3 → Lambda
    3: Database Change → DynamoDB → Lambda
    4: Schedule → CloudWatch Events → Lambda
    5: Message → SQS → Lambda

------------------------------------------------------------------------------------------------------------------------------------------------------------

How Lambda works:

1: You create a lambda function
    → Create a java code / class in IDE
    → Create jar file of that specific code
    → Upload it on AWS Lambda

2: Add a trigger
    → Create a trigger to run the lambda
    → Attach the trigger to lambda

------------------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle:
    Trigger → Lambda Container starts → Runs your code → Returns result → Container may stay warm for reuse

------------------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot Application Invoking Lambda:

1: Create AWS Lambda client
2: Create invokeRequest
3: Use invoke method and pass invoke request to run the lambda

@Service
public class ReportService {
    
    @Autowired
    private AWSLambda lambdaClient;
    
    public void generateReportAsync(ReportRequest request) {
        // Async report generation
        InvokeRequest invokeRequest = new InvokeRequest()
            .withFunctionName("report-generator-lambda")
            .withPayload(JsonUtils.toJsonString(request));
        
        lambdaClient.invoke(invokeRequest);
        // Returns immediately, Lambda runs in background
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------

Example of Thumbnail Generator on Lambda:

Lambda Code:

public class ThumbnailGenerator implements RequestHandler<S3Event, String> {
    public String handleRequest(S3Event event, Context context) {
        // Get uploaded file from S3 event
        String bucket = event.getRecords().get(0).getS3().getBucket().getName();
        String key = event.getRecords().get(0).getS3().getObject().getKey();
        
        // Download image, create thumbnail, upload back
        // Runs only when image uploaded
        // Spring Boot doesn't wait for this - async!
        
        return "Thumbnail created";
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------

Real Use Cases of Lambda:

Use Case 1: User Registration:
    Spring Boot: Handles registration form
    Lambda: Sends welcome email (triggered by DB insert)

Use Case 2: File Processing:
    Spring Boot: Accepts file upload
    Lambda: Converts PDF to images (triggered by S3 upload)

Use Case 3: Scheduled Tasks:
    Spring Boot: Main application
    Lambda: Daily report generation (triggered by CloudWatch schedule)

------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS SECRET MANAGER:
It is used to store username, passwords, auth tokens or any sensitive configurations securely and encrypted
Values are not added in the code it is passed at runtime using secret manager
Only services which has IAM role can access secrets so better security control

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