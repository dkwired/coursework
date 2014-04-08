#!/usr/bin/env python2.7
#
###################################
# CS141, 12 Spring
#
# fib2.py
###################################
import sys, timeit

sys.setrecursionlimit(1000)

def fib2_a(n):
    if n==1:
        return (0, 1)
    else:
        a, b = fib2_a(n-1)
	print a,b
        return (b, a+b)

def fib2(n):
    if n<1:

        return n
    return fib2_a(n)[1]

n=10
if len(sys.argv)>1:
    n=int(sys.argv[1])
t=timeit.Timer(lambda: fib2(n))
l=t.timeit(1)
print l
