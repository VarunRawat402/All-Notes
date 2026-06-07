-----------------------------------------------------------------------------------------------------------------------------------------------------
Java OOPs:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Destructor:
    → Java does not have destructors.

Default Constructor:
    → Automatically generated when no constructor is defined
    → If you define any constructor, default is not generated
    → Takes no parameters.

-----------------------------------------------------------------------------------------------------------------------------------------------------

Note:
1: Primitives are passed by value:
    → Value cannot be changed inside another method

2: Objects are passed by value of reference
    → Value can be changed inside another method
    → Cannot assign new reference to the object

3: Integer and String are also objects but they are immutable:
    → Value cannot be changed inside another method

-----------------------------------------------------------------------------------------------------------------------------------------------------

Access Modifiers:

1: Public:
    → Accessible from anywhere (any class, any package).

3: Private:
    → Not accessible from any other class.

3: Protected:
    → Accessible within the same package.
    → Accessible in another package only through inheritance (subclass).

4: Default:
    → Accessible within the same package only.
    → Not accessible outside the package.

-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Method Overloading:
    → Compile time Polymorphism
    → Same method name, different parameters

Ex:
    public class Calculator {
        public int add(int a, int b) {
            return a + b;
        }

        public int add(int a, int b, int c) {
            return a + b + c;
        }
    }

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Method Overriding:
    → Runtime Polymorphism
    → The method call is decided at runtime based on the object type.

Ex:
    public class Animal {
        public void makeSound() {
            System.out.println("Some generic sound");
        }
    }

    public class Cat extends Animal {
        @Override
        public void makeSound() {
            System.out.println("Meow");
        }
    }

    Animal cat = new Cat();
    cat.makeSound();            // Calls Cat's makeSound() method

-----------------------------------------------------------------------------------------------------------------------------------------------------
INHERITANCE:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1: Single Level Inheritance:
Ex:
    class Parent { }
    class Child extends Parent { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

2: Multilevel Inheritance:
Ex:
    class GrandParent { }
    class Parent extends GrandParent { }
    class Child extends Parent { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

3: Hierarchical Inheritance:

Ex:
    class Parent { }
    class Child1 extends Parent { }
    class Child2 extends Parent { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

4: Multiple Inheritance:    
    → In java we dont have multiple inheritance but we can acheive it through Interfaces.

Ex:   
    interface Father { }
    interface Mother { }
    class Child implements Father, Mother { }

-----------------------------------------------------------------------------------------------------------------------------------------------------

ENCAPSULATION:
    → Binding data + methods together and hiding internal data from outside access.

Key Concepts of Encapsulation

Private fields          → Restricts the access of data from outside.
Public getters/setters  → Give controlled access of Data to oustide.
Better Control          → Control over everything

-----------------------------------------------------------------------------------------------------------------------------------------------------

Super():
    → Used to access parent class things
    → super() is used to call the parent constructor, should be the first line in the childs constructor
    → super.name is used to access parent variable
    → super.hello() is used to call parent method

-----------------------------------------------------------------------------------------------------------------------------------------------------

Parent reference with Child object:

→ Parent p1 = new Child();
→ You can access parent variables and parent methods
→ You cannot access child variables and child methods
→ If parent methods are overriden then overriden methods will get executed ( run time polymorphism )

Note:
    Reference → what you CAN access
    Object    → what actually EXECUTES

-----------------------------------------------------------------------------------------------------------------------------------------------------

Object Class:
    → The root class of all Java classes.
    
hashCode():
    → Returns a unique hash value of the object

equals():
    → Default: compares reference of the objects.
    → Overridden in String, Integer, etc., to compare values.

toString():
    → It is used to return the String representation of Object

Finalize():
    → It is called automatically by the GC when object has no reference
    → It is used for cleanup Functions
    → Depricated after java 9

-----------------------------------------------------------------------------------------------------------------------------------------------------

Shallow Copy
    → Top-level object does not share reference
    → Nested objects share same reference
    → Default Behavior of clone()

Deep Copy
    → Top-level and nested objects both does not share reference
    → Must override clone() and manually clone nested objects
    → Must implement Cloneable interface

Cloneable:
    → Marker Interface
    → Must be implemented, otherwise throws CloneNotSupportedException 
    → Tells JVM that cloning is allowed

clone():
    → Method from Object class
    → Used to create copy of an object

-----------------------------------------------------------------------------------------------------------------------------------------------------