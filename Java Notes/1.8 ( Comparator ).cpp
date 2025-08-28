-------------------------------------------------------------------------------------------------------------------------------
Comparator
-------------------------------------------------------------------------------------------------------------------------------

A Comparator is used in Java to define custom sorting logic for objects.

Why Use Comparator?
🔹 The default sorting (Collections.sort()) doesnt know how to compare objects 
🔹 Solution? Use Comparator to define sorting rules for the objects

Syntax:
Collection.sort(List,Comparator)

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Age:

Student s1 = new Student("Varun",24);
Student s2 = new Student("Arunn",31);
Student s3 = new Student("Priti",32);

List<Student> l1 = new ArrayList<>();
l1.add(s1);
l1.add(s3);
l1.add(s2);

//In Ascending Order
Collections.sort(l1,(Student x,Student y)-> {
    return x.getAge() - y.getAge();
});

//Lambda Functions
Collections.sort(l1,(x,y)->(x.getAge()-y.getAge()));
Collections.sort(l1,(x,y)->(y.getAge())- x.getAge());  //Descending Order

//Modern Approach
Collections.sort(l1,Comparator.comparingInt(Student::getAge));
Collections.sort(l1,Comparator.comparingInt(Student::getAge).reversed());       //Descending Order

System.out.println(l1);

-------------------------------------------------------------------------------------------------------------------------------

Sorting Based on Name:

//Lambda Functions
Collections.sort(l1,(x,y)->(x.getName().compareTo(y.getName())));
Collections.sort(l1,(x,y)->(y.getName().compareTo(x.getName())));               //Descending Order


//Modern Approach
Collections.sort(l1,Comparator.comparing(Student::getName));
Collections.sort(l1,Comparator.comparing(Student::getName).reversed());

-------------------------------------------------------------------------------------------------------------------------------

Sort first by age then by Name:
Collections.sort(l1,
                    Comparator.comparingInt(Student::getAge)
                    .thenComparing(Student::getName));

-------------------------------------------------------------------------------------------------------------------------------

Comparator vs Comparable:

What is Comparable?

Comparable is an interface
It allows objects of a class to be compared and sorted using methods like Collections.sort()
Must override the method compareTo() to tell how object should get sorted
Use methods like Collections.sort() or Arrays.sort() with this.

-------------------------------------------------------------------------------------------------------------------------------

Code:

class Student implements Comparable<Student> {

    int id;
    String name;
    int age;

    public Student(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

    @Override
    public int compareTo(Student other) {
        return this.age - other.age;
    }

    @Override
    public String toString() {
        return name + " (" + age + ")";
    }
}

public class Main {
    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();
        students.add(new Student(1, "Alice", 22));
        students.add(new Student(2, "Bob", 20));
        students.add(new Student(3, "Charlie", 25));

        Collections.sort(students); // Uses compareTo()

        System.out.println(students); // [Bob (20), Alice (22), Charlie (25)]
    }
}

-------------------------------------------------------------------------------------------------------------------------------