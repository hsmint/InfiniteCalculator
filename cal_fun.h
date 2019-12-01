#include <stdlib.h>
#include <string.h>
//DEFINE

#define DATA char
#define CNT int

//TYPEDEF

typedef struct num{
    DATA         d;
    struct NUM* next;
    struct NUM* pre;
}NUM;

typedef struct node{
    struct NUM* head;
    struct node* next;
    struct node* pre;
}NODE;

//LIST
typedef struct list{
    CNT num;
    NODE* head;
}LIST;

typedef struct stack_node{
    DATA    d;
    struct st_data* next;
}S_NODE;

typedef struct stack{
    CNT num;
    S_NODE* head;
}STACK;

//STACK METHOD

void s_init(STACK* s);

void s_push(STACK* s, DATA data);

char s_pop(STACK* s);

int s_size(STACK* s);

int s_empty(STACK* s);

char s_top(STACK* s);

//LIST METHOD

void init(LIST*);

void push(LIST*, DATA);

void add(LIST*);

//Operation Function

//void(*func_p(const char opCode))(NODE*, NODE*);

//void add(NODE*, NODE*);

//void minus(NODE*, NODE*);