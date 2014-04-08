#! /bin/bash

# get current working directory and add file to path
PWD="`pwd`"
FILE="$PWD/$1"

# check if the file has the correct syntax
for line in $FILE
do
	if [[ $line =~ "[a-z]+\:[x]+\:[0-9]+\:[0-9]+\:" ]]
	then
		exit 1	
	fi
done

# check for duplicate UIDS
UIDS=`awk -F":" 'list[$3]++{print $3}' $FILE`
# check for duplicate UNAMES
UNAMES=`awk -F":" 'list[$1]++{print $1}' $FILE`

# search FILE for UIDS
for entry in $UIDS
do
	UIDLIST=`grep -F $entry $FILE`
done

# search FILE for UNAMES
for entry in $UNAMES
do
        UNAMELIST=`grep -F $entry $FILE`
done

# output UNAMELIST if not empty
if [ -n "$UNAMELIST" ]
then
        echo "$UNAMELIST" | while read line ; do
                echo DUP_USERNAME $line 1>&2
        done
fi

# output UIDLIST if not empty
if [ -n "$UIDLIST" ]
then
	echo "$UIDLIST" | while read line ; do
		echo DUP_UID $line 1>&2
	done
	exit 2
else
# else there are no duplicates	
	exit 0
fi
