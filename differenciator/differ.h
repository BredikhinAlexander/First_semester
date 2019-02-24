

#ifndef DESCENT_DIFFER_H
#define DESCENT_DIFFER_H



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


void destroy_node(Node* s);
void destroy_operation(Node* cur_el);
Node* add_node(Node* add_el, Node* cur_el, int side);
void print_tree_sc(Node* st);
Node* GetE();
Node* GetN();
Node* GetP();
Node* GetS();
Node* GetO();
Node* GetT();
Node* GetG(const char* str);
void print_par(Node* st);
Node* redirection(Node* cur_el, Node* new_node, Node* root);
void create_tree(Node* cur_el, FILE* dot_out);
void dot(Node* root);
void print_mode (Node* cur_el, FILE* dot_out);
Node* copy_tree(Node* cur_el);
Node* differ(Node* cur_el);
Node* simplifies(Node* cur_el, Node* root);
int is_leaf(Node* cur_el);
void print_file(Node* cur_el, FILE* file_out);
void Latex(Node* root, char* output);

#endif //DESCENT_DIFFER_H
