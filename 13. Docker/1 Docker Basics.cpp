----------------------------------------------------------------------------------------------------------------------------------------------
Docker Basics:
----------------------------------------------------------------------------------------------------------------------------------------------

Image:

→ Packs snapshot of application includes : code + runtime + libraries + dependencies
→ Guarantees app runs the same on every machine

----------------------------------------------------------------------------------------------------------------------------------------------

Container:
    → It is a running instance of image
    → It is used to run the application

----------------------------------------------------------------------------------------------------------------------------------------------

How to Dockerize a Spring Boot App:

1: Create docker file 
2: mvn clean install                    //Create JAR
3: docker build -t <image-name> .       //Build Docker image
4: docker run -it <image-name>          //Run the image in container

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Archietecture:

Docker CLI:
    → Used to run docker commands
    → Sends requests to Docker Daemon via REST API

Docker Daemon:
    → Background service 
    → Core working component
    → build + run image
    → manage volumne + network
    → pull + push image

Docker Engine:
    → docker cli + docker daemon + REST APIs

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Ignore:
    → Works like .gitignore → excludes files from Docker build
    → Smaller image size + faster builds

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Multi-Stage Builds:
    → Multiple FROM statements in one Dockerfile
    → Each FROM = new stage
    → Copy ONLY whats needed into final stage
    → Result: much smaller final image

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Hub:
    → Used to store + share Docker images
    → Public (anyone can pull) or Private (restricted)

----------------------------------------------------------------------------------------------------------------------------------------------

Push image to Docker Hub:

1. docker login -u varun402
2. docker build -t varun402/user-service:latest .   → tag with username
3. docker push varun402/user-service:latest         → push to Hub

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Container Commands:

'docker run -it <image>'                → Run Container
'docker container ls'                   → Show running containers
'docker container ls -a'                → Show running + stopped containers
'docker start <container>'              → Start container
'docker stop <container>'               → Stop container
'docker rm <container>'                 → Remove container
'docker exec -it <container> <shell>'   → Enter running container
    
----------------------------------------------------------------------------------------------------------------------------------------------

Docker Images Commands:

'docker images'                         → Show local images
'docker build -t <image> <path>'        → Build image from Dockerfile
'docker pull <image>'                   → Pull image from dockerhub
'docker image rm <image>'               → Delete image
'docker inspect <image>'                → Show image metadata
'docker tag <old> <new_image>:<tag>'    → Create new tag for image

----------------------------------------------------------------------------------------------------------------------------------------------

Basic Logging and monitoring:

'docker logs <container>'               → show logs
'docker logs -t <container>'            → show logs with timestamps
'docker stats <container>'              → live CPU + memory usage
'docker inspect <container>'            → full JSON metadata
'docker top <container>'                → processes running inside container

----------------------------------------------------------------------------------------------------------------------------------------------
