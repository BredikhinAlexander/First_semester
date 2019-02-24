//
// Created by Александр on 17.10.2018.
//

#ifndef MY_PROJECT_STACK_H
#define MY_PROJECT_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>





//  screaming printf

//#define MEO
//
//#ifdef MEOW
//#define PRINTF printf
//#else
//#define PRINTF if(0) printf
//#endif
//


// CARCKIYassert

#define DEBUG

#ifdef DEBUG
#define CARCKIYassert(check)                     \
    do                                           \
    {                                            \
        if ((check) < 0)                         \
        {                                        \
            printf("\n ======= FIASCO ======="); \
            printf( "\n                        \n\
############# ERROR in: %s                     \n\
############# file: %s                         \n\
############# line: %d                         \n\
############# function: %s\n ",                  \
#check, __FILE__, __LINE__, __FUNCTION__);       \
            stackDump(s);                        \
abort();                                         \
        }                                        \
    } while(0)
#else
#define CARCKIYassert(check) assert(check)
#endif


// unittest

static int num = 0;
#define UNITTEST(what, ref)                                                                  \
    do                                                                                       \
    {                                                                                        \
        ++(num);                                                                             \
                                                                                             \
        if ((what) != (ref))                                                                 \
            printf("unittest %d  FAILED: %s = %d, expected %d\n", num, #what, (what), ref);  \
        else                                                                                 \
           printf("unittest %d  PASSED\n", num);                                               \
    } while(0)
//писать в другом стиле

typedef struct stack
{
    double canary1;
    double canary2;
    int *data;
    double canary3;
    int size;
    double canary4;
    int capacity;
    double canary5;
    int hashsum;
    double canary6;
} stack;


//! The fuction for create stack
//! @param [in] s pointer to steck struct
void stackCtor(struct stack* s);


//! The fuction for delete stack
//! @param [in] s pointer to steck struct
void stackDtor(struct stack* s);


//! The fuction for check stack
//! @param [in] s pointer to steck struct
//! @return ERROR_CODE or 1 if all OK
int stackOK(struct stack* s);


//! The fuction for memory data relocation
//! @param [in] s pointer to steck struct
void stackReduceSize(struct stack* s);


//! The fuction for memory data relocation
//! @param [in] s pointer to steck struct
void stackIncreaseSize(struct stack* s);


//! The function for pushing element to stack
//! @param [in] s pointer to steck struct
//! @param [in] val val - element for pushing
void stackPush(struct stack* s, int val);


//! The function for pop element from stack
//! @param [in] s pointer to steck struct
int stackPop(struct stack* s);


//! The function return size of stack
//! @param [in] s pointer to steck struct
int stackSize(struct stack* s);


//! The function, which print all about stack
//! @param [in] s pointer to steck struct
void stackDump(struct stack* s);


//! check all canary check of stack
//! @param [in] s pointer to steck struct
int cannaryOK (struct stack* s);


//! compares two double numbers
//! @param [in] x1 first number
//! @param [in] x2 second number
//! @return true if a == b, false if a != b
int isEqual (double x1, double x2);


//! create values of canarys and return value canaryNum
// @param [in] canaryNum number of canary
double canaryValue (int canaryNum);


//! count hashsum of our stack
//! @param [in] s pointer to steck struct
int countHashsum (struct stack* s);


#endif //MY_PROJECT_STACK_H
