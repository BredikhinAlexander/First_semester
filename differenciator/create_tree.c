#include "differ.h"

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

