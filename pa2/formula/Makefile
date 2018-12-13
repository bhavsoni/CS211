CC = gcc
CCFLAGS = -Wall -ansi -pedantic

formula: formula.c formula.h nCr.h nCr.s
	$(CC) $(CCFLAGS) -o formula formula.c nCr.s


clean:
	rm -f formula
	rm -f *.o