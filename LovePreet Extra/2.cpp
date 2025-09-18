-------------------------------------------------------------------------------------------------------------------------------------
Refresh Token Implementation:
-------------------------------------------------------------------------------------------------------------------------------------

Auth Controller:

SignUp():
It is used to create a new user.
It checks if the user is already registered.
If not, it saves the user to the database.

-------------------------------------------------------------------------------------------------------------------------------------

Token Controller:

Login():
It is used to login the user
It validate the user using username and password
If valid, it generates an access token and a refresh token and returns it to the user.
If not valid, it returns an error message.

RefreshToken():
It checks if the refresh token is valid or expired
If valid, It generates new JWT token using username and returns both old refresh and new JWT Token
If expired, it returns an error message asking the user to login again.

-------------------------------------------------------------------------------------------------------------------------------------

Entities:

UserInfo:
userId, username, password, roles

Role:
roldId, roleName

RefreshToken:
tokenId, userId, token, expiryDate

-------------------------------------------------------------------------------------------------------------------------------------

Services:

CustomUserDetails:

It implements userDetails interface
It is used by UserDetailsService to load user-specific data.
Intialize userInfo object using constructor Injection

JwtUtilService:
It is jwt utitlity class
It has methods to extract username, expiration date, generate token and validate token

RefreshTokenService:

createRefreshToken():
It creates a new refresh token for the user and saves it to the database.

findByToken():
It finds the refresh token in the database using the token string.

verifyExpiration():
It checks if the refresh token is expired or not.
If expired, it deletes the token from the database and throws an exception.

UserDetailsServiceImpl:
It implements UserDetailsService interface
It loads user-specific data using username

SignUp():
It is used to create a new user.
It checks if the user is already registered.
If not, it saves the user to the database.

-------------------------------------------------------------------------------------------------------------------------------------