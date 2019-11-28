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

void s_init(STACK* s);

void s_push(STACK* s, DATA data);

char s_pop(STACK* s);

int s_size(STACK* s);


int s_empty(STACK* s);

char s_top(STACK* s);
