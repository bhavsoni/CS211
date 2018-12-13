#ifndef FORMAT_H_ //include guard
#define FORMAT_H_

typedef union Number {
    int i;
    float f;
} Num;

char* flip(char *x);

int binToInt(char * str);

static void get_float_digit(float, char*, int*, float*);

static void append(char*, char);

void floatToASCII( float x, char*);

void intToDecASCII(int, char*);

#endif //FORMAT_H_
