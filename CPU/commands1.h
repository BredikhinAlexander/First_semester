
DEF_CMD(push, 1, (
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;

            PRINTF("push val = %d\n", val);

            stackPush(&s.proc, val);
            break;
        }))

DEF_CMD(pushreg,  3, (
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;

            PRINTF("push reg = %d\n", val);

            switch (val)
            {
                case ax:
                    stackPush(&s.proc, s.reg_ax);
                    break;
                case bx:
                    stackPush(&s.proc, s.reg_bx);
                    break;
                case cx:
                    stackPush(&s.proc, s.reg_cx);
                    break;
                case dx:
                    stackPush(&s.proc, s.reg_dx);
                    break;
                default:
                    printf("FIASCO: there is no such register");
                    return Error_code;
            }
            break;
        }))

DEF_CMD(popreg,  4, (
        {
            sscanf(ptr, "%d%n", &val, &shift);
            ptr += shift;

            PRINTF("pop reg = %d\n", val);

            switch (val)
            {
                case ax:
                    s.reg_ax = stackPop(&s.proc);
                    break;
                case bx:
                    s.reg_bx = stackPop(&s.proc);
                    break;
                case cx:
                    s.reg_cx = stackPop(&s.proc);
                    break;
                case dx:
                    s.reg_dx = stackPop(&s.proc);
                    break;
                default:
                    printf("FIASCO: there is no such register");
                    return Error_code;
            }
            break;
        }))

