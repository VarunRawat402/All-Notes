-----------------------------------------------------------------------------------------------------------------------------------------
Map:
-----------------------------------------------------------------------------------------------------------------------------------------

It stores key-value pairs and allows you to retrieve a value based on its associated key.
Key should always be unique
If you store the key which is already been stored then the value will be replaced by the latest value.

-----------------------------------------------------------------------------------------------------------------------------------------

Why Use Map?
Fast Lookup 🔍 : Quickly find values using keys.
No Duplicate Keys 🚫 : Each key must be unique.

-----------------------------------------------------------------------------------------------------------------------------------------
Syntax:
    Map<Integer,String> m1 = new HashMap<>();
-----------------------------------------------------------------------------------------------------------------------------------------

Map<Integer,String> m1 = new HashMap<>();
    Random ordering of elements , Fastest

Map<Integer,String> m2 = new LinkedHashMap<>();
    Ordering maintains, slower

Map<Integer,String> m3 = new TreeMap<>();           //Or Sorted Map
    Sort the elements based on keys, 

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

Classes:
1: HashMap<>();
2: LinkedHashMap<>();
3: SortedMap<>();
4: HashTable<>();
5: TreeMap<>();

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

What is EnumMap?
✅ EnumMap<K, V> is a specialized Map designed only for Enums as keys.
✅ It is faster and more memory-efficient than HashMap.
✅ Keys are stored internally as an array, making lookups very fast (O(1)).

-----------------------------------------------------------------------------------------------------------------------------------------

Code:

enum Day { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY }

public class Main {
    public static void main(String[] args) {
        EnumMap<Day, String> schedule = new EnumMap<>(Day.class);

        schedule.put(Day.MONDAY, "Gym");
        schedule.put(Day.WEDNESDAY, "Meeting");
        schedule.put(Day.FRIDAY, "Movie Night");

        System.out.println(schedule); // {MONDAY=Gym, WEDNESDAY=Meeting, FRIDAY=Movie Night}
    }
}

✔ Only works with Enums.
✔ Keys are automatically sorted in Enums natural order (MONDAY → WEDNESDAY → FRIDAY).
✔ Faster than HashMap<Enum, V> because it uses an array internally.

-----------------------------------------------------------------------------------------------------------------------------------------

Immutable Map:

What is an Immutable Map?
✅ An Immutable Map is a Map that cannot be modified after creation.
✅ Prevents accidental changes (useful in multi-threading & constants).
✅ Java provides multiple ways to create an immutable map.

-----------------------------------------------------------------------------------------------------------------------------------------

Map.of() ( java 9+ ) ;
✔ Immutable directly (no need for Collections.unmodifiableMap()).
✔ Fastest & most memory-efficient way to create a small immutable map.

Code: 
Map<String, Integer> immutableMap = Map.of("Alice", 25, "Bob", 30);
System.out.println(immutableMap); // {Alice=25, Bob=30}

immutableMap.put("Charlie", 35); // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------

Map.copyOf() (Java 10+):
✔ Unlike Collections.unmodifiableMap(), original map changes wont affect this one.
✔ Best for creating an immutable snapshot of an existing map.

Code:
Map<String, Integer> mutableMap = new HashMap<>();
mutableMap.put("Alice", 25);
mutableMap.put("Bob", 30);

Map<String, Integer> immutableMap = Map.copyOf(mutableMap);

immutableMap.put("Charlie", 35); // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------





