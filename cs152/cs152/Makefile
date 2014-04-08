
CC=g++

all: y.tab.o lex.yy.o
	$(CC) -o my_compiler y.tab.o lex.yy.o -lfl

test: all
	cat primes.min | my_compiler

y.tab.c: mini_l.y
	bison -v -d --file-prefix=y mini_l.y

lex.yy.c: main.lex
	flex main.lex

clean:
	rm lex.yy.o lex.yy.c y.tab.o y.tab.c my_compiler y.tab.h y.output
