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
Direct access of value using keys instead of searching

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Maps:

Map<Integer,String> m1 = new HashMap<>();
    Random ordering of elements , Fastest

Map<Integer,String> m2 = new LinkedHashMap<>();
    Ordering maintains, slower

Map<Integer,String> m3 = new TreeMap<>();               
    Sort the elements based on keys

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
    Allows one null key and multiple null values
    Not thread-safe

2: LinkedHashMap<>();
    Maintains insertion order
    Slightly slower than HashMap
    Predictable iteration order

5: TreeMap<>();
    Sorted by keys (natural ordering or custom comparator)
    Implements SortedMap interface
    Slower than HashMap but provides ordering

4: HashTable<>();
    Legacy class, thread-safe
    Does not allow null keys or values
    Slower due to synchronization

5: ConcurrentHashMap<>();
    Thread-safe and high-performance
    Better than HashTable for concurrent access
    No null keys or values

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

What is an Immutable Map?
✅ An Immutable Map is a Map that cannot be modified after creation.
✅ Prevents accidental changes (useful in multi-threading & constants).
✅ Java provides multiple ways to create an immutable map.

-----------------------------------------------------------------------------------------------------------------------------------------

Map.of() ( java 9+ ) ;
Immutable directly
Fastest & most memory-efficient way to create a small immutable map.
Does not allow null keys or values.
Cannot add, remove or modify entries after creation.

Map<String, Integer> immutableMap = Map.of("Alice", 25,
    "Bob", 30,
    "Charlie", 35
);

System.out.println(immutableMap); // {Alice=25, Bob=30, Charlie=35}

-----------------------------------------------------------------------------------------------------------------------------------------

Map.copyOf() (Java 10+):
    Unlike Collections.unmodifiableMap(), original map changes wont affect this one.
    Best for creating an immutable snapshot of an existing map.

Code:
Map<String, Integer> mutableMap = new HashMap<>();
mutableMap.put("Alice", 25);
mutableMap.put("Bob", 30);

Map<String, Integer> immutableMap = Map.copyOf(mutableMap);

immutableMap.put("Charlie", 35); // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------

Internal working of HashMaps:

Put Operation:

Convert the key into hashcode, key.hashCode()
Get the bucket Index, hashCode % arraySize (bucket index)
Store in Bucket:
    If bucket empty → create new entry
    If bucket occupied (collision) →
        Java 7: Store in linked list
        Java 8+: Use balanced tree if list grows large

Get Operation:

Convert the key into hashcode, key.hashCode()
Find Bucket: hashCode % arraySize
Search in Bucket:
    Single entry → return value
    Multiple entries, Collision → use equals() to find exact match

-----------------------------------------------------------------------------------------------------------------------------------------
