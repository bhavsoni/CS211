#include<stdio.h>
#include<stdlib.h>
#include "mystery.h"

int num[200];

int add(int a, int b){
	return a + b;
}

int compute_fib(int x){
	//if the value is -1 at the index of the given input of the array then continue to follow fibonacci
	//else return value of array at the index of given argument 
	if(num[x] == -1){ 
		if(x == 0){			//fib of 0 is 0
			num[x] = 0;		//assigns value of array at index 0 to 0
		}
		else if( x == 1){	//fib of 1 is 1
			num[x] = 1;		//assigns the value of array at index 1 to 1
		}
		else{
			num[x] = add(compute_fib(x-2),compute_fib(x-1));	//recursive call of fib with use of add function 
		}
	}

	if(num[x] != -1){
		return num[x];		//if value of array at index of given argument is not -1, then return value of that array at index x
	}

	return num[x];
}

int main (int argc, char **argv){
	int n;
	
	//counter 
	int i;
	
	//converts argument string into integer
	n = atoi(argv[1]);

	//loops through the array and assigns negative one through 199 indices 
	for(i=0; i<=199; i++){
		num[i] = -1;
	}

	printf("Value:	%d\n", compute_fib(n));
	return 0; 
}