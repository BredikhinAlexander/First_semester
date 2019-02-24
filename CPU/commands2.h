
DEF_CMD(jmp, 50, (
    {
        int val_jump = 0;
        sscanf(ptr, "%d%n", &val_jump, &shift);
        PRINTF("val to jump  %d\n", val_jump);
        ptr += shift;
        ptr = buf;
        for (int i = 0; i < val_jump; i++)
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;
        }
        break;
    }))

DEF_CMD(ja, 51, (
    {
        int last = stackPop(&s.proc);
        int prelast = stackPop(&s.proc);
        if (last > prelast)
        {
            int val_jump = 0;
            sscanf(ptr, "%d%n", &val_jump, &shift);
            PRINTF("val to jump  %d\n", val_jump);
            ptr = buf;
            for (int i = 0; i < val_jump; i++)
            {
                sscanf(ptr, "%d%n", &val, &shift);
                ptr += shift;
            }
        }
        break;
    }))

DEF_CMD(jb, 52, (
        {
            //int last = stackPop(&proc);
            //int prelast = stackPop(&proc);
            int last = stackPop(&s.proc);
            int prelast = stackPop(&s.proc);
            if (last < prelast)
            {
                int val_jump = 0;
                sscanf(ptr, "%d%n", &val_jump, &shift);
                PRINTF("val to jump  %d\n", val_jump);
                ptr = buf;
                for (int i = 0; i < val_jump; i++)
                {
                    sscanf(ptr, "%d%n", &val, &shift);
                    ptr += shift;
                }
            }
            break;
        }))


DEF_CMD(je, 53, (
        {
            //int num1 = stackPop(&proc);
            //int num2 = stackPop(&proc);
            int num1 = stackPop(&s.proc);
            int num2 = stackPop(&s.proc);
            if (num2 == num1)
            {
                int val_jump = 0;
                sscanf(ptr, "%d%n", &val_jump, &shift);
                PRINTF("val to jump  %d\n", val_jump);
                ptr = buf;
                for (int i = 0; i < val_jump; i++)
                {
                    sscanf(ptr, "%d%n", &val, &shift);
                    ptr += shift;
                }
            }
            break;
        }))


DEF_CMD(jac, 54, (
    {
        int last = stackPop(&s.proc);
        int prelast = stackPop(&s.proc);
        if (last >= prelast)
        {
            int val_jump = 0;
            sscanf(ptr, "%d%n", &val_jump, &shift);
            PRINTF("val to jump  %d\n", val_jump);
            ptr = buf;
            for (int i = 0; i < val_jump; i++)
            {
                sscanf(ptr, "%d%n", &val, &shift);
                ptr += shift;
            }
        }
        break;
    }))



DEF_CMD(jbc, 55, (
    {
        int last = stackPop(&s.proc);
        int prelast = stackPop(&s.proc);
        if (last <= prelast)
        {
            int val_jump = 0;
            sscanf(ptr, "%d%n", &val_jump, &shift);
            PRINTF("val to jump  %d\n", val_jump);
            ptr = buf;
            for (int i = 0; i < val_jump; i++)
            {
                sscanf(ptr, "%d%n", &val, &shift);
                ptr += shift;
            }
        }
        break;
    }))


DEF_CMD(jrc, 56, (
    {
    int num1 = stackPop(&s.proc);
    int num2 = stackPop(&s.proc);
    if (num2 != num1)
    {
        int val_jump = 0;
        sscanf(ptr, "%d%n", &val_jump, &shift);
        PRINTF("val to jump  %d\n", val_jump);
        ptr = buf;
        for (int i = 0; i < val_jump; i++)
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;
        }
    }
    break;
    }))

DEF_CMD(jiz, 57, (
    {
        int num = stackPop(&s.proc);
        if (num == 0)
        {
            int val_jump = 0;
            sscanf(ptr, "%d%n", &val_jump, &shift);
            PRINTF("val to jump  %d\n", val_jump);
            ptr = buf;
            for (int i = 0; i < val_jump; i++)
            {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;
            }
        }
        break;
    }))

DEF_CMD(call, 60, (
    {
        int val_jump = 0;
        sscanf(ptr, "%d%n", &val_jump, &shift);
        PRINTF("val to call  %d\n", val_jump);
        ptr += shift;

        stackPush(&s.call, ptr);
        ptr = buf;

        for (int i = 0; i < val_jump; i++)
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;
            PRINTF("jump in %d   ", val);
        }
        PRINTF("\n");
        break;
    }))