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

//QUEUE
typedef struct qu{
    CNT num;
    NODE* head;
    NODE* tail;
}QUEUE;

//STACK METHOD

void s_init(STACK* s);

void s_push(STACK* s, DATA data);

char s_pop(STACK* s);

int s_size(STACK* s);


int s_empty(STACK* s);

char s_top(STACK* s);

//QUEUE METHOD

void q_init(QUEUE* q);

void q_push(QUEUE* q, DATA data);

char q_pop(QUEUE* q);

int q_size(QUEUE* q);

char q_front(QUEUE* q);

char q_back(QUEUE* q);

int q_empty(QUEUE* q);