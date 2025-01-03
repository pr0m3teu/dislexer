CFLAGS=-Wall -Wextra -std=c11 -pedantic -O1
CC=clang

.PHONY: all
all:
	make main
	make clean

main: main.c  lexer.o
	$(CC) -o ./build/lexer $(CFLAGS) main.c lexer.o

lexer.o: lexer.c lexer.h snur.o
	$(CC) -c $(CFLAGS) lexer.c 

.PHONY: clean
clean:
	rm -rf *.o
