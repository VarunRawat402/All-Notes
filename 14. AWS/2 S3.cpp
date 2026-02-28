----------------------------------------------------------------------------------------------------------------------------------------------
AWS S3 ( Simple Storage Service ):
----------------------------------------------------------------------------------------------------------------------------------------------

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

S3 Bucket Implementation:

1: Go to AWS Console → S3 → Create Bucket
    → Name should be unique + lowercase + no underscores

2: Choose a region

3: Configure:
    → Object Ownership: Can give bucket access to other AWS users
    → Public Access settings: Who can access the S3 Bucket
    → versioning + tag + encryption

4: Upload files via the Objects tab

----------------------------------------------------------------------------------------------------------------------------------------------

S3 Static Web Hosting:
    → S3 allows you to host a website directly from an Amazon S3 bucket without using servers.
    → It serves static content such as HTML, CSS, JavaScript, and images.

Note:
→ No Backend Code ( Springboot, php )
→ Each s3 Bucket can act as a website hosting
→ Configure index.html ( Home page ) & error.html ( error page )
→ Can use route53 for custom domain
→ Can use cloudFront for caching and HTTPS

----------------------------------------------------------------------------------------------------------------------------------------------

S3 Static Web Hosting:
    → Host a static website (HTML, CSS, JS, images) directly from S3 — no server needed.

→ No backend support (e.g. Spring Boot, PHP)
→ Set 'index.html' as home, 'error.html' for errors
→ Optionally use Route 53 for custom domain, CloudFront for HTTPS & caching

Setup:

Bucket → Properties → Static Website Hosting → Enable
Set index & error documents, add redirect rules if needed

Bucket Policy:
    {
    "Version": "2012-10-17",
    "Statement": [{
        "Effect": "Allow",
        "Principal": "*",
        "Action": "s3:GetObject",
        "Resource": "arn:aws:s3:::BUCKET-NAME/*"
    }]
    }

----------------------------------------------------------------------------------------------------------------------------------------------

