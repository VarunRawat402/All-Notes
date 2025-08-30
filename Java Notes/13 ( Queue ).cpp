-----------------------------------------------------------------------------------------------------------------------------------------
Stack:
-----------------------------------------------------------------------------------------------------------------------------------------

It is a Last In First Out 
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

Code:

Stack<Integer> stack = new Stack<>();

stack.push(1);
stack.push(2);
stack.push(3);

System.out.println(stack.pop());
System.out.println(stack.pop());
System.out.println(stack.pop());

System.out.println(stack.pop());	//This gives exception because popping from empty stack gives exception

stack.push(1);
stack.push(2);
stack.push(3);

int top = stack.peek();				//Gives the top element

-----------------------------------------------------------------------------------------------------------------------------------------
Queue:
-----------------------------------------------------------------------------------------------------------------------------------------

It is a Interface/Collection that follow the FIFO Principle ( First in First out )
Since it is an interface we cant make an object of it.

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
Implements Queue using a doubly linked list
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
Orders elements based on priority (default: ascending order)
Does NOT allow null values
Elements are NOT retrieved in insertion order
Useful for job/task scheduling
Implemented based on a binary min heap  

Code:
Queue<Integer> pq = new PriorityQueue<>();
pq.add(50);
pq.add(20);
pq.add(30);
System.out.println(pq.poll()); // 20 (smallest element first)

-----------------------------------------------------------------------------------------------------------------------------------------

You can use Comparator to customize the order of storing

Ex:

Queue<Integer> pq = new PriorityQueue<>(Comparator.reverseOrder());
pq.add(50);
pq.add(20);
pq.add(30);

System.out.println(pq.poll()); // 50 (largest first)

-----------------------------------------------------------------------------------------------------------------------------------------

Deque in Java:

A Deque is an Interface
    Insertion & removal from both ends (front & rear)
    Can work as both a Queue (FIFO) and a Stack (LIFO)
    Supports insertion/removal from both ends
    Faster than LinkedList for queue operations
    flexible than PriorityQueue (supports both ends, priority queue doesnt)

-----------------------------------------------------------------------------------------------------------------------------------------

Implementations of Deque
ArrayDeque (Fastest Deque, uses dynamic array)
LinkedList (Deque using Doubly Linked List)

-----------------------------------------------------------------------------------------------------------------------------------------

Deque Methods:

Adding Elements:

Deque<String> deque = new ArrayDeque<>();
deque.addFirst("Front");
deque.addLast("Rear");
System.out.println(deque); // [Front, Rear]

-----------------------------------------------------------------------------------------------------------------------------------------

Removing Elements:

Deque<Integer> deque = new ArrayDeque<>(List.of(10, 20, 30));

System.out.println(deque.pollFirst()); // 10 (removes first element)
System.out.println(deque.pollLast());  // 30 (removes last element)
System.out.println(deque); // [20]

-----------------------------------------------------------------------------------------------------------------------------------------

BlockingQueue (Thread-Safe Queue):
    It is a Queue that is thread safe
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