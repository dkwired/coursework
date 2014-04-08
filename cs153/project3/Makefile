
CC=g++

all: mypopen 

observer: mypopen.o
	$(CC) mypopen.o -o mypopen

main.o: mypopen.cc
	$(CC) -c mypopen.cc

clean:
	rm -rf *o mypopen
