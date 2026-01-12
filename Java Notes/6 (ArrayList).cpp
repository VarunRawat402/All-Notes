-----------------------------------------------------------------------------------------------------------------------------------------
Array List:
-----------------------------------------------------------------------------------------------------------------------------------------

It is used to store collection of data.
Default Capacity : 10 elements
When capacity is exceeded, a new larger array is created internally and all elements are copied into it.

Syntax:
    ArrayList<Integer> l1 = new ArrayList<>();
    ArrayList<Integer> l1 = new ArrayList<>(1000);      //Initial capacity is 1000 before creating bigger size array

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between Arrays and ArrayList:

Size:
Array → fixed size
ArrayList → dynamic size

Length / Size:
Array → length
ArrayList → size()

Operations:
Array → add/remove difficult, manual index handling
ArrayList → easy add, remove, update

Performance:
Array → faster, less memory overhead
ArrayList → slightly slower due to resizing and extra features

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and Vector:

Vector is synchronized → Thread-safe.
ArrayList is not synchronized → Not thread-safe.
Because of synchronization, Vector has more overhead and is slower.
Use ArrayList in single-threaded programs, Vector in multi-threaded scenarios (rarely recommended today).

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and CopyOnWriteArrayList:

ArrayList: 
    Modifies the original list.
    Cannot modify while iterating → Causes ConcurrentModificationException.

CopyOnWriteArrayList:
    On modification, creates a new copy of the list.
    Safe to modify while iterating because reading happens on the old array.
    Thread-safe.

-----------------------------------------------------------------------------------------------------------------------------------------

ArrayList():

List<String> l1 = new ArrayList<>();
    l1.add("Milk");
    l1.add("Eggs");
    l1.add("Bread");

for(String item : l1){
    if(item.equals("Eggs")){
        l1.add("Butter"); // ❌ ConcurrentModificationException
    }
}


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

-----------------------------------------------------------------------------------------------------------------------------------------

Methods of ArrayList:

1: add():
2: get():
3: remove():
4: set():

-----------------------------------------------------------------------------------------------------------------------------------------
ArrayList vs Arrays.asList vs List.of:
-----------------------------------------------------------------------------------------------------------------------------------------

ArrayList():
Mutable , Allows Null
Fast, Not ThreadSafe

-----------------------------------------------------------------------------------------------------------------------------------------

Arrays.asList():
Fixed Size, Not Mutable
Replace the element but not add and remove element
Allows null, Not Thread Safe

Ex:
List<String> list = Arrays.asList("A", "B", "C");
list.set(1, "X");       // ✅ Works fine (modifying elements)
// list.add("D");       // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------

List.of():
Immutable, No null allowed
Thread Safe 

Ex:
List<String> list = List.of("A", "B", "C");
// list.set(1, "X");    // ❌ Throws UnsupportedOperationException
// list.add("D");       // ❌ Throws UnsupportedOperationException

-----------------------------------------------------------------------------------------------------------------------------------------