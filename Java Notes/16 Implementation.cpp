-------------------------------------------------------------------------------------------------------------------------------
Implementation Of Data Structures:
-------------------------------------------------------------------------------------------------------------------------------

Set:

HashSet:
    Implemented using HashMap
    Each element is stored as a key in HashMap with a constant dummy value
    No duplicates
    Allows one null value

LinkedHashSet
    Implemented using LinkedHashMap
    Each element stored as a key with a constant dummy value
    Maintains insertion order
    No duplicates
    Allows one null value

TreeSet:
    Implemented using NavigableMap / TreeMap (Red-Black Tree)
    Sorted order of elements
    No duplicates
    Does not allow null values

-------------------------------------------------------------------------------------------------------------------------------

Map:

HashMap:
    Implemented using a hash table (array of buckets)
    Uses array of Node<K,V>
    No collision → one entry in that bucket
    Collision → entries stored as a LinkedList inside the bucket
    When buckets list becomes large (treeify threshold), converted to a Red-Black Tree

LinkedHashMap:
    Same internal structure as HashMap
    Additionally maintains a doubly linked list to preserve insertion order
    Predictable iteration order

TreeMap:
    Implemented using a Red-Black Tree
    Keys stored in sorted order

-------------------------------------------------------------------------------------------------------------------------------

queue:

LinkedList:
    Implemented as a Doubly Linked List
    Supports queue operations (offer, poll, peek)
    