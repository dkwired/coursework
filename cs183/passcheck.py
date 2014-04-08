#! /usr/bin/python
#David Klein
#860880864
#CS 183
#HW3

import sys
import re

list = []

try:
	f = open(str(sys.argv[1]))
	pattern = re.compile('[a-z]+[:][x][:]\d{1,4}[:]\d{1,4}[:]')
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
	matching = [s for s in list if entry[3] in s > 1]
for entry in list:
        matching2 = [s for s in list if entry[0] in s > 1]

if not matching and not matching2:
	print 'no errors'
	sys.exit(0)
else:
	for entry in matching:
		msg = 'DUP_UID '+':'.join(entry)
		sys.stderr.write(msg)
	for entry in matching2:
		msg2 = 'DUP_USERNAME '+':'.join(entry) 
		sys.stderr.write(msg2)
	sys.exit(2)
