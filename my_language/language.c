#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


#define gap while(*s == ' ' || *s == '\n') s++

const char* name_file_in = "cod.txt";
unsigned int Maxsize = 500;

typedef struct Node
{
    double value;
    int type;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

} Node ;

enum Side
{
    left_side  = 0,
    right_side = 1,
};

enum Type_of_data
{
    number    = 1,
    variable  = 2,
    operation = 3,
    Op        = 4,
    If        = 5,
    While     = 6,
};


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

Node* add_node(Node* add_el, Node* cur_el, int side)
{
    //Node* el = create_node(val, type);
    if (side == 0)
        cur_el->left = add_el;
    else
        cur_el->right = add_el;

    if (add_el != NULL)
        add_el->parent = cur_el;

    return cur_el;
}

Node* GetOp();
Node* GetE();
Node* GetComp();
Node* GetIf_W();
void print_tree_sc(Node* st);
char* s  = NULL;
const char* s0 = NULL;



Node* GetN() // считывает переменные, числа и пропускает пробелы
{
    double val = 0;

    if (*s == ' ' || *s == '\n')
        s++;

    if (0 <= *s - 'a' && *s - 'a' <= 'z')
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
    return create_node(val, number);
}

Node* GetP() //считывает скобочки
{
    if (*s == '(')
    {
        s++;
        Node* val = GetComp();
        gap;
        assert(*s == ')');
        s++;
        return val;
    } else
        return GetN();
}



Node* GetS()
{
    Node* val = GetP();
    gap;
    Node* new_node = NULL;
    while (*s == '^' || *s == 'S')
    {
        double op = *s;
        s++;
        Node* val2 = GetP();
        gap;

        new_node = create_node(op, operation);
        add_node(val, new_node, left_side);
        add_node(val2, new_node, right_side);
        val = new_node;
    }
    return val;
}

Node* GetO()
{
    Node* val = GetS();
    gap;
    Node* new_node = NULL;
    while (*s == 's' || *s == 'c')
    {
        double op = *s;
        s += 3;
        Node* val2 = GetS();
        gap;
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
    gap;

    Node* val = GetO();
    gap;
    Node* new_node = NULL;
    while (*s == '*' || *s == '/')
    {
        double op = *s;
        s++;
        Node* val2 = GetO();
        gap;
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
    gap;

    Node* val = GetT();
    gap;
    Node* new_node = NULL;
    while (*s == '+' || *s == '-')
    {
        double op = *s;
        s++;
        Node* val2 = GetT();
        gap;
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

Node* GetComp()
{
    gap;

    Node* val = GetE();
    gap;
    Node* new_node = NULL;
    while (*s == '<' || *s == '>' || *s == ':' || *s == '#')
    {
        double op = *s;
        s++;
        Node *val2 = GetE();
        gap;
        new_node = create_node(op, operation);
        add_node(val, new_node, left_side);
        add_node(val2, new_node, right_side);
        val = new_node;
    }
    return val;
}

Node* GetR_In() // считывает присваивание
{
    gap;
    // printf("%c\n", *s);

    Node* val = GetComp();
    gap;
    Node* new_node = NULL;


    while (*s == '=' || *s == 'I')
    {
        double op = *s;
        s += 1;
        if (op == '=')
        {
            Node* val2 = GetComp();
            gap;

            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            add_node(val2, new_node, right_side);
            val = new_node;
        } else if (op == 'I')
        {
            new_node = create_node(op, operation);
            add_node(val, new_node, left_side);
            //add_node(val2, new_node, right_side);
            val = new_node;
        }
    }
    return val;
}

Node* GetCkob()
{
    gap;
    //printf("eee %c\n", *s);

    assert(*s == '!');
    s += 3;
    gap;

    Node* val = GetOp();
    //printf("%c\n", (int)val->left->left->value);
    gap;

    Node* op = val;

    s += 3;
    //printf("exxxxx %c\n", *s);
    gap;

    return op;
}

Node* GetIf_W()
{
    gap;
    Node* val = GetR_In();
    gap;
    Node* node_if = NULL;
    Node* node_while = NULL;
    while (*s == 'M' || *s == 'W')
    {
        double op = *s;
        s += 4;
        gap;
        Node* val2 = GetCkob();
        gap;
        if (op == 'M')
        {
            node_if = create_node(op, If);
            add_node(val, node_if, left_side);
            add_node(val2, node_if, right_side);
            val = node_if;
        } else if (op == 'W')
        {
            node_while = create_node(op, While);
            add_node(val, node_while, left_side);
            add_node(val2, node_while, right_side);
            val = node_while;
        }

    }
    return val;


}

Node* GetOp()
{
    gap;

    Node* val = GetIf_W();
    gap;
    Node* node_op = NULL;
    while (*s == 'K')
    {
        s += 5;
        gap;
        Node *val2 = GetOp();
        gap;
        node_op = create_node('O', Op);
        add_node(val, node_op, left_side);
        add_node(val2, node_op, right_side);
    }
    return node_op;


}

Node* GetG(char* str)
{
    s = str;
    s0 = s;
    Node* val = GetOp();
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
    if (st->type == operation || st->type == variable || st->type == If || st->type == Op)
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
    FILE *file_dot = fopen("language.dot", "wb");
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

        case If: fprintf(dot_out, "[label = \"%c\", shape = \"Msquare\", "
                                  "color=\"#8B0000\", style=\"filled\", "
                                  "fillcolor = \"#FFA07A\"]", (int)cur_el->value);
            break;

        case Op: fprintf(dot_out, "[label = \"%c\", shape = \"Msquare\", "
                                  "color=\"#8B0000\", style=\"filled\", "
                                  "fillcolor = \"#FFA07A\"]", (int)cur_el->value);
            break;

        default:          fprintf(dot_out, "\"error\"");
            break;
    }
}


int count = 0;



void asembler(FILE* file_out, Node* cur_el)
{
    if (cur_el == NULL)
        return;

    if (cur_el->type == Op)
    {
        asembler(file_out, cur_el->left);

        if (cur_el->right != NULL)
            asembler(file_out, cur_el->right);
        else
            fprintf(file_out, "end\n");
    } else if (cur_el->type == If)
    {
        asembler(file_out, cur_el->left);

        fprintf(file_out, "jmp :%d\n", count + 1);
        fprintf(file_out, ":%d\n", count);
        count++;
        int count2 = count;

        asembler(file_out, cur_el->right);

        fprintf(file_out, ":%d\n", count2);

    } else if (cur_el->type == While)
    {
        fprintf(file_out, ":%d\n", count);

        int count2 = count;

        asembler(file_out, cur_el->left);
        asembler(file_out, cur_el->right);

        fprintf(file_out, "jmp :%d\n", count2);
        fprintf(file_out, ":%d\n", count);
        count++;
    } else if (cur_el->type == operation)
    {
        switch ((int)cur_el->value)
        {
            case '+':
                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "add\n");
                break;


            case '-':

                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "sub\n");
                break;

            case '*':

                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "mul\n");
                break;

            case '/':

                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "div\n");
                break;

            case '=':

                asembler(file_out, cur_el->right);
                if ((int)cur_el->left->value == 'k')
                    fprintf(file_out, "out\n");
                else
                    fprintf(file_out, "popreg %cx\n", (int)cur_el->left->value);
                break;

            case 'I':
                fprintf(file_out, "pushkb\n");
                fprintf(file_out, "popreg %cx\n", (int)cur_el->left->value);
                break;

            case 'S': // корень квадратный

                asembler(file_out, cur_el->right);
                fprintf(file_out, "squareroot\n");
                break;

            case '>':
                count++;
                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "jb :%d\n", count);
                break;

            case '<':
                count++;
                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "ja :%d\n", count);
                break;

            case ':':
                count++;
                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);
                fprintf(file_out, "jiz :%d\n", count);
                break;

            case '#':
                asembler(file_out, cur_el->left);
                asembler(file_out, cur_el->right);

                fprintf(file_out, "jrc :%d\n", count);
                count++;
                break;

            default:
                printf("ERROR_OP\n");
                printf("%c\n", (int)cur_el->value);
        }
    } else if (cur_el->type == number)
    {
        fprintf(file_out, "push %d\n", (int)cur_el->value);
    } else if (cur_el->type == variable)
    {
        if (cur_el->value == 'k' || cur_el->value == 'e')
        {
            fprintf(file_out, "out\n");
        } else
            fprintf(file_out, "pushreg %cx\n", (int)cur_el->value);
    } else
        printf("ERROR\n");
}


void create_comand(char* file, Node* root)
{
    FILE* file_out = fopen(file, "w");
    if (!file_out)
    {
        printf("ERROR\n");
        return;
    }
    asembler(file_out, root);
    fclose(file_out);

}

int main()
{
    FILE *file_in = fopen(name_file_in, "r");
    if (file_in == NULL) {
        printf("Do not open file equation.txt");
        return -1;
    }
    char *buf = (char *) calloc(Maxsize, sizeof(*buf));
    fread(buf, Maxsize, sizeof(*buf), file_in);

    Node *val = GetG(buf);
    printf("main_Node %c\n", (int) val->value);

    print_tree_sc(val);
    printf("\n");
    dot(val);
    create_comand("out.txt", val);
}

