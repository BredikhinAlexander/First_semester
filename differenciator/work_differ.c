#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>




#define start_left(n, m)        \
    if (n != NULL)              \
        simplifies(n, m);

#define start_right(n, m)       \
    if (n != NULL )             \
        simplifies(n, m);

#define del_node_left(n, m)    \
    Node* new_node = copy_tree(n->right); \
    root = redirection(n, new_node, m); \
    change = 1;

#define del_node_right(n, m) \
    Node* new_node = copy_tree(n->left); \
    root = redirection(n, new_node, m); \
    change = 1;

#define plus(n, m) \
    Node* new_node = create_node(n->left->value + n->right->value, number); \
    root = redirection(n, new_node, m); \
    change = 1;

#define sub(n, m) \
    Node* new_node = create_node(n->left->value - n->right->value, number); \
    root = redirection(n, new_node, m); \
    change = 1;

#define mul(n, m) \
    Node* new_node = create_node(n->left->value * n->right->value, number); \
    root = redirection(n, new_node, m); \
    change = 1;


#define FITCHA

#ifdef FITCHA
#define PRINTF printf
#else
#define PRINTF if(0) printf
#endif


enum Type_of_data
{
    number    = 1,
    variable  = 2,
    operation = 3,
};

enum Side
{
    left_side  = 0,
    right_side = 1,
};

const char* name_file_in = "equation.txt";
unsigned int Maxsize = 500;


typedef struct Node
{
    double value;
    int type;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

} Node ;



Node* create_node(double val, int type)
{
    Node *s = (Node *) calloc(1, sizeof(*s));
    s->left   = NULL;
    s->right  = NULL;
    s->parent = NULL;
    s->value  = val;
    s->type   = type;
    return s;
}

void destroy_node(Node* s)
{
    s->left   = NULL;
    s->right  = NULL;
    s->parent = NULL;
    s->value  = -666;
    s->type   = -1;
    free(s);
}

void destroy_operation(Node* cur_el)
{
    destroy_node(cur_el->left);
    destroy_node(cur_el->right);
    destroy_node(cur_el);
}

Node* add_node(Node* add_el, Node* cur_el, int side)
{
    //Node* el = create_node(val, type);
    if (side == 0)
        cur_el->left = add_el;
    else
        cur_el->right = add_el;

    add_el->parent = cur_el;

    return cur_el;
}

Node* GetE();
void print_tree_sc(Node* st);
const char* s = NULL;


Node* GetN()
{
    double val = 0;

    if (*s == 'x')
    {
        val = *s;
        s++;
        return create_node(val, variable);
    }


    while (0 <= *s - '0' && *s - '0' <= 9)
    {
        val = val*10 + *s - '0';
        s++;
    }
    //PRINTF("In N: %f\n", val);
    return create_node(val, number);


}

Node* GetP()
{
    if (*s == '(')
    {
        s++;
        Node* val = GetE();
        assert(*s == ')');
        s++;
        return val;
    } else
        return GetN();
}

Node* GetS()
{
    Node* val = GetP();
    Node* new_node = NULL;
    while (*s == '^')
    {
        double op = *s;
        s++;
        Node* val2 = GetP();
        if (op == '^')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        }
    }
    return val;
}

Node* GetO()
{
    Node* val = GetS();
    Node* new_node = NULL;
    while (*s == 's' || *s == 'c')
    {
        double op = *s;
        s += 3;
        Node* val2 = GetS();
        if (op == 's')
        {
            new_node = create_node(op, operation);
            //add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        } else if (op == 'c')
        {
            new_node = create_node(op, operation);
            //add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        }
    }
    return val;
}

Node* GetT()
{
    Node* val = GetO();
    Node* new_node = NULL;
    while (*s == '*' || *s == '/')
    {
        double op = *s;
        s++;
        Node* val2 = GetO();
        if (op == '*')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        } else if (op == '/')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        }

    }

    return val;
}

Node* GetE()
{
    Node* val = GetT();
    Node* new_node = NULL;
    while (*s == '+' || *s == '-')
    {
        double op = *s;
        s++;
        Node* val2 = GetT();
        if (op == '+')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
            //return new_node;
        } else if (op == '-')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        }
    }
    return val;

}

Node* GetG(const char* str)
{
    s = str;
    Node* val = GetE();
    if (*s == '\0' && s != str)
        return val;
    else
    {
        printf("ERROR: incorrect input format\n");
        return NULL;
    }
}


void print_tree_sc(Node* st)
{
    if (st == NULL)
        return;
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


int change = -1;

Node* simplifies(Node* cur_el, Node* root)
{
    if (cur_el->type == operation)
    {
        switch ((int)cur_el->value)
        {
            case '+':
            {

                if (cur_el->left->type == number && cur_el->right->type == number)
                {
                    plus(cur_el, root);
                } else if (cur_el->left->value == 0)
                {
                    del_node_left(cur_el, root);
                } else if (cur_el->right->value == 0)
                {
                    del_node_right(cur_el, root);
                } else if(cur_el->left->type == variable && cur_el->right->type == variable)
                {
                    cur_el->left->value = 2;
                    cur_el->left->type = number;
                    cur_el->value = '*';
                    change = 1;

                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root)
                }
                break;
            }

            case '-':
            {
                if (cur_el->left->type == number && cur_el->right->type == number)
                {
                    sub(cur_el, root);
                } else if (cur_el->left->value == 0)
                {
                    destroy_node(cur_el->left);
                    cur_el->left = NULL;
                } else if (cur_el->right->value == 0)
                {
                    del_node_right(cur_el, root);
                } else if (cur_el->left->type == variable && cur_el->right->type == variable)
                {
                    destroy_node(cur_el->left);
                    destroy_node(cur_el->right);
                    cur_el->left  = NULL;
                    cur_el->right = NULL;
                    cur_el->value = 0;
                    cur_el->type  = number;
                    change = 1;
                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root)
                }
                break;
            }

            case '*':
            {
                if (cur_el->left->value == 0 || cur_el->right->value == 0)
                {
                    Node* new_node = create_node(0, number);
                    root = redirection(cur_el, new_node, root);
                    change = 1;

                } else if (cur_el->left->value == 1)
                {
                    del_node_left(cur_el, root);
                } else if (cur_el->right->value == 1)
                {
                    del_node_right(cur_el, root);
                } else if (cur_el->left->type == number && cur_el->right->type == number)
                {
                    mul(cur_el, root);
                } else if (cur_el->left->type == variable && cur_el->right->type == variable)
                {
                    cur_el->value = '^';
                    cur_el->left->value = 'x';
                    cur_el->right->value = 2;
                    cur_el->right->type = number;
                    change = 1;

                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root)
                }
                break;
            }

            case '/':
            {
                if (cur_el->right != NULL && cur_el->right->value == 1)
                {
                    del_node_right(cur_el, root);
                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root);

                }
                break;
            }
            case '^':
            {
                if (cur_el->right != NULL && cur_el->right->value == 0)
                {
                    cur_el->value = 1;
                    cur_el->type = number;
                    destroy_node(cur_el->left);
                    destroy_node(cur_el->right);
                    cur_el->left = NULL;
                    cur_el->right = NULL;
                    change = 1;
                } else if (cur_el->right != NULL && cur_el->right->value == 1)
                {
                    del_node_right(cur_el, root);
                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root);
                }
                break;
            }

            case 's':
            {
                if (cur_el->right != NULL && cur_el->right->value == 0)
                {
                    del_node_right(cur_el, root);
                    cur_el->value = 0;
                    cur_el->type  = 0;
                } else
                {
                    start_left(cur_el->left, root);
                    start_right(cur_el->right, root);
                }
                break;

            }

            default:
            {
                break;
            }
        }
    } else
    {
        start_left(cur_el->left, root);
        start_right(cur_el->right, root)
    }
    return root;
}


int is_leaf(Node* cur_el)
{
    if (cur_el->left == NULL && cur_el->right == NULL)
        return 1;
    else
        return 0;
}

void print_file(Node* cur_el, FILE* file_out)
{
    if (cur_el == NULL)
        return;
    if (cur_el->type == operation)
    {
        if (cur_el->value == '/')
        {
            fprintf(file_out, "\\frac{");

            print_file(cur_el->left, file_out);
            fprintf(file_out, "}{");
            print_file(cur_el->right, file_out);

            fprintf(file_out, "}");

            return;

        } else if (cur_el->value == '^')
        {
            if (is_leaf(cur_el->left))
                print_file(cur_el->left, file_out);
            else
            {
                fprintf(file_out, "(");
                print_file(cur_el->left, file_out);
                fprintf(file_out, ")");
            }

            fprintf(file_out, "^{");
            print_file(cur_el->right, file_out);
            fprintf(file_out, "}");
            return;

        } else if (cur_el->value == '*')
        {
            if (is_leaf(cur_el->left)       ||
                cur_el->left->value == '*'  ||
                cur_el->left->value == '/'  ||
                cur_el->left->value == '^'    )

                print_file(cur_el->left, file_out);
            else
            {
                fprintf(file_out, "(");
                print_file(cur_el->left, file_out);
                fprintf(file_out, ")");
            }

            if (is_leaf(cur_el->right) ||
                cur_el->right->value == '*' ||
                cur_el->right->value == '/' ||
                cur_el->right->value == '^'   )

                print_file(cur_el->right, file_out);
            else
            {
                fprintf(file_out, "(");
                print_file(cur_el->right, file_out);
                fprintf(file_out, ")");
            }

            return;

        } else if(cur_el->value == '-')
        {
            print_file(cur_el->left, file_out);
            fprintf(file_out, "%c", '-');

            if (cur_el->right->value == '+' || cur_el->right->value == '-')
            {
                fprintf(file_out, "(");
                print_file(cur_el->right, file_out);
                fprintf(file_out, ")");
            } else
                print_file(cur_el->right, file_out);
            return;
        }

    }

    print_file(cur_el->left, file_out);

    switch (cur_el->type)
    {
        case variable:
        {
            fprintf(file_out, "%c", (int)cur_el->value);
            break;
        }

        case number:
        {
            fprintf(file_out, "%.2g", cur_el->value);
            break;
        }

        case operation:
        {
            switch ((int) cur_el->value)
            {
                case '+':
                {
                    //printf("aaaaaaa\n");
                    fprintf(file_out, "%c", '+');
                    break;
                }
                case '-':
                {
                    fprintf(file_out, "%c", '-');
                    break;
                }
                case 's':
                {
                    if (cur_el->right->type == number) fprintf(file_out, "\\sin ");
                    else if (cur_el->right->type == variable) fprintf(file_out, "\\sin %c", (int)cur_el->right->value);
                    else
                    {
                        fprintf(file_out, "\\sin");
                        fprintf(file_out, "(");
                        print_file(cur_el->right, file_out);
                        fprintf(file_out, ")");
                    }
                    return;
                }
                case 'c':
                {
                    if (cur_el->right->value == number) fprintf(file_out, "\\cos");
                    else if (cur_el->right->value == variable)
                        fprintf(file_out, "\\cos %c", (int) cur_el->right->value);
                    else
                    {
                        fprintf(file_out, "\\cos");
                        fprintf(file_out, "(");
                        print_file(cur_el->right, file_out);
                        fprintf(file_out, ")");
                    }
                    return;
                }
                default:
                    break;
            }
        }
        default:
            break;

    }

    print_file(cur_el->right, file_out);
}

void Latex(Node* root, char* output)
{
    FILE* out = fopen(output, "wb");
    assert(out);

    fprintf(out, "\\documentclass[a4paper, 12pt]{article}\n"
                 "\\usepackage[T2A]{fontenc}\n"
                 "\\usepackage[utf8]{inputenc}\n"
                 "\\usepackage[english,russian]{babel}\n"
                 "\\usepackage{graphicx}\n"
                 "\\usepackage{float}\n"
                 "\\usepackage{wrapfig}\n"
                 "\\usepackage{fancybox,fancyhdr}\n"
                 "\\usepackage{amsmath, amsfonts, amssymb, amsthm, mathtools}\n"
                 "\\usepackage{subfigure}\n"
                 "\n"
                 "\\title{Матанализ на физтехе}\n"
                 "\\author{Sasha Bredikhin}\n"
                 "\n"
                 "\\begin{document}\n"
                 "\\newpage\n");

    fprintf(out, "Каждая пара по матану начинается с подобных формул:\n");

    fprintf (out, "$");
    print_file(root, out);
    fprintf (out, "$");

    fprintf(out, "Думаешь, что сейчас будет легко, что всё всё поймёшь и заришь...\n");
    fprintf(out, "а затем ты поднимаешь глаза и видишь, вот это(((\n");

    root = differ(root);

    fprintf (out, "$");
    print_file(root, out);
    fprintf (out, "$");

    fprintf(out, "От таких выражений загрустит даже Полторашка\n");

    //fprintf (out, "\\begin{center}\n"
    //              "\\includegraphics[scale=0.7]{kotic1.jpg}\n"
    //              "\\end{center}\n");

    fprintf(out, "А что тут говорить про неопытного Пятилтраше и других котиках\n");
    fprintf(out, "Он не готов к такому\n");

    root = simplifies(root, root);

    fprintf(out, "Но переживать рано\n");
    fprintf(out, "Котии и многие студенты будут спасены\n");
    fprintf(out, "Близка сессия и студенты физтеха расшарили даже такие сложные выражения\n");

    fprintf (out, "$");
    print_file(root, out);
    fprintf (out, "$");

    change = -1;
    while (change != 0)
    {
        change = 0;
        root = simplifies(root, root);
    }

    fprintf(out, "Проблема с матаном решена!!!\n");
    fprintf(out, "Ведь теперь на контрольной все возьмут любую производную\n");
    fprintf(out, "Главное правильно переписать ответ\n");

    fprintf (out, "$");
    print_file(root, out);
    fprintf (out, "$");

    fprintf(out, "\n"
                 "\n"
                 "\\end{document}");

    assert(out);
    fclose(out);
}


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

    //Node* val_dif = differ(val);
   // PRINTF("main_dif_Node %c\n", (int)val_dif->value);
    //printf("\n");

   // print_tree_sc(val_dif);
    //printf("\n");
    ////print_par(val_dif);
//
    //while (change != 0)
    //{
    //    change = 0;
    //    val_dif = simplifies(val_dif, val_dif);
    //    printf("\n");
    //    //printf("%f\n", val_dif->value);
    //    print_tree_sc(val_dif);
    //    printf("\n");
    //    //printf("%d\n", change);
    //}
//
    Latex(val, "ouuut.tex");

    dot(val);

    return 0;
}






