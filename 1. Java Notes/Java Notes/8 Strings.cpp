-----------------------------------------------------------------------------------------------------------------------------------------------------
Strings:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: String          → Immutable (value cannot be changed)
2: StringBuilder   → Mutable, fast, not thread-safe
3: StringBuffer    → Mutable, slower, thread-safe

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Security:

→ Strings are used in sensitive areas like : Database URLs / File paths / Network connections.
→ If Strings were mutable, malicious code could change these values at runtime, leading to security issues.

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. String Pool:

→ Java stores string in a special memory String Pool.
→ String s1 = "Hello";
→ String s2 = "Hello"; 
→ Only one "Hello" object is created in the pool, s1 and s2 point to the same object
→ If Strings were mutable, changing s1 would also change s2, which breaks string pooling.

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Thread-Safety:

→ Strings cannot change after creation, means no state change
→ No thread can modify the actual string making other threads reads the same and correct value
→ No synchronization needed → better performance

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: HashCode Caching:

→ hashCode()    → converts key into hashcode.
→ Bucket index  → hashCode % numberOfBuckets
→ Inside bucket → .equals() is used to find exact key between multiple keys

If String were mutable:
        → Hashcode() is generated based on value
        → If value changes Hashcode would change
        → Key would become unreachable in HashMap / HashSet

-----------------------------------------------------------------------------------------------------------------------------------------------------

== vs .equals()

==              → compares references
.equals()       → compares values

Note:
→ In Object class, .equals() checks reference
→ String overrides .equals() to check value

-----------------------------------------------------------------------------------------------------------------------------------------------------

String s1 = "Hello";
String s2 = new String("Hello");

s1 == s2          → false (different references)
s1.equals(s2)     → true  (same values)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Why passwords are stored in chars[] not String:

→ When function ends all the objects and values inside the function lose their reference and gets collected by GC and removed
→ When you store passwords in Strings, The reference is gone but the value is still in memory because Strings is immutable
→ GC can collect it in minutes or hours you dont know so any hacker or developer can see the password in dump

→ Chars[] is used to store passwords because after use you can fill with \0 char which is 0 
→ and if anyone tries to see the password it shows 0 instead of the password

-----------------------------------------------------------------------------------------------------------------------------------------------------