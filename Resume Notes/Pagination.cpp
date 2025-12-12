------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pagination is an interface
PageRequest is a class 
PageRequest.of() is a static function

Sort is a utility class 
Used to define the sorting order when you fetch the results from the repository
    Used when you findAll(), Paginatiion, Custom Fetch queries
    By default data comes unsorted

offset = ( pageno - 1 ) * pageSize

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Basic Pagination using Page and PageSize:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Get PageNumber and PageSize in Controller
Pass both in PageRequest.of(), It returns object of Pageable
Pass the object to the service class

studentRepository.findAll(pageable), It returns Page<Student> not list of student
Page<Student> Contains:
    content: [list of students]
    totalElements: 150
    totalPages: 15
    pageNumber: 0
    pageSize: 10
    sort: name: ASC

studentRepository.findAll(pageable).getContent(), To get the acutal list of students

Controller:
@GetMapping("/student/")
public List<Student> getPagedStudents(@RequestParam int page, @RequestParam int pageSize){
    Pageable p1 = PageRequest.of(page-1,pageSize);
    return studentService.getAllStudents(p1);
}


Service:
public List<Student> getAllStudents(Pageable pageable) {
    return studentRepository.findAll(pageable).getContent();
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pagination with Sorting:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

sortBy: we sort based on this attribute like id, name , salary
sortDir: ascending or descending

@GetMapping("/student/")
public List<Student> getPagedStudents(@RequestParam(required = false, defaultValue = "1") int page,
                                        @RequestParam(required = false, defaultValue = "5") int pageSize,
                                        @RequestParam(required = false, defaultValue = "id") String sortBy,
                                        @RequestParam(required = false, defaultValue = "asc") String sortDir){
    
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
Pagination with Sorting and Searching with Name:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

When you search by name it will search based on name and returns a page of 5 entries with the searched name
This is not best approach as soon as the search type becomes 10 or 20
For that we can use JPA Specification

@GetMapping("/student/")
public List<Student> getPagedStudents(@RequestParam(required = false, defaultValue = "1") int page,
                                        @RequestParam(required = false, defaultValue = "5") int pageSize,
                                        @RequestParam(required = false, defaultValue = "id") String sortBy,
                                        @RequestParam(required = false, defaultValue = "asc") String sortDir,
                                        @RequestParam(required = false) String search){

    Sort sort = null;
    if(sortDir.equalsIgnoreCase("ASC")){
        sort = Sort.by(sortBy).ascending();
    }else if(sortDir.equalsIgnoreCase("DESC")){
        sort = Sort.by(sortBy).descending();
    }
    Pageable p1 = PageRequest.of(page-1,pageSize,sort);
    return studentService.getAllStudents(p1,search);
}

//If search is null, we will return normal pagination 
//if search has a name we will search by name
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
    It is an functional Interface with multiple defined methods and 1 abstract method 
    toPredicate() is the abstract method
    It takes 3 arguments ( root, query, criteriaBuilder )
    root -> used to get the student details
    query -> query to fetch data from database
    criteriaBuilder -> all the conditions to search by 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Basic Search filter with 1 search Feild:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@GetMapping("/student/")
public List<Student> getPagedStudents(@RequestParam(required = false, defaultValue = "1") int page,
                                        @RequestParam(required = false, defaultValue = "5") int pageSize,
                                        @RequestParam(required = false, defaultValue = "id") String sortBy,
                                        @RequestParam(required = false, defaultValue = "asc") String sortDir,
                                        @RequestParam(required = false) String search){

    Sort sort = null;
    if(sortDir.equalsIgnoreCase("ASC")){
        sort = Sort.by(sortBy).ascending();
    }else if(sortDir.equalsIgnoreCase("DESC")){
        sort = Sort.by(sortBy).descending();
    }
    Pageable p1 = PageRequest.of(page-1,pageSize,sort);
    return studentService.getAllStudents(p1,search);
}

public interface StudentRepository extends JpaRepository<Student,Integer>, JpaSpecificationExecutor<Student> {
    Page<Student> findByName(String name, Pageable pageable);
}

public class StudentSpecification {
    public static Specification<Student> getSpecification(String search){
        return new Specification<Student>() {
            @Override
            public @Nullable Predicate toPredicate(Root<Student> root, CriteriaQuery<?> query, CriteriaBuilder criteriaBuilder) {

                if(search==null || search.isEmpty()){
                    return criteriaBuilder.conjunction();
                }
                List<Predicate> l1 = new ArrayList<>();
                l1.add(criteriaBuilder.like(root.get("name"),"%" + search + "%"));
                l1.add(criteriaBuilder.like(root.get("position"),"%" + search + "%"));
                l1.add(criteriaBuilder.like(root.get("email"),"%" + search + "%"));
                return criteriaBuilder.or(l1.toArray(new Predicate[0]));
            }
        };
    }
}

public List<Student> getAllStudents(Pageable pageable, String search) {
    Specification<Student> spec = StudentSpecification.getSpecification(search);
    return studentRepository.findAll(spec,pageable).getContent();
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Multiple Search filters ( name, age, salary ):
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

@GetMapping("/student/")
public List<Student> getPagedStudents(@RequestParam(required = false, defaultValue = "1") int page,
                                        @RequestParam(required = false, defaultValue = "5") int pageSize,
                                        @RequestParam(required = false, defaultValue = "id") String sortBy,
                                        @RequestParam(required = false, defaultValue = "asc") String sortDir,
                                        @RequestParam(required = false) Integer age,
                                        @RequestParam(required = false) String position,
                                        @RequestParam(required = false) String email,
                                        @RequestParam(required = false) String name){
    Sort sort = null;
    if(sortDir.equalsIgnoreCase("ASC")){
        sort = Sort.by(sortBy).ascending();
    }else if(sortDir.equalsIgnoreCase("DESC")){
        sort = Sort.by(sortBy).descending();
    }
    Pageable p1 = PageRequest.of(page-1,pageSize,sort);
    return studentService.getAllStudents(p1,name,age,position,email);
}

public List<Student> getAllStudents(Pageable pageable, String name, Integer age, String position, String email) {
    Specification<Student> spec = StudentSpecification.getSpecification(name,age,position,email);
    return studentRepository.findAll(spec,pageable).getContent();
}

public class StudentSpecification {
    public static Specification<Student> getSpecification(String name, Integer age, String position, String email) {

        return (root, query, cb) -> {

            List<Predicate> predicates = new ArrayList<>();

            if (name != null && !name.trim().isEmpty()) {
                predicates.add(cb.like(root.get("name"),"%" + name.trim() + "%"));
            }

            if (age != null) {
                predicates.add(cb.equal(root.get("age"), age));
            }

            if (position != null && !position.trim().isEmpty()) {
                predicates.add(cb.like(root.get("position"),position.trim() + "%"));
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
