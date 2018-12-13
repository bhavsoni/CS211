#include<stdio.h>
#include<stdlib.h>
#include "mystery.h"

int num[200];

int add(int a, int b){
	return a + b;
}

int compute_fib(int x){
	int a;
	int b;

	if(num[x] == -1){
		if(x == 0){
			num[x] = 0;
		}
		else if( x == 1){
			num[x] = 1;
		}
		else{
			num[x] = add(compute_fib(x-2),compute_fib(x-1));
		}
	}

	if(num[x] != -1){
		return num[x];
	}

	return num[x];
}

int main (int argc, char **argv){
	int n;
	int i;
	n = atoi(argv[1]);

	for(i=0; i<=199; i++){
		num[i] = -1;
	}

	printf("Value: %d\n", compute_fib(n));
	return 0; 
}