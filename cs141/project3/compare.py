#! /usr/bin/python

import sys
import textwrap
from copy import copy, deepcopy
from heapq import *

def convert_str_to_num(string):
    num_string = []
    for i in xrange(len(string)):
        if(string[i] == '_'):
            num_string.append(-1)
        if(string[i] == 'A'):
            num_string.append(0)
        if(string[i] == 'G'):
            num_string.append(1)
        if(string[i] == 'C'):
            num_string.append(2)
        if(string[i] == 'T'):
            num_string.append(3)

    return num_string
            
def get_similarity_num(tmp_string1, tmp_string2, alignment):

    string1 = '_' + tmp_string1                     
    string2 = '_' + tmp_string2
    #alignment1 = []
    #alignment2 = []
    #print string1
    #print string2
    m = len(string1)
    n = len(string2)

    num_string1 = convert_str_to_num(string1)
    num_string2 = convert_str_to_num(string2)
    #print num_string1
    #print num_string2
    
    #creating data tables for alignment value, alignment characters and L reset data
    data = []
    for i in xrange(m):    
        data.append([])
        for j in xrange(n):
            data[i].append(0)
    
    if alignment == 1:
        align1_data = []
        for i in xrange(m):    
            align1_data.append([])
            for j in xrange(n):
                align1_data[i].append('')

        align2_data = []
        for i in xrange(m):
            align2_data.append([])
            for j in xrange(n):
                align2_data[i].append('')

    L_data = []
    for i in xrange(m):    
        L_data.append([])
        for j in xrange(n):
            L_data[i].append(0)

    #presetting all already known values in all tables
    data[0][0] = 0                                  #set data at [0][0] = 0

    L = 1                                           #preset data table values for first column
    for i in xrange(L,m):
        data[i][0] = 0 #-(.20+.05*(L-1))
        L += 1
    L = 1                                           #preset data table values for first row
    for i in xrange(L,n):
        data[0][i] = 0 #-(.20+.05*(L-1))
        L += 1
        
    L = 1                                           #preset L_data table values to 0 for first column
    for i in xrange(L,m):
        L_data[i][0] = 1
    for i in xrange(L,n):                           #preset L_data table values to 0 for first row
        L_data[0][i] = 1

        
    if alignment == 1:                                                #preset align1_data and align2_data
        for i in xrange(1,m):
                align1_data[i][0] = align1_data[i-1][0]+string1[i]
                align2_data[i][0] = align2_data[i-1][0]+'_'

        for j in xrange(1,n):
                align2_data[0][j] = align2_data[0][j-1]+string2[j]
                align1_data[0][j] = align1_data[0][j-1]+'_'

##    for i in xrange(m):
##        print align1_data[i]
##    print '\n'
##    for i in xrange(m):
##        print align2_data[i]

    for i in xrange(m):
        for j in xrange(n):
            if(i != 0) and (j != 0):
                if(i+1 < m) and (j+1 < n):
                    L_reset = 0  
                elif(L_data[i-1][j]>0):     
                    L_reset = -.20                  
                else:                            
                    L_reset = -.05
                if alignment == 1:
                    align1_data[i][j]=align1_data[i-1][j]+string1[i]
                    align2_data[i][j]=align2_data[i-1][j]+'_'
                maximum = data[i-1][j]+L_reset       
                
                if(i+1 < m) and (j+1 < n):
                    L_reset = 0                                
                elif(L_data[i][j-1]>0):           
                    L_reset = -.20                
                else:                
                    L_reset = -.05
                if(data[i][j-1]+L > maximum):
                    if alignment == 1:
                        align2_data[i][j]=align2_data[i][j-1]+string2[j]
                        align1_data[i][j]=align1_data[i][j-1]+'_'
                    maximum = data[i][j-1]+L_reset
                                                    
                if(data[i-1][j-1]+delta_table[num_string1[i]][num_string2[j]] > maximum):
                    if alignment == 1:                    
                        align1_data[i][j]=align1_data[i-1][j-1]+string1[i]
                        align2_data[i][j]=align2_data[i-1][j-1]+string2[j]
                    maximum = data[i-1][j-1]+delta_table[num_string1[i]][num_string2[j]]
                    L_data[i][j] = 1
                data[i][j] = maximum

##    print 'data'            
##    for i in range(m):
##        print data[i]
##    print 'align1_data'
##    for i in xrange(m):
##        print align1_data[i]
##    print 'align2_data'
##    for i in xrange(m):
##        print align2_data[i]
    
#    print 'alignment1:', align1_data[m-1][n-1]
#    print 'alignment2:', align2_data[m-1][n-1]
#   print 'similarity value:', data[m-1][n-1]

    if alignment == 1:
        return data[m-1][n-1], align1_data[m-1][n-1], align2_data[m-1][n-1]
    else:
        return data[m-1][n-1]                    
                

#main..

database = sys.argv[1]
query = sys.argv[2]
num_of_sequences = int(sys.argv[3])
alignment = int(sys.argv[4])

query_text = ""
f = open(query, 'r')
for line in f:
   query_text = line.strip()
f.close()

f = open(database, 'r')
db_array = []
for line in f:
   db_array.append( line.strip() )
f.close()


delta_table = []
delta_table.append([1.00, -.10, -.10, -.15])
delta_table.append([-.10, 1.00, -.15, -.10])
delta_table.append([-.10, -.15, 1.00, -.10])
delta_table.append([-.15, -.10, -.10, 1.00])

max_val = 0.0
lifeform = ""
string1 = ""
string2 = ""

h = []

i = 0
while i < len(db_array):
   lifeform = db_array[i]
   if alignment == 1:
       max_val, string1, string2 = get_similarity_num(db_array[i+1], query_text, alignment)
       heappush(h, (max_val, lifeform, string1, string2))
   else:
       max_val = get_similarity_num(db_array[i+1], query_text, alignment)
       heappush(h, (max_val, lifeform))
#   max_val, string1, string2 = get_similarity_num(string1, string2)
   i = i + 2

if num_of_sequences > len(db_array):
   num_of_sequences = len(db_array)

#sorted = []
#while i < num_of_sequences:
#   sorted.append(heappop(h))

#for i in range(0, num_of_sequences):
#print textwrap.wrap(s1, 80)
#print textwrap.wrap(s2, 80)

score = ""
name = ""
formatted1 = []
formatted2 = []

h.sort()

k = len(h) - 1
for i in range(0, num_of_sequences):
   if alignment == 1:
      score, name, s1, s2 = h[k]
   else:
      score, name = h[k]
   k = k - 1
   print str(i) + " * " + str(score) + " * " + name[1:]
   if alignment == 1:
      formatted1 = textwrap.wrap(s1, 80)
      formatted2 = textwrap.wrap(s2, 80)
      for j in range(0, len(formatted1)):
         print formatted1[j]
         print formatted2[j] + "\n"


#max_val = get_similarity_num(string1, string2)
#print max_val
