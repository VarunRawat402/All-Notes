-----------------------------------------------------------------------------------------------------------------------------------------
Strings:
-----------------------------------------------------------------------------------------------------------------------------------------

Java provides three classes to handle Strings:

String          : Immutable (value cannot change)
StringBuilder   : Mutable, fast, not thread-safe
StringBuffer    : MMutable, slightly slower, thread-safe
-----------------------------------------------------------------------------------------------------------------------------------------

Why is String Immutable in Java?
In Java, String is immutable, meaning once created, its value cannot be changed.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Security
Strings are used in sensitive operations such as:

Database URLs like: jdbc:mysql://...
File paths
Class names for class loading

If Strings were mutable, malicious code could modify these values during runtime, causing security vulnerabilities.

-----------------------------------------------------------------------------------------------------------------------------------------

2. String Pool (Memory Optimization):
Java stores String literals in the String Pool for reusability.

String s1 = "Hello";
String s2 = "Hello"; // ✅ Reuses the same object from the pool
Means In heap there is only 1 "Hello" and s1 and s2 are pointing to the same "Hello" for Memory Efficiency.
If Strings were mutable, changing s1 would also change s2, which breaks string pooling.

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

Collisions:
When two different keys produce the same hash code and mapped to the same bucket

How Java handles collisions:

Each bucket holds a Linked list / Red black tree of entries.
If multiple keys hash to the same bucket, they are stored in that list.
When the map grows beyond load factor, Java increases the bucket array and redistributes entries.

In bucket list/tree .equals() is used to get the correct key

-----------------------------------------------------------------------------------------------------------------------------------------

String (Immutable)
A String is immutable, meaning its value cannot be changed after creation.

Ex:
String s1 = "Hello";
s1.concat(" World");            // Does NOT modify s1
System.out.println(s1);         // Hello

Key Points:
Every modification creates a new String object.
Inefficient when doing many changes (loops, concatenations).

-----------------------------------------------------------------------------------------------------------------------------------------

StringBuilder (Mutable & Fast):
StringBuilder is mutable, meaning its value can be changed after creation.
No new object is created → Better performance.
Not thread-safe, meaning it may not work correctly in multi-threaded programs.
Best choice for most string manipulation tasks

Ex
StringBuilder sb = new StringBuilder("Hello");
sb.append(" World");
System.out.println(sb);         // Hello World

-----------------------------------------------------------------------------------------------------------------------------------------

StringBuffer (Mutable & Thread-Safe)
StringBuffer is similar to StringBuilder, but it is thread-safe, meaning it can be used safely in multi-threaded programs.
However, it is slower because it synchronizes methods.

Ex
StringBuffer sb = new StringBuffer("Hello");
sb.append(" World");
System.out.println(sb);         // Hello World

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

Note:
Using new keyword to create string will always create another string even if the value is same

Example 1:
String s1 = "Hello";                    
String s2 = "Hello";
s1==s2                          //True

Example 2:
String s1 = "Hello";
String s2 = new String("Hello");
s1==s2                          //False

-----------------------------------------------------------------------------------------------------------------------------------------

==  vs .equals():

==:
It checks the reference

.equals():
It checks the Value
Originally .equals() also checks the refernce in the object class but it is overridden in String class to check value

-----------------------------------------------------------------------------------------------------------------------------------------
