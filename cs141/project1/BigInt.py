#!/usr/bin/python

"""
CS 141 Project 1

David Klein
860880864
Revision history
"""

import math

class TestHarness:
    def TestCmp(self):
        print "Please enter a first integer"
        int1 = raw_input()
	try:
		val = long(int1)
	except ValueError:
		print("That's not a number!")
		return None
        print "Please enter a second integer"
        int2 = raw_input()
	try:
		val = long(int2)
	except ValueError:
		print("That's not a number!")
		return None
        
        instance = BigInt(int1)
        int2 = long(int2)
	
        result = instance.__cmp__(int2)
	
        if result == 1:
            print "Your first number is greater than the second."
        elif result == 0:
            print "Integers are equal."
        else:
            print "Your second number is greater than the first."

        return None

    def TestAdd(self):
        print "Please enter a first integer"
        int1 = raw_input()
	try:
		val = long(int1)
	except ValueError:
		print("That's not a number!")
		return None
        print "Please enter a second integer"
        int2 = raw_input()
	try:
		val = long(int2)
	except ValueError:
		print("That's not a number!")
		return None
        
        instance = BigInt(int1)
        int2 = long(int2)
	
	instance.__add__(int2)

        return None

    def TestMul(self):
        print "Please enter a first integer"
        int1 = raw_input()
	try:
		val = long(int1)
	except ValueError:
		print("That's not a number!")
		return None
        print "Please enter a second integer"
        int2 = raw_input()
	try:
		val = long(int2)
	except ValueError:
		print("That's not a number!")
		return None
        
        instance = BigInt(int1)
        int2 = long(int2)
	
	result = 0
	result = instance.__mul__(int2)

#	instance.karatsuba(100, 100)

	print result

        return None

class BigInt:
    def __init__(self, x=0):
        """
       	constructs a new BigInt objects for integer x
        """
	try:
            self.value = long(x)
            return None
	except ValueError:
            print "Input is not an integer!"
            return None
	
    def __str__(self):
        """
        returns the string representation of a BigInt number
        """
	s = ""
	s = str(self.value)
        return s

    def __cmp__(self, other):
        """
        returns a negative integer if self < other, zero if self ==
        other, a positive integer if self > other
        """
	
	if self.value < other:
            return -1
	elif self.value == other:
            return 0
	else:
            return 1

    def __add__(self, other):
        """
        returns the sum of self and other
        """
	num1 = []
	num2 = []
	temp = 0
	overflow = 0		#should have called this carry
	result = []
	
	
	for x in str(self.value):	#convert number to array
		num1.append(x)
	for x in str(other):		#convert number to array
		num2.append(x)

	if len(num1) > len(num2):	#two cases since first number could be greater than the second, or vice versa
		count1 = len(num1) - 1
		count2 = len(num2) - 1
		for i in num1:
			if( count2 >= 0):
				temp = long(num1[count1]) + long(num2[count2]) + overflow	#add the numbers together plus carry 1
				if temp >= 10:
					overflow = 1
					temp = temp % 10	#mod by 10 since we are in base 10
				else:
					overflow = 0		#no carry
				count1 -= 1
				count2 -= 1
				result.append(temp)
			else:
				temp = long(num1[count1]) + overflow
				result.append(temp)
				count1 -= 1
	else:
		count1 = len(num1) - 1
		count2 = len(num2) - 1
		for i in num2:
			if( count1 >= 0):
				temp = long(num1[count1]) + long(num2[count2]) + overflow
				if temp >= 10:
					overflow = 1
					temp = temp % 10
				else:
					overflow = 0
				count1 -= 1
				count2 -= 1
				result.append(temp)
			else:
				temp = long(num2[count2]) + overflow
				result.append(temp)
				count1 -= 1

	for i in reversed(result):
		print i
        return None

    def split_list(self, num_list):
	half = len(num_list)/2
	return num_list[:half], num_list[half:]

    def num_to_array(self, num):
	string = str(num)
	array = []
	for digit in string:
		array.append(int(digit))
	return array

    def karatsuba( self, x, y ):

	if x < 10 or y < 10:
		return x*y

	low1, high1 = self.split_list(list_x)
	low2, high2 = self.split_list(list_y)

	z0 = self.karatsuba(low1, low2)
	z1 = self.karatsuba((low1+high1), (low2+high2))
	z2 = self.karatsuba(high1, high2)

	return None

    def __mul__(self, other):
        """
        returns the product of self and other
        currently implemented as repeated addition
        need to be reimplemented according the the specs
        """

	x = long(self.value)
	y = long(other)

	n = max(len(str(x)),len(str(y)))	#calculate the degree of highest number
	m = n // 2 + (n & 1)			#calculate our exponent

	if x == 1 and y == 1:			#if its a small number just do regular multiplication
		return x * y
	else:
		x0 = x % 10 ** m
		x1 = x / 10 ** m
		y0 = y % 10 ** m
		y1 = y / 10 ** m

		z2 = x1 * y1
		z0 = x0 * y0
		z1 = (x0 + x1) * (y0 + y1) - z2 - z0

		result = z2 * 10**n + z1 * 10**(n>>1) + z0
		
		return result

def fact(n):
    """
    the definition of factorial to compare results
    """
    if n == 0:
        return 1
    else:
        return n*fact(n-1)

if __name__ == '__main__':
    import sys
#    if len(sys.argv) < 2:
#        sys.exit('Usage: %s <number>' % sys.argv[0])
#    prod = BigInt(1)
#    k = int(sys.argv[1])
#    for i in range(k):
#        prod = prod * BigInt(i+1)
#        print prod, fact(i+1)

    test = TestHarness()
    test.TestCmp()
    test.TestAdd()
    test.TestMul()
