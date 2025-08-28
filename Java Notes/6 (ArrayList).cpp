-----------------------------------------------------------------------------------------------------------------------------------------
Array List:
-----------------------------------------------------------------------------------------------------------------------------------------

It is used to store the collection of data.
Default Capacity : 10 elements
When elements increased more than the capacity it creates a new array with bigger size and 
copy the elements to the new array

Syntax:
    ArrayList<Integer> l1 = new ArrayList<>();
    ArrayList<Integer> l1 = new ArrayList<>(1000);      //Initial capacity is 1000 before creating bigger size array

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between Arrays and ArrayList:

Size:
Arrays: Have a fixed size that needs to be specified when the array is created. Once an array is created, its size cannot be changed.
ArrayLists: Did not have a fixed size and can increase and decrease the size dynamically.

Length/Size:
Arrays: Use the length property to get the size of the array.
ArrayLists: Use the size() method to get the number of elements in the ArrayList.

Mutability:
Arrays: Once created, the size of the array is fixed. You cannot add or remove elements easily.
ArrayLists: Can easily add, remove, or modify elements. They are more dynamic in terms of size.

Performance:
Arrays: Generally have slightly better performance as they are more lightweight and have a lower memory overhead.
ArrayLists: Have a higher memory overhead due to the underlying array and the additional features provided.

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and Vector:

Only Difference is vector is synchronized and thread safe while ArrayList is not ThreadSafe
Vector can increase performance overhead ( extra time, memory or power required by system due to synchronization )
So ArrayList is recommended in Single Thread while vector in MultiThread

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and CopyOnWriteArrayList:

When we modify the ArrayList it modifies the original list
thats why we cannot modify the ArrayList while reading it simultaneously and it will give us an exception
But when we modify the CopyOnWriteArrayList it creates a new list and now old list points to the new list
So, when we modify the CopyOnWriteArrayList while reading it, It will not give an exception
because we are reading the original list and modification is done on the new list and after the reading
old list will point to the new list 

CopyOnWriteArrayList is thread safe

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
    add( Index, Element ) = Will add element at the given index.
    add( Element ) = Will add element at the last.

2: get():
Syntax:
    get( Index ) = will get the element at the given index.

3: remove():
Syntax:
    remove( Index ) = will remove the element of the given index.

4: set():
Syntax:
    set( Index, Element ) = will replace the element at the given index with the given element.

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