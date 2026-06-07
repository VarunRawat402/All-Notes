-----------------------------------------------------------------------------------------------------------------------------------------------------
Set ( Collection ):
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Stores unique elements only
→ No Duplicate
→ No indexing - cannot access elements by index

Syntax:
    Set<Integer> set1 = new HashSet<>();
    Set<String>  set2 = new LinkedHashSet<>();
    Set<Double>  set3 = new TreeSet<>();

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: HashSet : 
    → Fastest, No Order
    → Average time → O(1)
    → Not thread-safe
    → Allows 1 null element

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: LinkedHashSet:
    → Maintains Insertion Order
    → Slightly slower than HashSet due to ordering overhead
    → Not thread-safe
    → Allows 1 null element

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: TreeSet:
    → Sorted Order
    → Uses Red-Black Tree
    → Slower than HashSet (O(log N))
    → Not thread-safe
    → No null elements allowed

-----------------------------------------------------------------------------------------------------------------------------------------------------
