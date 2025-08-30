-------------------------------------------------------------------------------------------------------------------------------
Implementation Of Data Structures:
-------------------------------------------------------------------------------------------------------------------------------

Set:

HashSet:
    It is implemented using HashMap
    Every value is stored as key in HashMap with constant dummy value
    No Duplicates
    Allows 1 Null values

LinkedHashSet
    It is implemented using LinkedHashMap
    Every value is stored as key in LinkedHashMap with constant dummy value
    No Duplicates
    Allows 1 Null values

TreeSet:
    It is implemented using NavigableMap / TreeMap, which is a Red-Black Tree
    No Duplicates
    Allows No Null values

-------------------------------------------------------------------------------------------------------------------------------

Map:

HashMap:
    It is implemented using HashTable ( array of buckets + Linkedlist/tree for collisions)
    Uses array of Nodes 
    If no collision, one element in 1 index
    If collision, Multiple elements stored in 1 index as LinkedList
    If LinkedList size excceeds, It converts the LL to Red-Black Tree

LinkedHashMap:
    Same has HashMap, instead of LL
    It uses Doubly Linked List

TreeMap:
    It implemented using RedBlack Tree

-------------------------------------------------------------------------------------------------------------------------------

queue:

LinkedList:
    Doubly Linked List
    