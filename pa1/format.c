#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "format.h"

//flips the bits - where 1 = 0 and then 0= 1
char* flip(char *x){
    
    int length = strlen(x);
    int i =0;

    for(; i <= length; i++){
        if(x[i] == '0'){
            x[i] = '1';
        }
        else{
            x[i] = '0';
        }
    }
    return x;
}


//converts a binary sequece into an integer 
int binToInt(char * str){
    int exponent;
    int twoComp;
    int length; 
    int output;
    
    output = 0;
    length = strlen(str);
    exponent = length-1;
   
    
    if(str[0] == '1'){
        str = flip(str);
        twoComp = 1;
    }
    
    for(int i = (length-1); i > 0; i--){
        if(str[i] == '1'){
            output += pow(2, (exponent-i));   //adds to output string while binary converted to integer
        }
    }

    //need to add the twos complement by 1 then multiply by negative 1
    if(twoComp == 1){
        output += 1;
        output *= -1;
    }
    return output;
}


//implementing this intToDecASCII to complement Profesor's given function that converts floating point to ASCII string
// function converts integer to ASCII string
void intToDecASCII(int x, char * output){
  int i;
  int length;
  int neg;

  length = 12;    //length of array/buffer of size 12 is only necessary for int 

  char arr[length];

  neg = 0; 
  
  if(x < 0){
    neg = 1;
    x *= -1; //make it positive for now
  }
  

  //adds decimal represenation into array 
  i = (length -2);    //puts the least signifnicant digits right to left 
  
  for(; i >=0; i--){
    arr[i] = (x%10)+'0';
    x = x/10;
    if(x == 0){
      break;
    }
  }
  

  //add negative to negative number in the front of the array 
  if(neg == 1){
    i--;
    arr[i] = '-';
  }
  

  for(;i<length; i++){
    *output = arr[i];
    output++;
  }
}

/***** PROFESSOR RUSSELL'S PROVIDED CODE*****/

// Convert IEEE 32-bit floating point to printable ASCII string

// input:  x is the 32-bit input.
// output:  digit is the output ASCII character
// output:  pow10 is the original pre-normalization power of 10.
// output: remainder is x after subtracting the higi-digit value

static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
  int     p10;

  if ( x == 0.0 )
  {
    *digit = '0';     // digit is always '0'
    *pow10 = 0;
    *remainder = 0.0;
  }
  else
  {
    *pow10 = 0;     // start with 10^0
    while ( x >= 10.0 )   // reduce
    {
      x /= 10.0;    // large values get smaller
      *pow10 += 1;
    }
    while ( x < 1.0 )   // increase
    {
      x *= 10.0;    // small values get larger
      *pow10 -= 1;
    }
    *digit = '0';
    do {        // 10.0 > x >= 1.0
      x -= 1.0;
      *digit += 1;    // digit is always non-'0'zero
    } while ( x >= 1.0 );
    p10 = 0;
    while ( p10 > *pow10 )    // leading digit is now removed from x
    {
      x /= 10;
      p10 -= 1;
    }
    while ( p10 < *pow10 )
    {
      x *= 10;
      p10 += 1;
    }
    *remainder = x;
  }
}

static void
append( char * s, char c )
{
  char    buf[2];

  buf[0] = c;
  buf[1] = '\0';
  strcat( s, buf );
}


void
floatToASCII( float x, char * output )
{
  char    c;
  int   pow10, p10, plast;
  int   i;
  float   remainder;
  char    exponent[10];
  union Number  a;
  unsigned int  biasedExp;
  unsigned int  mantissa;
  int   sign;

  a.f = x;
  biasedExp = a.i >> 23 & 0x000000ff;
  mantissa = a.i & 0x007fffff;
  sign = a.i >> 31;

  // +/- inf, +/- Nan stuff here
  if(biasedExp == 0xff){
    if(mantissa == 0){
      if(sign != 0){
        strcpy( output, "ninf" );   //negative infinity
        return;
      } else {
        strcpy( output, "pinf" );   //positive infinity
        return;
      }
    } else{
      if(sign != 0){
        strcpy( output, "NaN" );    //negative NaN
        return;
      }
      else{
        strcpy( output, "NaN" );    //positive NaN
        return;
      }
      
    }
}


  output[0] ='\0';
  if ( x < 0.0 )
  {
    append( output, '-' );
    x = -x;         // make x positive
  }
  get_float_digit( x, &c, &pow10, &remainder );
  append( output, c );
  append( output, '.' );
  x = remainder;
  plast = p10 = pow10;      // pow10 set by get_float_digit()
  for ( i = 1 ; i < 7 ; i++ )   // 7 significant digits in 32-bit float
  {
    get_float_digit( x, &c, &p10, &remainder );
    if ( (plast - p10) > 1 )
    {
      append( output, '0' );  // fill in zero to next nonzero digit
      plast -= 1;
    }
    else
    {
      append( output, c );
      x = remainder;
      plast = p10;
    }
  }
  if ( pow10 < 0 )    // negative exponent
  {
    exponent[0] = 'e';
    intToDecASCII( pow10, exponent+1 );
  }
  else if ( pow10 < 10 )    // positive single-digit exponent
  {
    exponent[0] = 'e';
    exponent[1] = '+';
    exponent[2] = '0';
    intToDecASCII( pow10, exponent+3 );
  }
  else        // positive multi-digit exponent
  {
    exponent[0] = 'e';
    exponent[1] = '+';
    intToDecASCII( pow10, exponent+2 );
  }
  strcat( output, exponent );
}



int main(int argc, char *argv[]){
  char *str;
  int outputValue;
  char outputStr[32];

  //checks number of arguments
  if(argc != 3){
    fprintf(stderr, "%s\n", "Error: not enough arguments" );
    return 0;
  }

  str = argv[1];

  //checks length fits 32 bits
  if(strlen(str) != 32){
    fprintf(stderr, "%s\n", "Error: bit length greater than or less than 32");
    return 0;
  }

  //checks whether input is a sequence of 0 or 1 bits
  for(int x = 0; x<32; x++){
    if(str[x] != '1' && str[x] != '0'){
      fprintf(stderr, "%s\n", "Error: invalid input - not 1s and 0s");
      return 0;
    }
  }


  //for integer types
  if( strcmp(argv[2], "int") == 0){
    outputValue = binToInt(str);
    intToDecASCII(outputValue, outputStr);
    printf("%s\n", outputStr);
    return 0;
    }


  //for float types 
  else if(strcmp(argv[2], "float") == 0){
    
    //call function make into readable float ascii - PROFESSORS CODE
    outputValue = binToInt(str);
    float flo;
    memcpy(&flo, &outputValue, sizeof(outputValue));
    floatToASCII(flo, outputStr);

    //if negative 0
    if(flo == -0.0){
      printf("-%s\n", outputStr);
      return 0;
    }
    else{  
      printf("%s\n", outputStr);
      return 0;
    }

  }

  else{
    fprintf(stderr,"%s\n", "Error: invalid argument" );
    return 0;
  }

  return 0; 
}

