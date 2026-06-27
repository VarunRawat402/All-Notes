----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
JAVA 8 STREAM QUESTIONS
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Print Students:
    → students.stream().forEach(x->System.out.println(x));

Print Student name and salary:
    → students.stream().forEach(x->System.out.println(x.getName() + " : " + x.getSalary()));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FILTER:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Print student who belongs to "Computer Science" department:
    → students.stream().filter(x->x.getDepartment().equals("Computer Science"));

Print student who belongs to "Computer Science" department & salary > 65000:
    → students.stream().filter(x->x.getDepartment().equals("Computer Science") && x.getSalary()>65000)

Get Students who belong to department = "Computer Science" and collect the id and name of students in Map
    → students.stream().filter(x -> x.getDepartment().equals("Computer Science")).collect(Collectors.toMap(Student::getId, Student::getName));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FLATMAP:
    → Used when you want to fetch nested classes
    → Used when relation is OneToMany
    → Student → List<Projects>, Fetch project


Nested Class with Map returns Stream
    → List<Stream<String>> l1 = students.stream().map(x -> x.getProjects().stream().map(x -> x.getName())).collect(Collectors.toList());

FlatMap:
    → List<String> l1 = students.stream().flatMap(x -> x.getProjects().stream().map(y -> y.getName())).distinct().collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SORTED:

→ List<Student> l1 = students.stream().sorted(Comparator.comparing(Student::getSalary)).collect(Collectors.toList());
→ List<Student> l1 = students.stream().sorted(Collections.reverseOrder(Comparator.comparing(Student::getSalary))).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAX & MIN:

→ Optional<Student> max = students.stream().max(Comparator.comparing(Student::getSalary));
→ Optional<Student> min = students.stream().min(Comparator.comparing(Student::getSalary));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

COUNT:

Count Male and Female Students:
→ long male = students.stream().filter(x -> x.getGender().equals("Male")).count();
→ long female = students.stream().filter(x -> x.getGender().equals("Female")).count();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GroupingBy:
    → It is used to group on some attribute
    → Return value becomes the key 

→ It takes three arguments:

1: Function:
    → Return value of the function becomes the key 
    → Elements having the same return value adds in same key    

2: Collector Downstream:
    → Custom map to collect the key and values
    → LinkedHashMap::new

3: Collector:
    → Perform some action on collected elements
    → counting(), summintInt(), averagingInt(), mapping(), filtering()

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
Group Students based on Gender:
    → students.stream().collect(Collectors.groupingBy(Student::getGender));

Group Student Names based on Gender:		
    → students.stream().collect(Collectors.groupingBy(Student::getGender, Collectors.mapping(Student::getName, Collectors.toList())));

Group Student based on gender and give count of each gender:
    → students.stream().collect(Collectors.groupingBy(Student::getGender, Collectors.counting()));

Group Students based on salary and give names of the students:
    → students.stream().collect(Collectors.groupingBy(Student::getSalary, Collectors.mapping(Student::getName, Collectors.toList())));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FindFirst:
    → Returns the first element of list

Find first student with "Development" department if not present throw an exception:
    → students.stream().filter(x -> x.getDepartment().equals("Development")).findFirst().orElseThrow(() -> new IllegalArgumentException("No student with this department"));

FindAny:
    → Used to check if entity is present or not
    → Used in ParallelStream to find the student optimized way:

→ students.parallelStream().filter(x -> x.getDepartment().equals("Development")).findAny().orElseThrow(() -> new IllegalArgumentException("No student with this department"));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Limit:
    → Used to limit the values 

Find Top 3 highest salary Students:
    → students.stream().sorted(Comparator.comparing(Student::getSalary).reversed()).limit(3).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Skip:
    → When u want to skip first some elements:

Get student and skip first 5:
    → List<String> collect = students.stream().map(x -> x.getName()).skip(5).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Take out average salary based on employee gender:
    → collect= students.stream().collect(Collectors.groupingBy(Student::getGender, Collectors.averagingDouble(Student::getSalary)));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Java 8 Program to get Highest paid Employee in Each department using stream api:

→ students.stream().collect(Collectors.groupingBy(Student::getDepartment, Collectors.maxBy(Comparator.comparing(Student::getSalary))));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Coding Questions from java 8 Streams:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1: First non-repeating character
String s = "swiss";     //w

Code:
Character c1 = s.chars().mapToObj(c -> (char) c)
        .collect(Collectors.groupingBy(c -> c, Collectors.counting()))
        .entrySet()
        .stream()
        .filter(x -> x.getValue() == 1)
        .map(x -> x.getKey())
        .findFirst().orElse(null);
System.out.println(c1);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2: Find duplicate elements in a list:
List<Integer> list = List.of(1,2,3,2,4,5,1);
o/p = 1,2

Code:
List<Integer> collect = list.stream().collect(Collectors.groupingBy(x -> x, Collectors.counting()))
        .entrySet().stream()
        .filter(x -> x.getValue()>1)
        .map(x -> x.getKey())
        .collect(Collectors.toList());
System.out.println(collect);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3: Find frequency of each character:
String s = "banana";

s.chars().mapToObj(c->(char)c).collect(Collectors.groupingBy(c->c,Collectors.counting()));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4: Sort a list in descending and ascending order
List<Integer> list = List.of(3,1,5,2);

List<Integer> collect = list.stream().sorted(Comparator.reverseOrder()).collect(Collectors.toList());
List<Integer> collect = list.stream().sorted().collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5: Find second highest number:
List<Integer> list = List.of(10,20,30,40);

list.stream().sorted(Comparator.reverseOrder())
				.skip(1)
				.findFirst().orElse(null);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

6: Check if list contains duplicate elements
List<Integer> list = List.of(1,2,3,4,2);

//collect elements into set or distinct elements and check size of both list
boolean collect = list.stream().distinct().count()!=list.size();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

7: Reverse a string using Stream API:
String s = "java";

String reduce = s.chars().mapToObj(c -> (char) c)
        .reduce("", (a, b) -> b + a, String::concat);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

8: Find longest string in a list:
List<String> list = List.of("java", "springboot", "api");

String longest = list.stream()
        .max(Comparator.comparingInt(String::length))
        .orElse("");

System.out.println(longest); // springboot

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

9: Find sum of all even numbers:
List<Integer> list = List.of(1,2,3,4,5,6);
int sum = list.stream()
        .filter(n -> n % 2 == 0)
                .mapToInt(x->(int) x).sum();
                
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

10: Count words in a sentence:
String sentence = "java stream api java";

Map<String, Long> collect = Arrays.stream(sentence.split(" "))
        .collect(Collectors.groupingBy(c -> c, Collectors.counting()));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

11: Flatten a list of list:

List<List<Integer>> list = List.of(
        List.of(1,2),
        List.of(3,4)
);

Set<Integer> collect = list.stream().flatMap(x -> x.stream()).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Entities for Java Stream Questions:

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Project {

    private String projectCode;
    private String name;
    private String client;
    private String leadName;
}


@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Student {


    private Integer  id;
    private String name;
    private Integer  age;
    private String Department;
    private double salary;
    private String gender;
    private List<Project> projects;

    public Integer checkError(){
        try{
            int a = 10/0;
            return a;
        }catch (ArithmeticException ex){
            System.out.println(ex.getMessage());
        }finally {
            System.out.println("Resources are cleared");
        }
        return null;
    }
}

package com.example.java_practice;

import lombok.Data;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Data
public class StudentDatabase {

    public static List<Student> getAllStudents(){
        // Create 10 projects
        Project p1 = new Project("P1001", "E-Commerce Platform", "Amazon", "John Smith");
        Project p2 = new Project("P1002", "Mobile Banking App", "Bank of America", "Sarah Johnson");
        Project p3 = new Project("P1003", "Healthcare System", "MediCare Inc", "Robert Chen");
        Project p4 = new Project("P1004", "Inventory Management", "Walmart", "Maria Garcia");
        Project p5 = new Project("P1005", "Learning Portal", "Coursera", "David Wilson");
        Project p6 = new Project("P1006", "Social Media App", "Meta", "Emily Davis");
        Project p7 = new Project("P1007", "IoT Smart Home", "Google", "Michael Brown");
        Project p8 = new Project("P1008", "Blockchain Wallet", "Coinbase", "Lisa Wang");
        Project p9 = new Project("P1009", "AI Chatbot", "OpenAI", "James Miller");
        Project p10 = new Project("P1010", "Cybersecurity Suite", "Cisco", "Jennifer Lee");

        // Create 10 students
        List<Student> students = new ArrayList<>();

        // Assuming Student class has parameterized constructor
        // Student(id, name, age, department, salary, gender, projects)

        students.add(new Student(101, "Alice Johnson", 22, "Computer Science",
                65000, "Female", Arrays.asList(p1, p2)));

        students.add(new Student(102, "Bob Williams", 24, "Software Engineering",
                72000, "Male", Arrays.asList(p2, p3)));

        students.add(new Student(103, "Carol Davis", 23, "Information Technology",
                68000, "Female", Arrays.asList(p3, p4)));

        students.add(new Student(104, "David Miller", 25, "Computer Science",
                75000, "Male", Arrays.asList(p4, p5)));

        students.add(new Student(105, "Emma Wilson", 21, "Data Science",
                70000, "Female", Arrays.asList(p5, p6)));

        students.add(new Student(106, "Frank Brown", 26, "Cybersecurity",
                78000, "Male", Arrays.asList(p6, p7)));

        students.add(new Student(107, "Grace Taylor", 22, "Computer Engineering",
                67000, "Female", Arrays.asList(p7, p8)));

        students.add(new Student(108, "Henry Lee", 24, "Software Engineering",
                73000, "Male", Arrays.asList(p8, p9)));

        students.add(new Student(109, "Isabella Moore", 23, "AI & ML",
                69000, "Female", Arrays.asList(p9, p10)));

        students.add(new Student(110, "Jack Anderson", 25, "Computer Science",
                76000, "Male", Arrays.asList(p10, p1)));

        return students;
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------