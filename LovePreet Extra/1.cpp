
Backend Development:

Code
Test
Deploy
CI/CD, Cloud
Scalable Systems
Design Patterns

Why java is Needed:

Platform Independence: Can run on any machine, windows, mac, linux.
Object-Oriented Programming: This makes code modular, reusable, and easier to maintain.
Automatic Memory Management: Java has a built-in garbage collector reducing the chances of memory leaks and other related issues.
Multithreading: Java allows developers to create applications that can perform multiple tasks simultaneously
Robust Standard Library: Java has a rich standard library making development faster and easier.

Why String[] args are Needed in the main method:

Entry Point: The main method is the entry point of any Java application. The Java Virtual Machine (JVM) looks for this method to start the execution of the program.
Command-Line Arguments: The String[] args parameter allows the program to accept command-line arguments. This enables users to pass information
This is like a “rule” so the JVM knows where to start execution.
If it allowed many different forms, the JVM wouldnt know which one to call first.

Proxy:
    It is a wrapper that wraps your actual object.
    It is used to interept the calls and apply extra logic before or after calling the actual method

Proxies in Spring:
AOP (Aspect-Oriented Programming) → e.g., logging, security, performance monitoring
Transactions → @Transactional
Caching → @Cacheable
Security → method-level authorization (@PreAuthorize)