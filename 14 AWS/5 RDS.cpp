------------------------------------------------------------------------------------------------------------------------------------------------------------
RDS (Relational Database Service):
------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Managed database on AWS 
→ no manual installation or maintenance

Features:
    → Install Database software 
    → Apply patches and Updates
    → Automatic Backups 
    → Scale storage 
    → Failover strategy (if primary fails, backup takes over)

------------------------------------------------------------------------------------------------------------------------------------------------------------

Key Configuration Options:

1. Database Type:
    → MySQL, PostgreSQL, Aurora

2. Version:
    → MySQL 8.0, MySQL 5.7 etc

3. Template:
    → Production  → high availability settings
    → Dev/Test    → cheaper, less redundancy
    → Free Tier   → t3.micro, minimal config

4. Availability:
    → Single DB    → one instance, cheaper
    → Multi-AZ     → AWS creates standby in different zone
                   → primary fails → standby takes over automatically → 0 downtime

5. Storage:
    → 20GB, 50GB etc → can auto-scale

6. Instance Type:
    → db.t3.micro  → dev/free tier
    → db.t3.medium → production

7. Connectivity:
    → VPC (Virtual Private Cloud) → private network where your AWS resources live
      → You define: IP ranges, subnets, routing, security rules
    → Subnet → smaller network inside VPC, lives in one Availability Zone
      → Public Subnet  → has route to internet
      → Private Subnet → no internet access (RDS goes here)
    → Create subnets in multiple zones → if one zone fails, other still running

8. Security Group:
    → Controls who can connect to RDS
    → Public access → NO (never expose DB to internet)
    → Allow only EC2 instance security group to connect ✅

9. Authentication:
    → Username + Password set during creation

10. Backup:
    → Automatic daily backups → 7 or 30 day retention

------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Boot Connection:

spring.datasource.url=jdbc:mysql://database-1.xxx.us-east-1.rds.amazonaws.com:3306/yourdb
spring.datasource.username=admin
spring.datasource.password=admin123!

Connect via terminal:
    mysql -h <rds-endpoint> -P 3306 -u <username> -p

------------------------------------------------------------------------------------------------------------------------------------------------------------

Best Practices:
    → Never enable public access → keep RDS in private subnet
    → Only allow EC2 security group to reach RDS → not open to internet
    → Use Multi-AZ for production → 0 downtime on failure
    → Use Secrets Manager to store DB password → not in application.properties

------------------------------------------------------------------------------------------------------------------------------------------------------------