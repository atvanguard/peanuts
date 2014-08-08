#safe_chat
=========
(Created on: October 26, 2013)

Encrypted Chat between two hosts.
ElGamal encyrption algorithm has been used for encryption.
Kindly note that this project was just to brush up concepts of Socket programming in C and the key exchange is totally unsafe.

So, yeah not really a very safe_chat.


##Elgamal Encryption Algorithm
Public keys: Large prime number p and generator g ----- (g,p)
Private Key: x
Calculate: A = g^x mod p
Server broadcasts: (A,g,p)

Client receives: (A,g,p)
Chooses private key: y
Calculate:
    c1 = g^y mod p
    and c2 = M*(A^y) mod p
Send (c1,c2)


