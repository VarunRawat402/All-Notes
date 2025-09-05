--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Monolithic:

Advantages:
1: Entire application is built as a single unit
2: All components in the application are tightly coupled together 
3: Easy to debug since all the code is in one place
4: Easy to testing since all the components are in the one place

Disadvantages:
1: Scalability is challenging since entire application needs to be scaled rather than just 1 component
2: Changing and Adding new things becomes complicated since all the components are tightly coupled
3: As the application gets bigger its hard to understand the code since everything is at one place
4: Deployment is challenging since you have to deploy whole application even if you change 1 thing


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MicroServices:

Application which consist of independent services that communicate through each other over a network.
Each service is responsible for a specific set of functionalities, and they can be developed, deployed, and scaled independently.
Different serives can be built using different technology allowing teams to choose the best tech for particular service
Fault in one service will not majorly effect the other services 

Disadvantages:
In this services connect with each other through network which can impact the performance
Services are distrubted which can lead to network latency, security concerns

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Note:
Whenever we are returning some data in the GetMapping its best practice to return the data in the ResponseEntity<>
to adjust the status of the HTTP as per the needs

ModelMapper:
It is used to map the attributes of one class to another class like we did in our project
with to() function.

There are 2 classes : Student | StudentResponse

So We have all the details in the student class but we want to return the StudentResponse in the GetMapping

Student student = { Getting the object from the Repository }
StudentResponse studentResponse = modelMapper.map(student,StudentResponse.class)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Spring Cloud:

It is a framework that provides tools and libraries for building distributed systems and microservices-based architectures.
It adds features and components that are specifically designed to address common challenges in developing cloud-native applications

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 