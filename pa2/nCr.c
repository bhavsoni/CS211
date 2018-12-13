#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "nCr.h"


extern int Factorial(int n){
  if(n == 0){
    return 1;
  }
  else{
    return n * Factorial(n-1) ;
  }
}

extern int nCr(int n, int r){
  int result;
  result = Factorial(n) / (Factorial(r) * Factorial((n-r)));
  return result;
}