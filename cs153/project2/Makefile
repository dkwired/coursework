
CC=g++

all: mystrace 

observer: mystrace.o
	$(CC) mystrace.o -o mystrace

main.o: mystrace.cc
	$(CC) -c mystrace.cc

clean:
	rm -rf *o mystrace
