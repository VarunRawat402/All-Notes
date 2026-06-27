-----------------------------------------------------------------------------------------------------------------------------------------------------
JAVA 
-----------------------------------------------------------------------------------------------------------------------------------------------------

JDK (Java Development Kit):
    → Compile + run java code
    → Coverts the java code to .class file using compiler
    → Contains JRE + JVM

JRE (Java Runtime Environment):
    → JVM + built-in Java libraries
    → Ex: Arraylist, Scanner etc.

JVM (Java Virtual Machine):
    → Runs the .class file and executes the java program
    → Handle GC

-----------------------------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive       : byte / short / int / long / char / boolean / float / double
Non-Primitive   : Integer / String / Boolean / Array / Class / Object

Primitive Default        → 0 / false
Non-primitive Default    → null

-----------------------------------------------------------------------------------------------------------------------------------------------------

ASCII Values:

'A' → 'Z'  →  65 to 90
'a' → 'z'  →  97 to 122
'0' → '9'  →  48 to 57

Ex:
char a = 'A';
System.out.println((int) a);        //65
System.out.println('A' + 'B');      //131
System.out.println('1' + 1);        // 50

-----------------------------------------------------------------------------------------------------------------------------------------------------

STACK:
    → Primitive values / Local variables / References of objects / Method() calls

HEAP:
    → Objects / Instance variables

Metaspace:
    → Class info / Static variables

Example:

1: int a = 10;         
    → a, 10 stored in stack

2: String s = "Varun"; 
    → s in stack
    → "Varun" in heap

3: static int b = 20; 
    → b, 20 stored in metaspace

-----------------------------------------------------------------------------------------------------------------------------------------------------

What is Garbage Collection:
    → It automatically removes objects with no reference from heap memory.
    → If no reference of objects → eligible for Garbage collection

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you ensure Garbage Collection is working correctly:
    → Avoid memory leaks ( remove references of objects when no need )
    → Heap usage is stable over time
    → Monitor via VisualVM / JConsole
    → Check GC logs

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you debug OutOfMemoryError:
    → Read error: tells which memory area is full
    → Take heap dump: -XX:+HeapDumpOnOutOfMemoryError
    → Analyze with Eclipse MAT or VisualVM
    → Look for leaked objects

-----------------------------------------------------------------------------------------------------------------------------------------------------