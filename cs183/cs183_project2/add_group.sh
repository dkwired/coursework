#! /bin/bash

if [ $2 == "-n" -o $2 = "-g" ]
then
	echo "group name not present"
	exit 1
fi

if [ -z "$4" ]
then
	echo "group id not supplied"
	exit 1
fi

GNAME_CHECK=`egrep -i "^$2" /etc/group`

if [[ $GNAME_CHECK ]]
then
	echo "group name found"
	exit 1
fi

GUID_CHECK=`id -G | grep $4`

if [[ $GUID_CHECK ]]
then
	echo "group id found"
	exit 1
fi

if [[ $2 =~ [a-zA-Z]+[a-zA-Z0-9]* ]]
then
	echo "name is okay"
else
	echo "ERROR: name is not alphanumeric"
	exit 1
fi

if [[ $4 =~ [0-9] ]]
then
	echo "gid is okay"
else
	echo "ERROR: gid is not numeric"
	exit 1
fi 

if [ $4 -ge 0 -a $4 -le 65535 ]
then
	echo "gid is between 0 and 65535"
else
	echo "ERROR: gid is not between 0 and 65535"
	exit 1
fi

NOW=$(date +"%s")

cp /etc/group /etc/group.$NOW

groupadd $2 --gid $4
