#include "differ.h"

void print_tree_sc(Node* st)
{
    if (st == NULL)
        return;
    //PRINTF("rrr %f", st->value);
    printf("%c", '{');
    if (st->left != NULL)
    {
        print_tree_sc(st->left);
    }

    if (st->type == operation || st->type == variable)
        printf("%c", (int)st->value);
    else
    {
        printf("%f", st->value);
    }

    if (st->right != NULL)
    {
        print_tree_sc(st->right);
    }
    printf("%c", '}');

}

void print_par(Node* st)
{
    if (st == NULL)
        return;
    if (st->left != NULL)
    {
        print_par(st->left);
    }

    if (st->parent != NULL)
        printf("el: %p : %d  parent: %p : %d\n",st, (int)st->value, st->parent, (int)st->parent->value);


    if (st->right != NULL)
    {
        print_par(st->right);
    }

}


Node* redirection(Node* cur_el, Node* new_node, Node* root)
{

    if (cur_el->parent != NULL)
    {
        new_node->parent = cur_el->parent;

        if (cur_el->parent->left == cur_el)
            cur_el->parent->left = new_node;
        else
            cur_el->parent->right = new_node;
    } else
    {
        root = new_node;
    }

    destroy_operation(cur_el);
    return root;
}



void print_mode (Node* cur_el, FILE* dot_out);
int tmp = 0;



void create_tree(Node* cur_el, FILE* dot_out)
{
    fprintf(dot_out, "\t\they%d", tmp);
    print_mode(cur_el, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (cur_el->left != NULL)
    {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(cur_el->left, dot_out);
    }

    if (cur_el->right != NULL)
    {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(cur_el->right, dot_out);
    }

}
void dot(Node* root)
{
    FILE *file_dot = fopen("diff.dot", "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_tree(root, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

}



void print_mode (Node* cur_el, FILE* dot_out)
{
    switch (cur_el->type) {
        case operation:     fprintf(dot_out, "[label = \"%c\", shape = \"Mcircle\", "
                                             "color=\"#006400\", style=\"filled\", "
                                             "fillcolor = \"#32CD32\"]", (int)cur_el->value);
            break;

        case variable:    fprintf(dot_out, "[label = \"%c\", shape = \"component\", "
                                           "color=\"#8B008B\", style=\"filled\", "
                                           "fillcolor = \"#9932CC\"]", (int)cur_el->value);
            break;

        case number: fprintf(dot_out, "[label = \"%d\", shape = \"Msquare\", "
                                      "color=\"#8B0000\", style=\"filled\", "
                                      "fillcolor = \"#FFA07A\"]", (int)cur_el->value);
            break;

        default:          fprintf(dot_out, "\"error\"");
            break;
    }
}




Node* copy_tree(Node* cur_el)
{
    Node* new_node = create_node(cur_el->value, cur_el->type);
    if (cur_el->left != NULL)
    {
        Node* cr_node = copy_tree(cur_el->left);
        new_node->left = cr_node;
        cr_node->parent = new_node;
    }

    if (cur_el->right != NULL)
    {
        Node* cr_node = copy_tree(cur_el->right);
        new_node->right = cr_node;
        cr_node->parent = new_node;
    }
    return new_node;
}


Node* differ(Node* cur_el)
{
    Node* new_node = NULL;

    switch (cur_el->type)
    {
        case number:
        {
            new_node = create_node(0, number);
            if (cur_el->left != NULL)
            {
                Node* cr_node = copy_tree(cur_el->left);
                new_node->left = cr_node;
                cr_node->parent = new_node;
            }

            if (cur_el->right != NULL)
            {
                Node* cr_node = copy_tree(cur_el->right);
                new_node->right = cr_node;
                cr_node->parent = new_node;
            }
            break;
        }

        case variable:
        {
            new_node = create_node(1, number);
            if (cur_el->left != NULL)
            {
                Node* cr_node = copy_tree(cur_el->left);
                new_node->left = cr_node;
                cr_node->parent = new_node;
            }

            if (cur_el->right != NULL)
            {
                Node* cr_node = copy_tree(cur_el->right);
                new_node->right = cr_node;
                cr_node->parent = new_node;
            }
            break;
        }

        case operation:
        {
            switch ((int)cur_el->value)
            {
                case '+':
                {
                    new_node = create_node(cur_el->value, operation);

                    Node* cr_node = differ(cur_el->left);
                    new_node->left = cr_node;
                    cr_node->parent = new_node;

                    cr_node = differ(cur_el->right);
                    new_node->right = cr_node;
                    cr_node->parent = new_node;

                    break;
                }

                case '-':
                {
                    new_node = create_node(cur_el->value, operation);

                    Node* cr_node = differ(cur_el->left);
                    new_node->left = cr_node;
                    cr_node->parent = new_node;

                    cr_node = differ(cur_el->right);
                    new_node->right = cr_node;
                    cr_node->parent = new_node;

                    break;
                }
                case '*':
                {
                    new_node = create_node('+', operation);
                    Node* new_node_left = create_node('*', operation);

                    new_node->left = new_node_left;
                    new_node_left->parent = new_node;

                    Node* new_node_right = create_node('*', operation);

                    new_node->right = new_node_right;
                    new_node_right->parent = new_node;

                    Node* cr_node = differ(cur_el->left);
                    new_node_left->left = cr_node;
                    cr_node->parent = new_node_left;

                    cr_node = copy_tree(cur_el->right);
                    new_node_left->right = cr_node;
                    cr_node->parent = new_node_left;

                    cr_node = copy_tree(cur_el->left);
                    new_node_right->left = cr_node;
                    cr_node->parent = new_node_right;

                    cr_node = differ(cur_el->right);
                    new_node_right->right = cr_node;
                    cr_node->parent = new_node_right;

                    break;
                }


                case 's':
                {
                    new_node = create_node('*', operation);
                    Node* new_node_left = create_node('c', operation);

                    new_node->left = new_node_left;
                    new_node_left->parent = new_node;

                    Node* cr_node = copy_tree(cur_el->right);
                    new_node_left->left = cr_node;
                    cr_node->parent = new_node_left;

                    cr_node = differ(cur_el->right);
                    new_node->right = cr_node;
                    cr_node->parent = new_node;

                    break;
                }

                case 'c':
                {
                    Node* minus = create_node(-1, number);
                    Node* mul = create_node('*', operation);

                    mul->left = minus;
                    minus->parent = mul;

                    new_node = create_node('*', operation);
                    mul->right = new_node;
                    new_node->parent = mul;

                    Node* new_node_left = create_node('s', operation);

                    new_node->left = new_node_left;
                    new_node_left->parent = new_node;

                    Node* cr_node = copy_tree(cur_el->right);
                    new_node_left->left = cr_node;
                    cr_node->parent = new_node_left;


                    cr_node = differ(cur_el->right);
                    new_node->right = cr_node;
                    cr_node->parent = new_node;

                    new_node = mul;

                    break;
                }
                case '/':
                {
                    if (cur_el->right->type == number)
                    {
                        new_node = create_node('/', operation);
                        Node* right = create_node(cur_el->right->value, number);
                        right->parent = new_node;
                        new_node->right = right;
                        Node* left = differ(cur_el->left);
                        left->parent = new_node;
                        new_node->left = left;
                    } else
                    {
                        new_node = create_node('/', operation);
                        Node* new_node_left = create_node('-', operation);

                        new_node->left = new_node_left;
                        new_node_left->parent = new_node;

                        Node* new_node_right = create_node('*', operation);

                        new_node->right = new_node_right;
                        new_node_right->parent = new_node;

                        Node* left_left = create_node('*', operation);
                        left_left->parent = new_node_left;
                        new_node_left->left = left_left;
                        left_left->left = differ(cur_el->left);
                        left_left->right = copy_tree(cur_el->right);

                        Node* left_right = create_node('*', operation);
                        left_right->parent = new_node_left;
                        new_node_left->right = left_right;
                        left_right->left = copy_tree(cur_el->left);
                        left_right->right = differ(cur_el->right);

                        new_node_right->left = copy_tree(cur_el->right);
                        new_node_right->right = copy_tree(cur_el->right);
                    }


                    break;

                }
                case '^':
                {
                    new_node = create_node('*', operation);
                    Node* left = create_node(cur_el->right->value, number);
                    left->parent = new_node;
                    new_node->left = left;

                    Node* right = create_node('*', operation);
                    right->parent = new_node;
                    new_node->right = right;

                    Node* right_right = differ(cur_el->left);
                    right_right->parent = right;
                    right->right = right_right;

                    Node* right_left = create_node('^', operation);
                    right_left->parent = right;
                    right->left = right_left;

                    Node* new_left = copy_tree(cur_el->left);
                    new_left->parent = right_left;
                    right_left->left = new_left;

                    Node* new_right = create_node(cur_el->right->value - 1, number);
                    new_right->parent = right_left;
                    right_left->right = new_right;
                    break;

                }
                default:
                {
                    printf("No operation\n");
                    printf("operation is %c", (int)cur_el->value);
                }
            }
            break;
        }
        default:
        {
            printf("No type\n");
            printf("type is %d", cur_el->type);
        }
    }

    return new_node;
}
