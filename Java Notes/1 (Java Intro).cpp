-------------------------------------------------------------------------------------------------------------------------------
JAVA 
-------------------------------------------------------------------------------------------------------------------------------

🔹 Source Code to Execution

    Source Code → Code written in Hello.java
    Compiler → Present in JDK, converts source code to Bytecode.
    Bytecode → Stored as .class file. Can run on any OS that has a JRE.
    JVM (Java Virtual Machine) → Converts bytecode into machine code and executes it.
    JDK (Java Development Kit) → Compiles .java → .class.
    JRE (Java Runtime Environment) → Contains JVM, required to run .class files.

Compile Time
    Conversion of Hello.java → Hello.class
    Done by compiler (JDK)
    Performs: Syntax checking, Type checking, Variable declaration errors

Run Time
    Phase where compiled bytecode is executed inside the JVM
-------------------------------------------------------------------------------------------------------------------------------

Data Types:

Primitive : byte , short , char, boolean, int , long 
Non-Primitive : Class, Object, String, Array

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
    //Case Sensitive
    //Can be letters, numbers, $, and _
    //First letter cannot be a number
    //Camel Case
    //Cannot use Java keywords as name

-------------------------------------------------------------------------------------------------------------------------------

Cloneable:
    Cloneable → Interface used for cloning objects
    clone() method → Creates a copy of an object
    Default: Shallow Copy
    For Deep Copy, override clone() and copy manually

Shallow Copy
    Cloned object shares same references as original
    Changes in one affect the other

Deep Copy
    Creates a new object with new references
    Same values, but different memory addresses
    Changes in one do not affect the other

Note:
    It only works with objects not primitive datatypes

-------------------------------------------------------------------------------------------------------------------------------