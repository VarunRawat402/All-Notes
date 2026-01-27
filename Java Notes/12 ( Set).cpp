-----------------------------------------------------------------------------------------------------------------------------------------
Set ( Collection ):
-----------------------------------------------------------------------------------------------------------------------------------------

→ Stores unique elements only
→ No Duplicate
→ No indexing - cannot access elements by index

Syntax:
    Set<Integer> set1 = new HashSet<>();
    Set<String>  set2 = new LinkedHashSet<>();
    Set<Double>  set3 = new TreeSet<>();

-----------------------------------------------------------------------------------------------------------------------------------------

Common Methods:
add()	        : Adds an element (E). Returns false if already present.
remove()	    : Removes an element.
contains()	    : Checks if an element exists.
size()	        : Returns the number of elements.
isEmpty()	    : Checks if the set is empty.
clear()	        : Removes all elements.

-----------------------------------------------------------------------------------------------------------------------------------------

1: HashSet : Fastest, No Order
→ Average time → O(1)
→ No order is maintained
→ Not thread-safe
→ Allows 1 null element

-----------------------------------------------------------------------------------------------------------------------------------------

2: LinkedHashSet:
→ Maintains Insertion Order
→ Slightly slower than HashSet due to ordering overhead
→ Not thread-safe
→ Allows 1 null element

-----------------------------------------------------------------------------------------------------------------------------------------

3: TreeSet:
→ Sorted Order
→ Uses Red-Black Tree
→ Slower than HashSet (O(log N))
→ Not thread-safe
→ No null elements allowed

-----------------------------------------------------------------------------------------------------------------------------------------


