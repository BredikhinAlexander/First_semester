#include "all.h"

//const char* name_file_in = "command.txt";
//const char* name_file_in = "deed.txt";
const char* name_file_in = "sq.txt";
//const char* name_file_in = "out.txt";
const char* name_file_out = "mashine_code.txt";
int Error_code = 0;
unsigned int Maxsize = 1000;




int compile(FILE* file_in, unsigned int n_strings, char* buf, int* mashine_code, int* lables, int flag)
{
    int index = 0;

    for (int j = 0; j < n_strings; j++)
    {
        fscanf(file_in, "%s", buf);
        if (buf[0] == ':' && flag == 1)
            lables[buf[1] - '0'] = index;

        #define DEF_CMD(name, num, ref) \
            if (strcmp(buf, #name) == 0) \
            { \
                mashine_code[index++] = CMD_##name; \
                fscanf(file_in, "%s", buf); \
                mashine_code[index++] = lables[strtol(buf, NULL, 10)]; \
            } \


        #include "commands2.h"
        #undef DEF_CMD

        #define DEF_CMD(name, num, ref) \
            if (strcmp(buf, #name) == 0) \
            { \
                mashine_code[index++] = CMD_##name;\
            }\


        #include "commands0.h"
        #undef DEF_CMD

        #define DEF_CMD(name, num, ref) \
        if (strcmp(buf, #name) == 0) \
        {\
            mashine_code[index++] = num;\
            fscanf(file_in, "%s", buf);\
            if (isdigit(buf[0])) \
            {\
                mashine_code[index++] = strtol(buf, NULL, 10); \
            }\
            else \
            { \
                if      (buf[0] == 'a') mashine_code[index++] = ax; \
                else if (buf[0] == 'b') mashine_code[index++] = bx; \
                else if (buf[0] == 'c') mashine_code[index++] = cx; \
                else if (buf[0] == 'd') mashine_code[index++] = dx; \
            } \
        }

        #include "commands1.h"
        #undef DEF_CMD

    }
    return index;

}


void print_array_lables(int* lables)
{
    printf("lables...\n");
    for (int i = 0; i < 21; i++)
    {
        printf("%d ", lables[i]);
    }
    printf("\n");
    printf("\n");
}


int main()
{
    char *buf = (char *) calloc(Maxsize, sizeof(char));
    FILE *file_in = fopen(name_file_in, "r");

    if (file_in == NULL)
    {
        Error_code = Open_error;
        printf("Do not open file Commands.txt");
        return Error_code;
    }

    int *lables = (int*)calloc(21, sizeof(*lables));
    unsigned int n_strings = calc_n_strings(file_in);
    int *machine_code = (int*)calloc(n_strings * 2 , sizeof(*machine_code));



    int n_el = compile(file_in, n_strings, buf, machine_code, lables, 1);


    //printf("%d\n", n_el);
    //print_array_lables(lables);

    fseek(file_in, 0, SEEK_SET);

    compile(file_in,n_strings,buf,machine_code, lables, 2);

    if (machine_code[n_el - 1] == machine_code[n_el - 2])
    {
        machine_code[n_el - 1] = 0;
        n_el -= 1;
    }

    write_file(machine_code, n_el);
    fclose(file_in);

}

unsigned int calc_n_strings(FILE *file_in)
{
    assert(file_in);

    unsigned int number_string = 0;
    char massiv[100] = " ";

    while (fgets(massiv, 100, file_in) != NULL)
        number_string++;
    fseek(file_in, 0, SEEK_SET);

    return number_string ;
}

void write_file(int* mashine_code, int n_el)
{
    assert(mashine_code);
    FILE *file_out = fopen(name_file_out, "w");

    if (file_out == NULL)
    {
        Error_code = Open_error;
        printf("Do not open file Mashine_code.txt");
        return;
    }

    for (int i = 0; i < n_el; i++)
    {
        fprintf(file_out, "%d ", mashine_code[i]);

        //printf("%d ", mashine_code[i]);
    }
    fclose(file_out);


}