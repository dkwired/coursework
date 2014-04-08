CS 141 PROJECT 1, DUE Tuesday NIGHT, May 1st

Download and unpack the zip file.  Inspect the files:

CS141.py has all the supplied code and function prototypes
that you need to implement. Replace the pass statement with
your python implementation.

gen_key
==================
"gen_key n" should generate and print out
a random RSA key (p,q,N,e,d) where the modulus N has about 
n bits.  (You may use the routines supplied in that file
for generating random primes, and random integers less
than N having a multiplicative inverse mod N.)


"rsa_encrypt x e N", where e and N are from the public part of an
RSA key, x is a sequence of integers less than N on standard input.
It should return the corresponding sequence of encrypted numbers on
standard output. 

"rsa_decrypt x d N", where d and N are from the private part
of the RSA key, and x is a sequence of encrypted numbers
(as produced by rsa_encrypt) It should return the
corresponding sequence of decrypted numbers on standard
output.  (To convert those numbers into the original text,
pipe them through "numbers_to_text".

"rsa_break e N", where e and N are from the public
part of an RSA key, should return the decryption 
exponent d for that RSA key.

Your routine should work in a few seconds for e and N with up to 40 bits.
If you can make it work for 100-bit keys, we will be very impressed :-).


solutions.txt

After finishing the functions gen_key, rsa_decrypt, rsa_encrypt,
and rsa_break, answer the questions in the file solutions.txt .

Submit two separate files:
    - CS141.py which includes all your implementation
    - solution.txt/pdf with answers to the questions

===============================================================
a sample of test code (shows only partial python and partial pseudo code)

# myrsa.py
from cs141 import * # cs141.py and myrsa.py in same directory

# generate p and q
N=p*q
phi=(p-1)*(q-1)
e=generate_random_invertible(e, phi)
d=inv(e,phi)
# check e*d=1 mod phi
msg = "this is my message"
nums = text_to_numbers(CAP, msg) # note CAP is the N in text_to_numbers
secret = rsa_encrypt(nums, e, N)
original = rsa_decrypt(secret, d, N)
msg2 = numbers_to_text(CAP, original)
print msg1
print msg2 # msg1 and msg2 are identical
