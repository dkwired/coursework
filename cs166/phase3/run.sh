#! /bin/bash

if [[ $# < 4 ]]; then
	echo "You must provide: <dbname> <dbport> <user> <password>"
	exit 1
fi

MY_PATH=edu/ucr/cs166
MY_CLASSPATH=lib/pg73jdbc3.jar:${MY_PATH}
JAVAHOME=/usr/csshare/pkgs/jdk1.6.0_02/bin/
export JAVAHOME

cd java
make

java -cp $CLASSPATH:$MY_CLASSPATH $MY_PATH/MovieNet $1 $2 $3 $4
