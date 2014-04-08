#!/usr/bin/env python2.7
# CS141, Lab 2
# slow_exp.py

import sys, timeit

def slow_exp(x, y, N):
    z=1
    for i in range(y):
        z = (z*x) % N    
    return z

if len(sys.argv) == 4: 
    x=int(sys.argv[1])
    y=int(sys.argv[2])
    N=int(sys.argv[3])
    print slow_exp(x,y,N)
    sys.exit()
else:
	for line in sys.stdin:
	    args=line.split()
	    x=int(args[0])
	    y=int(args[1])
	    N=int(args[2])
	    print x, y, N
	    t=timeit.Timer(lambda: slow_exp(x,y,N))
	    print t.timeit(1)