#! /bin/bash

if [[ $# < 2 ]]; then
	echo "You must provide: <doc_dir> <index_out_dir>"
	exit 1
fi

MY_CLASSPATH=/my_apache/lucene-3.6.2/lucene-core-3.6.2.jar:../jsoup-1.7.2.jar

java -cp ${CLASSPATH}:${MY_CLASSPATH} IndexRunner $1 $2
