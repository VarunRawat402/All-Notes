-----------------------------------------------------------------------------------------------------------------------------------------------------
Strings:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: String          → Immutable (new object on every change)
2: StringBuilder   → Mutable + fast + not thread-safe
3: StringBuffer    → Mutable + slower + thread-safe

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Security:

→ Strings used in DB URLs, file paths, network connections
→ Immutable = no one can change these values at runtime
→ Prevents malicious modification mid-execution

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. String Pool:

→ Java stores strings in String Pool to save memory
→ Multiple reference points to same object
        String s1 ----\
                        --> "Hello"
        String s2 ----/
→ If mutable → changing s1 would change s2 → pool breaks

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Thread-Safety:

→ Multiple threads can read the same string simultaneously without any synchronization needed. 
→ No one can modify it, so no conflicts.

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: HashMap Working:

→ hashCode()    → converts key into hashcode.
→ Calculates bucket Index using hashcode
→ Inside bucket → .equals() is used to find exact key between multiple keys

If String were mutable:
→ Value changes → hashcode changes → different bucket
→ Original key becomes unreachable — data lost in HashMap

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
→ When you store passwords in Strings, The reference is gone but the value is still in memory because Strings are immutable
→ GC can collect it in minutes or hours you dont know so any hacker or developer can see the password in dump

→ Chars[] is used to store passwords because after use you can fill with \0 char which is 0 
→ and if anyone tries to see the password it shows 0 instead of the password

-----------------------------------------------------------------------------------------------------------------------------------------------------