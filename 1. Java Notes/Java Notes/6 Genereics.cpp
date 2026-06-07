-----------------------------------------------------------------------------------------------------------------------------------------------------
GENERICS:
-----------------------------------------------------------------------------------------------------------------------------------------------------

What are Generics in Java?
    → It allows classes / methods to work with any data type with type safety at compile time
    → Arraylist<String> / HashMap<String,Integer>

Uses:
    → Type safety at compile time
    → No need for casting

-----------------------------------------------------------------------------------------------------------------------------------------------------

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
        c2.addValue("Hello");                   // Compile time error
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------