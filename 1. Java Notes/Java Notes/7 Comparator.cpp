-----------------------------------------------------------------------------------------------------------------------------------------------------
COMPARATOR VS COMPARABLE:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Comparator:
    → Functional Interface
    → Used to sort the objects 
    → Sorting is decided outside of the class

-----------------------------------------------------------------------------------------------------------------------------------------------------

Comparable:
    → Interface, Implemented by the class itself
    → The class itself implements and decides how to sort the objects
    → Needs to override compareTo() method for sorting logic
    → Works directly with Collections.sort() or Arrays.sort()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Age:

Collections.sort(l1, Comparator.comparingInt(Student::getAge));               
Collections.sort(l1, Comparator.comparingInt(Student::getAge).reversed());

-----------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Name:

Collections.sort(l1,Comparator.comparing(Student::getName));
Collections.sort(l1,Comparator.comparing(Student::getName).reversed());

-----------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Based on multiple feilds:

Collections.sort(l1,Comparator.comparingInt(Student::getAge).thenComparing(Student::getName));

-----------------------------------------------------------------------------------------------------------------------------------------------------

Code:
class Student implements Comparable<Student> {

    String name;
    int age;

    // ascending → this comes first
    // zero     → equal
    // descending → other comes first
    @Override
    public int compareTo(Student other) {
        return this.age - other.age;
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------