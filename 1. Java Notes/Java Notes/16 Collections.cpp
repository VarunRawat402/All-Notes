-----------------------------------------------------------------------------------------------------------------------------------------------------
Collect / Collectors / Collection / Collections:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Collection:
→ Root Interface of collection framework
→ Parent of List / Set / Queue
→ add() / remove() / size() / contains()

-----------------------------------------------------------------------------------------------------------------------------------------------------

Collections:
→ Utility Class
→ Contains static helper methods for collections

Methods():
→ Collections.sort(list)
→ Collections.min(list)
→ Collections.max(list)
→ Collections.reverse(list)
→ Collections.unmodifiableList(list)
→ Collections.synchronizedMap(map)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Collectors:
→ Utility class for stream operations
→ Convert streams into collections

Methods:
→ Collectors.toList()
→ Collectors.toSet()
→ Collectors.groupingBy(Employee::getDept)
→ Collectors.counting()
→ Collectors.summingInt()
→ Collectors.averagingDouble()
→ Collectors.mapping(Employee::getName, Collectors.toList())
→ Collectors.reducing(Integer::sum)
→ Collectors.joining(", ")

-----------------------------------------------------------------------------------------------------------------------------------------------------

Collect:
→ Stream terminal operation
→ Used to transform stream into collections using Collectors

Methods:
→ list.stream().collect(Collectors.toList());
→ list.stream().collect(Collectors.toSet());

-----------------------------------------------------------------------------------------------------------------------------------------------------

Basic Collecting Methods:

//Collect into List
List<String> nameList = names.stream().collect(Collectors.toList());

//Collect into Map (key = name, value = length)
Map<String, Integer> nameLengthMap = names.stream().collect(Collectors.toMap(name -> name, name -> name.length()));

-----------------------------------------------------------------------------------------------------------------------------------------------------

Joining Elements:
List<String> words = Arrays.asList("Java", "Streams", "Are", "Powerful");

// Join all words separated by space
String result = words.stream().collect(Collectors.joining(" "));        // Java Streams Are Powerful

-----------------------------------------------------------------------------------------------------------------------------------------------------

Grouping By:
List<Integer> numbers = Arrays.asList(10, 15, 20, 25, 30, 35);

-----------------------------------------------------------------------------------------------------------------------------------------------------

// Group numbers by certain condition
Map<String, List<Integer>> groupedNumbers = numbers.stream().collect(Collectors.groupingBy(n -> (n > 10) ? "bigger than 10" : "smaller than 10"));

-----------------------------------------------------------------------------------------------------------------------------------------------------

// Group numbers by even and odd
Map<String, List<Integer>> groupedNumbers = numbers.stream().collect(Collectors.groupingBy(n->(n%2==0)?"even":"odd"));

-----------------------------------------------------------------------------------------------------------------------------------------------------

List<String> words = Arrays.asList("apple", "banana", "cherry", "blueberry", "apricot");

// Group words by first letter
Map<Character, List<String>> groupedWords = words.stream().collect(Collectors.groupingBy(word -> word.charAt(0)));

-----------------------------------------------------------------------------------------------------------------------------------------------------        

List<String> words = Arrays.asList("apple", "banana", "apple", "cherry", "banana", "apple", "cherry", "cherry");

// Count occurrences of each word
Map<String, Long> wordCount = words.stream().collect(Collectors.groupingBy(word -> word, Collectors.counting()));

-----------------------------------------------------------------------------------------------------------------------------------------------------