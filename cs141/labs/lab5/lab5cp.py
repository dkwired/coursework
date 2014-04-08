#!/usr/bin/env python2.7
#
# CS 141, Lab 5
# Closest Pair
############################

#David Klein
#860880864
#Lab5

import sys
from operator import itemgetter
from math import sqrt
from random import random

def dist(p1, p2):
    def sqr(x): return x*x
    return sqrt(sqr(p1[0]-p2[0]) + sqr(p1[1]-p2[1]))

# input: pts[], a list of points 
# return: d, a floating point number that is 
# the min dist between any two points
# computed using dist() function
def closest_pair(pts):
    if( len(pts) == 0 ):
       return -1
    if( len(pts) == 1 ):
       return -1
    if( len(pts) == 2 ):
       return dist(pts[0],pts[1])
    else:
       left_list=[]
       right_list=[]
       for i in range(0, len(pts)/2):
          temp = pts[i]
          left_list.append(temp)
       for j in range(len(pts)/2, len(pts)):
          temp = pts[j]
          right_list.append(temp)

       d_left = closest_pair(left_list)
       d_right = closest_pair(right_list)

       if(d_left <> -1 and d_left < d_right):
          d = d_left
       else:
          d = d_right
       
       return d

def slow_cp(pts):
    n = len(pts)
    if n<2: return 0
    d = dist(pts[0], pts[1])
    for i in range(n-1):
        for j in range(i+1, n):
            d = min(d, dist(pts[i], pts[j]))
    return d

pts=[]
for line in sys.stdin:
    x = float(line.split()[0])
    y = float(line.split()[1])
    pts.append((x,y))

pts.sort(key=lambda tup: tup[0])

median_pt = pts[len(pts)/2]

left_list=[]
right_list=[]
for i in range(0, len(pts)/2):
   temp = pts[i]
   left_list.append(temp)
for j in range(len(pts)/2, len(pts)):
   temp = pts[j]
   right_list.append(temp)

d_left = closest_pair(left_list)
d_right = closest_pair(right_list)

if(d_left < d_right ):
   d = d_left
else:
   d = d_right

median_list=[]
lower = int(median_pt[0]-d/2)
upper = int(median_pt[0]+d/2)
for i in range(lower, upper):
   temp = pts[i]
   median_list.append(temp)

median_list.sort(key=lambda tup: tup[1])

d_median = closest_pair(median_list)

print "The smallest distance between two points is:"
if(d_median < d_left and d_median < d_right ):
   print d_median
if(d_left < d_right and d_left < d_median ):
   print d_left
if(d_right < d_left and d_right < d_median ):
   print d_median

#print median_list

# read pts from input
EPS=1.0e-6
