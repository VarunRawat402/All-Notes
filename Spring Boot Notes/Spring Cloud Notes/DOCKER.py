--------------------------------------------------------------------------------------------------------------------------------------------------------------------
DOCKER:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Docker is a tool that allows you to package applications and their dependencies into containers 
that can run on any system without worrying about environment differences.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Docker Image : A set of Bytes or template that contains everything needed to run an application (code, dependencies, runtime, etc.).
Docker Container → A running instance of a Docker Image. It is isolated and can run anywhere.
Docker Hub → A cloud repository where Docker images are stored and shared. Like GitHub but for Docker images.
Docker File → A Dockerfile is a script that contains a set of instructions to build a Docker image

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Docker File: ( Path : Inside main folder )
    FROM openjdk:18.0-slim                    #Sets the enviroment which type of application
    COPY target/*.jar app.jar                 #Copy the jar files from target folder to the container folder app.jar
    EXPOSE 8080                               #Port on which container will run
    ENTRYPOINT ["java","-jar","app.jar"]      #Configure the command that will be run at container launch 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOCKER IMAGE:
Command to create the Docker Image
    ( docker build -t varun/hello-docker:v1 . )

What It Does
    docker build →          #Builds a new Docker image.
    -t →                    #variable to use to assign the tags to docker image
    varun →                 #Namespace (usually your Docker Hub username).
    hello-docker →          #Image name.
    v1 →                    #Version tag (:v1 is optional, default is :latest).
    .  →                    #Specifies the current directory as the location of the Dockerfile. 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOCKER CONTAINER:
Command to create the Container
    ( docker run -d -p 8080:8080 varun/hello-docker:v1 )

What It Does
    docker run →                #Starts a new container.
    -d (detached mode) →        #Runs the container in the background.
    -p 8080:8080 →              #Maps port 8080 on your local machine to port 8080 inside the container.
    varun/hello-docker:v1 →     #Specifies the Docker image to run (which was built earlier).

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

JAR files ( Local Machine )
Steps to create Docker Image and Docker Container:

1: Copy the Demo things of project outside the demo folder and remove the Demo
    [ Make sure docker file, jar and code is in the same folder ]
2: Create the Docker folder file
3: Run 'mvn clean package' in the terminal so jar files can be created
4: with the help of docker commands those jar files will be copied to docker
5: Open cmd and cd to the project folder 
6: Run this command to create a docker image 
    [ docker build -t varun/hello-docker:v1 . ] 
7: Run this command to create container of that image
    [ docker run -d -p 8080:8080 varun/hello-docker:v1 ]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

JAR files ( In Container )
Steps to create docker image and docker Container

1: Copy the Demo things of project outside the demo folder and remove the Demo
    [ Make sure docker file, and code is in the same folder ]
2: Create the Docker folder with commands
3: Open cmd and cd to the project folder 
4: Run this command to create a docker image 
    [ docker build -t varun/hello-docker:v1 . ] 
5: Run this command to create container of that image
    [ docker run -d -p 8080:8080 varun/hello-docker:v1 ]

Docker Folder:
    FROM maven:3.8.4-openjdk-17 AS builder                  #Sets the environment for maven with builder name      
    WORKDIR /app                                            #Create a /app directory and cd into it
    COPY . .                                                #Copy the current location directory files to current container location
    RUN mvn clean package -DskipTests                       #this command will get run inside the maven in image

    FROM openjdk:17                                         #Sets the java environment
    WORKDIR /app                                            #Create a /app directory and cd into it
    COPY --from=builder /app/target/*.jar app.jar           #Copy from builder -> jar path -> to app.jar folder
    CMD ["java", "-jar", "app.jar"]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Maven PLUGIN ( No Docker Folder ):
1: Copy the Demo things of project outside the demo folder and remove the Demo
2: To give custom name to ur image add config->image->name in the pom
    No uppercase letter and special signs
	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
				<configuration>
					<image>
						<name>varun/currencymsv1-currencyexchange:${project.version}</name>
					</image>
					<pullPolicy>IF_NOT_PRESENT</pullPolicy>
				</configuration>
			</plugin>
		</plugins>
	</build>
3: Run this command in terminal, This command will update JAR files and create the image 
    [ mvn spring-boot:build-image ]
4: Open cmd and cd to the project folder 
5: Run this command to create container of that image
    Check the image name and the version using "docker image ls"
    [ docker run -d -p 8080:8080 <imagename:version> ]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Docker Compose:
    It is a docker file which is used to run all the docker images at one go
    instead of doing docker run for every images
    Create docker-compose.yaml file in the project folder

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ex:
version: '3.7'

services:

  CurrencyExchange:
    image: varun/currencymsv1-currencyexchange:0.0.1-SNAPSHOT
    ports:
      - "8000:8000"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka

  CurrencyConversion:
    image: varun/ccv1:0.0.1-SNAPSHOT
    ports:
      - "8100:8100"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka

  Api-Gateway:
    image: varun/apiv1:0.0.1-SNAPSHOT
    ports:
      - "9765:9765"
    networks:
      - currency-network
    depends_on:
      - Discovery-Service
    environment:
      EUREKA.CLIENT.SERVICEURL.DEFAULTZONE: http://Discovery-Service:8761/eureka

  Discovery-Service:
    image: varun/dsv1:0.0.1-SNAPSHOT
    ports:
      - "8761:8761"
    networks:
      - currency-network

networks:
  currency-network:

--------------------------------------------------------------------------------------------------------------------------------------------------------------------