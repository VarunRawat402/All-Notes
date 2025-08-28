-------------------------------------------------------------------------------------------------------------------------------
GENERICS:
-------------------------------------------------------------------------------------------------------------------------------

What is Generics in Java?
Generics allows you to create classes, interfaces, and methods that work with different data types while ensuring type safety at compile time.

Benefits
Type Safety (Prevents wrong type insertion).
No Type Casting (Cleaner code).
Code Reusability (Same class works for multiple types).

-------------------------------------------------------------------------------------------------------------------------------

ArrayList list = new ArrayList(); // ❌ No type safety
list.add("Hello");
list.add(100); // ❌ Allowed (Different type)

-------------------------------------------------------------------------------------------------------------------------------

ArrayList<String> list = new ArrayList<>();     //Type-safe (Only Strings)
list.add("Hello");
list.add(100);                                  // ❌ Compilation error (Wrong type)

String str = list.get(0);                       // ✅ No casting needed
System.out.println(str);

-------------------------------------------------------------------------------------------------------------------------------

How to Create a Generic class:


//Payment Class code
public class Payment<T> {

    private T value;

    Payment(T value){
        this.value=value;
    }

    public T getValue(){
        return value;
    }
}

// Main Class Code
//p object can only store Integer values
Payment<Integer> p = new Payment<>(20000);
System.out.println(p.getValue());

//p1 object can only store String values
Payment<String> p1 = new Payment<>("SBI Bank");
System.out.println(p1.getValue());

-------------------------------------------------------------------------------------------------------------------------------