----------------------------------------------------------------------------------------------------------------------------------------------
Docker Intro:
----------------------------------------------------------------------------------------------------------------------------------------------

Image:

→ Packs application into image.
→ Application code + Runtime Environment + Libraries + Dependencies
→ It ensures app runs the same everywhere

----------------------------------------------------------------------------------------------------------------------------------------------

Container:
    → It is a running instance of image
    → It is used to run the application

----------------------------------------------------------------------------------------------------------------------------------------------

Implementation:

1: Create docker file 
2: mvn clean install                    //create jar files
3: docker build -t <image-name> .       //build image
4: docker run -it <image-name>          //run image

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Container Commands:

'docker run -it <image>'            → Run the image
'docker container ls'               → List running containers
'docker container ls -a'            → List running + stopped containers
'docker start <container>'          → Start stopped container
'docker stop <container>'           → Stop running container
'docker logs <container>'           → Show container logs
'docker rm <container>'             → Remove container
'docker exec -it <container> <shell>'   → Enter running container
    
----------------------------------------------------------------------------------------------------------------------------------------------

Docker Images Commands:

'docker images'                   → Lists local images
'docker build -t <image> <path>'  → Build image from Dockerfile
'docker pull <image>'             → Download image from Docker Hub
'docker image rm <image>'         → Delete image
'docker inspect <image>'          → Show image metadata
'docker tag <old> <new_image>:<tag>'   → Create new tag for image

----------------------------------------------------------------------------------------------------------------------------------------------

Basic Logging and monitoring:

'docker logs <container_name_or_id>'
    → show container logs

'docker logs -t <container_name_or_id>'
    → show logs with timestamps

'docker stats <container_name_or_id>'
    → show container cpu, memory usage

'docker inspect <container_name_or_id>'
    → show container json meta-data

'docker top <container_name_or_id>'
    → shows processes running inside container

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
    → Works like .gitignore
    → Excludes files during build
    → Smaller image + fast re-builds

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Multi-Stage Builds:
    → Use multiple FROM statements in a single Dockerfile. 
    → Each FROM = new stage
    → You copy only required files to final stage

Advantages:
    → Small image size

----------------------------------------------------------------------------------------------------------------------------------------------

Docker Hub:
    → Used to store and manage docker images
    → public + private properties

Login:

'docker login -u varun402'
    → username → varun402

----------------------------------------------------------------------------------------------------------------------------------------------

Push Image to Docker Hub:

1: Login in docker hub
2: Tag the image with username/image-name

Commands:

'docker build -t varun402/user-service:latest .'    → tag image
'docker push varun402/user-service:latest'          → push image

----------------------------------------------------------------------------------------------------------------------------------------------