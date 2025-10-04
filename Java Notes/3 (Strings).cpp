-----------------------------------------------------------------------------------------------------------------------------------------
Strings:
-----------------------------------------------------------------------------------------------------------------------------------------

Java provides three classes to handle Strings:

String          : Immutable (Unchangeable).
StringBuilder   : Mutable & Fast (Not Thread-Safe).
StringBuffer    : Mutable & Thread-Safe (Slightly Slower).

-----------------------------------------------------------------------------------------------------------------------------------------

Why is String Immutable in Java?
In Java, String is immutable, meaning once created, its value cannot be changed.
This design choice was made for several important reasons:

-----------------------------------------------------------------------------------------------------------------------------------------

1: Security
String is widely used in security-sensitive operations, like:

Database connection URLs //(jdbc:mysql://...
File paths (C:/Users/...)
Class loading (Class.forName("com.example.MyClass"))
🔹 If String was mutable, an attacker could change values during execution, leading to serious security risks.

-----------------------------------------------------------------------------------------------------------------------------------------x`

2: String Pool Optimization (Memory Efficiency)
Java stores String literals in the String Pool for reusability.

String s1 = "Hello";
String s2 = "Hello"; // ✅ Reuses the same object from the pool
Means In heap there is only 1 "Hello" and s1 and s2 are pointing to the same value for Memory Efficiency.
If String was mutable, modifying s1 would also change s2, leading to unexpected behavior.

-----------------------------------------------------------------------------------------------------------------------------------------

3: Thread-Safety
Since String objects cannot change, multiple threads can safely use the same string without synchronization.
This improves performance in multi-threaded environments.

-----------------------------------------------------------------------------------------------------------------------------------------

4: HashCode Caching (Fast Performance in HashMap & HashSet)
Strings hashcode is cached to improve performance in collections like HashMap.

HashMap stored the key-value pair in hashCode to find it Efficienctly
When u get the value using key it convert the key into hashcode and search it in bucket using 
Hashcode % totalBuckets formula
If String was mutable, hashcode would change, breaking HashMap and HashSet functionality.

-----------------------------------------------------------------------------------------------------------------------------------------

String (Immutable)
A String is immutable, meaning its value cannot be changed after creation.

Ex:
String s1 = "Hello";
s1.concat(" World"); // ❌ This does NOT change s1
System.out.println(s1); // Output: Hello

Key Points:
✔ Every time we modify a String, a new object is created.
❌ This wastes memory & performance when making frequent changes.

-----------------------------------------------------------------------------------------------------------------------------------------

StringBuilder (Mutable & Fast)
StringBuilder is mutable, meaning it can be modified without creating new objects.
It is NOT thread-safe but is faster than StringBuffer.

Ex
StringBuilder sb = new StringBuilder("Hello");
sb.append(" World"); // ✅ Modifies the same object
System.out.println(sb); // Output: Hello World

Key Points:
✔ No new object is created → Better performance.
❌ Not thread-safe, meaning it may not work correctly in multi-threaded programs.

-----------------------------------------------------------------------------------------------------------------------------------------

StringBuffer (Mutable & Thread-Safe)
StringBuffer is similar to StringBuilder, but it is thread-safe, meaning it can be used safely in multi-threaded programs.
However, it is slower because it synchronizes methods.

Ex
StringBuffer sb = new StringBuffer("Hello");
sb.append(" World"); // ✅ Works like StringBuilder
System.out.println(sb); // Output: Hello World

Key Points:
✔ Thread-safe → Safe for multi-threaded applications.
❌ Slower due to synchronization overhead.

-----------------------------------------------------------------------------------------------------------------------------------------

Difference between StringBuilder and StringBuffer:

Code:
public class Test extends Thread{

        private StringBuilder sb;
        //private StringBuffer sb;

        Test(StringBuilder sb){
                this.sb = sb;
        }

        // Test(StringBuffer sb){
        //         this.sb = sb;
        // }

        @Override
        public void run(){
                for(int i=0;i<1000000;i++){
                sb.append("a");
                }
        }
}

Main:
StringBuilder s = new StringBuilder();
//StringBuffer s = new StringBuffer();
Test t1 = new Test(s);
Test t2 = new Test(s);

t1.start();
t2.start();

t1.join();
t2.join();

//Here correct answer should be 2000000 but it will come random
//coz t1 and t2 threads are working on it simultaneously and if both append at same time
//it will count as 1
System.out.println("length "+s.length());

//If we Use StringBuffer the output will be 2000000 Everytime

-----------------------------------------------------------------------------------------------------------------------------------------
