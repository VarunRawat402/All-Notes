-----------------------------------------------------------------------------------------------------------------------------------
Spring Security OATH 2.0
-----------------------------------------------------------------------------------------------------------------------------------

It is used by application to authorize the users by 3rd parties like google, facebook etc etc.
It is a way of security where the user will be authenticating using a 3rd party service and 
our application will be handling the authorization part only.

When application use 3rd party apps like google , facebook to authenticate the users for them
3rd party apps charge them also.

-----------------------------------------------------------------------------------------------------------------------------------

Flow:
User performed some actions on FE and the request goes to BE to run the user request but it needs authentication So, 
SB application goes to Github to authenticate the user, 
Now Github asks the user weathter you want to give this application to give access to some stuff and if the user said yes then it will return some data
to application which tells the application it is an authorized user and will perform the request.

-----------------------------------------------------------------------------------------------------------------------------------

OATH2.0

1: User revoking the access of the auth2.0 app from the application.
Why? Maybe user dont want to share his/her details with the 3rd party app anymore.

2: oath2.0 revoking the access of the user 
Why? Maybe 3rd party app made some changes in their policy/scope and wants user to authorize again with changed scope/policy.

When we register our application in the Github for auth2.0 serurity then github provides us with Client ID and Client Secrets.
We need to provide this ID and secrets in the application because when we send request to authorize user to github we send ID and secrets
to the github and github checks weather these ID and secrets match with the ID and secrets github gave to check if the site is trusted or not.

Syntax: ( In application Properties )
spring.security.oauth2.client.registration.github.client-id = sdsdsdsdsdsdsdsd
spring.security.oauth2.client.registration.github.client-secret = dsadsadasdsadsadas

This is pre defined property in the spring boot security for oauth2.0 which takes a map ( key value pair ) and github is just custom we added.
spring.security.oauth2.client.registration.

-----------------------------------------------------------------------------------------------------------------------------------