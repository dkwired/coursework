#!/bin/sh
cat /etc/passwd | grep "/home" | cut -d: -f1 > users.txt
cat /etc/group | grep "/home" | cut -d: -f1 >> users.txt
id $(<users.txt)
