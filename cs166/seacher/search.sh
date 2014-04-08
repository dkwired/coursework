#! /bin/bash

if [[ $# < 2 ]]; then
	echo "You must provide: <index_dir> <query>"
	exit 1
fi

MY_CLASSPATH=/my_apache/lucene-3.6.2/lucene-core-3.6.2.jar

java -cp ${CLASSPATH}:${MY_CLASSPATH} SearchRunner $1 $2
