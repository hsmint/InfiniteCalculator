#include <stdlib.h>

//DEFINE

#define DATA char
#define CNT int

//TYPEDEF

typedef struct node{
    DATA         d;
    struct node* next;
}NODE;

//LIST
typedef struct list{
    CNT num;
    NODE* head;
}LIST;

//LIST METHOD

void init(LIST*);

void push(LIST*, DATA);

char pop(LIST*);

int size(LIST*);

int empty(LIST*);

char top(LIST*);
