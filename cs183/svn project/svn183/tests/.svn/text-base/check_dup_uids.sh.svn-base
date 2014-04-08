#! /bin/bash

cd ..

passcheck.sh ./tests/test2.txt

if [[ $? -eq $((0)) ]]
then
	echo "Error: expected return value of 2, got 0"
	exit 1
elif [[ $? -eq $((2)) ]]
then
	echo "Succesfully detected errors!"
	exit 0
fi
