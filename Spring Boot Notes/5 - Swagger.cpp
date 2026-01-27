------------------------------------------------------------------------------------------------------------------------------------------------
Swagger:
------------------------------------------------------------------------------------------------------------------------------------------------

→ Swagger is a tool for documenting, visualizing, and testing REST APIs.
→ OpenAPI is used to document the API

Swagger UI is used to visualize it:
    → See all endpoints
    → View request/response models
    → Execute APIs directly from browser
    → ( URL : localhost:8080/swagger-ui/index.html )

------------------------------------------------------------------------------------------------------------------------------------------------
Open API Annotations:
------------------------------------------------------------------------------------------------------------------------------------------------

1: @OpenAPIDefinition : Used to define global API metadata.

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

@Tag        → Document Controller Class
@Operation  → Document API Methods

@Tag(name = "User", description = "User-related operations")
@RestController
public class UserController {

    @Operation(summary = "Get all users", description = "Returns list of users")
    @GetMapping("/users")
    public List<User> getAllUsers() {
        return List.of();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

3: @Parameter:
    → Document method parameters

@Operation(summary = "Get user by ID")
@GetMapping("/{id}")
public User getUserById( @Parameter(description = "User ID", required = true) @PathVariable Long id) {
    return new User();
}

------------------------------------------------------------------------------------------------------------------------------------------------

4: @ApiResponses and @ApiResponse:
    → Document possible responses from an API method

@Operation(summary = "Delete user")
@ApiResponses({
    @ApiResponse(responseCode = "200", description = "Deleted successfully"),
    @ApiResponse(responseCode = "404", description = "User not found"),
    @ApiResponse(responseCode = "500", description = "Server error")
})
@DeleteMapping("/{id}")
public ResponseEntity<Void> deleteUser(@PathVariable Long id) {
}

------------------------------------------------------------------------------------------------------------------------------------------------

5: @Schema:
    → Document entities and attributes

@Schema(description = "User entity")
public class User {

    @Schema(description = "User ID", example = "1")
    private Long id;

    @Schema(description = "User name", example = "Alice")
    private String name;

    @Schema(description = "User email", example = "alice@example.com")
    private String email;
}

------------------------------------------------------------------------------------------------------------------------------------------------

6:  @SecurityScheme & @SecurityRequirement 

@SecurityScheme:
    → Used to define the security Type and name

@SecurityRequirement:
    → Used to tell this method or class needs this type of auth/security

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

SWAGGER CODE:

@RestController
@RequiredArgsConstructor
@RequestMapping("/students")                                                    
@Tag(name = "Student", description = "Operations related to students")          // Controller Name
public class StudentController {

    private final StudentService studentService;

    @PostMapping("")
    @Operation(summary = "Create new Student", description = "Saves student in DB")                                 // API Description
    @ApiResponses({                                                                                                 //Possible responses from API
        @ApiResponse(responseCode = "201", description = "Student created successfully"),
        @ApiResponse(responseCode = "400", description = "Invalid student data"),
        @ApiResponse(responseCode = "500", description = "Internal server error")
    })                                                                                                              //Schema to provide for the API
    public ResponseEntity<String> saveStudent(@io.swagger.v3.oas.annotations.parameters.RequestBody(description = "Student Object that needs to be created",
            content = @Content(schema = @Schema(implementation = Student.class)),required = true) @RequestBody Student student){        
        Student saved = studentService.saveStudent(student);
        return ResponseEntity.status(200).body("Student has been created");
    }

    // GET STUDENT BY ID
    @GetMapping("/id/{id}")
    @Operation(summary = "Get Student By Id", description = "Fetch student using student ID")
    @ApiResponses({
        @ApiResponse(responseCode = "200", description = "Student found"),
        @ApiResponse(responseCode = "404", description = "Student not found"),
        @ApiResponse(responseCode = "400", description = "Invalid ID format"),
        @ApiResponse(responseCode = "500", description = "Internal server error")
    })
    public ResponseEntity<Student> getStudentById( @Parameter(description = "ID of the student", required = true) @PathVariable int id){
        Student student  = studentService.getStudentById(id);
        if(student ==null){
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(student );
    }

    // GET ALL STUDENTS
    @GetMapping("")
    @Operation(summary = "Get all Students",description = "Retrieve all students from the database"
    )
    @ApiResponses({
        @ApiResponse(responseCode = "200", description = "Students retrieved successfully"),
        @ApiResponse(responseCode = "204", description = "No students found"),
        @ApiResponse(responseCode = "500", description = "Internal server error")
    })
    public ResponseEntity<List<Student>> getAllStudent(){
        List<Student> students = studentService.getAllStudent();
        if(students.isEmpty()){
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.ok(students);
    }

    // GET STUDENTS BY COURSE
    @GetMapping("/course/{course}")
    @Operation(summary = "Get Students by Course",description = "Fetch students enrolled in a specific course"
    )
    @ApiResponses({
        @ApiResponse(responseCode = "200", description = "Students found"),
        @ApiResponse(responseCode = "204", description = "No students found for given course"),
        @ApiResponse(responseCode = "500", description = "Internal server error")
    })
    public ResponseEntity<List<Student>> getStudentByCourse( @Parameter(name = "course", description = "Course of the student", required = true) @PathVariable Course course){
        List<Student> students = studentService.getStudentByCourse(course);
        if(students.isEmpty()){
            return ResponseEntity.noContent().build();
        }
        return ResponseEntity.ok(students);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Advanteages of OpenAPI over swagger:

They are more standardized and widely adopted.
They support a broader range of tools and integrations.
OpenAPI is the evolution of Swagger, providing a more comprehensive and flexible specification for defining APIs.

------------------------------------------------------------------------------------------------------------------------------------------------

OPEN API ANNOTATIONS:

1: @Tag                 → Document Controller Class
2: @Operation           → Document API Methods
3: @ApiResponses        → Document possible responses from an API method
4: @APIResponse         → Document single response
5: @Parameter           → Document method parameters
6: @Schema              → Document entities and attributes
7: @Hidden              → Hide API from documentation
8: @RequestBody         → Document request body
9: @OpenAPIDefinition   → Document Microservice level metadata like title, version, description, contact info, server details, tags etc.

------------------------------------------------------------------------------------------------------------------------------------------------