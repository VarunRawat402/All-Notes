-----------------------------------------------------------------------------------------------------------------------------------------------------
Static:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Static Methods:
    → Can only access static variables and static methods
    → Used for utility classes
    Cannot be overridden

Static Blocks:
    → Executes one time when the class is loaded into memory
    → Runs before main()
    → Used to initialize connections
    → Multiple static blocks allowed → run in order written

-----------------------------------------------------------------------------------------------------------------------------------------------------
Final Keyword:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Final Variables:
    → Cannot change once assigned
    → Initialized directly or in constructor

2. Final functions:
    → Cannot be overridden by child classes

3. Final Classes:
    → Cannot be extended.
    → All methods automatically become non-overridable

4. Final Objects:
    → You can change the properties of final object
    → You cannot reassign the object again

Ex: 
    final Student s1 = new Student("Varun");
    s1.setName("New Name");         // ✅ Allowed
    s1 = new Student("X");          // ❌ Not allowed

---------------------------------------------------------------------------------------------------------------------------------------------------------------