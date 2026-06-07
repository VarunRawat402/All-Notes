-----------------------------------------------------------------------------------------------------------------------------------------------------
Composition Method:
-----------------------------------------------------------------------------------------------------------------------------------------------------

User Entity:
    → Implement the userDetails Interface
    → User will be validated in loadUserByUsername()
    → Mapped to every entity

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

-----------------------------------------------------------------------------------------------------------------------------------------------------

Student Entity:

@Entity
public class Student {

    private Long id;
    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "user_id")
    private User user;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Admin Entity:

@Entity
public class Admin {

    private Long id;
    @OneToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "user_id")
    private User user;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

Create Student:
    → First user is created and saved
    → Then student is created and mapped with user

public class RegistrationService {
    private final UserRepository userRepo;
    private final StudentRepository studentRepo;
    private final PasswordEncoder passwordEncoder;

    public void registerStudent(StudentRegistrationDto dto) {
        User user = new User();
        user.setEmail(dto.getEmail());
        user.setPassword(passwordEncoder.encode(dto.getPassword()));
        user.setRoles(Set.of(new Role("ROLE_STUDENT")));
        
        Student student = new Student();
        student.setUser(user);
        student.setStudentId(dto.getStudentId());
        student.setMajor(dto.getMajor());
        studentRepo.save(student);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------------------