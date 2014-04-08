#! /usr/bin/python

import sys
import os
import re

list = []

try:
	f = open(str(sys.argv[1]))
	pattern = re.compile('\d*\:\d{1}\:\d{1,4}\:\d{1,4}\:\d*\:\d*\:\d*')
	for line in f: 
		#check to see if line does follow seven seg passwd convention
		match = pattern.search(line)
		if match:
			#take line and split it based on colon
			list.append(line.split(":"))
		else:
			sys.stderr.write('wrong file pattern')
			sys.exit(1)
	f.close()
except IOError:
	print 'error opening file'

for entry in list:
	temp = entry
	print temp[0]
	
# pointless comment
