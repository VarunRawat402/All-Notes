-----------------------------------------------------------------------------------------------------------------------------------------------------
Coding Questions:
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. Reverse a String:
String s = "java";

//With using StringBuilder
StringBuilder sb = new StringBuilder(s).reverse();

//Without using StringBuilder
String reversed = "";
for (int i = s.length() - 1; i >= 0; i--) {
    reversed += s.charAt(i);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

5. Find Largest Element:
int[] arr = {1, 2, 3, 2, 4, 1};

    int maxi = arr[0];
    for(int i=0;i<arr.length;i++){
        maxi = Math.max(maxi,arr[i]);
    }
    System.out.println(maxi);

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------