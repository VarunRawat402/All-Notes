-------------------------------------------------------------------------------------------------------------------------------
JAVA 
-------------------------------------------------------------------------------------------------------------------------------

Source Code to Execution

Source Code → Code written in Hello.java
Compiler → Present in JDK, converts source code to Bytecode.
Bytecode → Stored in a .class file; platform-independent and can run on any OS with a JRE.

JDK (Java Development Kit) → Compiles .java → .class.
JVM (Java Virtual Machine) → Reads bytecode, converts it to machine code, and executes the program.
JRE (Java Runtime Environment) → Contains JVM + libraries needed to run Java programs; does not include compiler.

Compile Time
    Converts Hello.java → Hello.class
    Done by the compiler (inside JDK)
    Performs syntax checking, type checking, and variable declaration validation

Run Time
    Phase where compiled bytecode is executed inside the JVM
-------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive : byte, short, int, long, char, boolean, float, double
Non-Primitive : String, Array, Class, Object

Default value of primitive = 0
Default value of Non-primitive = null

-------------------------------------------------------------------------------------------------------------------------------

Byte -> short -> int -> long
( Based on capacity )

byte    ( 8bit )        ( -128 to 127 ) 
short   ( 16bit )       ( -32,768 to 32,767 )
int     ( 32bit )       ( -2,147,483,648 to 2,147,483,647 )
long    ( 64bit )       ( -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 )
Every Integral number is integer by default thats why you have to use 'L' to tell its Long

Ex:
    byte b  = 100;
    short s = 32000;
    int i   = 1000000;
    long l  = 10000000000L; // 'L' is required for long literals

-------------------------------------------------------------------------------------------------------------------------------

Decimal Numbers:
( float -> Double )
Every Decimal number is double as default thats why you have to use 'f' to tell its float

float   ( 32bit ) ( 6-7 decimal places )
Double  ( 64bit ) ( 15-16 decimal places )

Ex:
    float floatNumber   = 3.1415927f; // Requires 'f' suffix
    double doubleNumber = 3.141592653589793; // More precision

-------------------------------------------------------------------------------------------------------------------------------

Char ( 16bit ):
Used to store single digit characters
Every char has ASCII Value 

ASCII Values:

65 ('A') to 90 ('Z')
97 ('a') to 122 ('z')
0  ('1') to 9 ('57')

Ex:
chat a = 'A';
System.out.println((int) a);    //-> 65
System.out.println(a);          //-> A

-------------------------------------------------------------------------------------------------------------------------------

Naming Variables:
Case-sensitive

Can include letters, digits, $, and _

Cannot start with a digit

Follow camelCase for variable names

Cannot use Java keywords as variable names

-------------------------------------------------------------------------------------------------------------------------------

Shallow Copy
    Cloned object shares same references as original
    Changes in one affect the other

Deep Copy
    Creates a completely independent object
    New memory allocations for all fields
    Changes in one object do not affect the other

Cloneable:
    Cloneable → Interface used for cloning objects
    clone() → Creates a copy of an object

    Default cloning in Java is shallow copy
    For deep copy, override clone() and manually clone all fields
    
Note:
    It only works with objects not primitive datatypes

-------------------------------------------------------------------------------------------------------------------------------