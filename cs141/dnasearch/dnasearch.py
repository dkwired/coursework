#!/usr/bin/env python2.7

# see README for description of the lab.
#David Klein
#860880864
#Project 2

import sys

def diff(x, y):
   
   if( (x == "A" and y == "A") or (x == "G" and y == "G") or (x == "C" and y == "C") or (x == "T" and y == "T") ):
      return 1.0
   elif( (x == "A" and y == "G") or (x == "A" and y == "C") or (x == "G" and y == "T") or (x == "C" and y == "T") ):
      return -0.1
   elif( (x == "G" and y == "C") or (x == "A" and y == "T") ):
      return -0.15
   else:
      return 0

def align( AE, dbe, query, top, bottom, i, j ):

   if( (i == 0) and (j == 0) ):
      return top, bottom

   a = AE[i-1][j]
   b = AE[i][j-1]
   c = AE[i-1][j-1]

   AE_max = max( a, b, c )

   if( ((i == 0) and (j <> 0)) or (AE_max == b )):
      top = "-" + top
      bottom = query[j] + bottom
      return align( AE, dbe, query, top, bottom, i, j-1 )

   elif( ((i <> 0) and (j == 0)) or (AE_max == a )):
      top = dbe[i] + top
      bottom = "-" + bottom
      return align( AE, dbe, query, top, bottom, i-1, j )

   else:
      top = dbe[i] + top
      bottom = query[j] + bottom
      return align( AE, dbe, query, top, bottom, i-1, j-1 )

def E( dbe, query ):
   
   width = len(dbe)
   height = len(query)

   AE = [ [None] * width for i in range(height) ]

   for i in range(width): AE[0][i] = i*-0.2
   for j in range(height): AE[j][0] = j*-0.2

   for i in range(1, height):
      for j in range(1, width):
         a = AE[i-1][j] - .02
         b = AE[i][j-1] - .02
         c = AE[i-1][j-1] + diff(dbe[i],query[j])
         AE[i][j] = max( a, b, c )
   
   return AE

## main code begins here.

database = sys.argv[1]
query = sys.argv[2]
num_of_sequence = sys.argv[3]
alignment = sys.argv[4]

num_of_sequence = int(num_of_sequence)

f = open(database, 'r')
db_array = []
for line in f:
   db_array.append( line.strip() )

f = open(query, 'r')
for line in f:
   query_text = line.strip()

width = len(db_array[1])
height = len(query_text)

AE = []
top_array = ""
bottom_array = ""

total = []

for i in range(0, num_of_sequence*2, 2):
   temp1 = " " + db_array[i+1]
   temp2 = " " + query_text
   AE = E(temp1, temp2)
   top_array, bottom_array = align( AE, temp1, temp2, top_array, bottom_array, width-1, height-1 )
   #total[i].append( (AE[width-1][height-1], db_array[i], top_array, bottom_array) )
   print AE[width][height], " * ", db_array[i]
   print top_array
   print bottom_array + "\n"
   temp1 = ""
   temp2 = ""

