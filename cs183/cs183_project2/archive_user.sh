#! /bin/bash

if [ -z "$2" ]
then
	echo "no login supplied"
	exit 1
fi

LOGIN_CHECK=`egrep -i "^$2" /etc/passwd`

if [[ $LOGIN_CHECK ]]
then
	echo "login found"
else
	echo "login not found"
	exit 1
fi

NOW=$(date +"%s")

mv /home/login /arhived_homedirs/login.$NOW
passwd -d $2
