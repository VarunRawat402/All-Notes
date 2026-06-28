
----------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot + MySQL (Docker Compose Setup):
----------------------------------------------------------------------------------------------------------------------------------------------

Local Setup (Without Docker):

When you connect to MySQL using localhost:
  → spring.datasource.url=jdbc:mysql://localhost:3306/lbms
  → localhost → Your machine where mysql is running
  → App connects directly to local MySQL

Problem in Docker:
  → Inside a container, localhost = the container itself, NOT your machine
  → Spring Boot container cant find MySQL using localhost

Solution:
  → Put both containers in same custom Docker network
  → Use container NAME as hostname instead of localhost
  → spring.datasource.url=jdbc:mysql://mysql-db:3306/lbms

----------------------------------------------------------------------------------------------------------------------------------------------
Code:
----------------------------------------------------------------------------------------------------------------------------------------------

version: '3.8'
services:

  mysql-db:
    image: mysql:8.0                        # pull from Docker Hub
    container_name: mysql-db
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword123
      MYSQL_DATABASE: ecommerce_db
    ports:
      - "3306:3306"
    volumes:
      - mysql_data:/var/lib/mysql            # persist DB data
    networks:
      - app-network

  spring-boot-app:
    build: .                                # build from local Dockerfile
    container_name: spring-boot-app
    ports:
      - "8080:8080"
    environment:
      DB_HOST: mysql-db                     # use container name, not localhost
      DB_NAME: ecommerce_db
      DB_USER: app_user
      DB_PASS: apppassword123
    depends_on:
      - mysql-db                            # wait for MySQL to start first
    networks:
      - app-network

volumes:
  mysql_data:                               # named volume for DB persistence

networks:
  app-network:
    driver: bridge

----------------------------------------------------------------------------------------------------------------------------------------------

Startup Flow:

1. mysql-db starts → initializes DB with credentials

2. spring-boot-app starts:
  → reads env vars 
  → connects to mysql-db by name
  
3. App runs migrations/schema updates
4. Data persists in mysql_data volume even if containers restart/removed

----------------------------------------------------------------------------------------------------------------------------------------------