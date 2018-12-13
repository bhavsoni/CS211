#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"

//constant to declare the max and min ranges of the inputs

const  long  max_64b = 9223372036854775807;

const long min_64b =  -9223372036854775808; 

//overflow flag - used to detect overflow
int over_flow_flag = 0;

//detects incorrect base 
int incorrect_base_letter_input_flag = 0;

//constant delcares length of input is within 64 bits 
const int size = 64;

//converts string to the base given to 64b
//takes in str and base and sign
signed long string_to_base_64b(char* str, int base, int sign){
    //long long declared for 64 bits 
    long long  result = 0;
    int length = strlen(str);
    int pos = length-1;
    
    for(int x = 0; x<length; x++){

        if(str[x]<='9'&&str[x]>='0'){
            long long a = sign*(((str[x]-'0')+0)*((long long)pow(base,pos)));
            result+=a;
            
            //checks for overflow - if the result is greater or less than min or max values of 64bits
            if(result>max_64b||result<min_64b){
                over_flow_flag = 1;
                fprintf(stderr, "%s\n", "Error: overflow - Result either > or < 64bit range");
                return 0;
            }

            //for hex
        }else if(str[x]<='F'&&str[x]>='A'){
            long long a = (((str[x]-'A')+10)*((long long)pow(base,pos)));
            
            result+=a;
            
            //for hex 
        }else if(str[x]<='f'&&str[x]>='a'){
            long long a = (((str[x]-'a')+10)*((long long)pow(base,pos)));
            
            result+=a;
            
        }
       pos--;       //points to the next character in the string from right to left
    }
    return (long)result;
}

//converts the number to a string for 64
//computes the last n bits - so trailing 1's or 0's do not effect result
void num_to_str_64b(long num,  int base){

    //allocates 65 spaces for buffer for the 64 bit output
    char *output = (char*) malloc(65) ;
    output[64] = '\0';
    
    long index = 63;
    //ander is used to get the last n bits 
    long ander = ((long)(ceil(log(base)/log(2))));
    long shift = ander;
    
    long num_shift = 64/ander;
    //retain last n bits 
    ander = ((int)pow(2,ander))-1;
    
    for(long x = 0; x<num_shift; x++){
        
        if((num&ander)<=9){             //for other bases
            output[index]= (char)(((int)(num&ander))+'0');
        
        }else{                          //for hex 
            output[index]= (char)(((int)(num&ander)-10)+'A');
        }
        index--;
        num = num>>shift;           //shifts the number until last bits are retained 
    }
    if(base==8){                    ///for octal 
        if((num&1)<=9){
            output[index]= (char)(((int)(num&1))+'0');
            
        }else{
            output[index]= (char)(((int)(num&1)-10)+'A');
        }
    }
    
    printf("%s",&output[index+1]);
    
}
//converts to str but also checks for negative values 
void toStrNeg(long num){
  
    long long x = (long long) num;
    long long g = 1;
    if(x<-1){
        x = x*-1;
        printf("-d");
    }else{
        printf("d");
    }
    while(x/g!=0){
        
        g = g*10;
    }
    g = g/10;
    while(g!=0){
        char c = (char)((int)(x/g)+'0');
        printf("%c",c);
        x = x%g;
        g/=10;

    }
   printf("\n");
    
}

//checks validity of bases 
int check_base(char* number, char base){
    int len = strlen(number);
    if (base=='d'){             //decimal

        for(int x = 0; x<len; x++){
            if(number[x]<'0'|| number[x]>'9'){
                fprintf(stderr, "%s\n", "Type Error: invalid character for base");
                return 0;

            }
            

        }
        return 1;
    }
    if (base =='b'){            //binary
        if(len>size){
                over_flow_flag = 1;
                return 0;
            }
        for(int x = 0; x<len; x++){
            
            if(number[x]!='0'&& number[x]!='1'){
                fprintf(stderr, "%s\n", "Type Error: invalid character for base");
                return 0;

            }

        }
        return 1;

    }
    if(base=='o'){              //octal 
        if(size==64){           //for 64 bit inputs 
            if(len>22){
                over_flow_flag = 1;
                return 0;

            }else if(len==22 && (number[0]!='0'||number[0]!='1')){
                over_flow_flag = 1;
                return 0;
            }
        }
        if(size==32){           //for 32 bit inputs 
            if(len>11){
                over_flow_flag = 1;
                return 0;

            }else if(len==11 && (number[0]<'0'||number[0]>'3')){
                over_flow_flag = 1;
                return 0;
            }
            
        }
        for(int x = 0; x<len; x++){
            
                if(number[x]<'0'|| number[x]>'7'){
                    fprintf(stderr, "%s\n", "Type Error: invalid character for base");
                    return 0;

            }

            

        }
        return 1;

    }
    if(base =='x'){         //hex
        if(len > (size/4) ){
            over_flow_flag = 1;
            return 0;
        }
        for(int x = 0; x<len; x++){
            
                if((number[x]>='0'&&number[x]<='9')||(number[x]>='a'&&number[x]<='f')||(number[x]>='A'&&number[x]<='F')){
                    

                }else{
                    fprintf(stderr, "%s\n", "Type Error: invalid character for base");
                    return 0;
                }

            

        
        }
        return 1;

    }   

}

//calculates the necessary conversions and then proceeds to calculate it
int calc(char op, char* operand1 , char* operand2, char output_base){
    long op1, op2, result;
    
    //checks operands 
    if(op!='+' && op!='-' && op!='*'){
        fprintf(stderr, "%s\n", "Type Error: invalid operator");
        return 0;
    }

    if(operand1[0]=='-' && operand1[1]=='d'){
        if(check_base(&operand1[2],'d')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer\n" );
                
            }
            return 0;
        }
        op1 = string_to_base_64b(&operand1[2],10,-1);       //converts operand 1 to negative decimal
    }else if (operand1[0]=='d'){
        if(check_base(&operand1[1],'d')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer\n" );
                
            }
            return 0;
        }
        op1 = string_to_base_64b(&operand1[1],10,1);        //converts operand 1 to positve decimal

    }else if (operand1[0]=='o'){
        if(check_base(&operand1[1],'o')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer\n" );
                
            }
            return 0;
        }
        op1 = string_to_base_64b(&operand1[1],8,1);     //converts operand 1 to octal

    }else if (operand1[0]=='b'){
        if(check_base(&operand1[1],'b')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer\n" );
                
            }
            return 0;
        }
        op1 = string_to_base_64b(&operand1[1],2,1);     //converts operand 1 to binary

    }else if (operand1[0]=='x'){
        if(check_base(&operand1[1],'x')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op1 = string_to_base_64b(&operand1[1],16,1);    //converts operand 1 to hex 

    }else{
        fprintf(stderr, "%s\n", "Error: wrong base\n" );
        return 0;
    }
    if(operand2[0]=='-'&&operand2[1]=='d'){
        if(check_base(&operand2[2],'d')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op2 = string_to_base_64b(&operand2[2],10,-1);
    }else if (operand2[0]=='d'){
        if(check_base(&operand2[1],'d')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op2 = string_to_base_64b(&operand2[1],10,1);

    }else if (operand2[0]=='o'){
        if(check_base(&operand2[1],'o')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op2 = string_to_base_64b(&operand2[1],8,1);

    }else if (operand2[0]=='b'){
        if(check_base(&operand2[1],'b')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op2 = string_to_base_64b(&operand2[1],2,1);

    }else if (operand2[0]=='x'){
        if(check_base(&operand2[1],'x')==0){
            if(over_flow_flag==1){
                fprintf(stderr, "%s\n", "Error: operand(s) cannot fit 64 bit integer" );
                
            }
            return 0;
        }
        op2 = string_to_base_64b(&operand2[1],16,1);

    }else{
        fprintf(stderr, "%s\n", "Error: wrong base" );
        return 0;
    }
    if(output_base!='b'&&output_base!='x'&&output_base!='d'&&output_base!='o'){
        fprintf(stderr, "%s\n", "Error: wrong output base" );
        return 0;

    }

    //operations and computations are stored in result
    if(op =='+'){
        result = op1 + op2;

    } else if (op=='-'){
        result = op1 - op2;

    }else if (op == '*'){
        result = (op1 * op2);
    }
    
    //throws overflow error
    if(over_flow_flag==1){

        fprintf(stderr, "%s\n", "Type Error: invalid character for base");
        return 0;
    }

    //base for the output 
    int base;
    if(output_base=='b'){
        base = 2;

    }
    if(output_base=='o'){
        base = 8;
    }
    if(output_base=='x'){
        base = 16;
    }
    if(output_base=='d'){
        base = 10;
        toStrNeg(result);
        return 0;

    }
    printf("%c",output_base);
    num_to_str_64b(result,  base);     //converts the output into the necessary base 
    return 0;

}

int main(int argc, char* argsv[]){
    if(argc < 5 ){
        printf("Error: invalid amount of arguments\n");
        return 0;
    }

    calc(argsv[1][0], argsv[2] , argsv[3], argsv[4][0]);
    printf("\n");
    return 0; 


}
