#! /usr/bin/python

import sys
import os.path

dir = str(sys.argv[1])

try:
	if os.path.exists(dir):
		path = os.path.abspath(os.path.join(dir, os.path.pardir))
		path = path + "/" + dir
		for root, dirs, files in os.walk(path):
			for file in files:
				fname = os.path.join(path, file)
				os.chmod(fname, 711)
	else:
		raise Exception 
except Exception:
	print dir, 'directory does not exist.'
	os.abort()
