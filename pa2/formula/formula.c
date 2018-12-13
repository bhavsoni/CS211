#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<sys/time.h>
#include "formula.h"
#include "nCr.h"
//#include "nCr.c"


int main(int argc, char *argv[]){

	//declare beginning time and end time for time required
	struct timeval begin;
	struct timeval end; 
	gettimeofday(&begin, NULL);
	int timeRequired; 

	int exponent; 
	int coeff; 

	//counters
	int i;
	int j;


	if(strcmp(argv[1], "-h")==0){
		printf("Usage: formula <postive integer>\n");
		return 0;
	}

	if(argc >= 3){
		fprintf(stderr, "%s\n", "Error - Invalid amount of arguments (either too many or not enough)" );
		return 0;
	}

	if(atoi(argv[1]) < 0){
		fprintf(stderr, "%s\n", "Error - Argument must be postive \n" );
	}

	for(i =0; i < strlen(argv[1]); i++){
		if(!isdigit(argv[1][i])){
			fprintf(stderr, "%s\n", "Error - Must be a postive integer");
			return 0;
		}
	}

	exponent = atoi(argv[1]);


	if (exponent == 0){
		printf("(1 + x)^%d = 1", exponent);
		gettimeofday(&end, NULL);
		timeRequired = (end.tv_sec*1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec);
		printf("\nTime Required: %d microsecond\n", timeRequired);
		return 0;
	}

	
	printf("(1 + x)^%d = 1", exponent);

	//loop beigns printing out the expanded function 
	//for loop goes from counter j to exponent and prints out expanded form using the nCr fromula
	//error outputs if coefficient is a negative number or 0 which is an OVEFLOW. Outputs answwer to =1 to indicate failure 
	for(j=1; j<=exponent; j++){
		coeff = nCr(exponent, j);
		if(coeff <= 0){
			fprintf(stderr, "%s\n", "Error - OVERFFLOW (Output is = 1 due to overflow)" );
			return 0;
		} 
		else {
			printf(" + %d*x^%d", coeff, j);
		}

	}

	printf("\n");

	gettimeofday(&end, NULL);

	timeRequired = (end.tv_sec*1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec);
	printf("Time Required: %d microsecond\n", timeRequired);

	return 0; 

	

}