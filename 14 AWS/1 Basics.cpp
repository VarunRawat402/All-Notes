------------------------------------------------------------------------------------------------------------------------------------------------------------
AWS Notes:
------------------------------------------------------------------------------------------------------------------------------------------------------------

AWS Core Services:

1. EC2 (Elastic Compute Cloud):
    → Virtual machine in the cloud
    → Run your Spring Boot JAR, configure OS, install software

2. RDS (Relational Database Service):
    → Managed database (MySQL, PostgreSQL etc)
    → Automatic backups, scaling, patching

3. S3 (Simple Storage Service):
    → Online file storage
    → Store images, PDFs, backups, static files
    → Accessible from anywhere via URL

4. IAM (Identity and Access Management):
    → Security manager → controls WHO can access WHAT in AWS
    → Create users, roles, permissions
    → Never use root account → always use IAM users

5. CloudWatch:
    → Monitoring + logging service
    → View app logs, set alerts, track CPU/memory usage

6. Secrets Manager:
    → Store sensitive data safely (DB passwords, API keys)
    → Never hardcode credentials → fetch from Secrets Manager at runtime

7. Lambda:
    → Run small pieces of code WITHOUT managing servers
    → Triggered by events (API call, S3 upload, SQS message)
    → Pay only when code runs → cost efficient for background tasks

8. SQS (Simple Queue Service):
    → Managed message queue → async communication between services
    → Similar to Kafka → producer sends → consumer processes later
    → Use for: sending emails, notifications, background jobs

9. Elastic Beanstalk:
    → Auto-deploy platform → just upload your JAR
    → AWS handles: EC2, load balancing, scaling, monitoring
    → Easiest way to deploy Spring Boot to AWS

10. AWS SDK:
    → Java library to interact with AWS services directly from code
    → Use to: upload to S3, read from SQS, fetch secrets etc

------------------------------------------------------------------------------------------------------------------------------------------------------------


