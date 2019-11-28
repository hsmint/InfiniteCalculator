#include <stdlib.h>

//DEFINE

#define DATA char
#define CNT int

//TYPEDEF

typedef struct node{
    DATA         d;
    struct node* next;
}NODE;

//STACK
typedef struct st{
    CNT num;
    NODE* head;
}STACK;

typedef struct list{
    CNT op;
    CNT num;
    NODE* head;
}LIST;

// LIST METHOD

void l_init(LIST*);

//STACK METHOD

void init(STACK*);

void push(STACK*, DATA);

char pop(STACK*);

int size(STACK*);

int empty(STACK*);

char top(STACK*);
