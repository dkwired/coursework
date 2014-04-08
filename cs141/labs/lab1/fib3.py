#!/usr/bin/env python2.7
#
###################################
# CS141, 12 Spring
#
# fib3.py
###################################
import sys, timeit

def fib3(n):
    if n<1:
        return n
    a,b = 0,1
    for i in range(n-1):
        a,b = b, a+b
    return b

n=30
if len(sys.argv)>1:
    n=int(sys.argv[1])
t=timeit.Timer(lambda: fib3(n))
l=t.timeit(1)
print l
