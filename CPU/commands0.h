DEF_CMD(end, 100, (
        {
            PRINTF("all ended\n");
            return 0;
        }))

DEF_CMD(pop,  2, (
        {
            stackPop(&s.proc);
            PRINTF("i am pop\n");
            break;
        }))

DEF_CMD(pushkb, 5, (
        {
            int val = 0;
            scanf("%d", &val);

            PRINTF("pushkb val = %d\n", val);

            stackPush(&s.proc, val);
            break;
        }))

DEF_CMD(out, 9, (
        {
            printf("REZULT == %d\n", stackPop(&s.proc));
            break;
        }))


DEF_CMD(add,  10, (
        {
            int el1 = stackPop(&s.proc);
            int el2 = stackPop(&s.proc);
            int otvet = el1 + el2;
            PRINTF("add_otvet = %d\n", otvet);
            stackPush(&s.proc, otvet);
            break;
        }))

DEF_CMD(sub,  11, (
        {
            int el1 = stackPop(&s.proc);
            int el2 = stackPop(&s.proc);
            int otvet = el2 - el1;
            PRINTF("sub_otvet = %d\n", otvet);
            stackPush(&s.proc, otvet);
            break;
        }))

DEF_CMD(div,  12, (
    {
        int el1 = stackPop(&s.proc);
        int el2 = stackPop(&s.proc);
        int otvet = el2/el1;
        PRINTF("div_otvet = %d\n", otvet);
        stackPush(&s.proc, otvet);
        break;
    }))

DEF_CMD(mul,  13, (
    {
        int el1 = stackPop(&s.proc);
        int el2 = stackPop(&s.proc);
        int otvet = el2*el1;
        PRINTF("mul_otvet = %d\n", otvet);
        stackPush(&s.proc, otvet);
        break;
    }))

DEF_CMD(squareroot,  14, (
    {
        int el = stackPop(&s.proc);
        int otvet = sqrt(el);
        PRINTF("sqrt_otvet = %d\n", otvet);
        stackPush(&s.proc, otvet);
        break;
    }))

DEF_CMD(sqr,  15, (
    {
        int el = stackPop(&s.proc);
        int otvet = el*el;
        PRINTF("sqr_otvet = %d\n", otvet);
        stackPush(&s.proc, otvet);
        break;
    }))

DEF_CMD(ret, 61, (
{
    int val_jump = 0;
    val_jump = stackPop(&s.call);
    PRINTF("val to jump  %d\n", val_jump);
    ptr = buf;
    while (ptr != val_jump)
    {
        sscanf(ptr, "%d%n", &val, &shift);
        ptr += shift;
        //PRINTF("jump in %d\n", val);
    }
    break;
}))
