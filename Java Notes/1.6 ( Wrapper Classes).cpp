-------------------------------------------------------------------------------------------------------------------------------
Wrapper Classes:

Integer, String , Byte, Short are wrapper classes
-------------------------------------------------------------------------------------------------------------------------------

Wrapper classes convert primitive data types into objects.
Primitive   : int , short, char, long, boolean
Wrapper    :  Integer, Short, Character, Long, Boolean

Primitive Data Types : Stored in stack
Wrapper Object : Stored in Heap

-------------------------------------------------------------------------------------------------------------------------------

Conversion of Primitive Data Types to Wrapper objects:
Integer num2 = Integer.valueOf(10);

Auto-Boxing & Unboxing
📌 Auto-Boxing → Converts primitive to object automatically.
📌 Unboxing    → Converts object back to primitive automatically.

// Auto-boxing: Primitive → Object
Integer num = 10; // Compiler converts: Integer.valueOf(10)
Double pi = 3.14; // Compiler converts: Double.valueOf(3.14)

// Unboxing: Object → Primitive
int x = num; // Compiler converts: num.intValue()
double y = pi; // Compiler converts: pi.doubleValue()

-------------------------------------------------------------------------------------------------------------------------------

Wrapper Classes in Collections (Real Use Case)

Primitive types cannot be used in collections like ArrayList.
Wrapper classes allow storing numbers in lists.

ArrayList<Integer> list = new ArrayList<>(); // Only works with Wrapper classes
list.add(10); // Auto-boxing: Converts int → Integer
list.add(20);
list.add(30);

int num = list.get(0); // Unboxing: Converts Integer → int
System.out.println("First element: " + num);

-------------------------------------------------------------------------------------------------------------------------------