CC = gcc
CCFLAGS = -ansi -pedantic -Wall -std=c99 -lm

all: calc.c format.c
	$(CC) $(CCFLAGS) -o calc calc.c
	$(CC) $(CCFLAGS) -o format format.c

calc: calc.c calc.h
	$(CC) $(CCFLAGS) -o calc calc.c

format: format.c format.h
	$(CC) $(CCFLAGS) -o  format format.c 

clean:
	rm -f calc
	rm -f format 