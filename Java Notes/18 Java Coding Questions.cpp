----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Coding Questions:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Reverse a String:
String s = "java";

//With using StringBuilder
StringBuilder sb = new StringBuilder(s).reverse();

//Without using StringBuilder
String reversed = "";

for (int i = s.length() - 1; i >= 0; i--) {
    reversed += s.charAt(i);
}

System.out.println(reversed);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Check Palindrome ( same from both sides ):
String s = "madam";

static boolean checkPalindrome(String s){
    int length = s.length();
    for(int i=0;i<length/2;i++){
        if(s.charAt(i)!=s.charAt(length-i-1)){
            return false;
        }
    }
    return true;
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. First Non-Repeating Character:
String s = "swiss";

Map<Character,Integer> m1 = new LinkedHashMap<>();
for(int i=0;i<s.length();i++){
    char c = s.charAt(i);
    m1.put(c,m1.getOrDefault(c,0)+1);
}
for(Map.Entry<Character,Integer> entry : m1.entrySet()){
    if(entry.getValue()==1){
        System.out.println(entry.getKey());
        break;
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4. Check Anagrams:
String s1 = "listen";
String s2 = "silent";

static boolean checkAnagrams(String s1, String s2){
    if(s1.length()!=s2.length()) return false;

    Map<Character,Integer> m1= new HashMap<>();
    for(int i=0;i<s1.length();i++){
        m1.put(s1.charAt(i),m1.getOrDefault(s1.charAt(i),0)+1);
        m1.put(s2.charAt(i),m1.getOrDefault(s2.charAt(i),0)-1);
    }
    for (int val : m1.values()) {
        if (val != 0) return false;
    }
    return true;
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5. Find Largest Element:
		int[] arr = {1, 2, 3, 2, 4, 1};
		int maxi = arr[0];
		for(int i=0;i<arr.length;i++){
			maxi = Math.max(maxi,arr[i]);
		}
		System.out.println(maxi);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

6. Find Duplicate Elements
int[] arr = {1, 2, 3, 2, 4, 1};

Map<Integer,Integer> m1 = new HashMap<>();
for(int i=0;i<arr.length;i++){
    m1.put(arr[i],m1.getOrDefault(arr[i],0)+1);
    if(m1.get(arr[i])>1){
        System.out.println(arr[i]);
    }
}

List<Integer> collect = Arrays.stream(arr).boxed()
        .collect(Collectors.groupingBy(c -> c, Collectors.counting()))
        .entrySet().stream()
        .filter(x -> x.getValue() > 1)
        .map(x -> x.getKey()).collect(Collectors.toList());
System.out.println(collect);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

7: Find Second Largest Element:
int[] arr = {5, 3, 9, 1, 9};

int maxi = -1;
int secondMaxi = -1;
for(int i=0;i<arr.length;i++){
    if(arr[i]>maxi){
        secondMaxi = maxi;
        maxi = Math.max(maxi,arr[i]);
    }
    else if(arr[i]<maxi){
        secondMaxi = Math.max(arr[i],secondMaxi);
    }
}
System.out.println(secondMaxi);

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
