#include <stdlib.h>
#include <string.h>
//DEFINE

#define DATA char*
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

//Operation Function

void(*func_p(const char opCode))(NODE, NODE);

NODE* add(NODE*, NODE*);

NODE* minus(NODE*, NODE*);