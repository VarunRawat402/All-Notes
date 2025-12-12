----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
JAVA 8 STREAM API QUESTIONS
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Structure of the Entity:

Student class{
    private Integer  id;
    private String name;
    private String Department;
    private double salary;
    private String gender;
    private List<Project> projects;
}

public class Project {
    private String name;
}

//List Containing all the students
List<Student> students = EmployeeDatabase.getAllStudents();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Print Students:
students.stream().forEach(x->System.out.println(x));

Print Student name and salary:
students.stream().forEach(x->System.out.println(x.getName() + " : " + x.getSalary()));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Print student names who belongs to "Computer Science" department:
students.stream().filter(x->x.getDepartment().equals("Computer Science")).forEach(x->System.out.println(x.getName()));

Print student names who belongs to "Computer Science" department & salary > 65000:
students.stream().filter(x->x.getDepartment().equals("Computer Science") && x.getSalary()>65000).forEach(x->System.out.println(x.getName()));

Print student names who belongs to "Computer Science" department & salary > 65000 & salary < 76000:
students.stream().filter(x->x.getDepartment().equals("Computer Science") && x.getSalary()>65000 && x.getSalary()<76000).forEach(x->System.out.println(x.getName() + x.getSalary()));

Get Students who belong to department = "Computer Science" and collect in Map with id and name of students:
Map<Integer, String> m1 = students.stream().filter(x -> x.getDepartment().equals("Computer Science")).collect(Collectors.toMap(Student::getId, Student::getName));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Get all the department:
List<String> l1 = students.stream().map(x -> x.getDepartment()).collect(Collectors.toList());               //All the dept, contains duplicate
Set<String> l1 = students.stream().map(x -> x.getDepartment()).collect(Collectors.toSet());                 //Unique depts
List<String> l1 = students.stream().map(x -> x.getDepartment()).distinct().collect(Collectors.toList());    //distinct() to get unique elements

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

flatmap:
Used to when you want to fetch the nested class attribute
Used when relation is OneToMany
Fetch project name, student -> project -> name

Map:
//When fetch nested class attribute with map you get data wrapped in stream, to avoid that
List<Stream<String>> l1 = students.stream().map(x -> x.getProjects().stream().map(x -> x.getName())).collect(Collectors.toList());

FlatMap:
List<String> l1 = students.stream().flatMap(x -> x.getProjects().stream().map(y -> y.getName())).distinct().collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting:

List<Student> l1 = students.stream().sorted(Comparator.comparing(Student::getSalary)).collect(Collectors.toList());
List<Student> l1 = students.stream().sorted(Collections.reverseOrder(Comparator.comparing(Student::getSalary))).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Max and Min:

Optional<Student> max = students.stream().max(Comparator.comparing(Student::getSalary));
Optional<Student> min = students.stream().min(Comparator.comparing(Student::getSalary));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Count male and Female Students:
long male = students.stream().filter(x -> x.getGender().equals("Male")).count();
long female = students.stream().filter(x -> x.getGender().equals("Female")).count();

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GroupingBy:
Used to group students based on attribute:

Group Students based on Gender:
Map<String, List<Student>> collect = students.stream().collect(Collectors.groupingBy(Student::getGender));

Group Student Names based on Gender:
		Map<String, List<String>> l1 = students.stream()
				.collect(Collectors.groupingBy(Student::getGender
						, Collectors.mapping(Student::getName, Collectors.toList())));

Group Student based on gender and give count of each gender:
Map<String, Long> l1 = students.stream().collect(Collectors.groupingBy(Student::getGender, Collectors.counting()));

Group Students based on salary and give names of the students:
Map<Double, List<String>> l1 = students.stream().collect(Collectors.groupingBy(Student::getSalary, Collectors.mapping(Student::getName, Collectors.toList())));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FindFirst:
Used to find the first element from the elements

Find first student with "Development" department if not present throw an exception:
		Student student = students.stream().filter(x -> x.getDepartment().equals("Development")).findFirst().orElseThrow(() -> new IllegalArgumentException("No student with this department"));
		System.out.println(student);

FindAny:
Used to check if any student is present based on condition
Used in ParallelStream to find the student optimized way:

Student student = students.parallelStream().filter(x -> x.getDepartment().equals("Development")).findAny().orElseThrow(() -> new IllegalArgumentException("No student with this department"));

anyMatch()
allMatch()
noneMatch()

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Limit:
Used to limit the values 

Find Top 3 highest salary Students:
List<Student> collect = students.stream().sorted(Comparator.comparing(Student::getSalary).reversed()).limit(3).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Skip:
When u want to skip first some elements:

Get student and skip first 5:
List<String> collect = students.stream().map(x -> x.getName()).skip(5).collect(Collectors.toList());

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Take out average salary based on employee gender:
collect= students.stream().collect(Collectors.groupingBy(Student::getGender, Collectors.averagingDouble(Student::getSalary)));

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Java 8 Program to get Highest paid Employee in Each department using stream api:
Map<String, Optional<Student>> collect = students.stream().collect(Collectors.groupingBy(Student::getDepartment, Collectors.maxBy(Comparator.comparing(Student::getSalary))));
collect.forEach((dept,student)->{
    System.out.println(dept + " : " + student.get().getName() + " : " + student.get().getSalary());
});

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Write a program to print the first non-duplicate character using Stream API (input: swisss, output: w)
String input = "swisss";

input.chars()
     .mapToObj(c -> (char)c)
     .filter(c -> input.indexOf(c) == input.lastIndexOf(c))  // appear only once
     .findFirst()
     .ifPresent(System.out::println);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

