#include "List.c"

int main()
{

    List first_list = {};

    list_ctor(&first_list);

    List_Elem* el0 = add_front(&first_list, 10);

    list_print(&first_list);
    printf("\n");

    add_back(&first_list, 5);

    list_print(&first_list);
    printf("\n");

    remove_back(&first_list);

    list_print(&first_list);
    printf("\n");

    add_back(&first_list, 30);

    list_print(&first_list);
    printf("\n");

    List_Elem* el1 = add_after(&first_list, 100, el0);

    list_print(&first_list);
    printf("\n");

    List_Elem* el3 = add_before(&first_list, 200, el1);

    list_print(&first_list);
    printf("\n");

    //printf("2: %d\n",list_remove(&first_list, 2));
    list_remove(&first_list, el3);

    list_print(&first_list);
    printf("\n");

    printf("%d\n",find_val(&first_list, 100)->value);

    printf("3: %d\n\n",remove_front(&first_list));

    list_print(&first_list);
    printf("\n");

    killer_elements(&first_list);

    list_dtor(&first_list);

    return 0;

}
