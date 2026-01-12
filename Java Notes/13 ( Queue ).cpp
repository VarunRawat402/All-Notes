-----------------------------------------------------------------------------------------------------------------------------------------
Stack:
-----------------------------------------------------------------------------------------------------------------------------------------

Last In First Out 
It is a class
Stack<Integer> stack = new Stack<>();

-----------------------------------------------------------------------------------------------------------------------------------------

Important Methods

push(E item)            → Add element on top
pop()                   → Remove and return top element
peek()                  → Return top element (without removing)
isEmpty()               → Check if stack is empty
search(Object o)        → Returns 1-based position from the top

-----------------------------------------------------------------------------------------------------------------------------------------

Queue:

Follow the FIFO Principle ( First in First out )
Queue is an interface, Cannot create object directly

-----------------------------------------------------------------------------------------------------------------------------------------

Syntax:
    Queue<Integer> q = new LinkedList<>();

Important Methods of Queue

add(e)	        Inserts element, throws exception if capacity full.
offer(e)	    Inserts element, returns false if capacity full (better than add).
remove()	    Removes and returns head, throws exception if empty.
poll()	        Removes and returns head, returns null if empty (safer than remove).
element()	    Returns head without removing, throws exception if empty.
peek()	        Returns head without removing, returns null if empty.

-----------------------------------------------------------------------------------------------------------------------------------------

Types of Queues:
    LinkedList()
    PriorityQueue()
    ArrayDeque()

-----------------------------------------------------------------------------------------------------------------------------------------

1: LinkedList (Queue Implementation)
Doubly linked list
Allows null values
Insertion and deletion are fast
Maintains insertion order

Code:
Queue<String> queue = new LinkedList<>();
queue.add("A");
queue.add("B");
queue.add("C");
System.out.println(queue.poll()); // Removes "A"

-----------------------------------------------------------------------------------------------------------------------------------------

2: PriorityQueue (Sorted Queue)
Orders elements based on priority ( default sorted order )
Does NOT allow null values
Useful for job/task scheduling
Implemented based on a binary min heap  

-----------------------------------------------------------------------------------------------------------------------------------------

Note:
    You can use Comparator to customize the order of storing
    Ex:
    Queue<Integer> pq = new PriorityQueue<>(Comparator.reverseOrder());

-----------------------------------------------------------------------------------------------------------------------------------------

Deque in Java (Double Ended Queue):

A Deque is an Interface
    Works as Queue + Stack
    Supports insertion/removal from both ends
    flexible than PriorityQueue (supports both ends, priority queue doesnt)

-----------------------------------------------------------------------------------------------------------------------------------------

Implementations of Deque
ArrayDeque → Fastest, recommended
LinkedList → Doubly linked list

-----------------------------------------------------------------------------------------------------------------------------------------

Deque Methods:

Adding Elements:

Deque<String> deque = new ArrayDeque<>();
deque.addFirst("Front");
deque.addLast("Rear");

-----------------------------------------------------------------------------------------------------------------------------------------

Removing Elements:

Deque<Integer> deque = new ArrayDeque<>(List.of(10, 20, 30));

deque.pollFirst(); // 10
deque.pollLast();  // 30

-----------------------------------------------------------------------------------------------------------------------------------------

BlockingQueue (Thread-Safe Queue):
    Thread-safe
    It is used in multi-threading
    Automatically waits when empty/full
    Commonly used for producer-consumer problems

Code:

BlockingQueue<Integer> bq = new ArrayBlockingQueue<>(3);
bq.put(10);
bq.put(20);
bq.put(30);
System.out.println(bq.take()); // Removes 10

-----------------------------------------------------------------------------------------------------------------------------------------