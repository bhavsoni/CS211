CC = gcc
CCFLAGS = -ansi -pedantic -Wall -std=c99 -lm

all: y86emul.c
	$(CC) $(CCFLAGS) -o y86emul y86emul.c

y86emul: y86emul.c y86emul.h
	$(CC) $(CCFLAGS) -o y86emul y86emul.c

clean:
	rm -f y86emul