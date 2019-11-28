#include "Header/node.h"

//LIST METHOD

void init(LIST* s){
    s->num = 0;
    s->head = NULL;
}

void push(LIST* s, DATA data){
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->next = s->head;
    tmp->d = data;
    s->head = tmp;
    s->num += 1;
}

char pop(LIST* s){
    NODE* new_head = s->head->next;
    DATA pop_d = s->head->d;
    free(s->head);
    s->num -= 1;
    s->head = new_head;
    return pop_d;
}

int size(LIST* s){
    return s->num;
}

int empty(LIST* s){
    if (s->num == 0) return 0;
    else return -1;
}

char top(LIST* s){
    if (s->num == 0) return '\0';
    else return s->head->d;
}