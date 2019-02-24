#include "List.h"


int list_ok(List* s)
{
    if (List_error != No_error)
    {
        return List_error;
    }
    if (s->count < 0)
    {
        List_error = Num_error;
        printf("FIASCO: count <0!!!");
    }
    if ((s->count != 0 && s->head == NULL) ||(s->count != 0 && s->tail == NULL))
    {
        List_error = Point_error;
        printf("FIASCO: pointer is NULL!!!");
    }
    if (s->head != NULL)
    {
        List_Elem* cur_el = s->head;
        while (cur_el != s->tail)
        {
            if(cur_el->next->prev != cur_el)
            {
                List_error = Order_error;
                printf("FIASCO: order of list fail!!!");
                break;
            }
            cur_el = cur_el->next;
        }
    }
    return List_error;
}




int list_ctor (struct List *s)
{
    assert(s);
    s->tail = NULL;
    s->head = NULL;
    s->count = 0;
    return List_error;
}

struct List_Elem* list_elem_ctor()
{
    List_Elem *s = (List_Elem*) calloc(1, sizeof(*s));
    if (s == NULL)
    {
        List_error = Calloc_error;
        return NULL;
    }
    s->next = NULL;
    s->prev = NULL;
    s->value = 0;
    return s;
}



void stackDump(List* s)
{
    list_print(s);
}



int list_dtor (struct List* s)
{
    s->tail = 0;
    s->head = 0;
    s->count = -666;
    return List_error;
}

int list_elem_dtor(struct List_Elem* s)
{
    assert(s);
    s->value = -666;
    free(s);
    s = NULL;
    return List_error;
}

List_Elem* add_front(List *s, int val)
{

    List_Elem* el = list_elem_ctor();
    el->value = val;
    if (s->count == 0)
    {
        el->next = NULL;
        el->prev = NULL;
        s->tail  = el;
        s->head  = el;
    }
    else
    {
        s->head->prev = el;
        el->next = s->head;
        s->head = el;
        el->prev = NULL;
    }
    s->count++;
    CARCKIYassert(list_ok(s));
    return el;
}

List_Elem* add_back(List* s, int val)
{
    CARCKIYassert(list_ok(s));

    List_Elem* el = list_elem_ctor();
    el->value = val;
    if (s->count == 0)
    {
        el->next = NULL;
        el->prev = NULL;
        s->tail  = el;
        s->head  = el;
    }
    else
    {
        s->tail->next = el;
        el->prev = s->tail;
        s->tail = el;
        el->next = NULL;
    }
    s->count++;

    CARCKIYassert(list_ok(s));

    return el;
}
List_Elem* find_num(List *s, int num)
{
    CARCKIYassert(list_ok(s));

    //printf("%d %d\n",num, s->count);
    if (num > s->count)
    {
        List_error = Num_error;
        return NULL;
    }
    List_Elem* cur_el = s->head;
    for (int i = 0; i < num - 1; i++)
    {
        cur_el = cur_el->next;
    }

    CARCKIYassert(list_ok(s));

    return cur_el;
}

List_Elem* add_after(List* s, int val, List_Elem* cur_el)
{

    CARCKIYassert(list_ok(s));

    List_Elem* el = list_elem_ctor();

    if (s->count == 1 || s->count == 0)
        return add_back(s, val);
    else
    {
        el->value = val;
        el->prev = cur_el;
        el->next = cur_el->next;
        cur_el->next->prev = el;
        cur_el->next = el;
        s->count++;
    }

    CARCKIYassert(list_ok(s));

    return el;
}

List_Elem* add_before(List* s, int val, List_Elem* cur_el)
{

    CARCKIYassert(list_ok(s));

    List_Elem* el = list_elem_ctor();

    if (s->count == 1 )
        return add_front(s, val);
    else
    {
        el->value = val;
        el->next = cur_el;
        el->prev = cur_el->prev;
        cur_el->prev->next = el;
        cur_el->prev = el;
        s->count++;
    }

    CARCKIYassert(list_ok(s));

    return el;
}

int list_remove (List* s, List_Elem* cur_el)
{
    CARCKIYassert(list_ok(s));

    cur_el->next->prev = cur_el->prev;
    cur_el->prev->next = cur_el->next;

    int val = cur_el->value;

    list_elem_dtor(cur_el);
    s->count--;

    CARCKIYassert(list_ok(s));

    return val;
}

int remove_front(List* s)
{
    CARCKIYassert(list_ok(s));

    List_Elem* cur_el = s->head;
    cur_el->next->prev = NULL;
    int val = cur_el->value;
    s->head = cur_el->next;
    list_elem_dtor(cur_el);
    s->count--;

    CARCKIYassert(list_ok(s));

    return val;
}

int remove_back(List* s)
{
    CARCKIYassert(list_ok(s));

    List_Elem* cur_el = s->tail;
    cur_el->prev->next = NULL;
    int val = cur_el->value;
    s->tail = cur_el->prev;
    list_elem_dtor(cur_el);
    s->count--;

    CARCKIYassert(list_ok(s));

    return val;
}

List_Elem* find_val(List* s, int val)
{
    CARCKIYassert(list_ok(s));

    List_Elem* cur_el = s->head;
    while (cur_el->value != val)
    {
        cur_el = cur_el->next;
    }
    CARCKIYassert(list_ok(s));
    return cur_el;
}

void list_print(List* s)
{
    printf("list.....\n");
    printf("head %8p tail %8p count %d\n",s->head,s->tail,s->count);
    List_Elem* cur_el = s->head;
    for (int i =0; i < s->count; i++)
    {
        printf("cur_el %8p   :    val %d  :  next %8p  :  prev %8p\n",cur_el, cur_el->value, cur_el->next, cur_el->prev);
        cur_el = cur_el->next;
    }
}

void killer_elements(List* s)
{
    List_Elem* cur_el = s->head;
    printf("%d\n", cur_el->value);
    for (int i = 0; i < s->count - 1; i++)
    {
        cur_el = cur_el->next;
        list_elem_dtor(cur_el);
    }
    list_elem_dtor(s->head);
    //s->head = NULL;
    //s->tail = NULL;
}





