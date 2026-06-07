-----------------------------------------------------------------------------------------------------------------------------------------------------
Spring Security: Key Concepts and Explanations
-----------------------------------------------------------------------------------------------------------------------------------------------------

1. MITM (Man-in-the-Middle) Attacks:

→ Attacker intercepts communication between user and server.
→ Can steal: username/password, JWT tokens, session cookies, personal data

Prevention:
  → HTTPS          → encrypts data in transit, attacker cant read it
  → Certificate    → validates server 
  → VPN            → encrypted tunnel for communication

-----------------------------------------------------------------------------------------------------------------------------------------------------

2. CSRF (Cross-Site Request Forgery):

How attack works:
  1. User logs into bank → sessionId stored in browser cookie
  2. User visits attackers site
  3. Attacker triggers request to bank from their site
  4. Browser automatically sends sessionId cookie with request
  5. Bank thinks its a valid request → money transferred

Prevention:
  → Spring Security generates a CSRF token per session
  → Every request must include correct CSRF token + session
  → Missing/wrong token → request blocked

Note:
  → CSRF protection needed when auth uses cookies/sessions
  → JWT auth → CSRF not required (JWT not auto-sent by browser like cookies)

-----------------------------------------------------------------------------------------------------------------------------------------------------

3. CORS (Cross-Origin Resource Sharing):

→ Browser blocks requests to a different origin by default (security feature)
→ Origin = protocol + domain + port
  "http://frontend.com" ≠ "http://api.com" → different origin → blocked

→ Server allows specific origins by sending CORS headers in response
→ Browser sees header → allows the request

-----------------------------------------------------------------------------------------------------------------------------------------------------

Hashing:
  → 1-way transformation → cant reverse
  → "password123" → 5f4dcc3b5aa765d61d8327deb882cf99
  → Used for storing passwords (server never stores raw password)

-----------------------------------------------------------------------------------------------------------------------------------------------------

Encryption:
  → 2-way transformation → can encrypt and decrypt
  → plaintext → encrypt → ciphertext → decrypt → plaintext
  → Used when you need the original data back

1. Symmetric Encryption:
  → Same key encrypts and decrypts
  → Fast but risky → key must be shared, if leaked everything exposed
  → Example: AES

2. Asymmetric Encryption:
  → Two keys → Public key encrypts, Private key decrypts
  → Public key shared openly, Private key never leaves server
  → Slower than symmetric but more secure
  → Example: RSA

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTTP:
  → Defaut Port : 80

The Problem with HTTP:
  → Data you are sending is not encrypted
  → Data sent as plain text → anyone on same WiFi can read it
  → No server verification → you could be talking to a fake site without knowing

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS:
  → Secure version of HTTP
  → HTTP + TLS encryption.
  → Defaut Port : 443

Encryption:
  → Encrypt the data so attackers cannot read it 
  → Browser + server share secret keys to encrypt/decrypt

Security:
  → Attacker cannot modify the data 
  → TLS checks if data was modified or not
  → Even single character change → connection fails

Working
  → Server proves its identity using SSL/TLS Certificate
  → Confirms youre talking to real site, not an imposter

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTTPS Handshake:
  → Before any data is sent, browser and server establish a secure connection

Steps:
  1. Browser → Server   : "Hello, I want to connect securely"
  2. Server  → Browser  : Sends SSL/TLS Certificate (contains public key)
  3. Browser verifies   : Is this certificate valid and trusted?
  4. If valid           : Browser uses public key to agree on a temporary secret key
  5. Both sides now use : That secret key to encrypt all communication (symmetric)

Why temporary secret key:
  → Asymmetric (public/private key) is slow → only used during handshake
  → After handshake → switch to fast symmetric key for actual communication

-----------------------------------------------------------------------------------------------------------------------------------------------------




