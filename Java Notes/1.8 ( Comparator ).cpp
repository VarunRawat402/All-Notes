-------------------------------------------------------------------------------------------------------------------------------
Comparator
    A Comparator is a functional interface used to define custom sorting logic for objects.
-------------------------------------------------------------------------------------------------------------------------------

Students:
    Student s1 = new Student("Varun",24);
    Student s2 = new Student("Arunn",31);
    Student s3 = new Student("Priti",32);

Sorting Based on Age:

Lambda Function:
Collections.sort(l1, (x, y) -> x.getAge() - y.getAge());       // Ascending
Collections.sort(l1, (x, y) -> y.getAge() - x.getAge());       // Descending

Modern approach:
Collections.sort(l1, Comparator.comparingInt(Student::getAge));               
Collections.sort(l1, Comparator.comparingInt(Student::getAge).reversed());

Note:
x.getAge() - y.getAge() can cause integer overflow in rare cases.

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Name:

Lambda Function:
Collections.sort(l1,(x,y)->(x.getName().compareTo(y.getName())));

Modern approach:
Collections.sort(l1,Comparator.comparing(Student::getName));
Collections.sort(l1,Comparator.comparing(Student::getName).reversed());

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on multiple feilds:

First by age, then by name:
Collections.sort(
    l1,Comparator.comparingInt(Student::getAge).thenComparing(Student::getName)
);

-------------------------------------------------------------------------------------------------------------------------------

Comparable:
Comparable is an interface used to define default sorting logic inside the class itself.

Class must implement Comparable<T>
Override compareTo() method
Used when one natural sorting order is needed
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