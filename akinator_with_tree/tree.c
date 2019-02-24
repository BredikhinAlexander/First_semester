#include "tree.h"


int Tree_ctor (struct Tree* s)
{
    assert(s);

    s->root = NULL;
    s->count = 0;

    return List_error;
}

struct Node* node_ctor() {
    Node *s = (Node *) calloc(1, sizeof(*s));
    if (s == NULL)
    {
        List_error = Calloc_error;
        return NULL;
    }
    s->left = NULL;
    s->right = NULL;
    s->value = (char *) calloc(Maxsize, sizeof(*(s->value)));
    return s;
}


int tree_dtor(struct Tree* s)
{
    assert(s);
    s->count = -666;
    s->root = NULL;
    return List_error;
}

int node_dtor(struct Node* s)
{
    assert(s);
    s->value = NULL;
    free(s);
    s = NULL;
    return List_error;
}

Node* add(Tree* s, char* val, Node* cur_el, int flag)
{
    Node* el = node_ctor();
    el->value = val;
    if (flag == 0)
    {
        cur_el->left = el;
    } else
    {
        cur_el->right = el;
    }
    s->count++;
    return el;
}

char* node_remove(Tree* s, Node* cur_el, int flag)
{
    char* val = 0;
    if (flag == 0)
    {
        val = cur_el->left->value;
        cur_el->left = NULL;
    } else
    {
        val = cur_el->right->value;
        cur_el->right = NULL;
    }
    s->count--;
    return val;
}

void print_tree_sc(Node* s)
{
    if (s == NULL)
        return;
    printf("%c", '{');
    if (s->left != NULL)
    {
        print_tree_sc(s->left);
    }
    printf("%s", s->value);
    if (s->right != NULL)
    {
        print_tree_sc(s->right);
    }
    printf("%c", '}');

}

void change_tree(Node* s, FILE* file_out)
{
    if (s == NULL)
        return;
    //PRINTF("%s\n", s->value);
    fprintf(file_out, "%c\n", '{');
    if (s->left != NULL)
    {
        change_tree(s->left, file_out);
    }
    fprintf(file_out, "%s\n", s->value);
    if (s->right != NULL)
    {
        change_tree(s->right, file_out);
    }
    fprintf(file_out, "%c\n", '}');
}

Node* search_person(Node* cur_el, char* person)
{
    Node* result = NULL;
    if (strcmp(cur_el->value, person))
    {
        if (cur_el->left != NULL)
        {
            result = search_person(cur_el->left, person);
            return result;
        }
        else if (cur_el->right != NULL)
        {
            result = search_person(cur_el->right, person);
            return result;
        }

    } else
        return cur_el;
    return result;
}

/*
char person_description(Tree* s)
{
    char name[Maxsize];
    printf("Enter person name\n");
    scanf("\n%s", name);

    Node* person = search_person(s->root, name);
    if (person != NULL)
    {

    }
}
*/

Node* read_el(Tree* s, int *index, char* buf)
{
    Node* new_node = node_ctor();
    s->count++;

    //PRINTF("%c\n", buf[*index]);

    if (buf[*index] == '{')
    {
        *index += 2;

        if (buf[*index] == '{')
        {
            new_node->left = read_el(s, index, buf);
        }
        char* str = (char*)calloc(Maxsize, sizeof(*str));
        int i = 0;
        assert(str);
        while (buf[*index] != '{' && buf[*index] != '}')
        {
            //PRINTF("%c", buf[*index]);
            str[i++] = buf[(*index)++];
        }
        str[--i] = '\0';
        new_node->value = str;

        if (buf[*index] == '{')
        {
            new_node->right = read_el(s, index, buf);
        }
    }
    if (buf[*index] == '}')
    {
        //PRINTF("%c\n", buf[*index]);
        *index += 2;
        return new_node;
    }
    return NULL;
}

void read_tree(Tree* akinator)
{
    FILE* file_in = fopen(name_file_in, "r");
    if (file_in == NULL)
    {
        List_error = Point_error;
        printf("Do not open file Tree.txt");
        return;
    }
    char* buf = (char*)calloc(Maxsize, sizeof(*buf));
    fread(buf, Maxsize, sizeof(*buf), file_in);


    int index = 0;

    akinator->root = read_el(akinator, &index, buf);
    free(buf);
    fclose(file_in);
}

void add_person(Tree* s, Node* cur_el)
{
    char* buf = (char*)calloc(Maxsize, sizeof(*buf));
    printf("Who is this?\n");

    scanf("%s", buf);
    printf("What %s is different from %s?\n", buf, cur_el->value);

    char* person_new = strdup(buf);
    char* person_old = strdup(cur_el->value);

    memset(buf, 0, sizeof(*buf));

    scanf("%s", buf);
    cur_el->value = buf;

    add(s,person_old, cur_el, 0);
    add(s, person_new, cur_el, 1);
}

int Akinator()
{
    Tree ak = {};

    Tree_ctor(&ak);

    read_tree(&ak);
    Node* cur_el = ak.root;



    for(;;)
    {
        if (cur_el->left == NULL)
        {
            printf("Is he or she %s ?\n", cur_el->value);
            //printf("press [y] for YES and [n] for NO\n");
            break;
        }

        printf("Does he or she %s?\n", cur_el->value);

        char asw = 0;
        scanf("\n%c", &asw);

        if (asw == 'y')
        {
            cur_el = cur_el->right;
        }
        else if(asw == 'n')
        {
            cur_el = cur_el->left;
        } else
            printf("I don't understand, my Creator is lazy:)\n");

    }
    char user = 0;
    scanf("\n%c", &user);
    //PRINTF("aaaaa %c\n", user);
    if (user == 'y')
    {
        printf("Ehooo, I am very clever\n");
        printf("Let's play one more time!\n");
        printf("Do you want to play?\n");
    }
    else if (user == 'n')
    {
        add_person(&ak, cur_el);
        printf("I know more now than you do\n");
        printf("Do you want to play?\n");
    } else
        printf("No no, you're wrong\n");

    scanf("\n%c", &user);

    FILE* file_out = fopen(name_file_in, "w");
    change_tree(ak.root, file_out);
    fclose(file_out);


    if (user == 'y')
        Akinator();
    else
    {
        print_tree_sc(ak.root);
        akinator_dot(&ak);
    }
    return 0;

}

void create_tree (Node *s, FILE *f)
{
    if (s->left != NULL)
    {
        fprintf (f, "\t%s[shape = \"egg\", color=\"green\", style=\"filled\", fillcolor = \"white\"];\n\t%s->%s[label = \"No\"];\n", s->value, s->value, s->left->value);
        create_tree (s->left, f);
    }
    if (s->right != NULL)
    {
        fprintf (f, "\t%s[shape = \"egg\", color=\"green\", style=\"filled\", fillcolor = \"white\"];\n\t%s->%s[label = \"Yes\"];\n", s->value, s->value, s->right->value);
        create_tree (s->right, f);
    }
    return;
}



void akinator_dot (Tree *s)
{
    FILE *file_dot = fopen("akinator.dot", "w");
    fprintf(file_dot, "digraph\n{\n");
    fprintf(file_dot, "node[shape = \"septagon\", color=\"darkgreen\",fontsize=10, style=\"filled\", fillcolor = \"#9CC98D\"];\nedge[color=\"darkgreen\",fontsize=12];\n");
    create_tree (s->root, file_dot);
    fprintf(file_dot, "}");
	fclose(file_dot);
    return;
}

