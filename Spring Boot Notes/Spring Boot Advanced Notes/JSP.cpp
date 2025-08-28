------------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to use JSP with Spring Boot:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Steps:

Dependency:
    <dependency>
    <groupId>org.apache.tomcat.embed</groupId>
    <artifactId>tomcat-embed-jasper</artifactId>
    </dependency>

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

JSP file:

Jsp file path:
    src/main/resources/META-INF/resources/WEB-INF/jsp

//If we use @ResponseBody then it convert the string to json and return it as it is
//So we dont use that so it can use the jsp file { sayHello is the name of the jsp }
Controller Code:
    @Controller
    public class SBController {
        
        @GetMapping("/jsp-hello")
        public String jspHello(){
            return "sayHello";
        }
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Use QueryParameters in JSP File:

//We will take the query parameter and will put it in the ModelMap
//Whatever we put in the modelmap we can use in jsp file
Code:
    @Controller
    public class SBController {

        @GetMapping("/jsp-hello")
        public String jspHello(@RequestParam String name, @RequestParam int age, ModelMap model){
            model.put("name",name);
            model.put("age",age);
            return "sayHello";
        }
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
