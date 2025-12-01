-------------------------------------------------------------------------------------------------------------------------------
Wrapper Classes:
-------------------------------------------------------------------------------------------------------------------------------

Wrapper classes convert primitive data types into objects.

Primitive         : int , short, char, long, boolean
Wrapper classes   :  Integer, Short, Character, Long, Boolean

Primitive Data Types : Stored in stack
Wrapper Object : Stored in Heap

-------------------------------------------------------------------------------------------------------------------------------

Conversion of Primitive Data Types to Wrapper objects:
Integer num2 = Integer.valueOf(10);

Auto-Boxing: primitive → Object
Unboxing: Object → primitive

// Auto-boxing
Integer num = 10;     // Compiler: Integer.valueOf(10)
Double pi = 3.14;     // Compiler: Double.valueOf(3.14)

// Unboxing
int x = num;          // Compiler: num.intValue()
double y = pi;        // Compiler: pi.doubleValue()


-------------------------------------------------------------------------------------------------------------------------------

Wrapper Classes in Collections (Real Use Case)

Collections such as ArrayList cannot store primitive types.
Wrapper classes allow storing numbers in lists.

ArrayList<Integer> list = new ArrayList<>();
list.add(10);   // Auto-boxing: int → Integer
list.add(20);
list.add(30);

int num = list.get(0); // Unboxing: Integer → int
System.out.println("First element: " + num);

-------------------------------------------------------------------------------------------------------------------------------