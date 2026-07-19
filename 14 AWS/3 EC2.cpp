------------------------------------------------------------------------------------------------------------------------------------------------------------
EC2 (Elastic Compute Cloud):
------------------------------------------------------------------------------------------------------------------------------------------------------------\

Core Components:

1. Instance:
    → The actual virtual computer where your app runs

2. Instance Type:
    → Defines CPU + RAM power of the machine
    → t3.micro → small, cheap (free tier)
    → m5.large, r5.large → bigger, production use

3. AMI (Amazon Machine Image):
    → The operating system (Windows / macOS / Linux)
    → Choose when creating instance

4. EBS Volume:
    → Virtual hard disk attached to instance (HDD/SSD)
    → Stores OS, JAR, logs, files
    → Data persists even if instance restarts

5. Security Group:
    → Firewall → controls WHO can connect on WHICH port
    → All traffic blocked by default → must explicitly open ports

Common ports to open:
    → Port 22   → SSH (so YOU can log into server terminal)
    → Port 80   → HTTP (users access app in browser)
    → Port 443  → HTTPS (encrypted, production)
    → Port 8080 → Spring Boot default (if not behind 80/443)

6. Key Pair:
    → SSH login credentials
    → Public key stored on EC2, private key (.pem file) stays with you
    → Used to securely connect to instance from your machine

------------------------------------------------------------------------------------------------------------------------------------------------------------

Networking:
    → Every instance gets a Public IP (internet) + Private IP (internal AWS)
    → Public IP CHANGES when you stop + start instance ⚠️
    → Fix → attach Elastic IP (static IP that never changes)

SSH (Secure Shell):
    → Securely connect to remote server and run commands from your terminal

------------------------------------------------------------------------------------------------------------------------------------------------------------

How to Connect to EC2:

1. Key Pair (most common):
    ssh -i key.pem ec2-user@<public-ip>

2. AWS Console:
    → EC2 → Select instance → Connect → EC2 Instance Connect
    → Browser-based terminal, no SSH command needed

------------------------------------------------------------------------------------------------------------------------------------------------------------

Deploy Spring Boot JAR on EC2 (Manual Flow):

1. Create EC2 instance → configure AMI, instance type, security group, key pair
2. Build JAR locally → mvn clean package → get JAR from target/
3. Copy JAR to EC2:
    → scp -i key.pem app.jar ec2-user@<public-ip>:/home/ec2-user/
    → OR upload to S3 → download on EC2
4. SSH into EC2 → install Java
    → sudo yum install java-17
5. Run app in background (keeps running after SSH disconnect):
    → nohup java -jar app.jar &

------------------------------------------------------------------------------------------------------------------------------------------------------------