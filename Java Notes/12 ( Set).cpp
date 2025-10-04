-----------------------------------------------------------------------------------------------------------------------------------------
Set ( Collection ):
-----------------------------------------------------------------------------------------------------------------------------------------

Collection that stores unique elements only
No Duplicate
No indexing - cannot access elements by index

Syntax:
    Set<Integer> set1 = new HashSet<>();
    Set<String> set2 = new LinkedHashSet<>();
    Set<Double> set3 = new TreeSet<>();

-----------------------------------------------------------------------------------------------------------------------------------------

Common Methods:
add(E e)	    : Adds an element (E). Returns false if already present.
remove(E e)	    : Removes an element.
contains(E e)	: Checks if an element exists.
size()	        : Returns the number of elements.
isEmpty()	    : Checks if the set is empty.
clear()	        : Removes all elements.

-----------------------------------------------------------------------------------------------------------------------------------------

1: HashSet : Fastest, No Order
Fastest operations O(1)
No order is maintained
Not thread-safe
Allows one null element

Ex:
    Set<Integer> set = new HashSet<>();
    set.add(5);
    set.add(2);
    set.add(8);
    set.add(1);
    System.out.println(set); // Output: [1, 2, 5, 8] (Order NOT guaranteed)

-----------------------------------------------------------------------------------------------------------------------------------------

2: LinkedHashSet:
Maintains Insertion Order
Slightly slower than HashSet due to ordering overhead
Not thread-safe
Allows one null element

Ex:
Set<Integer> set = new LinkedHashSet<>();
set.add(5);
set.add(2);
set.add(8);
set.add(1);
System.out.println(set); // Output: [5, 2, 8, 1] (Order maintained)

-----------------------------------------------------------------------------------------------------------------------------------------

3: TreeSet:
Sorted Order
Uses a balanced tree (Red-Black Tree)
Slower than HashSet (O(log N))
Not thread-safe
No null elements allowed

Ex;
Set<Integer> set = new TreeSet<>();
set.add(5);
set.add(2);
set.add(8);
set.add(1);
System.out.println(set); // Output: [1, 2, 5, 8] (Sorted order)

-----------------------------------------------------------------------------------------------------------------------------------------


