------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pageable            → an interface used to define pagination information.
PageRequest         → an implementation class of Pageable.
PageRequest.of()    → static factory method to create a Pageable object.
Sort                → utility class to define sorting order.

By default:
    → Data is returned unsorted
    → Pagination is zero-based

Offset Formula:
    → offset = (pageNumber - 1) x pageSize

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Basic Pagination with Page and PageSize:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Flow:

1: Controller receives page and pageSize.
2: Create Pageable object using PageRequest.of(page-1, pageSize).
3: Pass Pageable to repository method
4: Repository returns a Page<T> object.

What Page<T> Contains
1: content         → actual list of records
2: totalElements   → total rows in DB
3: totalPages      → 15
4: pageNumber      → 0
5: pageSize        → 0
6: sort            → ASC

To get the actual data:
    → studentRepository.findAll(pageable).getContent();

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination with Sorting
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sorting Parameters:

1: sortBy   → Feild name ( id, name , salary )
2: sortDir  → Asc or Desc

public List<Student> getAllCustomer(int page, int pageSize, String sortBy, String sortDir){
    
    Sort sort = null;
    if(sortDir.equalsIgnoreCase("ASC")){
        sort = Sort.by(sortBy).ascending();
    }else if(sortDir.equalsIgnoreCase("DESC")){
        sort = Sort.by(sortBy).descending();
    }
    
    Pageable p1 = PageRequest.of(page-1,pageSize,sort);
    return studentService.getAllStudents(p1);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Fetch Customers by Name with Pagination:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@GetMapping("/student/")
public List<Student> getAllCustomer(int page, int pageSize, String search){
    
    Pageable p1 = PageRequest.of(page-1,pageSize);
    return studentService.getAllStudents(p1,search);
}

public List<Student> getAllStudents(Pageable pageable, String search) {

    if (search == null) {
        return studentRepository.findAll(pageable).getContent();
    }
    else{
        return studentRepository.findByName(search, pageable).getContent();
    }
}

public interface StudentRepository extends JpaRepository<Student,Integer> {
    Page<Student> findByName(String name, Pageable pageable);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Specification:
    → A functional interface used for dynamic query building.
    → Abstract method() → toPredicate(root, query, criteriaBuilder)
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
