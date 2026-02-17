------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pageable            → Interface
PageRequest         → Class 
PageRequest.of()    → static method to create Pageable object
Sort                → utility class to define sorting order.

Note:
    → Data is unsorted by default
    → Pagination is zero-based index

Offset Formula:
    → offset = (pageNumber - 1) x pageSize

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Basic Pagination with Page and PageSize:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pageable p1             = PageRequest.of(0,50);
Page<Customer> page     = customerRepository.findAll(pageable);
List<Customer> list     = page.getContent();

What Page<T> Contains
    1: content              → List<Customer>
    2: totalElements        → Total customers fetched by query
    3: totalPages           → Total pages
    4: pageNumber           → 0
    5: pageSize             → 50
    6: sort                 → ASC
    7: Is first/last page   → Check if current page is first or last

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination with Sorting
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Parameters:
    1: sortBy   → Feild name ( id, name , salary )
    2: sortDir  → Asc or Desc

public List<Student> getAllCustomer(int page, int pageSize, String sortBy, String sortDir){
    
    Sort.Direction direction = Sort.Direction.fromString(sortDir);
    Sort sort = Sort.by(direction, sortBy)

    Pageable pageable = PageRequest.of( page-1, pageSize, sort);
    return studentService.getAllStudents(pageable);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Fetch Customers by Name with Pagination:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@GetMapping("/student/")
public List<Student> getAllCustomer(String name, int page, int pageSize){
    
    Pageable pageable = PageRequest.of(page-1,pageSize);
    return studentService.getAllStudents( name, pageable );
}

public List<Student> getAllStudents(Pageable pageable, String name) {
    return studentRepository.findByName(name, pageable).getContent();
}

public interface StudentRepository extends JpaRepository<Student,Integer> {
    Page<Student> findByName(String name, Pageable pageable);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Specification:
    → A functional interface used for dynamic query building.
    → toPredicate(root, query, criteriaBuilder)
        root            → Entity
        query           → final SQL query
        criteriaBuilder → used to build conditions (AND / OR / LIKE / EQUAL)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Multiple Search filters ( name, age, salary ):
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Flow: 
1: Create Pageable Object using pageRequest.of()
2: Create Specification Object using toPredicate()
3: Create predicates for all feilds and return them in specification
4: Pass Specification and pageable to repository method

@GetMapping("/student/")
public List<Student> getPagedStudents(int page, int pageSize, String email, String name){

    Pageable p1 = PageRequest.of(page-1,pageSize);
    return studentService.getAllStudents(p1,name,email);
}

public List<Student> getAllStudents(Pageable pageable, String name, String email) {
    Specification<Student> spec = StudentSpecification.getSpecification(name,email);
    return studentRepository.findAll(spec,pageable).getContent();
}

public class StudentSpecification {
    public static Specification<Student> getSpecification(String name, String email) {

        return (root, query, cb) -> {

            List<Predicate> predicates = new ArrayList<>();

            if (name != null && !name.trim().isEmpty()) {
                predicates.add(cb.like(root.get("name"),"%" + name.trim() + "%"));
            }

            if (email != null && !email.trim().isEmpty()) {
                predicates.add(cb.like(root.get("email"),email.trim() + "%"));
            }

            // If no filters given, return all results
            if (predicates.isEmpty()) {
                return cb.conjunction();
            }

            return cb.and(predicates.toArray(new Predicate[0]));
        };
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
