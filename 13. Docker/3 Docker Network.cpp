----------------------------------------------------------------------------------------------------------------------------------------------
Network:
----------------------------------------------------------------------------------------------------------------------------------------------

→ Used to communicate between containers
→ Use container names instead of IP address
→ Isolated from external system

----------------------------------------------------------------------------------------------------------------------------------------------

1: Bridge Network (Default):
    'docker run --network=bridge ubuntu'

→ Use internal IPs to communicate
→ Containers are isolated from host
→ Port-mapping is required
→ Provides good security.

----------------------------------------------------------------------------------------------------------------------------------------------

2: Host Network:
    'docker run --network=host ubuntu'

→ Containers use host network
→ No Port-mapping
→ Better performance but Less isolation

----------------------------------------------------------------------------------------------------------------------------------------------

3: None Network:
    'docker run --network=none ubuntu'

→ No network connectivity.
→ Cannot communicate with Host or other containers

----------------------------------------------------------------------------------------------------------------------------------------------

4: Custom Network:

→ Use container names to communicate
→ Better isolation than default bridge

'docker create network lbms-network -d bridge'
    → Creates user-defined bridge network

'docker run --network=lbms-network user-service'
    → Run container in custom network

----------------------------------------------------------------------------------------------------------------------------------------------

Port Mapping:

→ Your application runs on application port, 8000
→ When your application runs inside container, you cannot directly use the port
→ You need to map the application port to host port to use it

'docker run -it -p 6000:8000 user-service:latest'
    → App port    - 8000
    → Host port   - 6000

----------------------------------------------------------------------------------------------------------------------------------------------

Environmental variables:
    → Used to configure application properties at runtime

'docker run -it -e key=value <application-name>'

Ex:
    → server.port=${PORT}
    → docker run -it -e PORT=8000 user-service
    → Port value is passed at runtime

----------------------------------------------------------------------------------------------------------------------------------------------