-----------------------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Node  =  data + reference of next node
→ Dynamically sized
→ Does not require contiguous memory allocation

Syntax:
    LinkedList<String> ll = new LinkedList<>();

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

1. Adding Elements:

list.add("Apple");        // Add at end
list.add(1, "Mango");     // Add at index

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. Removing Elements:

list.remove("Apple");                // Remove specific element
list.remove(2);                      // Remove element at index

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. Accessing Elements:

list.getFirst();        // Get first element
list.getLast();         // Get last element
list.get(2);            // Get element at index

-----------------------------------------------------------------------------------------------------------------------------------------------------

4. Searching & Checking:

list.contains("Apple");          // Check if element exists
list.size();                     // Get number of elements
list.isEmpty();                  // Check if empty

-----------------------------------------------------------------------------------------------------------------------------------------------------