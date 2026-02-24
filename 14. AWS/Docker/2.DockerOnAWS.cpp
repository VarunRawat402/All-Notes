----------------------------------------------------------------------------------------------------------------------------------------------
AWS Docker:
----------------------------------------------------------------------------------------------------------------------------------------------

ECR ( Elastic Container Registry ):
    → Store and manage docker images in AWS

Features:
    → Secured and Authorized AWS users can access it onlyu
    → Automatic scanning to detect vulnerabilities
    → Automatic deleting of old and un-taged images
    → Replicate images on different region for faster access

----------------------------------------------------------------------------------------------------------------------------------------------

ECS ( Elastic Container Service ):
    → Orchestration service that runs docker containers on EC2 instances
    → Pulls images from ECR

Features:

1: Cluster: Group of EC2 instances.

2: Task Definition :
        → Json Config file:
            → image details
            → cpu + memory requirements
            → ports + env variables
            → health-checks + logging

        → In simple terms, a Task = one running instance of your application.
        → Two tasks = two instances (containers) of the same application.

3: Service :
    → manage running instances in the cluster
    → Each service manage 1 type of task / 1 application
    → Configuration:
        → Number of tasks
        → Load balancer + auto scaling
        → Deployment type

----------------------------------------------------------------------------------------------------------------------------------------------

ECR Implementation:
    All commands are provided by AWS ECR.

1: Create repo in ECR
2: Authenticate docker with ECR 
3: Build + tag image with ECR repo url
4: Push the image to ECR

----------------------------------------------------------------------------------------------------------------------------------------------

ECS Implementation:

1: Create a cluster and configure machine (Fargate or EC2).
2: Create and configure task for image
3: Create service and connect to task
4: 10 application needs 10 services

----------------------------------------------------------------------------------------------------------------------------------------------

Health monitoring:

1: Create health-check API endpoint in application
2: ECS hits the api every 30 seconds
3: If API responds, container is marked healthy
4: If not, ECS terminates the container and start healthy one

----------------------------------------------------------------------------------------------------------------------------------------------

Deploying a New Version:

1: Build + push new version image to ECR
2: In ECS, open service choose force-update
3: ECS starts new containers
4: If new are healthy, remove old ones
5: If not, remove new ones and start again

----------------------------------------------------------------------------------------------------------------------------------------------

How to cleanup:

1: Open service and set the running tasks to 0
2: Force-Update the service
3: Delete service + cluster

----------------------------------------------------------------------------------------------------------------------------------------------

EC2 Instance:
    → It stands for Elastic compute cloud
    → It is a virtual machine that run on AWS infrastructure.

→ Instead of buying and installing physical servers, you can launch a virtual server within seconds.

----------------------------------------------------------------------------------------------------------------------------------------------

Install Docker on EC2 Instance:
    sudo apt-get update
    sudo apt-get install docker.io

----------------------------------------------------------------------------------------------------------------------------------------------

S3 Bucket Implementation:

1: Log into AWS Console
2: Navigate to S3 Service → click Create Bucket 
    → Name should be unique
    → No uppercases and underscores
3: Choose AWS region 
4: Configure:
    → Object Ownership: Can give bucket access to other AWS users
    → Block Public Access settings: Who can access the S3 Bucket
    → Versioning: Create versioning like gitHub
    → Tags: Lable the Bucket
    → Encryption: Choose Type of Encryption you need for sensitive files in the bucket
5: Upload Files:
    → Go to Objects tab -> Click Upload

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

S3 Web Hosting Implementation:

1: After bucket creation, click on your bucket name
2: Go to Properties tab -> Scroll down to Static website hosting
3: Click Edit -> Select Enable
4: Configure:
    Hosting type: Enable static website hosting
    Index document: index.html
    Error document: error.html (optional)
    Redirection Rules: Based on path redirect to your html files    
        Example: /home -> index.html & /error -> error.html

Bucket Policy Implementation:
1: Go to Permissions tab
2: Scroll to Bucket policy -> Click Edit
3: Add Policies based on your requirements:
    Example: ReadOnly Policy, Public can read this file now
    {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Sid": "PublicReadGetObject",
                "Effect": "Allow",
                "Principal": "*",
                "Action": "s3:GetObject",
                "Resource": "arn:aws:s3:::BUCKET-NAME/*"
            }
        ]
    }

Upload Files:
1: Go to Objects tab -> Click Upload
2: Add your files:
    index.html
    error.html

----------------------------------------------------------------------------------------------------------------------------------------------

IAM:
    → A service in AWS used to control who can access your AWS resources and what actions they can perform.

It lets you:
    → Create users and give them specific permissions.
    → Group users and assign common access rules.
    → Use roles to give temporary access to AWS services or applications.

----------------------------------------------------------------------------------------------------------------------------------------------

AWS CLI:
    Use AWS commands to interact with AWS services using Command line

Install:
1: Install the AWS CLI
2: 'aws configure' to configure the client
3: Provide access key + secret key + default region

Example Commands
    aws s3 ls                           → Lists all S3 buckets.
    aws ec2 describe-instances          → Shows all EC2 instances.

----------------------------------------------------------------------------------------------------------------------------------------------
