#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


//popitka.c

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
    struct Node* left;
    struct Node* right;

} Node ;


typedef struct Tree
{
    Node* root;
    int count;
} Tree ;


Node* create_node(double val, int type)
{
    Node *s = (Node *) calloc(1, sizeof(*s));
    s->left = NULL;
    s->right = NULL;
    s->value = val;
    s->type = type;
    return s;
}

Node* add_node(Node* add_el, Node* cur_el, int side)
{
    //Node* el = create_node(val, type);
    if (side == 0)
        cur_el->left = add_el;
    else
        cur_el->right = add_el;
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
        //PRINTF("ssss\n");
        s++;
        Node* val = GetE();
        assert(*s == ')');
        s++;
        return val;
    } else
        return GetN();
}

Node* GetO()
{
    Node* val = GetP();
    Node* new_node = NULL;
    while (*s == 's' || *s == 'c')
    {
        double op = *s;
        s += 3;
        Node* val2 = GetP();
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

    //if (new_node == NULL)
    return val;
    //return new_node;
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
            //return new_node;
        }
    }
    //if (new_node == NULL)
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



void create_tree (Node *s, FILE *f)
{
    if (s->left != NULL)
    {
        fprintf (f, "\t%f[shape = \"egg\", color=\"green\", style=\"filled\", fillcolor = \"white\"];\n\t%f->%f;\n", s->value, s->value, s->left->value);
        create_tree (s->left, f);
    }
    if (s->right != NULL)
    {
        fprintf (f, "\t%f[shape = \"egg\", color=\"green\", style=\"filled\", fillcolor = \"white\"];\n\t%f->%f;\n", s->value, s->value, s->right->value);
        create_tree (s->right, f);
    }
    return;
}

void diff_dot (Node *s)
{
    FILE *file_dot = fopen("diff.dot", "w");
    fprintf(file_dot, "digraph\n{\n");
    fprintf(file_dot, "node[shape = \"septagon\", color=\"darkgreen\",fontsize=10, style=\"filled\", fillcolor = \"#9CC98D\"];\nedge[color=\"darkgreen\",fontsize=12];\n");
    create_tree (s, file_dot);
    fprintf(file_dot, "}");
    fclose(file_dot);
    return;
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
    PRINTF("eee %c\n", (int)val->value);

    //printf("%d\n", val);
    print_tree_sc(val);

    diff_dot(val);

    return 0;
}