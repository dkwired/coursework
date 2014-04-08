#David Klein
#860880864
#lab 3

#!/bin/bash

#1. Find all files in /bin, /sbin, /usr/bin, and /usr/sbin that are setuid and owned by root.
find /bin -perm -u+s -user root -type f
find /sbin -perm -u+s -user root -type f
find /usr/bin -perm -u+s -user root -type f
find /usr/sbin -perm -u+s -user root -type f

#Gaining access to these files is an easy way to escalate privileges to root access.

#2. Find all files in /var that have changed in the last 20 minutes.
find /var -mmin -20

#3. Find all files in /var that are regular files of zero length.
find /var -size 0 -type f

#4. Find all files in /dev that are not regular files and also not directories.
find /dev/ -not -type f | ls -l

#5. Find all directories in /home that are not owned by root. 
chmod 711 $(find /home/ -type d -not -user root)

#6. Find all regular files in /home that are not owned by root.
chmod 755 $(find /home/ -type d -not -user root)

#7. Find all files (of all types) in /etc that have changed in the last 5 days.
find /etc/.* -mtime 5
