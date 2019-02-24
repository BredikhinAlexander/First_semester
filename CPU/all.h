

#ifndef MY_PROJECT_ALL_H
#define MY_PROJECT_ALL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "Stack.h"

#define FITCH

#ifdef FITCHA
#define PRINTF printf
#else
#define PRINTF if(0) printf
#endif

enum Type_error
{
    Open_error = -1,
    Calloc_error = -2,
    String_error = -3,
};

enum Num_registr
{
    ax = 1,
    bx = 2,
    cx = 3,
    dx = 4,
};

enum Commands
{
    #define DEF_CMD(name, num, ref) CMD_##name = (num),
    #include "commands0.h"
    #include "commands1.h"
    #include "commands2.h"
};
#undef DEF_CMD

int* read_file();
unsigned int calc_n_strings(FILE *file_in);
void write_file(int* mashine_code, int n_el);

#endif //MY_PROJECT_ALL_H
