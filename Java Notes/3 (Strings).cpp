-----------------------------------------------------------------------------------------------------------------------------------------
Strings:
-----------------------------------------------------------------------------------------------------------------------------------------

String          → Immutable (value cannot be changed)
StringBuilder   → Mutable, fast, not thread-safe
StringBuffer    → Mutable, slower, thread-safe

-----------------------------------------------------------------------------------------------------------------------------------------

Why is String Immutable in Java:

Once a String object is created, its value cannot be changed.
Any modification creates a new object.

-----------------------------------------------------------------------------------------------------------------------------------------

1: Security

Strings are used in sensitive areas like:

Database URLs (jdbc:mysql:)
File paths
Class names used by ClassLoader

If Strings were mutable, malicious code could change these values at runtime, leading to security issues.

-----------------------------------------------------------------------------------------------------------------------------------------

2. String Pool (Memory Optimization):

Java stores string literals in a special memory String Pool.

String s1 = "Hello";
String s2 = "Hello"; 

Only one "Hello" object is created in the pool, s1 and s2 point to the same object
If Strings were mutable, changing s1 would also change s2, which breaks string pooling.

-----------------------------------------------------------------------------------------------------------------------------------------

3: Thread-Safety
Strings cannot change, Multiple threads can safely share the same String
No synchronization needed → better performance

-----------------------------------------------------------------------------------------------------------------------------------------

4: HashCode Caching (Fast Performance in HashMap & HashSet):

Key → hashCode()
Bucket index → hashCode % numberOfBuckets
Inside bucket → .equals() is used to find exact key

If String were mutable:
        Hashcode would change
        Key would become unreachable in HashMap / HashSet

Collisions:
When two different keys produce the same hash code and mapped to the same bucket

How Java handles collisions:
Each bucket holds a Linked list / Red black tree of entries.
If multiple keys hash to the same bucket, they are stored in that list.

In bucket .equals() is used to get the correct key

-----------------------------------------------------------------------------------------------------------------------------------------

Note:
Using new keyword to create string will always create another string even if the value is same

Example 1:
        String s1 = "Hello";
        String s2 = "Hello";
        System.out.println(s1 == s2);           // true


Example 2:
        String s1 = "Hello";
        String s2 = new String("Hello");
        System.out.println(s1 == s2);           // false


-----------------------------------------------------------------------------------------------------------------------------------------

== vs .equals()

==              → compares references
.equals()       → compares values

Note:
In Object class, .equals() checks reference
String overrides .equals() to check value

-----------------------------------------------------------------------------------------------------------------------------------------
