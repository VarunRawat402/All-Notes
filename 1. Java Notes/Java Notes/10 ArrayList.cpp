-----------------------------------------------------------------------------------------------------------------------------------------------------
Array List:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Syntax:
    ArrayList<Integer> l1 = new ArrayList<>();
    ArrayList<Integer> l1 = new ArrayList<>(1000);      //Initial capacity is 1000 before creating bigger size array

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference Between Arrays and ArrayList:

→ Array has fixed size , length()
→ ArrayList has dynamic size, size()
→ Add / Remove is difficult in array due to manual index shifting
→ Array is faster than ArrayList due to less memory overhead

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and Vector:

→ Vector is synchronized → Thread-safe.
→ ArrayList is not synchronized → Not thread-safe.
→ Because of synchronization, Vector has more overhead and is slower.
→ Use ArrayList in single-threaded programs, Vector in multi-threaded scenarios (rarely recommended today).

-----------------------------------------------------------------------------------------------------------------------------------------------------

ArrayList vs LinkedList:

ArrayList
    → Dynamic array
    → Fast random access (index-based) ✅
    → Less memory overhead
    → Best for read-heavy operations

LinkedList
    → Doubly linked list
    → Fast insert/delete at start/middle ✅
    → No random access
    → More memory usage

Uses:

ArrayList
    → Returning list from REST API
    → DTO collections
    → Index-based loops

LinkedList
    → Task queues
    → Sliding window
    → BFS traversal

-----------------------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and CopyOnWriteArrayList:

ArrayList: 
    → Modifies the original list.
    → Cannot modify while iterating → Causes ConcurrentModificationException.

CopyOnWriteArrayList:
    → On modification, creates a new copy of the list.
    → Safe to modify while iterating because reading happens on the old array.
    → Thread-safe.

-----------------------------------------------------------------------------------------------------------------------------------------------------

CopyOnWriteArrayList():

List<String> l1 = new CopyOnWriteArrayList<>();
    l1.add("Milk");
    l1.add("Eggs");
    l1.add("Bread");

for(String item : l1){
    if(item.equals("Eggs")){
        l1.add("Butter"); // ✅ Safe
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------
ArrayList vs Arrays.asList vs List.of:
-----------------------------------------------------------------------------------------------------------------------------------------------------

ArrayList():
    → Mutable
    → Allows Null
    → Not-ThreadSafe

-----------------------------------------------------------------------------------------------------------------------------------------------------

Arrays.asList():
    → Can change the value of the element
    → Cannot add or remove elements
    → Allows null
    → Not-Thread Safe

Ex:
List<String> list = Arrays.asList("A", "B", "C");
list.set(1, "X");       // ✅ Works fine (modifying elements)
// list.add("D");       // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------------------

List.of():
    → Immutable
    → No null allowed
    → Thread Safe 

Ex:
List<String> list = List.of("A", "B", "C");
// list.set(1, "X");    // ❌ Throws UnsupportedOperationException
// list.add("D");       // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------------------