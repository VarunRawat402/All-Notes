-----------------------------------------------------------------------------------------------------------------------------------------------------
STACK & QUEUE:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Stack:
    → Last In First Out 
    → It is a class
    → Stack<Integer> stack = new Stack<>();
    → push() / pop() / peek() / isEmpty() / search()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Queue:
    → First in First out
    → It is an Interface
    → add() / offer() / remove() / poll() / peek ()

Queue<Integer> q    = new LinkedList<>();
Queue<Integer> pq   = new PriorityQueue<>();

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: LinkedList (Queue Implementation)
    → Doubly linked list
    → Maintains insertion order
    → Allows null values

Code:
Queue<String> queue = new LinkedList<>();

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: PriorityQueue (Sorted Queue)
    → Sorted order
    → No null values
    → Implemented based on a binary min heap  
    → Useful for job/task scheduling

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
    → You can use Comparator to customize the order of storing
    → Queue<Integer> pq = new PriorityQueue<>(Comparator.reverseOrder());

-----------------------------------------------------------------------------------------------------------------------------------------------------

Deque (Double Ended Queue):
    → It is an Interface
    → Works as Queue + Stack
    → Insertion and Deletion from both sides
    → Deque<String> deque = new ArrayDeque<>();
    → Deque<String> deque = new LinkedList<>();
    → addFirst() / addLast() / removeFirst() / removeLast() / getFirst() / getLast()
    
-----------------------------------------------------------------------------------------------------------------------------------------------------

BlockingQueue (Thread-Safe Queue):
    → Thread-safe
    → Used in Multithreading
    → Automatically waits when empty/full
    → Commonly used for producer-consumer problems
    → BlockingQueue<Integer> bq = new ArrayBlockingQueue<>(3);

-----------------------------------------------------------------------------------------------------------------------------------------------------
