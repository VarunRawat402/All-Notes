-----------------------------------------------------------------------------------------------------------------------------------------
Java 8 Features:
    Java 8 made Java more readable, faster, and functional
-----------------------------------------------------------------------------------------------------------------------------------------

Streams():
    Functional way to process collections
    Processes data without modifying original collection
    Supports operations like filter, map, reduce

Syntax:

// Array to Stream
int[] arr = {1,2,3,4};
IntStream s1 = Arrays.stream(arr);

// Normal Stream
Stream<Integer> s2 = Stream.of(1,2,3,4);

-----------------------------------------------------------------------------------------------------------------------------------------

Parallel Streams():
Normally, streams execute sequentially, meaning one item at a time. If the dataset is large, this can be slow.
Parallel streams split the work across multiple threads, utilizing multiple CPU cores to process data faster.
Used when dataset is large, operation is CPU intesive, No shared data, Each element takes time to process

-----------------------------------------------------------------------------------------------------------------------------------------

1: Lambda Expressions (Anonymous Functions)
    Reduces boilerplate code
    More readable

Ex:
interface Greeting {
    void sayHello();
}

Greeting g = () -> System.out.println("Hello Java 8");

-----------------------------------------------------------------------------------------------------------------------------------------

2:  Functional Interfaces (@FunctionalInterface)

Interface with exactly 1 abstract method
It can have any number of static and default method, but abstract method should be 1 only
Example: Runnable, Comparator, Callable.

-----------------------------------------------------------------------------------------------------------------------------------------

3: Default & Static Methods in Interfaces

default → has body, can be overridden
static → belongs to interface itself, not instances

-----------------------------------------------------------------------------------------------------------------------------------------

4 : Optional :
    Optional<T> is used to avoid NullPointerException.
    Encourages null-safe coding

Example:

//This will throw null pointer Exception if name is null
static public String upperCase(String name){
    return name.toUpperCase();
}

static public Optional<String> upperCase(String name){
    return Optional.ofNullable(name).map(String::toUpperCase);
}

-----------------------------------------------------------------------------------------------------------------------------------------

5: Predicate:
A Predicate<T> is a functional interface
Takes a condition return true or false

Predicate<Integer> isEven = num -> num % 2 == 0;

System.out.println(isEven.test(10)); // true
System.out.println(isEven.test(11)); // false

-----------------------------------------------------------------------------------------------------------------------------------------

Predicate with filter() in Streams
We often use Predicate with Streams to filter elements.

List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6);
Predicate<Integer> isEven = num -> num % 2 == 0;

List<Integer> evenNumbers = numbers.stream().filter(isEven).collect(Collectors.toList());

-----------------------------------------------------------------------------------------------------------------------------------------

Joining 2 Predicates:

Predicate<String> startsWithV = x -> x.toLowerCase().startsWith("v");
Predicate<String> endsWithT = x -> x.toLowerCase().endsWith("t");

Predicate<String> and = startsWithV.and(endsWithT);

String name = "Varun Rawat";
System.out.println(and.test(name));

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