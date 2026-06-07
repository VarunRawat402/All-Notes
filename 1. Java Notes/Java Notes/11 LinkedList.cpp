-----------------------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Node  =  data + reference of next node
→ LinkedList<String> ll = new LinkedList<>();

Time Complexity:

Insertion:  O(1) at beginning/end, O(n) at specific position
Deletion:   O(1) at beginning, O(n) at end/specific position
Search:     O(n) — must traverse from head
Access:     O(n) — cannot directly access index

1. Singly Linked List:
    → Each node points only to next node
    → Traversal only forward

2. Doubly Linked List:
    → Each node points to both next and previous nodes
    → Can traverse in both directions

3. Circular Linked List:
    → Last node points back to first node
    → Forms a circular chain

4. Doubly Circular Linked List:
    → Combination of doubly + circular
    → First ↔ Last connected both ways

Note:
→ In java LinkedList is implemented as a Doubly Linked List

-----------------------------------------------------------------------------------------------------------------------------------------------------