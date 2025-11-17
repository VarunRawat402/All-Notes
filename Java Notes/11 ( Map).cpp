-----------------------------------------------------------------------------------------------------------------------------------------
Map:
-----------------------------------------------------------------------------------------------------------------------------------------

Stores key-value pairs
Keys must be unique (duplicate keys overwrite existing values)
Values can be duplicated

-----------------------------------------------------------------------------------------------------------------------------------------

Why Use Map?

O(1) average time complexity for HashMap
No Duplicate Keys
Logical grouping of related data
Direct access through keys (no searching required)

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Maps:

Map<Integer,String> m1 = new HashMap<>();      
// Random order, fastest

Map<Integer,String> m2 = new LinkedHashMap<>(); 
// Maintains insertion order

Map<Integer,String> m3 = new TreeMap<>();        
// Sorted by keys

-----------------------------------------------------------------------------------------------------------------------------------------

How to Iterate over Map:

1: ForEach() ( Modern Approach ):

Map<Integer,String> m = new HashMap<>();
m.put(1,"Varun");
m.put(2,"Arun");
m.put(3,"Priti");

m.forEach((key,value)->System.out.println(key + " " + value));

-----------------------------------------------------------------------------------------------------------------------------------------

2: KeySet():

Map<Integer,String> m = new HashMap<>();
m.put(1,"Varun");
m.put(2,"Arun");
m.put(3,"Priti");

//Just Create a keySet of map in for loop
for(int i:m.keySet()){
    System.out.println(m.get(i));
}

-----------------------------------------------------------------------------------------------------------------------------------------

3: EntrySet():

Map<Integer,String> m = new HashMap<>();
m.put(1,"Varun");
m.put(2,"Arun");
m.put(3,"Priti");

//Just Create a EntrySet of map in for loop
//Map.Entry<Integer,String> This is the type of key like int in keySet
for(Map.Entry<Integer,String> i:m.entrySet()){
    i.setValue(i.getValue().toUpperCase());
    System.out.println(i.getValue());
}

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Maps:

1: HashMap<>();
    No ordering guarantees
    Fastest operations
    Allows one null key + multiple null values
    Not thread-safe

2: LinkedHashMap<>();
    Maintains insertion order
    Slightly slower than HashMap
    Predictable iteration order

5: TreeMap<>();
    Sorted by keys (natural ordering or custom comparator)
    Implements SortedMap
    Slower than HashMap but provides ordering

4: HashTable<>();
    Legacy, thread-safe
    No null keys/values
    Slow due to synchronization

5: ConcurrentHashMap<>();
    Modern, thread-safe
    Better concurrency than Hashtable
    No null keys/values

-----------------------------------------------------------------------------------------------------------------------------------------

Methods:

1: put( key, value )
2: get(key)
3: containsKey(key)
4: containsValue(value)
5: size()
6: remove(key)

-----------------------------------------------------------------------------------------------------------------------------------------

Enum Map:
    Keys should be enum
    Faster and more memory-efficient than HashMap
    Keys are automatically sorted in Enums natural order
    No null keys allowed

-----------------------------------------------------------------------------------------------------------------------------------------

Code:

enum Day { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY }

public class EnumMapExample {
    public static void main(String[] args) {

        EnumMap<Day, String> schedule = new EnumMap<>(Day.class);
        
        schedule.put(Day.MONDAY, "Work from office");
        schedule.put(Day.WEDNESDAY, "Team meeting");
        schedule.put(Day.FRIDAY, "Casual Friday");
        schedule.put(Day.SATURDAY, "Weekend plans");
        
        System.out.println(schedule);
        System.out.println(schedule.get(Day.MONDAY)); // Work from office
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Immutable Map:

Cannot be modified after creation
Prevents accidental changes
Useful for constants and multi-threading
Java provides multiple ways to create it

-----------------------------------------------------------------------------------------------------------------------------------------

Map.of() ( java 9+ ) ;
Directly creates immutable map
Fastest for small maps
No null keys/values
No add/remove/modify allowed

Map<String, Integer> immutableMap = Map.of("Alice", 25,
    "Bob", 30,
    "Charlie", 35
);

System.out.println(immutableMap);           // {Alice=25, Bob=30, Charlie=35}

-----------------------------------------------------------------------------------------------------------------------------------------

Map.copyOf() (Java 10+):
    Creates immutable copy of an existing map
    Changes in original map do NOT affect the new one

Code:
Map<String, Integer> mutableMap = new HashMap<>();
mutableMap.put("Alice", 25);
mutableMap.put("Bob", 30);

Map<String, Integer> immutableMap = Map.copyOf(mutableMap);

immutableMap.put("Charlie", 35);    // Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------

Internal working of HashMaps:

Put Operation:

Convert the key into hashcode, key.hashCode()
Calculate bucket index → hashCode % arraySize
Store in Bucket:
    Empty bucket → store directly
    If bucket occupied (collision) →
        Java 7 → LinkedList
        Java 8+ → Tree structure (if bucket grows large)

Get Operation:

Convert the key into hashcode, key.hashCode()
Find bucket → hashCode % arraySize
Search inside bucket:
    If one entry → return value
    If multiple → use equals() to find correct key

-----------------------------------------------------------------------------------------------------------------------------------------
