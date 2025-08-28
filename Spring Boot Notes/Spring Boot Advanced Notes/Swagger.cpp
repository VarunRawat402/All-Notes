------------------------------------------------------------------------------------------------------------------------------------------------
Swagger:
------------------------------------------------------------------------------------------------------------------------------------------------

Swagger is a tool/framework for documenting RESTful APIs.
Used Swagger to create clear, interactive documentation for the APIs you developed.
This documentation allows other developers to easily understand how to use the API

------------------------------------------------------------------------------------------------------------------------------------------------
Open API Annotations:
------------------------------------------------------------------------------------------------------------------------------------------------

1: @OpenAPIDefinition : Used at application level

@OpenAPIDefinition(
    info = @Info(
        title = "User Management API",
        version = "1.0",
        description = "API for managing users",
        contact = @Contact(name = "Support", email = "support@example.com")
    ),
    servers = @Server(url = "http://localhost:8080"),
    tags = {
        @Tag(name = "User", description = "User-related operations")
    }
)
@SpringBootApplication
public class MyApp { }

------------------------------------------------------------------------------------------------------------------------------------------------

2: @Tag & @Operation

@Tag = Used to describle the controller classes
@Operation = Used to describe the APIs / controller methods

@Tag(name = "User", description = "Operations related to users")
public class UserController {

    @Operation(summary = "Get all users", description = "Returns a list of users")
    public List<User> getAllUsers() {
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

3: @Parameter : Used to describle the parameter of the API Endpoint

@Operation(summary = "Get user by ID")
@GetMapping("/{id}")
public User getUserById( @Parameter(description = "ID of the user to retrieve", required = true) @PathVariable Long id ){
}

------------------------------------------------------------------------------------------------------------------------------------------------

4: @ApiResponses and @ApiResponse : Used to define possible response for the API

@Operation(summary = "Delete a user")
@ApiResponses(value = {
    @ApiResponse(responseCode = "200", description = "User deleted successfully"),
    @ApiResponse(responseCode = "404", description = "User not found"),
    @ApiResponse(responseCode = "500", description = "Internal server error")
})
public ResponseEntity<Void> deleteUser() {
}

------------------------------------------------------------------------------------------------------------------------------------------------

5: @Schema : Used to describle the Entity/Model or feilds

@Schema(description = "User entity")
public class User {

    @Schema(description = "Unique identifier of the user", example = "1")
    private Long id;

    @Schema(description = "Name of the user", example = "Alice")
    private String name;

    @Schema(description = "Email address", example = "alice@example.com")
    private String email;
}

------------------------------------------------------------------------------------------------------------------------------------------------

6:  @SecurityScheme & @SecurityRequirement 

@SecurityScheme : Used to define the security Type and name
@SecurityRequirement : Used to tell this method or class needs this type of auth/security

//This class defines the bearer auth and have schema of the auth
@SecurityScheme(
    name = "bearerAuth",
    type = SecuritySchemeType.HTTP,
    scheme = "bearer",
    bearerFormat = "JWT"
)
public class SecurityConfig { }

//This function requires the auth of the schema name 'bearerAuth'
@Operation(security = @SecurityRequirement(name = "bearerAuth"))
@GetMapping("/secure-data")
public String getSecureData() { ... }

------------------------------------------------------------------------------------------------------------------------------------------------

Code for Swagger:

Student Controller:

@RestController
@RequiredArgsConstructor
@RequestMapping("/students")                                                    // Common URL
@Tag(name = "Student", description = "Operations related to students")          // Controller Name
public class StudentController {

    private final StudentService studentService;

    @PostMapping("")
    @Operation(summary = "Create a new Student", description = "Saves a new student in the Database")               // API Description
    @ApiResponses(value = {                                                                                         // Possible Responses from the API
            @ApiResponse(responseCode = "201",description = "Student created successfully"),        
            @ApiResponse(responseCode = "500", description = "Internal Server Error"),
            @ApiResponse(responseCode = "400", description = "Invalid Student data provided")
    })                                                                                                              //Schema to provide for the API
    public ResponseEntity<String> saveStudent(@io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Student Object that needs to be created",
            content = @Content(schema = @Schema(implementation = Student.class)),required = true) @RequestBody Student student){        
        Student saved = studentService.saveStudent(student);
        return ResponseEntity.status(200).body("Student has been created");
    }

    @GetMapping("/id/{id}")
    @Operation(summary = "Get Student By Id", description = "Takes the student Id and returns the student")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200",description = "Student Found"),
            @ApiResponse(responseCode = "500",description = "Internal Server Error"),
            @ApiResponse(responseCode = "404",description = "Student with given Id does not exist"),
            @ApiResponse(responseCode = "400",description = "Invalid Format")
    })
    public ResponseEntity<Student> getStudentById( @Parameter(name = "id", description = "Id of the student", required = true) @PathVariable int id){
        Student s = studentService.getStudentById(id);
        if(s==null){
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(s);
    }

    @GetMapping("")
    @Operation(summary = "Get all Students", description = "Returns all the students present in the Database")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200",description = "Successfully Retrieved all students"),
            @ApiResponse(responseCode = "500",description = "Internal Server Error"),
            @ApiResponse(responseCode = "204",description = "No student found, Empty Database"),
    })
    public ResponseEntity<List<Student>> getAllStudent(){
        List<Student> students = studentService.getAllStudent();
        if(students.isEmpty()){
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.ok(students);
    }

    @GetMapping("/course/{course}")
    @Operation(summary = "Return student by course", description = "Takes the course and returns the student which have the same course")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Returns the students with given course"),
            @ApiResponse(responseCode = "500", description = "Internal Server error"),
            @ApiResponse(responseCode = "404", description = "No student with given course is found")
    })
    public ResponseEntity<List<Student>> getStudentByCourse( @Parameter(name = "course", description = "Course of the student", required = true) @PathVariable Course course){
        List<Student> students = studentService.getStudentByCourse(course);
        if(students.isEmpty()){
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.ok(students);
    }
}
