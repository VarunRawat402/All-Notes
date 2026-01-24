-------------------------------------------------------------------------------------------------------------------------------
GENERICS:
-------------------------------------------------------------------------------------------------------------------------------

What are Generics in Java?
    Generics allows you to create classes, interfaces, and methods that work with different data types 
    while ensuring type safety at compile time.

Type Safety         → Prevents inserting the wrong data type
No Type Casting     → Cleaner and safer code
Code Reusability    → Same logic works for multiple types

-------------------------------------------------------------------------------------------------------------------------------

How to Create a Generic class:

public class Custom<T> {

    List<T> l1 = new ArrayList<>();

    public void addValue(T value) {
        l1.add(value);
    }

    public List<T> getValue() {
        return l1;
    }
}

public class Main {
    public static void main(String[] args) {

        // Custom with String
        Custom<String> c1 = new Custom<>();
        c1.addValue("Hello");
        c1.addValue("World");
        System.out.println(c1.getValue());      // [Hello, World]

        // Custom with Integer
        Custom<Integer> c2 = new Custom<>();
        c2.addValue(10);
        c2.addValue(20);
        System.out.println(c2.getValue());      // [10, 20]
    }
}

-------------------------------------------------------------------------------------------------------------------------------