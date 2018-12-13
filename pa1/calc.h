#ifndef CALC_H_
#define CALC_H_

signed long string_to_base_64b(char* str, int base, int sign);

void num_to_str_64b(long num,  int base);

void toStrNeg(long num);

int check_base(char* number, char base);

int calc(char op, char* operand1 , char* operand2, char output_base);

#endif