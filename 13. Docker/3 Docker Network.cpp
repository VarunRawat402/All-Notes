----------------------------------------------------------------------------------------------------------------------------------------------
Docker Networking:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Allows containers to communicate with each other
→ Use container names instead of IP addresses (IPs change on restart)
→ Isolated from external systems by default

----------------------------------------------------------------------------------------------------------------------------------------------

1: Bridge Network (Default):
    → Containers get internal IPs, isolated from host
    → Containers can talk to each other via IP
    → Port mapping required to access from outside
    → Good security

'docker run --network=bridge ubuntu'

----------------------------------------------------------------------------------------------------------------------------------------------

2: Host Network:
    → Container shares host machine's network directly
    → No port mapping needed
    → Better performance but less isolation

'docker run --network=host ubuntu'

----------------------------------------------------------------------------------------------------------------------------------------------

3: None Network:
    → No network at all
    → Container completely isolated, cant talk to anything

'docker run --network=none ubuntu'

----------------------------------------------------------------------------------------------------------------------------------------------

4: Custom Network:
    → Containers communicate using container NAMES (not IPs)
    → Better isolation than default bridge
    → All containers on same custom network can find each other by name

'docker network create lbms-network -d bridge'    → create custom network
'docker run --network=lbms-network user-service'  → run container in it

----------------------------------------------------------------------------------------------------------------------------------------------

Port Mapping:

→ App runs inside container on application port, 8000
→ When your application runs inside container, you cant access it directly from outside
→ You need to map the application port to host port

'docker run -it -p 6000:8000 user-service:latest'
    → App port    - 8000
    → Host port   - 6000

----------------------------------------------------------------------------------------------------------------------------------------------

Environmental variables:
    → Pass config values to container at runtime
    → Avoids hardcoding values in application

'docker run -it -e PORT=8000 user-service'
    → application.properties: server.port=${PORT}
    → Port value injected at runtime ✅

'docker run -it -e DB_URL=jdbc:mysql://db:3306/mydb user-service'
    → pass DB URL, credentials etc same way

----------------------------------------------------------------------------------------------------------------------------------------------