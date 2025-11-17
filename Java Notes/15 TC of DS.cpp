-------------------------------------------------------------------------------------------------------------------------------
Time Complexity of Data Structures:
-------------------------------------------------------------------------------------------------------------------------------

ArrayList:

Insertion & Deletion (middle/start)   - O(n)   (shifting elements)
Insertion & Deletion at end           - O(1)
Searching                              - O(n)
get() and set()                        - O(1)

-------------------------------------------------------------------------------------------------------------------------------

LinkedList:
    
Insertion & Deletion at middle         - O(n)   (traversal required)
Insertion & Deletion at start/end      - O(1)
Searching                               - O(n)
get() and set()                         - O(n)   (no index-based access)

-------------------------------------------------------------------------------------------------------------------------------

Set: 

HashSet, LinkedHashSet:
    All operations (add, remove, search)   - O(1)

TreeSet:
    All operations                         - O(log n)

-------------------------------------------------------------------------------------------------------------------------------

Map:

HashMap, LinkedHashMap:
    Insertion & Deletion                  - O(1)
    Access (get/containsKey)              - O(1)

TreeMap:    
    Insertion and Deletion      - O(logn)
    Accessing                   - O(logn)

-------------------------------------------------------------------------------------------------------------------------------

Stack:
    
    push(), pop(), peek()                 - O(1)
    search()                              - O(n)

-------------------------------------------------------------------------------------------------------------------------------

Queue:
    
    LinkedList Queue          - O(1)
    PriorityQueue             - O(log n)
    ArrayDeque                - O(1)

-------------------------------------------------------------------------------------------------------------------------------
