
#include "all.h"


const int CAPACITY = 100;

const int SIZE_STACK = 0;
const double REDUCE = 1.5;
const double EPSILON = 1e-6;
const double VALU = 666666;
const int Poison = 666;


int ERROR_CODE = 0;
enum ERROR_TYPE
{
    CALLOC_ERROR   = -1,
    REALLOC_ERROR  = -2,
    EMPTY_ERROR    = -3,
    CAPACITY_ERROR = -4,
    DATA_ERROR     = -5,
    CANARY_ERROR   = -6,
    HASH_ERROR     = -7,
};

/*int main()
{
    stack first_stack = {};

    stackCtor(&first_stack);

    stackPush(&first_stack, 22);

    stackPush(&first_stack, 11);

    printf("stack size is %d\n", stackSize(&first_stack));

    int pop_element =stackPop(&first_stack);
    UNITTEST(pop_element, 11);

    pop_element = stackPop(&first_stack);
    UNITTEST(pop_element, 22);

    stackPush(&first_stack, 14);

    pop_element = stackPop(&first_stack);
    UNITTEST(pop_element, -3);

    stackDtor(&first_stack);

    if (ERROR_CODE != 0)
        printf("ERROR_CODE %d", ERROR_CODE);

    return ERROR_CODE;
}
*/
void stackCtor(struct stack* s)
{
    assert (s);
    s -> data = (int*)calloc(CAPACITY, sizeof(*(s -> data)));
    if (s -> data == NULL)
    {
        PRINTF("Calloc fail\n");
        ERROR_CODE = CALLOC_ERROR;
        return;
    }
    for (int i = 0; i < CAPACITY; i++)
        s -> data[i] = Poison;

    s -> size = SIZE_STACK;
    s -> capacity = CAPACITY;

    s -> canary1 = canaryValue(1);
    s -> canary2 = canaryValue(2);
    s -> canary3 = canaryValue(3);
    s -> canary4 = canaryValue(4);
    s -> canary5 = canaryValue(5);
    s -> canary6 = canaryValue(6);

    s -> hashsum = countHashsum(s);

    CARCKIYassert(stackOK(s));
}

void stackDtor(struct stack* s)
{
    CARCKIYassert(stackOK(s));

    free(s -> data);
    s -> data = NULL;
    s -> size = -1;
    s -> capacity = -1;

    //CARCKIYassert(stackOK(s)); /////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
}

int stackOK(struct stack* s)
{
    if ((s -> size < 0) || (s -> capacity < 0))
    {
        PRINTF("Size stack or campacity low zerro\n");
        ERROR_CODE = EMPTY_ERROR;
        return ERROR_CODE;
    }

    if (s -> capacity < s ->size)
    {
        PRINTF("capacity low size stack\n");
        ERROR_CODE = CAPACITY_ERROR;
        return ERROR_CODE;
    }

    if (s -> data == NULL)
    {
        PRINTF("data not exit\n");
        ERROR_CODE = DATA_ERROR;
        return ERROR_CODE;
    }

    if (cannaryOK(s) != 0)
    {
        PRINTF ("canory is change\n");
        ERROR_CODE = CANARY_ERROR;
        return ERROR_CODE;
    }

    if (countHashsum(s) != s -> hashsum)
    {
        PRINTF("hash sum is change\n");
        ERROR_CODE = HASH_ERROR;
        return ERROR_CODE;
    }
    return 0;
}

void stackReduceSize(struct stack* s)
{
    CARCKIYassert(stackOK(s));

    s -> data = realloc(s -> data, s -> size * sizeof(int));
    if (s -> data == NULL)
    {
        PRINTF("Realloc fail\n");
        ERROR_CODE = REALLOC_ERROR;
        return;
    }
    s -> capacity = s -> size;

    CARCKIYassert(stackOK(s));
}

void stackIncreaseSize(struct stack* s)
{
    CARCKIYassert(stackOK(s));

    s -> capacity = CAPACITY * 2;
    s -> data = realloc(s -> data, s -> capacity * sizeof(int));
    if (s -> data == NULL)
    {
        PRINTF("Realloc fail\n");
        ERROR_CODE = REALLOC_ERROR;
        return;
    }

    CARCKIYassert(stackOK(s));
}

void stackPush(struct stack* s, int val)
{
    CARCKIYassert(stackOK(s));

    if (s -> size >= s -> capacity)
        stackIncreaseSize(s);
    s -> data[s -> size] = val;

    s -> size += 1;

    s -> hashsum = countHashsum(s);


    CARCKIYassert(stackOK(s));
}

int stackPop(struct stack* s)
{
    CARCKIYassert(stackOK(s));

    if (s -> size -1 < 0)
    {
        //PRINTF("Stack empty\n");
        ERROR_CODE =  EMPTY_ERROR;
        return ERROR_CODE;
    }
    int last_val = s -> data[s -> size - 1];

    s -> data[s -> size - 1] = Poison;
    s -> size -= 1;

    s -> hashsum = countHashsum(s);

    if (s -> size / s -> capacity > REDUCE && s -> size > 0)
        stackReduceSize(s);

    return last_val;
}

int stackSize(struct stack* s)
{
    CARCKIYassert(stackOK(s));
    return s -> size;
}

int cannaryOK (stack* s)
{

    if (!isEqual(s -> canary1, canaryValue(1)))
        return 1;
    if (!isEqual(s -> canary2, canaryValue(2)))
        return 2;
    if (!isEqual(s -> canary3, canaryValue(3)))
        return 3;
    if (!isEqual(s -> canary4, canaryValue(4)))
        return 4;
    if (!isEqual(s -> canary5, canaryValue(5)))
        return 5;
    if (!isEqual(s -> canary6, canaryValue(6)))
        return 6;

    return 0;
}

int isEqual (double x1, double x2)
{
    return fabs(x1 - x2) < EPSILON;
}


double canaryValue (int canaryNum)
{
    static double canary1 = VALU;
    static double canary2 = VALU;
    static double canary3 = VALU;
    static double canary4 = VALU;
    static double canary5 = VALU;
    static double canary6 = VALU;

    assert (canaryNum >  0);
    assert (canaryNum <= 6);

    switch (canaryNum)
    {
        case 1 : return canary1;
            break;
        case 2 : return canary2;
            break;
        case 3 : return canary3;
            break;
        case 4 : return canary4;
            break;
        case 5 : return canary5;
            break;
        case 6 : return canary6;
            break;
        default:
            ERROR_CODE = CANARY_ERROR;
            return ERROR_CODE;
    }
}

void stackDump(struct stack* s)
{
    printf("\n");
    printf("========= Stack situation =========\n");
    printf("pointer stack %p\n", s);
    printf("stack_ size: %d \n", s -> size);
    printf("stac_capacity %d \n", s -> capacity);
    printf("pointer_data %p \n", s -> data);

    if (s ->data != 0)
    {
        for (int i = 0; i < s -> size - 1; i++)
            printf("n = %d  val = %d\n", i, s -> data[i]);
    }

    printf("hash sum %d   should be %d", countHashsum(s), s -> hashsum);
    printf("\n");
    printf("========= canory vaiues =========\n");
    printf("  value canory 1 = %lg  should be %lg\n", s -> canary1, canaryValue(1));
    printf("  value canory 2 = %lg  should be %lg\n", s -> canary2, canaryValue(2));
    printf("  value canory 3 = %lg  should be %lg\n", s -> canary3, canaryValue(3));
    printf("  value canory 4 = %lg  should be %lg\n", s -> canary4, canaryValue(4));
    printf("  value canory 5 = %lg  should be %lg\n", s -> canary5, canaryValue(5));
    printf("  value canory 6 = %lg  should be %lg\n", s -> canary6, canaryValue(6));

}


int countHashsum (struct stack* s)
{
    int hash_sum = 0;
    int sgn = -1;

    for (int i = 0; i < s -> capacity; i++)
    {
        hash_sum += sgn * s -> data[i];
        sgn *= -1;
    }
    return hash_sum;
}
