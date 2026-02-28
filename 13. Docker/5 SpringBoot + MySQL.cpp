
----------------------------------------------------------------------------------------------------------------------------------------------
Spring Boot + MySQL (Docker Compose Setup):
----------------------------------------------------------------------------------------------------------------------------------------------

Local Setup (Without Docker):

When you connect to MySQL using localhost:
    → spring.datasource.url=jdbc:mysql://localhost:3306/lbms
    → localhost → Your machine where mysql is running
    → App connects directly to local MySQL

Problem in Docker:

→ Inside a container
→ localhost → container itself, not your machine
→ Containers are isolated
→ So, Spring Boot container cannot find MySQL using localhost

Solution — Shared Docker Network:
    → Run both MySQL and Spring Boot containers in the same custom Docker network.
    → Use container names to communicate instead of localhost.
    → spring.datasource.url=jdbc:mysql://mysql-db:3306/lbms

----------------------------------------------------------------------------------------------------------------------------------------------

Run Two application in same network:

'docker create network student-app-network -d bridge'       
    → create custom network

'docker run -d --name mysql-db --network student-app-network mysql:8.0'
    → run mysql in custom network

'docker run -d --name student-app --network student-app-network student-app'
    → run spring boot app in same network


----------------------------------------------------------------------------------------------------------------------------------------------
Code:
----------------------------------------------------------------------------------------------------------------------------------------------

version: '3.8'
services:

  mysql-db:
    image: mysql:8.0
    container_name: mysql-db
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword123
      MYSQL_DATABASE: ecommerce_db
    ports:
      - "3306:3306"
    volumes:
      - mysql_data:/var/lib/mysql
    networks:
      - app-network

  spring-boot-app:
    build: .
    container_name: spring-boot-app
    ports:
      - "8080:8080"
    environment:
      DB_HOST: mysql-db
      DB_NAME: ecommerce_db
      DB_USER: app_user
      DB_PASS: apppassword123
    depends_on:
      - mysql-db
    networks:
      - app-network

volumes:
  mysql_data:

networks:
  app-network:
    driver: bridge

----------------------------------------------------------------------------------------------------------------------------------------------

Flow:

1: mysql-db service starts first
    → MySQL initializes with your DB, username, and password.

2: spring-boot-app starts next
    → Reads environment variables
    → Connects to MySQL via hostname mysql-db
    → Runs migrations or schema updates 
3: Data persists inside the named volume mysql_data.

----------------------------------------------------------------------------------------------------------------------------------------------