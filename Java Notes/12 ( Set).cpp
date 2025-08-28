-----------------------------------------------------------------------------------------------------------------------------------------
Set ( Collection ):
-----------------------------------------------------------------------------------------------------------------------------------------

It is a collection that does not allow duplicate elements and can be unordered
or sorted based on the implementation.

Syntax:
    Set<Integer> s1 = new HashSet<>();

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Set:
1: HashSet<>();
2: LinkedHashSet<>();
3: SortedSet<>();
4: TreeSet<>();

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
Uses hashing for fast lookup (O(1))
No order is maintained
Best for quick operations (adding, removing, checking for an element)

Ex:
Set<Integer> set = new HashSet<>();
set.add(5);
set.add(2);
set.add(8);
set.add(1);
System.out.println(set); // Output: [1, 2, 5, 8] (Order NOT guaranteed)

-----------------------------------------------------------------------------------------------------------------------------------------

2: LinkedHashSet:
LinkedHashSet : Maintains Insertion Order
Preserves the order of insertion
Slightly slower than HashSet due to ordering overhead

Ex:
Set<Integer> set = new LinkedHashSet<>();
set.add(5);
set.add(2);
set.add(8);
set.add(1);
System.out.println(set); // Output: [5, 2, 8, 1] (Order maintained)

-----------------------------------------------------------------------------------------------------------------------------------------

3: TreeSet:
TreeSet : Sorted Order
Stores elements in sorted (ascending) order
Uses a balanced tree (Red-Black Tree)
Slower than HashSet (O(log N))

Ex;
Set<Integer> set = new TreeSet<>();
set.add(5);
set.add(2);
set.add(8);
set.add(1);
System.out.println(set); // Output: [1, 2, 5, 8] (Sorted order)

-----------------------------------------------------------------------------------------------------------------------------------------


