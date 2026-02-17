-----------------------------------------------------------------------------------------------------------------------------------------------------
Map:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Stores key-value pairs
→ Keys      → unique
→ Values    → duplicated
→ TC        → O(1) 
→ Duplicate keys overwrite existing values

-----------------------------------------------------------------------------------------------------------------------------------------------------

Types of Maps:

1: HashMap<>();
    → No ordering guarantees
    → Fastest
    → Allows 1 null key + multiple null values
    → Not thread-safe

2: LinkedHashMap<>();
    → Maintains insertion order
    → Slightly slower than HashMap

5: TreeMap<>();
    → Sorted by keys
    → Uses Red-Black Tree
    → Slower than HashMap but provides ordering

4: HashTable<>();
    → Legacy, thread-safe
    → No null keys/values
    → Slow due to synchronization

5: ConcurrentHashMap<>();
    → Modern, thread-safe
    → Better concurrency than Hashtable
    → No null keys/values

-----------------------------------------------------------------------------------------------------------------------------------------------------
How to Iterate over Map:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: ForEach() ( Modern Approach ):

m1.forEach((key, value) ->
    System.out.println(key + " " + value)
);

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: EntrySet():

Map<Integer,String> m = new HashMap<>();

for(Map.Entry<Integer,String> val : m.entrySet()){
    System.out.println(val.getKey() + " " val.getValue());
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Immutable Map:
    → Map that cannot be modified after creation
    → Prevent accidental changes
    → Thread-safe
    → Ideal for constants/configuration
    → Map.of()
    → Map.copyof()

1: Map.of():
    → Directly creates immutable map
    → Fastest for small maps
    → No null keys/values
    → java 9+

2: Map.copyOf():
    → Creates immutable copy of an existing map
    → Changes in original map do NOT affect the new one
    → java 10+

-----------------------------------------------------------------------------------------------------------------------------------------------------

Concurrent Hashmap():
    → Thread-safe implementation of Map
    → Alternative to Collections.synchronizedMap()

Collections.synchronizedMap():
    → One global lock → poor concurrency

ConcurrentHashMap:
→ No global lock ✅
→ Reads (get) 🔹 lock-free, very fast
    → hash → bucket → read volatile value
→ Writes (put) 🔹 fine-grained locking
    → hash → bucket → lock bucket → insert/update → unlock
    → Multiple threads can work on different buckets concurrently

Notes:
→ volatile → guarantees memory visibility
→ Reads dont need locks → very fast
→ Writes lock only the affected bucket → high throughput


-----------------------------------------------------------------------------------------------------------------------------------------------------
Internal working of HashMaps:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Put Operation:

→ Convert the key into hashcode → key.hashCode()
→ Calculate bucket index using hashCode()
→ Compare with existing objects in bucket if they are equal or not using equals()
→ If true → overrides, if false → add

→ Store in Bucket:
    → Empty bucket → store directly
    → If bucket occupied (collision) →
        → Java 7    → LinkedList
        → Java 8+   → Tree structure (if bucket grows large)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Get Operation:

→ Convert the key into hashcode → key.hashCode()
→ Calculate bucket index using hashCode()
→ Search inside bucket:
    → If one entry → return value
    → If multiple → use equals() to find correct key

-----------------------------------------------------------------------------------------------------------------------------------------------------
Contract between Hashcode() and Equals():
-----------------------------------------------------------------------------------------------------------------------------------------------------

hashCode()   → creates hashcode using feilds
equals()     → check if objects are equals using feilds

Contract:
If a.equals(b) is true
    → a.hashCode() = b.hashCode() 

If a.hashCode() == b.hashCode()
    → a.equals(b) may be true or false

Important Rule:
→ Need to override both if overriding one method to maintain contract
→ Always use same feilds to check equals() and generate hashcode()
→ equals()      → based on Id
→ hashcode()    → based on Id

-----------------------------------------------------------------------------------------------------------------------------------------------------

Example 1: 
equals()    → overriden ( checks id )
hashcode()  → same      ( same memory based )

Student s1 = new Student(1,"varun");
Student s2 = new Student(1,"varun");

s1.equals(s2)   → true ( same id )
hashcode()      → different due to different memory

s1 and s2 have different memory → different hashcode → different buckets
no equals() check → both objects added → unique keys behaviour broken

-----------------------------------------------------------------------------------------------------------------------------------------------------

Example 2:
equals()    → same      ( checks reference )
hashcode()  → overriden ( generates on Id )

Student s1 = new Student(1,"varun");
Student s2 = new Student(1,"varun");

hashcode()      → same ( same id )
equals()        → different due to different memory

s1 and s2 have same hashcode → same bucket → checks equals() for duplicate values
equals() shows different objects due to memory → both added → unique keys behaviour broken

-----------------------------------------------------------------------------------------------------------------------------------------------------
