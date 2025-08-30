-----------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------

It is a data structure that consist of elements where each element points towards the next element.
It is dynamically sized data structure.
Insert TC -> O(1)
Search TC -> O(n)
Linked list consists of nodes
Each node has data & next ( data = value, next = reference of next element )

There are 4 Types of LL:
1: Singly LL
2: Doubly LL
3: Circular LL
4: Doubly Circular LL

-----------------------------------------------------------------------------------------------------------------------------------------

Key Points:
It is better for frequent insertions and deletions as it does not reqire shifting of elements
Slow fetching access coz it has to traverse from starting to desired index
It use more memory as it needs to store the data and the address of the next node
There is only 1 implementation of LL in java, It is doubly Linked List

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

Difference Between ArrayList and LinkedList:

Insertion and Deletion is better in LL due to not shifting of elements
get(index) is slower in LL than ArrayList becuase it has to traverse the whole LL
LL requires more memory head as it contains the address of the next node too

-----------------------------------------------------------------------------------------------------------------------------------------