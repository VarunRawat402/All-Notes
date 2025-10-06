-------------------------------------------------------------------------------------------------------------
Authentication strategy:
-------------------------------------------------------------------------------------------------------------

1: Interface Method:

Easily To Implement
Every Entity has seperate authentication

-------------------------------------------------------------------------------------------------------------

Interface:
This interface allows different entities to be treated uniformly through the UserAccount while having
specific Implementation.
All the Entities implements UserAccount and override all the methods

public interface UserAccount extends UserDetails {

}

-------------------------------------------------------------------------------------------------------------

Student Entity:

@Entity
public class Student implements UserAccount {

    private Long id;    
    private String username;
    private String password;
    private Set<Role> roles = new HashSet<>();
    
    // UserDetails methods
    @Override public String getUsername() { return username; }
    @Override public String getPassword() { return password; }
    @Override public Collection<? extends GrantedAuthority> getAuthorities() {
        return roles.stream()
            .map(role -> new SimpleGrantedAuthority(role.getName()))
            .collect(Collectors.toList());
    }
}

-------------------------------------------------------------------------------------------------------------

Admin Entity:

@Entity
public class Admin implements UserAccount {

    private Long id;
    private String username;
    private String password;
    private Set<Role> roles = new HashSet<>();

    @Override public String getUsername() { return username; }
    @Override public String getPassword() { return password; }
    @Override public Collection<? extends GrantedAuthority> getAuthorities() {
        return roles.stream()
            .map(role -> new SimpleGrantedAuthority(role.getName()))
            .collect(Collectors.toList());
    }
}

-------------------------------------------------------------------------------------------------------------

UserDetailsService:
Every entity is responsible for their own authentication and implementation of UserDetails methods
Every entity is validated as a seperate entity in loadByUsername

@Service
@RequiredArgsConstructor
public class CustomUserDetailsService implements UserDetailsService {
    private final StudentRepository studentRepo;
    private final AdminRepository adminRepo;

    @Override
    public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
        Optional<Student> student = studentRepo.findByEmail(email);
        if (student.isPresent()) {
            return student.get();
        }
        
        Optional<Admin> admin = adminRepo.findByEmail(email);
        if (admin.isPresent()) {
            return admin.get();
        }
        
        throw new UsernameNotFoundException("User not found");
    }
}

-------------------------------------------------------------------------------------------------------------

2: Composition Method:

-------------------------------------------------------------------------------------------------------------

User Entity:
Only User entity will implement the UserDetails and override the methods
Only User entity will be validated in authentication 
User entity is mapped to every entity 
User will be the foreign key in all the entities

@Entity
public class User {

    private Long id;
    private String email;
    private String password;
    private Set<Role> roles = new HashSet<>();

    @OneToOne(mappedBy = "user")
    private Student student;
    
    @OneToOne(mappedBy = "user")
    private Admin admin;
}

-------------------------------------------------------------------------------------------------------------

Student Entity:

@Entity
public class Student {

    private Long id;
    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "user_id")
    private User user;
}

-------------------------------------------------------------------------------------------------------------

Admin Entity:

@Entity
public class Admin {

    private Long id;
    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "user_id")
    private User user;
}

-------------------------------------------------------------------------------------------------------------

Create Student:
First user is created and saved
Then student is created and mapped with user

public class RegistrationService {
    private final UserRepository userRepo;
    private final StudentRepository studentRepo;
    private final PasswordEncoder passwordEncoder;

    public void registerStudent(StudentRegistrationDto dto) {
        User user = new User();
        user.setEmail(dto.getEmail());
        user.setPassword(passwordEncoder.encode(dto.getPassword()));
        user.setRoles(Set.of(new Role("ROLE_STUDENT")));
        userRepo.save(user);
        
        Student student = new Student();
        student.setUser(user);
        student.setStudentId(dto.getStudentId());
        student.setMajor(dto.getMajor());
        studentRepo.save(student);
    }
}

-------------------------------------------------------------------------------------------------------------

UserDetailsService:

@Service
@RequiredArgsConstructor
public class CustomUserDetailsService implements UserDetailsService {
    private final UserRepository userRepo;

    @Override
    public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
        User user = userRepo.findByEmail(email)
            .orElseThrow(() -> new UsernameNotFoundException("User not found"));
        
        return new CustomUserDetails(user);
    }
}

-------------------------------------------------------------------------------------------------------------