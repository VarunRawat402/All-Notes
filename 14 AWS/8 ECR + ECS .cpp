----------------------------------------------------------------------------------------------------------------------------------------------
ECR + ECS:
----------------------------------------------------------------------------------------------------------------------------------------------

ECR — ( Elastic Container Registry ):

→ Stores and manages Docker images on AWS.
→ Only authorized AWS users can access it
→ Auto-scans for vulnerabilities
→ Auto-deletes old/untagged images
→ Replicates images across regions for faster access

----------------------------------------------------------------------------------------------------------------------------------------------

ECR Implementation:

1: Create repo in ECR
2: Authenticate docker with ECR 
3: Build + tag image with ECR repo url
4: Push image to ECR

----------------------------------------------------------------------------------------------------------------------------------------------

ECS — ( Elastic Container Service ):

Runs and manages Docker containers on EC2
Pull images from ECR.

1: Cluster: Group of EC2 instances

2: Task Definition :
        → Json Config defining: → image + cpu + memory + ports + env variables + health-checks + logging
        → 1 running task = 1 running instance of your application.

3: Service :
    → Manages running tasks in the cluster
    → Each service handles one application.
    → Configuration:
        → Task count + Load balancer + auto scaling + Deployment type

----------------------------------------------------------------------------------------------------------------------------------------------

ECS Implementation:

1: Create a cluster → choose Fargate or EC2
2: Create task for your image
3: Create service → connect it to the task
4: Each application needs its own service

----------------------------------------------------------------------------------------------------------------------------------------------

Health monitoring:

1: Create a '/health'    API endpoint in your app
2: ECS pings it every 30 seconds
3: Responds → container marked healthy
4: No response → ECS kills it and starts a new one

----------------------------------------------------------------------------------------------------------------------------------------------

Deploying a New Version:

1: Build + push new image to ECR
2: In ECS → open service → force update
3: ECS starts new containers
4: New containers healthy  → old ones removed
5: Not healthy  → new ones removed, old ones kept

----------------------------------------------------------------------------------------------------------------------------------------------

How to cleanup:

1: Set running tasks to 0 in the service
2: Force-update the service
3: Delete service + Delete cluster

----------------------------------------------------------------------------------------------------------------------------------------------

