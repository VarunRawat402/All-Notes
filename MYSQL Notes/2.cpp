------------------------------------------------------------------------------------------------------------------------------------------------------------
Data Types In MYSQL:
------------------------------------------------------------------------------------------------------------------------------------------------------------

Numbers:

Integers: [ TINYINT, SMALLINT, MEDIUMINT, INT, BIGINT ] :
    Does not store numbers after decimal
    Every type has different range
    Use according to your range

Floating: [ FLOAT, DOUBLE ]
    Float can hold upto 7 Digits including positive
    Double can hold upto 15 Digits including positive

    So if the number is close to 6 or 7 digits float will round of the digits after DECIMAL
    So if the number is close to 15 or 16 digits double will round of the digits after DECIMAL

DECIMAL:
    It is a fixed point number
    Use when accuracy matters
    DECIMAL ( p, s ), p is total digits & s is digits after decimal
    It does not round of the value just store the number according to given range
    DECIMAL(6,2) means it can store total 6 digits, 4 digits before decimal and 2 digits after decimal exactly

------------------------------------------------------------------------------------------------------------------------------------------------------------

Integers: ( only digits before decimal )

1           - 1
1.34        - 1
14.234      - 14

------------------------------------------------------------------------------------------------------------------------------------------------------------

Float:  ( max digits can be 6 to 7 after that it rounds off)

1.234               - 1.234
14.234              - 14.234
50000.23456         - 50000.2

------------------------------------------------------------------------------------------------------------------------------------------------------------

Double: ( max digits can be 15 or 16 after that it rounds off)

50000.23456                 - 50000.23456
50000.12345678              - 50000.12345678
50000.1234567891234         - 50000.12345678912

------------------------------------------------------------------------------------------------------------------------------------------------------------

Decimal(6,2):

50.23                       - 50.23
50.234                      - 50.23                     It stores first 2 digits because range is 2 and digits after decimal is out of range
5000.234                    - 5000.23  
50000.234                   - Error because digits before decimal range is 4 but in example its 5

------------------------------------------------------------------------------------------------------------------------------------------------------------



