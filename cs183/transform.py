#! /usr/bin/python
import time
import sys
import os
import shutil
import re

config_controller = str(sys.argv[1])
config_file = str(sys.argv[2])
target_controller = str(sys.argv[3])
target_file = str(sys.argv[4])

if config_controller != '-c':
	sys.stderr.write('must include -c before config file\n')
	sys.exit(1)

if target_controller != '-t':
	sys.stderr.write('must include -t before target file\n')
	sys.exit(1)

if not os.path.isfile(config_file):
	sys.stderr.write('config file not a regular file\n')
	sys.exit(2)

if not os.path.isfile(target_file):
	sys.stderr.write('target file not a regular file\n')
	sys.exit(2)

ttime = time.strftime("%Y%m%d%H%M%S", time.localtime())

f_target = open(target_file, "a+")
f_config = open(config_file, "r")

backup_file = target_file + "." + ttime

try:
	shutil.copy(target_file, backup_file)
except Exception, e:
	print 'Failed backing up target_file'

config_regex = re.compile('[A-Z]+[=]+')
target_regex = re.compile('[$][A-Z]+[$]')

replacestring = ""

for line in f_target:
	match = target_regex.search(line)
	if match:
		string = match.group()
		string = string[1:-1]
		string1 = string + "="
		for line2 in f_config:
			temp_regex = re.compile(string1)
			match2 = temp_regex.search(line2)
			if match2:
				temp2_regex = re.compile('[=][A-Z]+\n')
				match3 = temp2_regex.search(line2)
				replacestring = match3.group()
				replacestring = replacestring[1:]
				target_regex.sub(replacestring, string)

f_target.close()
f_config.close()
