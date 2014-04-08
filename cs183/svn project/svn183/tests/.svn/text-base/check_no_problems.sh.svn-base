#! /bin/bash

cd ..

passcheck.sh ./tests/test.txt

if [[ $? -eq $((0)) ]]
	then echo "no errors"
elif [[ $? -eq $((1)) ]]
	then echo "expected return value of 0, got 1"
else
	echo "expected no standard error, got"
	echo "$?"
fi
