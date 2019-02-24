
#ifndef AKINATOR_TREE_H
#define AKINATOR_TREE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


#define FITCHA

#ifdef FITCHA
#define PRINTF printf
#else
#define PRINTF if(0) printf
#endif



const char* name_file_in = "Tree.txt";
unsigned int Maxsize = 500;

int List_error = 0;
enum list_error
{
    No_error     = 0,
    Calloc_error = -1,
    Num_error    = -2,
    Point_error  = -3,
    Order_error  = -4,
};


typedef struct Node
{
    char* value;
    struct Node* left;
    struct Node* right;

} Node ;


typedef struct Tree
{
    Node* root;
    int count;
} Tree ;

int Tree_ctor (struct Tree* s);
struct Node* node_ctor();
int tree_dtor(struct Tree* s);
int node_dtor(struct Node* s);
Node* add(Tree* s, char* val, Node* cur_el, int flag);
char* node_remove(Tree* s, Node* cur_el, int flag);
void print_tree_sc(Node* s);
void change_tree(Node* s, FILE* file_out);
Node* read_el(Tree* s, int *index, char* buf);
void read_tree(Tree* akinator);
int Akinator();
void create_tree (Node *s, FILE *f);
void akinator_dot (Tree *s);
Node* search_person(Node* cur_el, char* person);


#endif //AKINATOR_TREE_H
