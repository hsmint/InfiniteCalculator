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

//STACK METHOD

void init(STACK* s);

void push(STACK* s, DATA data);

char pop(STACK* s);

int size(STACK* s);

int empty(STACK* s);

char top(STACK* s);
