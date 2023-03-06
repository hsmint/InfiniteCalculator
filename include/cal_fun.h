#include <stdlib.h>
#include <stdio.h>

//Num-list
typedef struct NUM{
    char data;
    struct NUM* pre;
    struct NUM* next;
}num;

typedef struct NODE{
    int f_size;
    int b_size;
    num* head;
    num* tail;
    struct NODE* pre_data;
    struct NODE* next_data;
}node;

typedef struct LIST{
    int cnt;
    node* back;
}list;


//Stack
typedef struct STACK_NODE{
    char op_data;
    struct STACK_NODE* next_node;
}s_node;

typedef struct STACK{
    int cnt;
    s_node* head;
}stack;

//Function

void init(list*);

void s_init(stack*);

void node_add(list*);

void data_push(list*, char);

void s_push(stack*, char);

char s_top(stack*);

int s_empty(stack*);

void s_pop(stack*);

void read(FILE*, char**);

void num_push(node*, char);

void node_init(node*);

void add(list*);

void minus(list*);

void multiply(list*);