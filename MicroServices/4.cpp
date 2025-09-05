------------------------------------------------------------------------------------------------------------------------------------------------------------------------

In Mircoservices we are constanlty upgrading and degrading the servers which changes the IP and port
So how can we know the IP or port of the servers
Thats why hardcoding the url is not good practice

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Server Side Load Balancing / Front load Balancer :

When service A is making request to load balancer and then load balancer passing the
request to service B in distributed manner 

Disadvantages of this:

2 remote call : First from client to LB then LB to servers
Single point of failure : If LB crashed no call will go to the servers
Need maintainence cost and seperate team : Since we need to configre LB and the port and IP to maintains 
Need manual Configuration
Does not support Scalability

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Discovery service:
It is a registration service where all the servers Instances Ip and port were registered and LB will check the 
avail instances and their configs on whome which he can call

Server Side Discovery:

client A makes a request to the LB
LB does a query to the Discovery service
Discovery service responded back with the config of available servers
Then LB Picks one of the servers and makes a request 
client A does not talk to the Discovery service directly

Ex: NGNIX, AWS ELB

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Client Side Load Balancing:

Client A makes a call to the Discovery service and it gives the avail instances for service B
Then Service A has all the avail instances of service B so it will load balance on its own 
without any external server router or LB 
So client A is doing LB thats why its called Load Balancing

When Client A makes a query to get the avail instances from the Discovery service
it caches the data into the cache and does not make another call to DS again for some time

Ex: Netflix Eureka , Zookeeper

For Discovery : Spring cloud starter Eureka client
For LB : Spring cloud starter Load Balancer

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
