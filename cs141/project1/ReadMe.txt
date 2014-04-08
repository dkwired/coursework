David Klein
860880864
Project 1
ReadMe.txt

For the initialization function I just return a long if correct input is received for both numbers. When comparing numbers, we just convert the string to a number then compare the values. I have two cases for the addition function. First I take the numbers and turn them into arrays. Then we iterate through the arrays adding the single digits and keeping track of the carry. I left the answer in array form to show that the addition and carry was being done properly. I intially implemented a form of karatsuba's that is not recursive. This way has a bug for any number result > 1000 and < 10000. There is a tens place missing. For any number over 10000 this issue seems to go away. I later tried to implement a recursive form of karatsuba's but did not complete it.

Running instructions:
Modify the bottom of BigInt.py to call:
test.TestCmp()
test.TestAdd()
test.TestMul()

By removing the sharp (#). That is, unless you want to run all tests consecutively.
