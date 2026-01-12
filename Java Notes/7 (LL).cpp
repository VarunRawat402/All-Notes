-----------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------

Linear data structure where elements are stored in nodes
Each node → data + reference of next node

Dynamically sized - grows/shrinks at runtime
Does not require contiguous memory allocation

Syntax:
    LinkedList<String> ll = new LinkedList<>();

Time Complexity:

Insertion:  O(1) at beginning/end, O(n) at specific position
Deletion:   O(1) at beginning, O(n) at end/specific position
Search:     O(n) — must traverse from head
Access:     O(n) — cannot directly access index

1. Singly Linked List:
    Each node points only to next node
    Traversal only forward

2. Doubly Linked List:
    Each node points to both next and previous nodes
    Can traverse in both directions

3. Circular Linked List:
    Last node points back to first node
    Forms a circular chain

4. Doubly Circular Linked List:
    Combination of doubly + circular
    First ↔ Last connected both ways

Note:
Java’s LinkedList is implemented as a Doubly Linked List

-----------------------------------------------------------------------------------------------------------------------------------------

Key Points:

Best for frequent insertions/deletions, No element shifting required
Slow random access
Higher memory usage (extra references)
No contiguous memory needed

-----------------------------------------------------------------------------------------------------------------------------------------

1. Adding Elements:

list.add("Apple");        // Add at end
list.addFirst("Orange");  // Add at beginning
list.addLast("Banana");   // Add at end
list.add(1, "Mango");     // Add at index

-----------------------------------------------------------------------------------------------------------------------------------------

2. Removing Elements:

list.remove();                       // Remove first element
list.removeFirst();                  // Remove first element
list.removeLast();                   // Remove last element
list.remove("Apple");                // Remove specific element
list.remove(2);                      // Remove element at index
list.removeFirstOccurrence("Apple"); // Remove first occurrence
list.removeLastOccurrence("Apple");  // Remove last occurrence
list.clear();                        // Remove all elements

-----------------------------------------------------------------------------------------------------------------------------------------

3. Accessing Elements:

list.getFirst();        // Get first element
list.getLast();         // Get last element
list.get(2);            // Get element at index
list.peek();            // Retrieve but don't remove first element
list.poll();            // Retrieve and remove first element

-----------------------------------------------------------------------------------------------------------------------------------------

4. Searching & Checking:

list.contains("Apple");          // Check if element exists
list.indexOf("Apple");           // Find first occurrence index
list.lastIndexOf("Apple");       // Find last occurrence index
list.size();                     // Get number of elements
list.isEmpty();                  // Check if empty

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and LinkedList:

LL is better for insertions/deletions → no shifting
get(index) is slower in LL → must traverse
LL uses more memory → every node stores next/prev references

-----------------------------------------------------------------------------------------------------------------------------------------