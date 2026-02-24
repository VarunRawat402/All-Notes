-----------------------------------------------------------------------------------------------------------------------------------------------------
JAVA 
-----------------------------------------------------------------------------------------------------------------------------------------------------

JVM (Java Virtual Machine):
    → Executes .class file and runs the java program
    → Handle GC
    
JRE (Java Runtime Environment):
    → JVM + Java libraries

JDK (Java Development Kit):
    → Used to Develop Java programs
    → Compiles code
    → Runs code
    → Contains JRE + JVM

-----------------------------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive       : byte / short / int / long / char / boolean / float / double
Non-Primitive   : Integer / String / Boolean / Array / Class / Object

Primitive Default        → 0 / false
Non-primitive Default    → null

-----------------------------------------------------------------------------------------------------------------------------------------------------

Char ( 16bit ):
    → Used to store single digit characters
    → Every char has ASCII Value 

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
    → It automatically removes unused objects from heap memory.
    → If no reference of objects → eligible for Garbage collection

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you ensure Garbage Collection is working correctly:
    → Check JVM GC logs
    → VisualVM
    → JConsole
    → Check Heap usage monitoring
    → Check GC metrics dashboards

-----------------------------------------------------------------------------------------------------------------------------------------------------

How do you debug OutOfMemoryError:
    → Enable Heap Dump
    → Capture dump on OOM
    → Analyze the dumps using tools
    → Find memory leaks
    → Check caches or fix static references

-----------------------------------------------------------------------------------------------------------------------------------------------------