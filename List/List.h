

#ifndef SPICOK_LIST_H
#define SPICOK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>




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
            printf("%d\n", List_error);          \
            stackDump(s);                        \
abort();                                         \
        }                                        \
    } while(0)
#else
#define CARCKIYassert(check) assert(check)
#endif




int List_error = 0;
enum list_error
{
    No_error     = 0,
    Calloc_error = -1,
    Num_error    = -2,
    Point_error  = -3,
    Order_error  = -4,
};


typedef struct List_Elem
{
    int value;
    struct List_Elem* next;
    struct List_Elem* prev;

} List_Elem ;


typedef struct List
{
    List_Elem* head;
    List_Elem* tail;
    int count;
} List ;

int list_ok(List* s);
int list_ctor (struct List *s);
struct List_Elem* list_elem_ctor();
void stackDump(List* s);
int list_dtor (struct List* s);
int list_elem_dtor(struct List_Elem* s);
List_Elem* add_front(List *s, int val);
List_Elem* add_back(List* s, int val);
List_Elem* find_num(List *s, int num);
List_Elem* add_after(List* s, int val, List_Elem* cur_el);
List_Elem* add_before(List* s, int val, List_Elem* cur_el);
int list_remove (List* s, List_Elem* cur_el);
int remove_front(List* s);
int remove_back(List* s);
List_Elem* find_val(List* s, int val);
void list_print(List* s);
void killer_elements(List* s);

#endif //SPICOK_LIST_H
