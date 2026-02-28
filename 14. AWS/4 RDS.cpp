------------------------------------------------------------------------------------------------------------------------------------------------------------
RDS:
------------------------------------------------------------------------------------------------------------------------------------------------------------

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