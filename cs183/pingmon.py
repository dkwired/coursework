#! /usr/bin/python

# David Klein
# 860880864
# CS 183 HW4

import subprocess
import sys
import csv
import os
import time
import re

timestamp = int(time.time())

host = sys.argv[1]
filename = host + ".csv"

pathname = os.path.dirname(sys.argv[0])        
path = os.path.abspath(pathname)
filepath = path + "/" + filename

try:
        subprocess.check_call(["ping", "-w", "1", host], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pingcheck = 1
except subprocess.CalledProcessError:
        pingcheck = 0

ping = subprocess.Popen(
    ["ping", "-w", "3", host],
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE
)

pattern = re.compile("rtt min/avg/max/mdev = (\d+.\d+)/(\d+.\d+)/(\d+.\d+)/(\d+.\d+)(\s)(\w+)")
for line in ping.stdout:
	if pattern.search(line):
		match = pattern.match(line).groups()
		if pingcheck == 1:
			pingavg = match[1]
			pingtime = match[5]
	else:
		pingavg = ''
		pingtime = ''

with open(filename, 'a') as csvfile:
        csventry = csv.writer(csvfile)
        csventry.writerow([timestamp, pingcheck, pingavg, pingtime])
