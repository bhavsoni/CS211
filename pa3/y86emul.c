#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include "y86emul.h"

//converts hex into decimal
int hex_Dec(char* x){
	int result;
	result =0;

	int i;
	int length; 
	length = strlen(x);

	for(i = length-1; i>=0; i--){
		if(isdigit(x[i])){
			result += (x[i]-48) * ((int)pow(16, length-(i+1)));
		}else{
			if(x[i] == 'a' || x[i] == 'A'){
				result += 10*((int)pow(16,length- (i+1)));
			}
			else if(x[i] == 'b' || x[i] == 'B'){
				result += 11*((int)pow(16,length- (i+1)));
			}
			else if(x[i] == 'c' || x[i] == 'C'){
				result += 12*((int)pow(16,length- (i+1)));
			}
			else if(x[i] == 'd' || x[i] == 'D'){
				result += 13*((int)pow(16,length- (i+1)));
			}
			else if(x[i] == 'e' || x[i] == 'E'){
				result += 14*((int)pow(16,length- (i+1)));
			}
			else if(x[i] == 'f' || x[i] == 'F'){
				result += 15*((int)pow(16,length- (i+1)));
			}
		}
	}
	return result; 
}

//gets the two bytes for the op code - hex 
int twoB(char * s, int x){
	
	char * two = (char *) malloc(3);
	
	
	two[0] = s[x];
	two[1] = s[x + 1];
	two[2] = '\0';
	
	int result = hex_Dec(two);
	
	return result;
}


int main(int argc, char **argv)
{
    if (argc != 2){
		fprintf(stderr, "%s\n","ERROR: incorrect argument");
		return 0;
	}
	
	if (argv[1][0]=='-' && argv[1][1]=='h'){
			printf("Usage: y86emul [-h] <y86 input file>\n");
			return 0;
	}
	
   
    char const* const fileName = argv[1]; 
    
    char type[] = "r\0";
    FILE* file = fopen(fileName, type);

    if(file == NULL){
    	fprintf(stderr, "%s\n", "Error: No file found");
    	return 0;
    }
    
    char line[1000];
    
    unsigned char *cpumem;
    
    int reg[8] = {0,0,0,0,0,0,0,0};
    
    /*
    Registers: 
	    0 - eax
		1 - ecx
		2 - edx
		3 - ebx
		4 - esp
		5 - ebp
		6 - esi
		7 - edi
    */

    int begin;

    //flags
	unsigned int OF = 0;
	unsigned int ZF = 0;
	unsigned int SF = 0;

    
    int containsText=0;
	
	int containsSize=0;

	int progcount =0; 

	char temp[100];

	char arg1[1000];

	char arg2[1000];

	unsigned int* hexaddr=malloc(256);

	//readb
	char readchar = '\0';
   
    while (fgets(line, 1000, file)) {

        
        sscanf(line, "%s %[^\r\n]", temp,arg1);

        char *token = strtok(line, "\t\r\n");

		
        //.size directive
        if(strcmp(token, ".size") == 0){	
        	containsSize++;
			cpumem = (unsigned char*)malloc(hex_Dec(arg1)*sizeof(char));
		}
		
		//.string directive
		else if(strcmp(token, ".string") == 0){	
			sscanf(arg1, "%x %[^\r\n]",hexaddr,arg2);

			unsigned char* tmp = cpumem+*hexaddr;

			for(int i = 0; i<strlen(arg2)-1; i++){
				tmp[i] = (arg2+1)[i];
			}
			
		}
		
		//.long directive
		else if(strcmp(token, ".long") == 0){	
			sscanf(arg1, "%x %[^\r\n]",hexaddr,arg2);
			
			unsigned int temp = atoi(arg2);

			unsigned char* tmp = cpumem+*hexaddr;

			for(int i=0; i<sizeof(int); i++){
				tmp[i] = (&temp)[i];
			}
		}
		
		//.byte directive
		else if(strcmp(token, ".byte") == 0){	
			sscanf(arg1, "%x %[^\r\n]",hexaddr,arg2);
			
			unsigned int yuhhurd = hex_Dec(arg2);

			unsigned char* tmp = cpumem+*hexaddr;

			for(int i=0; i<1; i++){
				tmp[i] = (&yuhhurd)[i];
			}
		}
		
		//.text directive
		else if(strcmp(token, ".text") == 0){	
			
			containsText++;
			sscanf(arg1, "%x %[^\r\n]",hexaddr,arg2);
			
			progcount = *hexaddr;
			//printf("%d\n", begin);
			
			int i=0;
			while(i<strlen(arg2)) {
				unsigned int twob = twoB(arg2,i);
				i+=2;
				
				unsigned char* tmp = cpumem+*hexaddr;

				for(int i=0; i<1; i++){
					tmp[i] = (&twob)[i];
				}
				
				*hexaddr+=1;
			}
		}

		else {
			fprintf(stderr, "%s\n", "Invalid Directive");
			printf("%s\n", "INS");
			return 0;

		}
	}
	
	 
	if(containsSize != 1 || containsText != 1) {
		fprintf(stderr, "%s\n", "Error: No .size or .text instruction");
		return 0;
	}
	
	
	//progcount=begin;
	char go = 1;
	while(go==1){
		switch (cpumem[progcount]) {
			//nop
			case 0x00 :{
				
				progcount++;
				break;
			}

			//halt 
			case 0X10:{
				
				printf("%s\n", "Status: HLT");

				go = 0;
				//progcount++;

				break;
			}
			
			//rrmovl
			case 0x20:{

				unsigned int ra = (cpumem[progcount+1]);
				ra /=16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);
				
				reg[rb] = reg[ra];
				
				progcount +=2; 

				break;
			}
			
			//irmovl
			case 0x30:{
				int rb = cpumem[progcount+1];
				rb = rb%16;
				
				int value;

				value = cpumem[progcount+2] + (cpumem[progcount+3] <<8) + (cpumem[progcount+4] <<16) + (cpumem[progcount+5] <<24);
				
				reg[rb]=value;
				
				progcount+=6;

				break;
			}
			
			//rmmovl
			case 0x40:{

				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				unsigned int rb = (cpumem[progcount+1]);
				rb = rb%16;

				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);
				
				unsigned int temp = reg[rb] + displacement;

				memcpy(cpumem+temp,reg+ra,4);

				progcount +=6; 

				break;
				
			} 
			
			//mrmovl
			case 0x50: {

				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);

				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);

				unsigned int temp = reg[rb] + displacement;

				reg[ra] = cpumem[temp +0] + (cpumem[temp + 1] >> 8) + (cpumem[temp + 2] >> 16) + (cpumem[temp + 3] >> 24);

				progcount+=6;
				
				break;
			}

			//addl
			case 0x60:{
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);


				int value;
				value =reg[ra]+reg[rb];
				
				if( (reg[ra]>0 && reg[rb]>0 && value <0) ||  (reg[ra]<0 && reg[rb]<0 && value>0) ){
					OF = 1;
				} else{
					OF = 0;
				}
				
				ZF = (value ==0)?1:0;
				
				SF = (value < 0)?1:0;
				
				reg[rb]=value;

				progcount+=2;

				break;
			}
			
			//subl
			case 0x61:{
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);
				
				int value;
				value =reg[rb]-reg[ra];
				
				if( (reg[ra]<0 && reg[rb]>0 && value < 0) || (reg[ra]>0 && reg[rb]<0 && value > 0) ){
					OF = 1;
				}else{
					OF =0;
				}
				
				
				ZF = (value ==0)?1:0;
				
				SF = (value < 0)?1:0;
				
				reg[rb]=value;
				
				progcount+=2;

				break;
			}
			
			//andl
			case 0x62:{
				
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);
				
				int value;
				value =reg[ra] & reg[rb];
				
				OF = 0;

				ZF = (value == 0)?1:0;
				
				SF = (value < 0)?1:0;
				
				progcount+=2;

				break;
			}
			
			//xorl
			case 0x63:{
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);
			
				int value;
				value = reg[ra] ^ reg[rb];
				
				OF =0;
				
				ZF = (value ==0)?1:0;
				
				SF = (value < 0)?1:0;
				
				progcount+=2;

				break;
			}
			
			//mull
			case 0x64:{

				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);

				int value;
				value =reg[ra] * reg[rb];
				
				if( (reg[ra] > 0 && reg[rb] > 0 && value < 0) ||
					(reg[ra] < 0 && reg[rb] > 0 && value > 0) ||
					(reg[ra] > 0 && reg[rb] < 0 && value > 0) ||
					(reg[ra] < 0 && reg[rb] < 0 && value < 0) ){
					
						OF = 1;
				} else{
					OF =0;
				}
				
			
				reg[rb]=value;
				
				ZF = (reg[rb] ==0)?1:0;
				
				SF = (reg[rb] < 0)?1:0;
				
				
				progcount+=2;

				break;
			}
			
			//cmpl
			case 0x65: {
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);

				int value;
				value =reg[rb]-reg[ra];
				
				if( (reg[ra]<0 && reg[rb]>0 && value < 0) || (reg[ra]>0 && reg[rb]<0 && value > 0) ){
					OF = 1;
				}else{
					OF =0;
				}
				
				
				ZF = (value ==0)?1:0;
				
				SF = (value <0)?1:0;
				
				
				progcount+=2;

				break;
			}
			
			//jmp
			case 0x70: {
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				
				progcount= displacement;
				
				break;
			}
			
			//jle
			case 0x71: {
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				

				
				if( (SF ^ OF) == 1 || ZF ==1 ){
					progcount = displacement;
				}else{
					progcount+=5;
				}

				break;
				
			}
			
			//jl
			case 0x72: {
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);

				if( (OF ^ SF) == 1){
					progcount = displacement;
				}else{
					progcount+=5;
				}

				break;
			}
			
			//je
			case 0x73:{
				
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				
				
				
				if(ZF == 1){
					progcount=displacement;
				}
				else{
					progcount+=5;
				}
				
				break;
			}
			
			//jne
			case 0x74: {
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				

				if(!ZF){
					progcount=displacement;
				}
				else{
					progcount+=5;
				}
				
				break;
			}
			
			//jge
			case 0x75:{
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				

				if( !((SF ^ OF) && ZF==0) ){
					progcount=displacement;
				}
				else{
					progcount+=5;
				}
				
				break;
			}
			
			//jg
			case 0x76:{
				unsigned int displacement;
				
				displacement = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				
				
				if( !( ZF == 1 || (SF ^ OF) ) ){
					progcount=displacement;
				}
				else{
					progcount+=5;
				}
				
				break;
			}
			
			//call
			case 0x80: {

				reg[4] -= 4;					//decrease stack pointer

				int temp;

				temp = progcount+5;				//increase pc by 5 

				unsigned int destination;
				
				destination = cpumem[progcount +1] + (cpumem[progcount +2] << 8) +(cpumem[progcount +3] << 16) + (cpumem[progcount +4] << 24);
				
				//esp register
				cpumem[reg[4] + 0] = (temp & 0x000000ff);
				cpumem[reg[4] + 1] = (temp & 0x0000ff00) >> 8;
				cpumem[reg[4] + 2] = (temp & 0x00ff0000) >> 16;
				cpumem[reg[4] + 3] = (temp & 0xff000000) >> 24;
				
				
				progcount=destination;			//assign the new pc by the destination
				

				break;
			}
			
			//ret
			case 0x90: {
				int value;
				
				memcpy(&value, cpumem+reg[4],4); 		//copy previous value of pc
				
				reg[4]+=4;								//increase stack pointer 
				
				progcount=value;


				break;
			}
			
			//push
			case 0xa0:{
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				
				
				reg[4]-=4;
				cpumem[reg[4]+0] = reg[ra];
				cpumem[reg[4]+1] = (reg[ra] & 0x0000ff00)>>8;
				cpumem[reg[4]+2] = (reg[ra] & 0x00ff0000)>>16;
				cpumem[reg[4]+3] = (reg[ra] & 0xff000000)>>24;
				
				progcount+=2;

				break;
			}
			
			//popl
			case 0xb0:{
				
				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				
				reg[ra] = cpumem[reg[4]+0] + (cpumem[reg[4]+1] << 8) +(cpumem[reg[4]+2] << 16) + (cpumem[reg[4]+3] << 24);
				
				
				reg[4]+=4;
				
				progcount+=2;
				
				break;
			}
			
			//readb
			case 0xc0: {
				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				
				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);
				

				ZF = 0;
				
				if(1 > sscanf("%c", &readchar)){
					ZF = 1;
				}

				cpumem[reg[ra] + displacement] = readchar;
				
			
				progcount+=6;

				break;
			}
			
			//readl
			case 0xc1:{

				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				
				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);
				
				ZF =0;
				
				int temp = reg[ra]+displacement;
				
				char tempbuf[50];
				
				fgets(tempbuf, 4, stdin);
				
				if (tempbuf[0] == '\n') {
					ZF = 1;
				} else {
					ZF = 0;
					unsigned int word;
					word =  atoi(tempbuf);
					for(int i = 0; i<4; i++){
						(cpumem+temp)[i] = (&word)[i];
					}	
					
				}
				
				progcount+=6;
				break;
			}
			
			//writeb
			case 0xd0:{
				
				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				
				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);
				
				unsigned int temp = reg[ra] + displacement;
				
				printf("%c",cpumem[temp]);
				
				progcount+=6;
				
				break;
			}
			
			//writel
			case 0xd1:{
				unsigned int ra = cpumem[progcount+1];
				ra /=16;
				
				
				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);
				
				int value;
				
				memcpy(&value,cpumem+reg[ra]+displacement,4);

				printf("%d",value);
				
				progcount+=6;

				break;
			}
			
			//movsbl
			case 0xe0:{
				unsigned int ra = cpumem[progcount+1];
				ra /= 16;
				unsigned int rb = (cpumem[progcount+1] & 0x0f);

				unsigned int displacement;
				
				displacement = cpumem[progcount +2] + (cpumem[progcount +3]<< 8) +(cpumem[progcount +4] << 16) + (cpumem[progcount +5] << 24);

				int temp = reg[rb] + displacement;

				char b;

				for(int i=0; i<1; i++){
					(&b)[i] = (cpumem+temp)[i];
				}

				reg[ra] = (int)b;

				progcount+=6;


					break;
			}
			
			//if all else fails 
			default: {
				fprintf(stderr, "%s\n", "Error: Invlaid Instruction ");
				printf("%s\n","INS" );
				return 0;
			}
		}
	}
		
	progcount=0;

	
	
    fclose(file);
	free(cpumem);
	
    return 0;
}
