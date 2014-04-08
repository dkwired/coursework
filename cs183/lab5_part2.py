#! /usr/bin/python

import os
import re

directory = '/etc/'
regex = re.compile(r'(?:[\d]{1,3})\.(?:[\d]{1,3})\.(?:[\d]{1,3})\.(?:[\d]{1,3})$')
for root, dirs, files in os.walk(directory):
	for file in files:
		if file.endswith('.conf'):
			path = directory+file
			f = open(path, 'r')
			data = f.read()
			for line in data:
				if regex.search(line):
					print file

