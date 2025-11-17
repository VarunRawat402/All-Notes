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
Arrays → Fixed size, cannot change after creation.
ArrayList → Dynamic size, grows and shrinks automatically.

Length/Size:
Arrays → Use length property.
ArrayList → Use size() method.

Mutability:
Arrays → Cannot add/remove elements easily; must manage indexes manually.
ArrayList → Supports add, remove, update operations easily.

Performance:
Arrays → Slightly faster, lower memory overhead.
ArrayList → Higher overhead due to dynamic resizing and extra features.

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
    Ex:

    List<String> l1 = new ArrayList<>();
    l1.add("Milk");
    l1.add("Eggs");
    l1.add("Bread");

    for(String item:l1){

        //We are adding butter while reading the list so it will give us an exception
        if(item.equals("Eggs")){
            l1.add("Butter");
        }
        System.out.println(item);
    }

CopyOnWriteArrayList():
    Ex:

    List<String> l1 = new ArrayList<>();
    l1.add("Milk");
    l1.add("Eggs");
    l1.add("Bread");

    for(String item:l1){

        //Butter is added to the new list and after the loop l1 is pointing to the new list
        if(item.equals("Eggs")){
            l1.add("Butter");
            System.out.println("Added butter in the list while reading");
        }
        System.out.println(item);
    }

-----------------------------------------------------------------------------------------------------------------------------------------

Methods of ArrayList:

1: add():
Syntax:
    add( Index, Element ) = add element at the given index.
    add( Element ) = add element at the last.

2: get():
Syntax:
    get( Index ) = get the element at the given index.

3: remove():
Syntax:
    remove( Index ) = remove the element of the given index.

4: set():
Syntax:
    set( Index, Element ) = replace the element at the given index with the given element.

5: Sort():
Syntax: 
    List<Integer> l1 = new ArrayList<>();
    Collections.sort(l1);

-----------------------------------------------------------------------------------------------------------------------------------------
ArrayList vs Arrays.asList vs List.of:
-----------------------------------------------------------------------------------------------------------------------------------------

ArrayList():
Mutable , Allows Null
Fast, Not ThreadSafe

Ex:
List<String> list = new ArrayList<>();
list.add("A");
list.add("B");
list.remove("A");  // ✅ Works fine
System.out.println(list); // [B]

-----------------------------------------------------------------------------------------------------------------------------------------

Arrays.asList():
Fixed Size, Not Mutable
Replace the element but not add and remove element
Allows null, Not Thread Safe

Ex:
List<String> list = Arrays.asList("A", "B", "C");
list.set(1, "X");  // ✅ Works fine (modifying elements)
// list.add("D");  // ❌ Throws UnsupportedOperationException
System.out.println(list); // [A, X, C]

-----------------------------------------------------------------------------------------------------------------------------------------

List.of():
Immutable, No null
Thread Safe 

Ex:
List<String> list = List.of("A", "B", "C");
// list.set(1, "X");  // ❌ Throws UnsupportedOperationException
// list.add("D");  // ❌ Throws UnsupportedOperationException
System.out.println(list); // [A, B, C]

-----------------------------------------------------------------------------------------------------------------------------------------