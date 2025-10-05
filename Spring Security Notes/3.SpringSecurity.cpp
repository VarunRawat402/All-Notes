-------------------------------------------------------------------------------------------------------------
New Spring Security Configs ( Security Filter Chain ):
-------------------------------------------------------------------------------------------------------------

Features:

Component based Configuration, Not inheritance
Lambda DSL, Cleaner Syntax, No more .and()
Multiple Filter chains
RequestMatchers() instead of antMatchers()
Oath2 and JWT First class supports
Easier to mock SecurityFilterChain than Override methods

-------------------------------------------------------------------------------------------------------------

Authorization:

Code:
    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                .csrf(csrf -> csrf.disable()) // Explicitly disable CSRF
                .authorizeHttpRequests(auth -> auth
                        .requestMatchers("/admin/**").hasRole("ADMIN")
                        .requestMatchers("/user/**").hasRole("USER")
                        .anyRequest().authenticated()
                )
                .formLogin(withDefaults())
                .logout(withDefaults());

        return http.build();
    }

-------------------------------------------------------------------------------------------------------------

InMemory Authorization:
    In this we hardcode the credentials and store in the InMemory of application

Code:
    @Bean
    public UserDetailsService userDetailsService(){

        UserDetails admin = User.withUsername("varun")
                .password(passwordEncoder().encode("1234")).roles("ADMIN").build();

        UserDetails user = User.withUsername("arun")
                .password(passwordEncoder().encode("1234")).roles("USER").build();
        return new InMemoryUserDetailsManager(admin,user);
    }

------------------------------------------------------------------------------------------------------------------------------------------------------

User Based Authorization:

Code:

    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration authConfig) throws Exception {
        return authConfig.getAuthenticationManager();
    }

------------------------------------------------------------------------------------------------------------------------------------------------------