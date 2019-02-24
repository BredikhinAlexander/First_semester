#include "create_tree.c"
#include "differenciator.c"
#include "simple.c"

// add_executable(descent differ.h create_tree.c differenciator.c simple.c main_diff.c)
int main()
{
    FILE* file_in = fopen(name_file_in, "r");
    if (file_in == NULL)
    {
        printf("Do not open file equation.txt");
        return -1;
    }
    char* buf = (char*)calloc(Maxsize, sizeof(*buf));
    fread(buf, Maxsize, sizeof(*buf), file_in);

    Node* val = GetG(buf);
    PRINTF("main_Node %c\n", (int)val->value);

    print_tree_sc(val);
    printf("\n");
    //print_par(val);

    printf("\n");

    Node* val_dif = differ(val);
    PRINTF("main_dif_Node %c\n", (int)val_dif->value);
    printf("\n");

    print_tree_sc(val_dif);
    printf("\n");
    //print_par(val_dif);

    while (change != 0)
    {
        change = 0;
        val_dif = simplifies(val_dif, val_dif);
        printf("\n");
        //printf("%f\n", val_dif->value);
        print_tree_sc(val_dif);
        printf("\n");
        //printf("%d\n", change);
    }

    Latex(val_dif, "ouuut.txt");

    dot(val_dif);

    return 0;
}

