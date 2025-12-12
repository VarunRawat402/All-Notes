-----------------------------------------------------------------------------------------------------------------------------------------
Java 8 Features:
-----------------------------------------------------------------------------------------------------------------------------------------

It made Java faster, more readable, and more functional with lambda expressions, streams, functional interfaces, and more.

-----------------------------------------------------------------------------------------------------------------------------------------

Streams():

Streams provide a functional way to process collections.
They support operations like filter, map, reduce, etc., without modifying the original collection.

Syntax:

// Array to Stream
int[] arr = {1,2,3,4,5,6,7,8};
IntStream stream1 = Arrays.stream(arr);

// Normal Stream
Stream<Integer> stream2 = Stream.of(1,2,3,4);

// Stream of constant value (size 10)
Stream<Integer> stream3 = Stream.generate(() -> 1).limit(10);   

-----------------------------------------------------------------------------------------------------------------------------------------

Primitive Stream():
Normally, when you create a stream, it works with Objects (like Integer), not primitive types (int).
This can cause performance issues because Java boxes and unboxes primitive values into objects (which takes extra memory and time).

public class PrimitiveStreamExample {
    public static void main(String[] args) {

        IntStream.range(1, 5).forEach(System.out::println); 
        // 1 2 3 4

        int sum = IntStream.rangeClosed(1, 5).sum();
        System.out.println("Sum: " + sum); // 15
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Parallel Streams():
Normally, streams execute sequentially, meaning one item at a time. If the dataset is large, this can be slow.
Parallel streams split the work across multiple threads, utilizing multiple CPU cores to process data faster.
Used when dataset is large, operation is CPU intesive, No shared data, Each element takes time to process

Example:
public class ParallelStreamExample {
    public static void main(String[] args) {

        List<Integer> numbers = IntStream.rangeClosed(1, 1000).boxed().toList();

        long start = System.currentTimeMillis();
        int sumSequential = numbers.stream().reduce(0, Integer::sum);
        long end = System.currentTimeMillis();
        System.out.println("Sequential Time: " + (end - start));

        start = System.currentTimeMillis();
        int sumParallel = numbers.parallelStream().reduce(0, Integer::sum);
        end = System.currentTimeMillis();
        System.out.println("Parallel Time: " + (end - start));
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

1: Lambda Expressions (Anonymous Functions)

Reduces boilerplate code
More readable

Ex:

interface Greeting {
    void sayHello();
}

public class Main {
    public static void main(String[] args) {
        //No need to create class and implemet Greeting
        Greeting g = () -> System.out.println("Hello, Java 8!");
        g.sayHello();
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

2:  Functional Interfaces (@FunctionalInterface)

A functional interface is an interface with only one abstract method.
It can have any number of static and default method, but abstract method should be 1 only

Example: Runnable, Comparator, Callable.

Ex:
@FunctionalInterface
interface Calculator {
    int add(int a, int b);
}

public class Main {
    public static void main(String[] args) {
        Calculator calc = (a, b) -> a + b;
        System.out.println(calc.add(5, 10));
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

3: Default & Static Methods in Interfaces

default → has body, can be overridden
static → belongs to interface itself, not instances

4: New Date & Time API (java.time)

public class Main {
    public static void main(String[] args) {
        LocalDate today = LocalDate.now();
        System.out.println(today); // 2025-03-09 (Example Output)
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

4 : Optional :
    Optional<T> is used to avoid NullPointerException.

Example:

//This will throw null pointer Exception if name is null
static public String upperCase(String name){
    return name.toUpperCase();
}

//This will return object.Empty() if name is null and not throw an exception
static public Optional<String> upperCase(String name){
    return Optional.ofNullable(name).map(String::toUpperCase);
}

-----------------------------------------------------------------------------------------------------------------------------------------

5: Predicate:
A Predicate<T> is a functional interface
Predicate<T> → Performs a function, returns true or false

@FunctionalInterface
public interface Predicate<T> {
    boolean test(T t);
}

Predicate<Integer> isEven = num -> num % 2 == 0;

System.out.println(isEven.test(10)); // true
System.out.println(isEven.test(11)); // false

-----------------------------------------------------------------------------------------------------------------------------------------

Predicate with filter() in Streams
We often use Predicate with Streams to filter elements.

List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6);
Predicate<Integer> isEven = num -> num % 2 == 0;

List<Integer> evenNumbers = numbers.stream().filter(isEven).collect(Collectors.toList());
System.out.println(evenNumbers);        // Output: [2, 4, 6]

-----------------------------------------------------------------------------------------------------------------------------------------

Joining 2 Predicates:

Predicate<String> startsWithV = x -> x.toLowerCase().startsWith("v");
Predicate<String> endsWithT = x -> x.toLowerCase().endsWith("t");

Predicate<String> and = startsWithV.and(endsWithT);

String name = "Varun Rawat";
System.out.println(and.test(name));

-----------------------------------------------------------------------------------------------------------------------------------------

6: Consumer:
It is a Functional Interface
Consumer<T> → Performs a function, returns nothing

@FunctionalInterface
public interface Consumer<T> {
    void accept(T t);
}

//Perform some action or modify something 
Consumer<String> printConsumer = message -> System.out.println("Message: " + message);
printConsumer.accept("Hello, Java!"); // Output: Message: Hello, Java!

-----------------------------------------------------------------------------------------------------------------------------------------

7: Reduce():
Used to combine all stream elements into one result (sum, max, min, concatenation).
In reduce method we give condition on how to accumulate the data

Sum of Numbers:

List<Integer> numbers = Arrays.asList(10, 20, 30, 40, 50);
int sum = numbers.stream().reduce(0, (a, b) -> a + b);

Max number:

Optional<Integer> max = l2.stream().reduce((x, y) -> x > y ? x : y);

or

Optional<Integer> max = l2.stream().reduce(Integer::max);

-----------------------------------------------------------------------------------------------------------------------------------------

Example of Streams():

List<String> l1 = List.of("Ram","Shyam","Geeta","Gaurav");
List<Integer> l2 = List.of(1,2,3,4,5,6,7,8);

// Uppercase
l1.stream().map(String::toUpperCase).forEach(System.out::println);

// Starts with G
l1.stream().filter(x -> x.startsWith("G")).forEach(System.out::println);

// Count odd numbers
long count = l2.stream().filter(x -> x % 2 == 1).count();
System.out.println(count);

// Count occurrences of 'l'
String sentence = "Hello world";
long c = sentence.chars().filter(ch -> ch == 'l').count();

//Max and Min element in the List
Optional<Integer> maxi = l1.stream().reduce((a, b)->a>b?a : b);
Optional<Integer> mini = l1.stream().reduce((a, b)->a>b?b : a);
-----------------------------------------------------------------------------------------------------------------------------------------