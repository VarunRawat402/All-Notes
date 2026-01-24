-------------------------------------------------------------------------------------------------------------------------------
Comparator:
    Functional Interface, used to design custom sorting logic for objects
-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Age:

Modern approach:
Collections.sort(l1, Comparator.comparingInt(Student::getAge));               
Collections.sort(l1, Comparator.comparingInt(Student::getAge).reversed());

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Name:

Modern approach:
Collections.sort(l1,Comparator.comparing(Student::getName));
Collections.sort(l1,Comparator.comparing(Student::getName).reversed());

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on multiple feilds:

Collections.sort(
    l1,Comparator.comparingInt(Student::getAge).thenComparing(Student::getName)
);

-------------------------------------------------------------------------------------------------------------------------------

Comparable:
    Interface, used to define one sorting logic for objects inside the class
    Needs to implement Comparable interface
    Override compareTo() 
    Works directly with Collections.sort() or Arrays.sort()

-------------------------------------------------------------------------------------------------------------------------------

Code:
class Student implements Comparable<Student> {

    String name;
    int age;

    @Override
    public int compareTo(Student other) {
        return this.age - other.age;            // Default sorting: by age
    }

    @Override
    public String toString() {
        return name + " (" + age + ")";
    }
}

-------------------------------------------------------------------------------------------------------------------------------