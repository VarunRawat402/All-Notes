----------------------------------------------------------------------------------------------------------------------
Old Spring Security Configs ( WebSecurityConfigurerAdapter ):
----------------------------------------------------------------------------------------------------------------------

In this, SecurityConfig Implements WebSecurityConfigurerAdapter and override its 2 methods
for authentication and authorization

Note:
Add 'ROLE_' prefix in UserDetails Role authority method
Role should be Uppercase
PasswordEncoder is must in AuthenticationManagerBuilder

----------------------------------------------------------------------------------------------------------------------

Authorization:

@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
            .authorizeRequests()
                .antMatchers("/").permitAll()
                .antMatchers("/user/**").hasRole("USER")
                .antMatchers("/admin/**").hasRole("ADMIN")
                .anyRequest().authenticated()
                .and()
            .formLogin()
                .and()
            .logout()
                .permitAll();
    }
}

----------------------------------------------------------------------------------------------------------------------
In Memory Authentication:
----------------------------------------------------------------------------------------------------------------------

@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.inMemoryAuthentication()
            .withUser("user")
                .password(passwordEncoder().encode("password"))
                .roles("USER")
                .and()
            .withUser("admin")
                .password(passwordEncoder().encode("admin"))
                .roles("ADMIN", "USER");
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}

----------------------------------------------------------------------------------------------------------------------
Authentication Via Database:
----------------------------------------------------------------------------------------------------------------------

@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

    @Autowired
    private UserDetailsService userDetailsService;

    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.userDetailsService(userDetailsService)
            .passwordEncoder(passwordEncoder());
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}

----------------------------------------------------------------------------------------------------------------------