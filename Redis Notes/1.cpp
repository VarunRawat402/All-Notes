-----------------------------------------------------------------------------------------
Lecture 15: REDIS INTRODUCTION:
-----------------------------------------------------------------------------------------

To connect Redis to any port:
	redis-cli -p 6380

To connect Redis to any host:
	redis-cli -h { Host Name } -p { Port No } -a { Password }
	Port No will be the first number in the Host Name
	When you connect to the cloud Server you need to give the password too

----------------------------------------------------------------------------------------------------------------------------	

Redis is an in-memory data used for DB, Caching and Message Broker

Always store the data in the redis with expiraty date

When the storage is full in the cache memory we have 2 options:
	1: Increase the storage by installing more servers/memory.
	2: Delete the existing data in the cache based on some policies for the new coming data.

Policy:
	volatile-lru = Delete the least recently used keys where expiry date is true
	Ex: D1 - 8 Days Expiry		        D2 - 5 Days Expiry		--> D2 will be deleted
    	D1 - No Expiry date				D2 - No Expiry date 	--> No data will be deleted and insertion will fail		
	That is why we need to set the data with an expiry date so we wont get this 

----------------------------------------------------------------------------------------------------------------------------

When we store some data in redis its storing in memory (RAM) but when we shuts down the server it stores all the data 
to the disk so we dont loose the data.

1: Redis acts as a cache for real time queries.
2: It also persist the data onto the disk in a b/g thread to provide persitant capabilities.

Disadvantage of 2nd property:
	1: Load time / Starting time will be high due to the data loading from the disk.
	2: Duplicate data will be in memory and disk when server is running 
		Ex: 1 gb data loaded from disk in memory when server starts.
		    So Memory is using 1 gb and disk is also using 1 gb of storage of same data.

----------------------------------------------------------------------------------------------------------------------------

Types of Data we can store in the Redis DB:

It does not store int, float and double	
It only store the data in form of strings.
It can return integer to the user but store only Strings.

Keys : 
	Strings ( It can only be strings )

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

4: SETEX ( setex key time value ):
	Sets data with expiry date ( Seconds )
	Ex: setex name 90 varun

5: PSETEX ( setex key time value ):
	Sets data with expiry date ( Milliseconds )
	Ex: setex name 90 varun

6: TTL ( ttl key )
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
A List in Redis is an ordered collection of strings.

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
A Redis Set is an unordered collection of unique strings.
No duplicates allowed
No guaranteed order
Very fast for add, remove, and check operations

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

Hashes in redis is similar to HashMaps in java
There is no particular order in HashMaps

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