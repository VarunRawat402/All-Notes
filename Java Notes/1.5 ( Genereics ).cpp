-------------------------------------------------------------------------------------------------------------------------------
GENERICS:
-------------------------------------------------------------------------------------------------------------------------------

What are Generics in Java?
    Generics allows you to create classes, interfaces, and methods that work with different data types while ensuring type safety at compile time.

Type Safety - Prevents inserting the wrong type.
No Type Casting - Cleaner and safer code.
Code Reusability - Same class works for multiple types.

-------------------------------------------------------------------------------------------------------------------------------

ArrayList list = new ArrayList();   // Not type-safe
list.add("Hello");
list.add(100);                      // Allowed (different types)

String s = (String) list.get(1);    // Runtime error: ClassCastException

-------------------------------------------------------------------------------------------------------------------------------

ArrayList<String> list = new ArrayList<>();

list.add("Hello");
list.add(100);              // Compilation error (wrong type)

String str = list.get(0);   // No casting needed
System.out.println(str);

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
        System.out.println(c1.getValue());   // [Hello, World]

        // Custom with Integer
        Custom<Integer> c2 = new Custom<>();
        c2.addValue(10);
        c2.addValue(20);
        System.out.println(c2.getValue());   // [10, 20]
    }
}

-------------------------------------------------------------------------------------------------------------------------------