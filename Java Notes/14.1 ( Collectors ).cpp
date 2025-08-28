-----------------------------------------------------------------------------------------------------------------------------------------
Collectors:
-----------------------------------------------------------------------------------------------------------------------------------------

The Collectors class provides various methods for collecting stream elements 
into different data structures like List, Set, Map, or performing operations like grouping, partitioning, and summing.

-----------------------------------------------------------------------------------------------------------------------------------------

Methods:

Collecting Stream Elements:

List<String> names = Arrays.asList("Alice", "Bob", "Charlie", "David");

//Collect into list
List<String> nameList = names.stream().collect(Collectors.toList());

//Collect into set which will have unique values
Set<String> nameSet = names.stream().collect(Collectors.toSet());

//Collect into map with name and name's length
Map<String, Integer> nameLengthMap = names.stream()
        .collect(Collectors.toMap(name -> name, name -> name.length()));

-----------------------------------------------------------------------------------------------------------------------------------------

Joining:

List<String> words = Arrays.asList("Java", "Streams", "Are", "Powerful");

//will join every word into one string divided by space
String result = words.stream().collect(Collectors.joining(" "));
System.out.println(result); // Output: Java Streams Are Powerful

-----------------------------------------------------------------------------------------------------------------------------------------

Grouping By:

List<Integer> numbers = Arrays.asList(10, 15, 20, 25, 30, 35);

-----------------------------------------------------------------------------------------------------------------------------------------

// Group numbers by certain condition
Map<String, List<Integer>> groupedNumbers = numbers.stream()
        .collect(Collectors.groupingBy(n -> (n > 10) ? "bigger than 10" : "smaller than 10"));
System.out.println(groupedNumbers);

-----------------------------------------------------------------------------------------------------------------------------------------

// Group numbers by even and odd
Map<String, List<Integer>> groupedNumbers = numbers.stream()
        .collect(Collectors.groupingBy(n->(n%2==0)?"even":"odd"));

-----------------------------------------------------------------------------------------------------------------------------------------

List<String> words = Arrays.asList("apple", "banana", "cherry", "blueberry", "apricot");
// Group words by first letter
Map<Character, List<String>> groupedWords = words.stream()
        .collect(Collectors.groupingBy(word -> word.charAt(0)));

-----------------------------------------------------------------------------------------------------------------------------------------        

List<String> words = Arrays.asList("apple", "banana", "apple", "cherry", "banana", "apple", "cherry", "cherry");

// Count occurrences of each word
Map<String, Long> wordCount = words.stream()
        .collect(Collectors.groupingBy(word -> word, Collectors.counting()));

-----------------------------------------------------------------------------------------------------------------------------------------