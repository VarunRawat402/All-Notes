-----------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------

It is a data structure that consist of elements where each element points towards the next element.
It is dynamically sized data structure.
Insert TC -> O(1)
Search TC -> O(n)
Linked list consists of nodes
Each node has data & next ( data = value, next = reference of next element )

-----------------------------------------------------------------------------------------------------------------------------------------

Key Points:
It is better for frequent insertions and deletions as it does not reqire shifting of elements
Slow fetching access coz it has to traverse from starting to desired index
It use more memory as it needs to store the data and the address of the next node

-----------------------------------------------------------------------------------------------------------------------------------------

Syntax:
    LinkedList<String> ll = new LinkedList<>();

    l1.add("Orange");
    l1.add("Banana");
    l1.add("Apple");

-----------------------------------------------------------------------------------------------------------------------------------------

Methods:

1: add() & addLast():
    Add element at the end of the linked list.
    l1.add("Orange");

2: addFirst():
    Add element at the front of the linked list.
    l1.addFirst("Apple");

3: removeFirst() & removeLast():
    Remove First element & Remove last element from the linked list.
    l1.removeFirst();
    l1.removeLast();

4: remove():
    Remove given element
    l1.remove("Apple");

5: Contains():
    Check if the given element is present in the linked list or not    
    l1.contains("Orange");

6: get():
    To get the element at the given index
    l1.get(0);

-----------------------------------------------------------------------------------------------------------------------------------------