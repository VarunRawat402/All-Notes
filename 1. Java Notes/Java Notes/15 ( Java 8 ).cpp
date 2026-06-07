-----------------------------------------------------------------------------------------------------------------------------------------------------
Java 8 Features:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Sequential Programming:
    → You write everything manually what you want to do 
    → Create loop, add all the values into sum
    → returns sum

Functional Programming:
    → Use functions to do the task instead of writitng everything manually

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Streams():
    → Functional way to process collections
    → Processes data without modifying original collection

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Parallel Streams():
    → Normally, streams execute sequentially, meaning one item at a time. If the dataset is large, this can be slow.
    → Parallel streams split the work across multiple threads, utilizing multiple CPU cores to process data faster.
    → Used when dataset is large, operation is CPU intesive, No shared data, Each element takes time to process

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Lambda Expressions (Anonymous Functions):
    → Reduces boilerplate code
    → More readable

Ex:
interface Greeting {
    void sayHello();
}

Greeting g = () -> System.out.println("Hello Java 8");
g.sayHello();

-----------------------------------------------------------------------------------------------------------------------------------------------------

4:  Functional Interface:

→ Interface with exactly 1 abstract method
→ It can have any number of static and default method, but abstract method should be 1 only
→ Example: Runnable, Comparator, Callable.

-----------------------------------------------------------------------------------------------------------------------------------------------------

5: Default & Static Methods in Interfaces:

default → has body, can be overridden
static  → belongs to interface itself, not instances

-----------------------------------------------------------------------------------------------------------------------------------------------------

6: Optional<T>:
    → Optional<T> is used to avoid NullPointerException.
    → Encourages null-safe coding

Example:

public String upperCase(String name){               //If String is null → Throws NullPointerException
    return name.toUpperCase();
}

public Optional<String> upperCase(String name){
    return Optional.ofNullable(name).map(String::toUpperCase);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

7: Predicate<T>:
    → Functional Interface
    → Takes a condition return true or false

Predicate<Integer> isEven = num -> num % 2 == 0;
System.out.println(isEven.test(10));                    // true

-----------------------------------------------------------------------------------------------------------------------------------------------------

Predicate with filter() in Streams:
    → We use Predicate with Streams to filter elements.

List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6);
Predicate<Integer> isEven = num -> num % 2 == 0;
List<Integer> evenNumbers = numbers.stream().filter(isEven).collect(Collectors.toList());

-----------------------------------------------------------------------------------------------------------------------------------------------------

Joining 2 Predicates:

Predicate<String> startsWithV = x -> x.toLowerCase().startsWith("v");
Predicate<String> endsWithT = x -> x.toLowerCase().endsWith("t");

Predicate<String> and = startsWithV.and(endsWithT);
String name = "Varun Rawat";
System.out.println(and.test(name));

-----------------------------------------------------------------------------------------------------------------------------------------------------

8: Reduce():
    → Used to combine all stream elements into one result
    → sum, max, min, concatenation.
    → Based on condition, accumulate the data

Sum of Numbers:
int sum = numbers.stream().reduce(0, (a, b) -> a + b);

Max number:
Optional<Integer> max = l2.stream().reduce((x, y) -> x > y ? x : y);
Optional<Integer> max = l2.stream().reduce(Integer::max);

-----------------------------------------------------------------------------------------------------------------------------------------------------