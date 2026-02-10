--------------------------------------------------------------------------------------------------------------------------------------------
ACTUAL PRODUCTION CODE BASED ON YOURS:
--------------------------------------------------------------------------------------------------------------------------------------------

1. Controller (Clean & Focused)

@RestController
@RequestMapping("/api/students")
@Validated
public class StudentController {
    
    private final StudentService studentService;
    
    // Cache allowed fields for sort validation
    private static final Set<String> ALLOWED_SORT_FIELDS = 
        Set.of("id", "name", "email", "createdAt", "updatedAt");
    
    @GetMapping
    public ResponseEntity<Map<String, Object>> getStudents(
            @RequestParam(defaultValue = "1") @Min(1) int page,
            @RequestParam(defaultValue = "10") @Min(1) @Max(100) int size,
            @RequestParam(defaultValue = "id") String sortBy,
            @RequestParam(defaultValue = "asc") String direction,
            @RequestParam(required = false) String email,
            @RequestParam(required = false) String name) {
        
        //Validate Sort Feild and direction
        validateSortField(sortBy);
        validateSortDirection(direction);
        
        //Create Sort and Pageable Object
        Sort sort = buildSort(sortBy, direction);
        Pageable pageable = PageRequest.of(page - 1, size, sort);
        
        //Call Customer Service
        Page<StudentDTO> result = studentService.searchStudents(pageable, name, email);
        
        //Build response with all the page data and metadata
        Map<String, Object> response = buildPageResponse(result, page, size);
        
        return ResponseEntity.ok(response);
    }
    
    private void validateSortField(String sortBy) {
        if (!ALLOWED_SORT_FIELDS.contains(sortBy.toLowerCase())) {
            throw new IllegalArgumentException("Invalid Sorting feild");
        }
    }
    
    private void validateSortDirection(String direction) {
        if (!direction.equalsIgnoreCase("asc") && !direction.equalsIgnoreCase("desc")) {
            throw new IllegalArgumentException("Invalid Sort Direction");
        }
    }
    
    private Sort buildSort(String sortBy, String direction) {
        return direction.equalsIgnoreCase("desc") 
            ? Sort.by(sortBy).descending() 
            : Sort.by(sortBy).ascending();
    }
    
    private Map<String, Object> buildPageResponse(Page<StudentDTO> page, int requestedPage, int size){

        Map<String, Object> response = new LinkedHashMap<>();
        response.put("data", page.getContent());
        response.put("currentPage", requestedPage);
        response.put("pageSize", size);
        response.put("totalElements", page.getTotalElements());
        response.put("totalPages", page.getTotalPages());
        response.put("hasNext", page.hasNext());
        response.put("hasPrevious", page.hasPrevious());
        return response;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

2. Service Layer (Production Ready)

@Service
@Slf4j
@Transactional(readOnly = true)
public class StudentService {
    
    private final StudentRepository studentRepository;
    private final StudentMapper studentMapper;
    
    public Page<StudentDTO> searchStudents(Pageable pageable, String name, String email) {
        
        log.debug("Searching Customers with filters - name: {}, email: {}", name, email);
        
        try {
            Specification<Student> spec = buildSpecification(name, email);                          //Create Specification Object
            Page<Student> page = studentRepository.findAll(spec, pageable);                         //Pass Specification and Pageable Object to Repository method
            
            log.info("Found {} students matching criteria", page.getTotalElements());
            return page.map(studentMapper::toDTO);                                                  //Map Customers to CustomerDTO

        } catch (Exception e) {
            log.error("Error searching students with filters", e);
            throw new ServiceException("Failed to search students", e);
        }
    }
    
    private Specification<Student> buildSpecification(String name, String email) {      //We create each feild predicate with seperate function and chain them using .and()            
        return Specification.where(hasName(name))                                       //With this we dont need to check for empty predicate, it will handle empty automatically                                                     
                .and(hasEmail(email));                                                  //With this, if we want to add another predicate we can just create seperate method and pass here
    }                                                                                   
    
    private Specification<Student> hasName(String name) {                               //Creates specification object using predicate
        return (root, query, cb) -> {                                       
            return cb.like(cb.lower(root.get("name")), "%" + name.toLowerCase() + "%"); 
        };
    }
    
    private Specification<Student> hasEmail(String email) {
        return (root, query, cb) -> {
            if (StringUtils.isBlank(email)) return null;
            return cb.like(cb.lower(root.get("email")), email.toLowerCase() + "%");
        };
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

3. Repository (Enhanced)

@Repository
public interface StudentRepository extends JpaRepository<Student, Long>, 
                                          JpaSpecificationExecutor<Student> {
    
    // Optional: Add query hints for performance
    @QueryHints({
        @QueryHint(name = "org.hibernate.readOnly", value = "true"),
        @QueryHint(name = "javax.persistence.query.timeout", value = "3000")
    })
    @Override
    Page<Student> findAll(Specification<Student> spec, Pageable pageable);
    
    // Optional: Add database-level filtering for performance
    @QueryHints(@QueryHint(name = "org.hibernate.cacheable", value = "true"))
    List<String> findDistinctPositions();
}

--------------------------------------------------------------------------------------------------------------------------------------------

4. DTO (For Response - Optional but Recommended)

@Data
@NoArgsConstructor
@AllArgsConstructor
public class StudentDTO {
    private Long id;
    private String name;
    private Integer age;
    private String email;
    private String position;
    private LocalDateTime createdAt;
    private LocalDateTime updatedAt;
}

--------------------------------------------------------------------------------------------------------------------------------------------

5. Configuration (application.yml)

# Production Pagination Settings
app:
  pagination:
    max-page-size: 100
    default-page-size: 20

# Database pool settings for production
spring:
  datasource:
    hikari:
      maximum-pool-size: 10
      minimum-idle: 5
      connection-timeout: 30000
      idle-timeout: 600000
      max-lifetime: 1800000

--------------------------------------------------------------------------------------------------------------------------------------------


6. Global Exception Handler (Critical for Production)

@RestControllerAdvice
public class GlobalExceptionHandler {
    
    @ExceptionHandler(IllegalArgumentException.class)
    public ResponseEntity<Map<String, Object>> handleIllegalArgument(IllegalArgumentException ex) {
        Map<String, Object> error = new HashMap<>();
        error.put("timestamp", LocalDateTime.now());
        error.put("status", HttpStatus.BAD_REQUEST.value());
        error.put("error", "Bad Request");
        error.put("message", ex.getMessage());
        error.put("path", ((ServletRequestAttributes) RequestContextHolder
                .currentRequestAttributes()).getRequest().getRequestURI());
        
        return ResponseEntity.badRequest().body(error);
    }
    
    @ExceptionHandler(DataAccessException.class)
    public ResponseEntity<Map<String, Object>> handleDataAccessException(DataAccessException ex) {
        log.error("Database error occurred", ex);
        
        Map<String, Object> error = new HashMap<>();
        error.put("timestamp", LocalDateTime.now());
        error.put("status", HttpStatus.INTERNAL_SERVER_ERROR.value());
        error.put("error", "Database Error");
        error.put("message", "A database error occurred. Please try again.");
        
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(error);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Optimization:

1. enforce maxPageSize (e.g., 100) in production:
    → It caps the result to return only 100 pages of content

2. Index the columns used in filtering and sorting
    → When u create index, it sorts the data and make lookup easy for searching 
    → Dont work with %john%
    → Works with only john%

3. Avoid LIKE '%...%' when possible:
→ What it is  : Using % at the start of a LIKE search prevents the database from using indexes.
→ What it does: Queries become full table scans, which are slow for millions of rows.

4: Fetch only ResponseDTO feilds using projection:
@Query("SELECT new com.example.StudentDTO(s.id, s.name, s.age) FROM Student s WHERE ...")
Page<StudentDTO> findStudents(..., Pageable pageable);

5: Avoid cb.lower() in queries if possible or use database-specific case-insensitive collations.

--------------------------------------------------------------------------------------------------------------------------------------------