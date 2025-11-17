-----------------------------------------------------------------------------------------
Lecture 15: REDIS INTRODUCTION:
-----------------------------------------------------------------------------------------

To connect Redis to a specific port:
	redis-cli -p 6380

To connect Redis to a specific host:
	redis-cli -h { Host Name } -p { Port No } -a { Password }

Cloud Redis usually requires a password.
Port number is typically the number shown in the connection string.

----------------------------------------------------------------------------------------------------------------------------	

Redis is an in-memory data used for DB, Caching and Message Broker
Always store data with an expiry time to keep cache clean and avoid memory issues.ate

When Redis Cache Memory Is Full:
	1: Increase memory / add more Redis nodes.
	2: Evict (delete) existing keys based on eviction policies.

Eviction Policy Example: 
	volatile-lru = Deletes Least Recently Used keys only if they have an expiry time.
	Ex: D1 - 8 Days Expiry		        D2 - 5 Days Expiry		--> D2 will be deleted
    	D1 - No Expiry date				D2 - No Expiry date 	--> No data will be deleted and insertion will fail		
	If keys have no expiry, nothing is deleted → insertion fails.
	This is why expiry time is important.

----------------------------------------------------------------------------------------------------------------------------

How Redis Stores Data:

Redis stores data in RAM for fast access.
When the server shuts down, Redis saves data to disk for persistence.

Redis acts as:

1: Real-time cache (primary use).
2: Persistent storage by writing snapshots/logs to disk.

Disadvantages:
	1: Startup time increases because Redis loads data from disk into RAM.
	2: Duplicate storage — same data in RAM and disk at the same time.
		Ex: 1 gb data loaded from disk in memory when server starts.
		    So Memory is using 1 gb and disk is also using 1 gb of storage of same data.

----------------------------------------------------------------------------------------------------------------------------

Data Types in Redis:

Redis stores everything as strings internally.
It returns integers for convenience but stores them as strings.

Keys : 
	Always strings.

Values: 
	Strings, List<Strings> , Hash<String,String> , set<String> .. etc etc

----------------------------------------------------------------------------------------------------------------------------	
Redis Commands:
----------------------------------------------------------------------------------------------------------------------------	

KEYS In REDIS:

1: SET (set key value):
	set name varun

2: GET (get key): 
	Ex: get name		//varun

3: DEL ( del key ):
	Ex: del name

4: SETEX (seconds expiry):
	Sets data with expiry date ( Seconds )
	Ex: setex name 90 varun

5: PSETEX (milliseconds expiry):
	Sets data with expiry date ( Milliseconds )
	Ex: setex name 90 varun

6: TTL ( check remaining expiry )	
	Returns remaining expirty time
	Ex: ttl name

7: INCR / INCRBY ( INCR key / INCRBY key amount ):
	Increment the Value 
	Ex: incr age 					//age 22 --> 23
	Ex: incrby age 20				//age 22 --> 42
	
	Convert the age string to int , increment it and then save it again as a string

8: DECR / DECRBY ( DECR key / DECRBY key amount ):
	Increment the Value 
	Ex: decr age 					//age 22 --> 21
	Ex: decrby age 20				//age 22 --> 2

----------------------------------------------------------------------------------------------------------------------------

LIST In REDIS:
A Redis List is an ordered collection of strings.

1: LPUSH / RPUSH
	Add element in list from both left and right
	Ex: lpush names varun
	Ex: rpush names arun

2 LPOP / RPOP:
	Remove element in list from both left and right
	Ex: lpop names varun
	Ex: rpop names arun
	Ex: lpop names 3			//pop 3 elements from left

3: LRANGE:
	It is used to get the elements from the list:
	Ex: lrange name 0 2			//from 0th index to 2nd index ( inclusive )
	Ex: lrange name 0 -1		//0th to last index
	( -1 = last element , -2 = Second last element )

----------------------------------------------------------------------------------------------------------------------------

SET In REDIS:
	Unordered
	Unique elements
	Very fast for add/remove/check

1: SADD:
    Add element in set
    Ex: sadd names varun rawat

2: SMEMBERS:
    Get all elements from set
    Ex: smembers name

3: SISMEMBER:
    It is used to check if the element is present in the set or not
    Ex: sismember name varun
    o/p = 1 --> Present / 0 --> Not Present

3: SREM:
    It is used to remove the element from the set using value
    Ex: srem name varun

4: SPOP :
    It is used to remove the element from the set using count
    Ex: spop name 3 
    It removes random 3 elements.

----------------------------------------------------------------------------------------------------------------------------

HASHSET In REDIS:
	Redis Hash = Java HashMap (field → value)

Keys : {
		feild : Value
	}	

Student : {
		name : Varun
		age : 23
		country : India
	  }

Commands:

1: hset - It is used to add the data into the hashset
	Ex: hset student name varun age 20

2: hget - It is used to get the value using feild name
	Ex: hget student name

3: hmget - It is used to get the multiple values using mutliple feild names
	Ex: hmget student name age 

4: hgetall - It is used to get all thee feild:value of the key
	Ex: hgetall student

5: HKEYS / HAVALS - It is used to get all the keys / values
	Ex: hkeys student
	Ex: hvaks student

6: HDEL : It is used to delete the feild:value 
	Ex: hdel student name
	
-----------------------------------------------------------------------------------------------------------------------------------