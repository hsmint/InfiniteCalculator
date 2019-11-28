#include "Header/node.h"

//STACK METHOD

void init(STACK* s){
    s->num = 0;
    s->head = NULL;
}

void push(STACK* s, DATA data){
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->next = s->head;
    tmp->d = data;
    s->head = tmp;
    s->num += 1;
}

char pop(STACK* s){
    NODE* new_head = s->head->next;
    DATA pop_d = s->head->d;
    free(s->head);
    s->num -= 1;
    s->head = new_head;
    return pop_d;
}

int size(STACK* s){
    return s->num;
}

int empty(STACK* s){
    if (s->num == 0) return 0;
    else return -1;
}

char top(STACK* s){
    if (s->num == 0) return '\0';
    else return s->head->d;
}