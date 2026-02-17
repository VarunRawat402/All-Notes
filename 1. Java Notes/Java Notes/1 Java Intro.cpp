-----------------------------------------------------------------------------------------------------------------------------------------------------
JAVA 
-----------------------------------------------------------------------------------------------------------------------------------------------------

JDK (Java Development Kit)      → Source code → byte code
JVM (Java Virtual Machine)      → Bytecode → Machine code → Executes program
JRE (Java Runtime Environment)  → Contains JVM + libraries needed to run Java programs; does not include compiler.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive       : byte, short, int, long, char, boolean, float, double
Non-Primitive   : String, Array, Class, Object

Default value of primitive        → 0 / false
Default value of Non-primitive    → null

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
    → Primitive values
    → Local variables
    → References of objects
    → Method() calls

HEAP:
    → Objects
    → Arrays
    → Instance variables

Metaspace:
    → Class info (class name, class structure)
    → Static variables

Example:

int a = 10;         
    → a and 10 stored in stack

String s = "Varun"; 
    → s in stack
    → "Varun" in heap

static int b = 20; 
    → b and 20 stored in metaspace

-----------------------------------------------------------------------------------------------------------------------------------------------------