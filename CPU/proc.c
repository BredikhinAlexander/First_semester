#include "all.h"


const int Maxsize = 1000;
int Error_code = 0;
const char* mashine_code = "mashine_code.txt";

typedef struct CPU
{
    stack proc;
    stack call;

    int reg_ax;
    int reg_bx;
    int reg_cx;
    int reg_dx;
}CPU;

void CPU_ctor(struct CPU *s)
{
    stackCtor(&(s->proc));
    stackCtor(&(s->call));

    s->reg_ax = 0;
    s->reg_bx = 0;
    s->reg_cx = 0;
    s->reg_dx = 0;
}

int main()
{

    struct CPU s = {};
    CPU_ctor(&s);


    FILE *file_in = fopen(mashine_code, "r");
    assert(file_in);

    if (file_in == NULL)
    {
        Error_code = Open_error;
        printf("Do not open file mashine_code.txt");
        return Error_code;
    }


    char *buf = (char *)calloc(Maxsize, sizeof(*buf));

    fread(buf, Maxsize, sizeof(*buf), file_in);
    fseek(file_in, 0, SEEK_SET);
    assert(buf);

    char* ptr = buf;
    int shift = 0;
    int val = -1;
    //while (val != 0)
    while (1 != 0)
    {
        val = 0;
        sscanf(ptr, "%d%n", &val, &shift);
        ptr += shift;

        PRINTF("ax=%d bx=%d cx=%d dx=%d\n",s.reg_ax, s.reg_bx, s.reg_cx, s.reg_dx);
        PRINTF("val = %d\n", val);

        switch (val)
        {
            #define DEF_CMD(name, num, code) \
                case num: code; \

                #include "commands1.h"
                #include "commands0.h"
                #include "commands2.h"

            default:
                //printf("FIASCO: there is no such case\n");
                break;
        }
    }
    return 0;
}
