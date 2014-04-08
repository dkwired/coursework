#!/usr/bin/env python2.7
# CS141, Lab 2
# fast_exp.py

import sys, timeit

sys.setrecursionlimit(10000)

# computes x raised to y-th power
# modulo N
def fast_exp(x, y, N):
    # your implementation here
    z = 1
    if y == 0:
	return 1
    elif (y % 2) == 0:
	z = fast_exp(x, y/2, N)
	return (z*z % N)
    elif (y % 2) == 1:
	z = fast_exp( x, (y-1)/2, N )
	return( z*z*x ) % N
    else:
    	return 1

if len(sys.argv) == 4: 
    x=int(sys.argv[1])
    y=int(sys.argv[2])
    N=int(sys.argv[3])
    print fast_exp(x,y,N)
    sys.exit()
else:
	for line in sys.stdin:
	    args=line.split()
	    x=int(args[0])
	    y=int(args[1])
	    N=int(args[2])
	    #print x, y, N
	    t=timeit.Timer(lambda: fast_exp(x,y,N))
	    print t.timeit(1)

