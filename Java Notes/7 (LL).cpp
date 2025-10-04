-----------------------------------------------------------------------------------------------------------------------------------------
Linked List:
-----------------------------------------------------------------------------------------------------------------------------------------

Linear data structure where elements are stored in nodes
Each node contains data and reference to next node
Dynamically sized - grows/shrinks at runtime
Does not require contiguous memory allocation

Time Complexity:

Insertion: O(1) at beginning/end, O(n) at specific position
Deletion: O(1) at beginning, O(n) at end/specific position
Search: O(n) - must traverse from head
Access: O(n) - must traverse to index

1. Singly Linked List:
    Each node points only to next node
    Can traverse only in forward direction

2. Doubly Linked List:
    Each node points to both next and previous nodes
    Can traverse in both directions

3. Circular Linked List:
    Last node points back to first node
    Forms a circular chain

4. Doubly Circular Linked List:
    Combination of doubly and circular
    Last node points to first, first points to last

Note: Java's LinkedList class implements Doubly Linked List

-----------------------------------------------------------------------------------------------------------------------------------------

Key Points:

✅ Better for frequent insertions/deletions - No element shifting required
✅ Dynamic size - No pre-allocation needed
❌ Slow random access - Must traverse from head to desired index
❌ More memory overhead - Each node stores data + references
✅ Efficient memory utilization - No contiguous block required

-----------------------------------------------------------------------------------------------------------------------------------------

Syntax:
    LinkedList<String> ll = new LinkedList<>();

-----------------------------------------------------------------------------------------------------------------------------------------

1. Adding Elements:

list.add("Apple");                   // Add at end
list.addFirst("Orange");             // Add at beginning
list.addLast("Banana");              // Add at end (same as add())
list.add(1, "Mango");                // Add at specific index

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

String first = list.getFirst();      // Get first element
String last = list.getLast();        // Get last element
String element = list.get(2);        // Get element at index
String peek = list.peek();           // Retrieve but don't remove first element
String poll = list.poll();           // Retrieve and remove first element
-----------------------------------------------------------------------------------------------------------------------------------------

4. Searching & Checking:

boolean hasApple =  list.contains("Apple");          // Check if element exists
int index =         list.indexOf("Apple");           // Find first occurrence index
int lastIndex =     list.lastIndexOf("Apple");       // Find last occurrence index
int size =          list.size();                     // Get number of elements
boolean isEmpty =   list.isEmpty();                  // Check if empty

-----------------------------------------------------------------------------------------------------------------------------------------

Difference Between ArrayList and LinkedList:

Insertion and Deletion is better in LL due to not shifting of elements
get(index) is slower in LL than ArrayList becuase it has to traverse the whole LL
LL requires more memory head as it contains the address of the next node too

-----------------------------------------------------------------------------------------------------------------------------------------