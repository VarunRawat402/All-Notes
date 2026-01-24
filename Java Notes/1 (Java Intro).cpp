-------------------------------------------------------------------------------------------------------------------------------
JAVA 
-------------------------------------------------------------------------------------------------------------------------------

Source Code     → Java code in .java file
Bytecode        → .class file, platform independent
Compiler        → Converts source code to byte code

JDK (Java Development Kit)      → Converts source code to byte code
JVM (Java Virtual Machine)      → Reads bytecode, converts it to machine code, and executes the program.
JRE (Java Runtime Environment)  → Contains JVM + libraries needed to run Java programs; does not include compiler.

-------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive : byte, short, int, long, char, boolean, float, double
Non-Primitive : String, Array, Class, Object

Default value of primitive        → 0, false
Default value of Non-primitive    → null

-------------------------------------------------------------------------------------------------------------------------------

Char ( 16bit ):
Used to store single digit characters
Every char has ASCII Value 

ASCII Values:

'A' → 'Z'  →  65 to 90
'a' → 'z'  →  97 to 122
'0' → '9'  →  48 to 57

Ex:
char a = 'A';
System.out.println((int) a);        //65
System.out.println('A' + 'B');      //131
System.out.println('1' + 1);        // 50

-------------------------------------------------------------------------------------------------------------------------------

Shallow Copy
    → Top-level object is copied
    → Nested objects share same reference
    → Changes in nested objects affect both
    → Default Behavior

Deep Copy
    → Top-level and nested objects are copied
    → No shared references
    → Changes do not affect the other object
    → Must override clone()
    → Manually clone nested objects

Cloneable:
    Cloneable   → Marker Interface, Tells JVM that cloning is allowed
    clone()     → Method from Object class, Used to create copy of an object

-------------------------------------------------------------------------------------------------------------------------------