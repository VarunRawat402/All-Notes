------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination — Production Code
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. CONTROLLER

@RestController
@RequiredArgsConstructor
public class StudentController {

    private final StudentService studentService;

    @GetMapping
    public ResponseEntity<Map<String, Object>> getStudents(
            @RequestParam(defaultValue = "1")   @Min(1)             int page,
            @RequestParam(defaultValue = "10")  @Min(1) @Max(100)   int size,
            @RequestParam(defaultValue = "id")                      String sortBy,
            @RequestParam(defaultValue = "asc")                     String direction,
            @RequestParam(required = false)                         String name,
            @RequestParam(required = false)                         String email) {

        Sort sort             = Sort.by(Sort.Direction.fromString(direction), sortBy);
        Pageable pageable     = PageRequest.of(page - 1, size, sort);

        Page<StudentDTO> result = studentService.searchStudents(pageable, name, email);

        Map<String, Object> response = buildPageResponse(result, page, size);

        return ResponseEntity.ok(response);
    }

    private Map<String, Object> buildPageResponse(Page<StudentDTO> page, int requestedPage, int size) {
        Map<String, Object> response = new LinkedHashMap<>();
        response.put("data",          page.getContent());
        response.put("currentPage",   requestedPage);
        response.put("pageSize",      size);
        response.put("totalElements", page.getTotalElements());
        response.put("totalPages",    page.getTotalPages());
        response.put("hasNext",       page.hasNext());
        response.put("hasPrevious",   page.hasPrevious());
        return response;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
2. SERVICE
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Service
@Slf4j
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class StudentService {

    private final StudentRepository studentRepository;
    private final StudentMapper studentMapper;

    public Page<StudentDTO> searchStudents(Pageable pageable, String name, String email) {
        try {
            Specification<Student> spec = buildSpecification(name, email);
            Page<Student> page          = studentRepository.findAll(spec, pageable);
            return page.map(studentMapper::toDTO);                                          // Entity → DTO

        } catch (Exception e) {
            log.error("Error searching students with filters", e);
            throw new ServiceException("Failed to search students", e);
        }
    }

    // Chains individual Specifications into one combined Specification
    private Specification<Student> buildSpecification(String name, String email) {
        return Specification
                .where(hasName(name))
                .and(hasEmail(email));
    }

    // LIKE %name% — contains match (case-insensitive)
    private Specification<Student> hasName(String name) {
        return (root, query, cb) -> {
            if (StringUtils.isBlank(name)) return null;
            return cb.like(cb.lower(root.get("name")), "%" + name.toLowerCase() + "%");
        };
    }

    // LIKE email% — starts-with match (case-insensitive)
    private Specification<Student> hasEmail(String email) {
        return (root, query, cb) -> {
            if (StringUtils.isBlank(email)) return null;
            return cb.like(cb.lower(root.get("email")), email.toLowerCase() + "%");
        };
    }
}

Note: Returning null from a Specification method means "no filter for this field" — Spring Data JPA ignores null predicates automatically.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
3. REPOSITORY
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@Repository
public interface StudentRepository extends JpaRepository<Student, Long>,JpaSpecificationExecutor<Student> {
}

Note: JpaSpecificationExecutor provides findAll(Specification, Pageable) out of the box — no need to declare it manually.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
4. CONFIGURATION (application.yml)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Pagination limits
app:
  pagination:
    max-page-size: 100
    default-page-size: 20

# HikariCP connection pool (production settings)
spring:
  datasource:
    hikari:
      maximum-pool-size: 10       # max concurrent DB connections
      minimum-idle: 5             # min idle connections kept alive
      connection-timeout: 30000   # ms to wait for a connection before throwing
      idle-timeout: 600000        # ms before idle connection is removed (10 min)
      max-lifetime: 1800000       # ms max connection lifetime (30 min)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PRODUCTION OPTIMIZATIONS
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Enforce maxPageSize:
    → Cap page size at 100 so clients cant request millions of rows in one call.
    → Done via @Max(100) on the size param in the controller.

2. Avoid LIKE '%value%' (leading wildcard) when possible:
    → A leading % prevents the DB from using indexes.
    → Results in a full table scan — very slow on large datasets.
    → Prefer starts-with LIKE 'value%' (no leading %) where the use case allows.
    → For name/full-text search on millions of rows, consider a dedicated search engine (Elasticsearch) instead.

3. Use Projections / DTO queries to fetch only needed fields:
    → Avoid loading full Entity objects when only a few fields are needed.
    → Use a JPQL constructor expression:

@Query("SELECT new com.example.StudentDTO(s.id, s.name, s.age) FROM Student s WHERE ...")
Page<StudentDTO> findStudents(Pageable pageable);

4. Avoid cb.lower() if possible:
    → cb.lower() applies a function to every row, which prevents index usage.
    → Prefer database-level case-insensitive collations (e.g., utf8_general_ci in MySQL) so the DB handles case insensitivity natively without extra computation.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------