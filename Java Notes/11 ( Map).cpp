-----------------------------------------------------------------------------------------------------------------------------------------
Map:
-----------------------------------------------------------------------------------------------------------------------------------------

→ Stores key-value pairs
→ Keys must be unique (duplicate keys overwrite existing values)
→ Values can be duplicated

-----------------------------------------------------------------------------------------------------------------------------------------

Why Use Map?
    → HashMap → O(1) average time
    → No duplicate keys
    → Natural way to store related data

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Maps:

Map<Integer, String> m1 = new HashMap<>();          // No order, fastest
Map<Integer, String> m2 = new LinkedHashMap<>();    // Insertion order
Map<Integer, String> m3 = new TreeMap<>();          // Sorted by key

-----------------------------------------------------------------------------------------------------------------------------------------

How to Iterate over Map:

1: ForEach() ( Modern Approach ):

m1.forEach((key, value) ->
    System.out.println(key + " " + value)
);

-----------------------------------------------------------------------------------------------------------------------------------------

2: EntrySet():

Map<Integer,String> m = new HashMap<>();

for(Map.Entry<Integer,String> val : m.entrySet()){
    System.out.println(val.getKey() + " " val.getValue());
}

-----------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------

Immutable Map:

→ Map that cannot be modified after creation
→ Prevent accidental changes
→ Thread-safe
→ Ideal for constants/configuration

-----------------------------------------------------------------------------------------------------------------------------------------

Map.of() ( java 9+ ) :

→ Directly creates immutable map
→ Fastest for small maps
→ No null keys/values

Map<String, Integer> immutableMap = Map.of("Alice", 25,
    "Bob", 30,
    "Charlie", 35
);

System.out.println(immutableMap);           // {Alice=25, Bob=30, Charlie=35}

-----------------------------------------------------------------------------------------------------------------------------------------

Map.copyOf() (Java 10+):
    → Creates immutable copy of an existing map
    → Changes in original map do NOT affect the new one

Code:
Map<String, Integer> mutableMap = new HashMap<>();
Map<String, Integer> immutableMap = Map.copyOf(mutableMap);

-----------------------------------------------------------------------------------------------------------------------------------------

Internal working of HashMaps:

Put Operation:

→ Convert the key into hashcode → key.hashCode()
→ 
→ Store in Bucket:
    → Empty bucket → store directly
    → If bucket occupied (collision) →
        → Java 7 → LinkedList
        → Java 8+ → Tree structure (if bucket grows large)

Get Operation:

→ Convert the key into hashcode → key.hashCode()
→ Calculate bucket index using hashCode()
→ Search inside bucket:
    → If one entry → return value
    → If multiple → use equals() to find correct key

-----------------------------------------------------------------------------------------------------------------------------------------
