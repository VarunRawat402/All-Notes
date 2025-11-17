-----------------------------------------------------------------------------------------------------------------------------------------
Collectors:
-----------------------------------------------------------------------------------------------------------------------------------------

The Collectors class provides built-in methods to collect Stream results into different data structures like List, Set, Map
and to perform operations such as grouping, partitioning, joining, and counting.

-----------------------------------------------------------------------------------------------------------------------------------------

Basic Collecting Methods:

Collecting Stream Elements:

List<String> names = Arrays.asList("Alice", "Bob", "Charlie", "David");

// Collect into List
List<String> nameList = names.stream()
        .collect(Collectors.toList());

// Collect into Set (unique values)
Set<String> nameSet = names.stream()
        .collect(Collectors.toSet());

// Collect into Map (key = name, value = length)
Map<String, Integer> nameLengthMap = names.stream()
        .collect(Collectors.toMap(name -> name, name -> name.length()));

-----------------------------------------------------------------------------------------------------------------------------------------

Joining Elements:

List<String> words = Arrays.asList("Java", "Streams", "Are", "Powerful");

// Join all words separated by space
String result = words.stream()
        .collect(Collectors.joining(" "));
System.out.println(result);                     // Java Streams Are Powerful

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