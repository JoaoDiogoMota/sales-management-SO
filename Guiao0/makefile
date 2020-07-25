CC = gcc
CFLAGS = -Wall -g

program: program.o operators.o

operator.o:operators.h operators.c

program.o: operators.h program.c

clean: 
	rm -f program *.o