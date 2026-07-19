------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination & Specifications:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pageable            → Interface
PageRequest         → Class that implements Pageable
PageRequest.of()    → static method to create Pageable object
Sort                → Utility class to define sort field and direction

Notes:
    → Data is unsorted by default
    → Pagination is zero-indexed (page 0 = first page)

Offset Formula:
    → offset = (pageNumber - 1) × pageSize

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BASIC PAGINATION:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pageable pageable       = PageRequest.of(0, 50);                    // page 0, 50 items per page
Page<Customer> page     = customerRepository.findAll(pageable);
List<Customer> list     = page.getContent();

What Page<T> Contains
    1: content              → List<Customer> for the current page
    2: totalElements        → Total records matching the query
    3: totalPages           → Total number of pages
    4: pageNumber           → current page index (0-based)
    5: pageSize             → Records per page
    6: sort                 → sort applied (ASC/DESC)
    7: Is first/last page   → Whether this is the first or last page

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination with Sorting
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Parameters:
    1: sortBy   → Feild name ( id, name , salary )
    2: sortDir  → Asc or Desc

public List<Student> getAllStudents(int page, int pageSize, String sortBy, String sortDir) {

    Sort.Direction direction = Sort.Direction.fromString(sortDir);
    Sort sort                = Sort.by(direction, sortBy);
    Pageable pageable        = PageRequest.of(page - 1, pageSize, sort);

    return studentRepository.findAll(pageable).getContent();
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PAGINATION WITH FILTERING (Single Field Name):
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Controller
@GetMapping("/students")
public List<Student> getStudentsByName(String name, int page, int pageSize) {
    Pageable pageable = PageRequest.of(page - 1, pageSize);
    return studentService.getAllStudents(name, pageable);
}

// Service
public List<Student> getAllStudents(String name, Pageable pageable) {
    return studentRepository.findByName(name, pageable).getContent();
}

// Repository — Spring Data JPA generates the query automatically
public interface StudentRepository extends JpaRepository<Student, Integer> {
    Page<Student> findByName(String name, Pageable pageable);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SPECIFICATION (Dynamic Query Building):

→ A functional interface used to build dynamic queries at runtime.
→ Instead of writing a separate repository method for every filter combo, you build predicates conditionally and combine them.

toPredicate(root, query, criteriaBuilder):
    → root            → the Entity being queried (like FROM student)
    → query           → the final SQL query being constructed
    → criteriaBuilder → used to build conditions (AND, OR, LIKE, EQUAL, etc.)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PAGINATION + MULTIPLE FILTERS (name, email)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Flow:

1: Create Pageable via PageRequest.of()
2: Create Specification via toPredicate()
3: Build predicates conditionally for each filter field
4: Pass Specification + Pageable to repository.findAll()

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Controller
@GetMapping("/students")
public List<Student> getPagedStudents(int page, int pageSize, String name, String email) {
    Pageable pageable = PageRequest.of(page - 1, pageSize);
    return studentService.getAllStudents(pageable, name, email);
}

// Service
public List<Student> getAllStudents(Pageable pageable, String name, String email) {
    Specification<Student> spec = StudentSpecification.getSpecification(name, email);
    return studentRepository.findAll(spec, pageable).getContent();
}

// Specification
public class StudentSpecification {

    public static Specification<Student> getSpecification(String name, String email) {

        return (root, query, cb) -> {

            List<Predicate> predicates = new ArrayList<>();

            if (name != null && !name.trim().isEmpty()) {
                predicates.add(cb.like(root.get("name"), "%" + name.trim() + "%"));     // contains
            }

            if (email != null && !email.trim().isEmpty()) {
                predicates.add(cb.like(root.get("email"), email.trim() + "%"));         // starts with
            }

            // No filters provided → return all results
            if (predicates.isEmpty()) {
                return cb.conjunction();
            }

            return cb.and(predicates.toArray(new Predicate[0]));
        };
    }
}

// Repository — extend JpaSpecificationExecutor to support Specification queries
public interface StudentRepository extends JpaRepository<Student, Integer>,JpaSpecificationExecutor<Student> {
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INTERVIEW Q & A
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Q: Why use Specification instead of writing individual repository methods?
    → Writing a method for every filter combo explodes quickly (findByName, findByEmail, findByNameAndEmail, etc.).
    → Specification lets you build predicates conditionally at runtime — one method handles any combination of filters cleanly.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Q: What does cb.conjunction() return?
    → A predicate that always evaluates to TRUE — effectively no filter.
    → Used when no search params are provided so all records are returned.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Q: Why is pagination zero-indexed and how do you handle it for clients?
    → JPA/Spring Data uses 0-based page index internally.
    → APIs typically accept 1-based page numbers from clients for readability.
    → Handle it by passing page - 1 into PageRequest.of() so page 1 from the client maps to index 0 internally.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Q: What does Page<T> give you over just List<T>?
    → Page<T> includes metadata: totalElements, totalPages, isFirst, isLast, current page number and size — all needed to render pagination UI.
    → List<T> gives you just the data with no context about total results.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------