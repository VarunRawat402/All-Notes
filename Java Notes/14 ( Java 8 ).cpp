-----------------------------------------------------------------------------------------------------------------------------------------
Java 8 Features:
-----------------------------------------------------------------------------------------------------------------------------------------

It made Java faster, more readable, and more functional with lambda expressions, streams, functional interfaces, and more.

-----------------------------------------------------------------------------------------------------------------------------------------

Streams():

Java Streams provide a functional approach to processing collections of data. 
They allow you to perform operations like filtering, mapping, and reducing in a concise and efficient way.

Syntax:

//Arrays into stream
int[] arr = {1,2,3,4,5,6,7,8};
IntStream stream1 = Arrays.stream(arr);

//Creating Stream normally
Stream<Integer> stream2 = Stream.of(1,2,3,4);

//Creating stream with all 1 value with size 10
Stream<Integer> stream3 = Stream.generate(() -> 1).limit(10);

-----------------------------------------------------------------------------------------------------------------------------------------

Primitive Stream():
Normally, when you create a stream, it works with Objects (like Integer, Double, etc.), not primitive types (int, double).
This can cause performance issues because Java boxes and unboxes primitive values into objects (which takes extra memory and time).

Why Use Primitive Streams?
Avoids Boxing and Unboxing (int instead of Integer).
Better Performance (Uses less memory and is faster).
Specialized Methods (like sum(), average(), etc.).

Example: Using Primitive Streams:
import java.util.stream.IntStream;

public class PrimitiveStreamExample {
    public static void main(String[] args) {
        // Example 1: Generating a range of numbers
        IntStream.range(1, 5).forEach(System.out::println); // 1, 2, 3, 4
        
        // Example 2: Sum of numbers
        int sum = IntStream.rangeClosed(1, 5).sum(); // 1 + 2 + 3 + 4 + 5 = 15
        System.out.println("Sum: " + sum);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Parallel Streams():
Normally, streams execute sequentially, meaning one item at a time. If the dataset is large, this can be slow.
Parallel streams split the work across multiple threads, utilizing multiple CPU cores to process data faster.

Example:
import java.util.List;
import java.util.stream.IntStream;

public class ParallelStreamExample {
    public static void main(String[] args) {
        List<Integer> numbers = IntStream.rangeClosed(1, 1000).boxed().toList();
        
        // Sequential Stream (One thread processes all numbers)
        long start = System.currentTimeMillis();
        int sumSequential = numbers.stream().reduce(0, Integer::sum);
        long end = System.currentTimeMillis();
        System.out.println("Sequential Sum: " + sumSequential + ", Time: " + (end - start) + "ms");
        
        // Parallel Stream (Multiple threads process numbers in parallel)
        start = System.currentTimeMillis();
        int sumParallel = numbers.parallelStream().reduce(0, Integer::sum);
        end = System.currentTimeMillis();
        System.out.println("Parallel Sum: " + sumParallel + ", Time: " + (end - start) + "ms");
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

1: Lambda Expressions (Anonymous Functions)

What is it?
Before Java 8:  We needed to create an entire class for simple logic.
After Java 8:   We can write functions inline using Lambda expressions.

Benefits:
✔ Reduces boilerplate code
✔ More readable

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

🔹 Benefits:
✔ Helps in writing cleaner code
✔ Supports Lambda expressions

Ex:

@FunctionalInterface
interface Calculator {
    int add(int a, int b);
}

public class Main {
    public static void main(String[] args) {
        Calculator calc = (a, b) -> a + b;
        System.out.println(calc.add(5, 10)); // 15
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

3: Default & Static Methods in Interfaces

Defualt Methods : You can provide implementations of the method
Static Method : Method Belongs to the class/Interfaces

4: New Date & Time API (java.time)

import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        LocalDate today = LocalDate.now();
        System.out.println(today); // 2025-03-09 (Example Output)
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

4 : Optional :

Optional<T> is a container object introduced to handle cases where a value might be null.
It helps avoid NullPointerException and makes code more readable and safe.

1. Avoiding NullPointerException:

@SpringBootApplication
public class DemoApplication {

	public static void main(String[] args) throws InterruptedException {
		SpringApplication.run(DemoApplication.class, args);

		System.out.println(upperCase(null));

    }

    //This will throw null pointer Exception if name is null
    static public String upperCase(String name){
		return name.toUpperCase();
	}

    //This will return object.Empty() if name is null and not throw an exception
	static public Optional<String> upperCase(String name){
		return Optional.ofNullable(name).map(String::toUpperCase);
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------

5: Predicate:
A Predicate<T> is a functional interface
It represents a condition (boolean-valued function) that takes an input and returns true or false.

Syntax:
@FunctionalInterface
public interface Predicate<T> {
    boolean test(T t);
}

Basic Example:

public class PredicateExample {
    public static void main(String[] args) {
        Predicate<Integer> isEven = num -> num % 2 == 0; 

        System.out.println(isEven.test(10)); // true
        System.out.println(isEven.test(11)); // false
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

Predicate with filter() in Streams
We often use Predicate with Streams to filter elements.

List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6);
Predicate<Integer> isEven = num -> num % 2 == 0;

List<Integer> evenNumbers = numbers.stream().filter(isEven).collect(Collectors.toList());
System.out.println(evenNumbers); // Output: [2, 4, 6]

-----------------------------------------------------------------------------------------------------------------------------------------


Joining 2 Condition using Predicate:

Predicate<String> startsWithV = x -> x.toLowerCase().startsWith("v");
Predicate<String> endsWithT = x -> x.toLowerCase().endsWith("t");

Predicate<String> and = startsWithV.and(endsWithT);

String name = "Varun Rawat";
System.out.println(and.test(name));

-----------------------------------------------------------------------------------------------------------------------------------------

6: Consumer:
The Consumer<T> interface is a functional interface in Java that represents an operation that takes a single input but returns no result

Syntax:
@FunctionalInterface
public interface Consumer<T> {
    void accept(T t);
}

accept(T t): Takes one input and performs an action without returning anything.


public class Main {
    public static void main(String[] args) {

        //Perform some action or modify something 
        Consumer<String> printConsumer = message -> System.out.println("Message: " + message);
        printConsumer.accept("Hello, Java!"); // Output: Message: Hello, Java!
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------

7: Reduce():
The reduce() method is used to perform operations (like sum, product, concatenation) on stream elements and return a single result.
In reduce method we give condition on how to accumulate the data

Sum of Numbers:
List<Integer> numbers = Arrays.asList(10, 20, 30, 40, 50);
int sum = numbers.stream().reduce(0, (a, b) -> a + b);

Max number:
Optional<Integer> max = l2.stream().reduce((x, y) -> x > y ? x : y);
or
Optional<Integer> max = l2.stream().reduce(Integer::max);
System.out.println(max);

-----------------------------------------------------------------------------------------------------------------------------------------

Example of Streams():

List<String> l1 = List.of("Ram","Shyam","Geeta","Gaurav");
List<Integer> l2 = List.of(1, 2, 3, 4, 5, 6, 7, 8);

//To Uppercase
l1.stream().map(String::toUpperCase).forEach(System.out::println);

//Print names starts with G
l1.stream().filter(x->x.startsWith("G")).forEach(System.out::println);

//Count all the even numbers
long count = l2.stream().filter(x->x%2==1).count();
System.out.println(count);

//Count occurrence of l
//It takes every char not every string
String sentence = "Hello world";
sentence.chars().filter(x->x=='l').count();

-----------------------------------------------------------------------------------------------------------------------------------------