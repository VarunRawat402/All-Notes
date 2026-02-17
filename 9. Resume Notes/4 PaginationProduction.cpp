--------------------------------------------------------------------------------------------------------------------------------------------
ACTUAL PRODUCTION CODE BASED ON YOURS:
--------------------------------------------------------------------------------------------------------------------------------------------

1. Controller:

public class StudentController {
    
    private final StudentService studentService;
    
    @GetMapping
    public ResponseEntity<Map<String, Object>> getStudents(
            @RequestParam(defaultValue = "1") @Min(1) int page,
            @RequestParam(defaultValue = "10") @Min(1) @Max(100) int size,
            @RequestParam(defaultValue = "id") String sortBy,
            @RequestParam(defaultValue = "asc") String direction,
            @RequestParam(required = false) String email,
            @RequestParam(required = false) String name) {
        
        Sort sort = buildSort(sortBy, direction);                                                                 
        Pageable pageable = PageRequest.of(page - 1, size, sort);
        
        //Call Service class
        Page<StudentDTO> result = studentService.searchStudents(pageable, name, email);
        
        //Build Response from returned page
        Map<String, Object> response = buildPageResponse(result, page, size);
        
        return ResponseEntity.ok(response);
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
        
        try {
            Specification<Student> spec = buildSpecification(name, email);                          //Create Specification Object
            Page<Student> page = studentRepository.findAll(spec, pageable);                         //Pass Specification and Pageable Object to Repository method
            return page.map(studentMapper::toDTO);                                                  //Map Customers to CustomerDTO

        } catch (Exception e) {
            log.error("Error searching students with filters", e);
            throw new ServiceException("Failed to search students", e);
        }
    }
    
    //Create single specification using multiple specification function for each feild
    //Chain all specification into one and returns it
    private Specification<Student> buildSpecification(String name, String email) {      
        return Specification.where(hasName(name)).and(hasEmail(email));                                                
    }                                                                                   
    
    //Create specification for Name
    private Specification<Student> hasName(String name) {                               
        return (root, query, cb) -> {                                       
            return cb.like(cb.lower(root.get("name")), "%" + name.toLowerCase() + "%"); 
        };
    }
    
    //Create specification for Email
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
public interface StudentRepository extends JpaRepository<Student, Long>, JpaSpecificationExecutor<Student> {
    Page<Student> findAll(Specification<Student> spec, Pageable pageable);
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

Optimization:

1. enforce maxPageSize (e.g., 100) in production:
    → It caps the result to return only 100 pages of content

2. Avoid LIKE '%...%' when possible:
→ What it is  : Using % at the start of a LIKE search prevents the database from using indexes.
→ What it does: Queries become full table scans, which are slow for millions of rows.

3: Fetch only ResponseDTO feilds using projection:
@Query("SELECT new com.example.StudentDTO(s.id, s.name, s.age) FROM Student s WHERE ...")
Page<StudentDTO> findStudents(..., Pageable pageable);

5: Avoid cb.lower() in queries if possible or use database-specific case-insensitive collations.

--------------------------------------------------------------------------------------------------------------------------------------------