------------------------------------------------------------------------------------------------------------------------------------------------------------
IAM (Identity and Access Management):
------------------------------------------------------------------------------------------------------------------------------------------------------------

→ Controls WHO can access WHAT in AWS (users, apps, services)

------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Users:
    → Individual people (you, teammate, admin)
    → Long-term identity for humans

How to authenticate:
    → AWS Console (browser)  → username + password
    → CLI / SDK (local)      → Access Key + Secret Key

------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Groups:
    → Collection of users (Developers, Admins, DevOps)
    → Attach policy ONCE to group → all users in group get same permissions
    → Add user to group → gets permissions | Remove → loses permissions
    → Much easier than assigning policies to each user individually

------------------------------------------------------------------------------------------------------------------------------------------------------------

3. Roles:
    → Temporary permissions
    → EC2 uses a role to access S3, RDS, Secrets Manager etc
    → No long-term credentials → permissions auto-refresh before expiry
    → Users can also temporarily ASSUME a role to perform specific actions

------------------------------------------------------------------------------------------------------------------------------------------------------------

4. Policies:
    → JSON document defining what is ALLOWED or DENIED
    → Attached to User, Group, or Role
    → Examples:
      → Allow read/write to specific S3 bucket
      → Allow fetching secrets from Secrets Manager

------------------------------------------------------------------------------------------------------------------------------------------------------------

Best Practices:
    → Never use root account for daily work → create IAM users
    → Use Groups to manage permissions at scale
    → Use Roles for EC2/Lambda → never hardcode Access Keys in code
    → Give minimum permissions needed (Principle of Least Privilege)

------------------------------------------------------------------------------------------------------------------------------------------------------------