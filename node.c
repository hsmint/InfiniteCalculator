#include "cal_fun.h"

//STACK METHOD

void s_init(STACK* s){
    s->num = 0;
    s->head = NULL;
}

void s_push(STACK* s, DATA data){
    S_NODE* tmp = (S_NODE*)malloc(sizeof(S_NODE));
    tmp->d = data;
    tmp->next = s->head;
    s->head=tmp;
    s->num += 1;
}

char s_pop(STACK* s){
    if (s->num == 0) return 0;
    char data = s->head->d;
    S_NODE* delete = s->head;
    s->head = s->head->next;
    free(delete);
    s->num -=1;
    return data;
}

int s_size(STACK* s){
    return s->num;
}

int s_empty(STACK* s){
    if (s->num == 0) return 0;
    else return -1;
}

char s_top(STACK* s){
    if (s->num == 0) return 0;
    else return s->head->d;
}

//LIST METHOD

void init(LIST* l){
    l->num = 0;
    l->head = NULL;
}

void add(LIST* l){
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->pre = NULL;
    if (l->head != NULL) tmp->next = l->head;
    else{
        l->head->pre = tmp;
        tmp->next = NULL;
    }
    l->head = tmp;
}

void push(LIST* l, DATA data){
    NUM* tmp = (NUM*)malloc(sizeof(NUM));
    tmp->pre = NULL;
    tmp->next = l->head;
    tmp->d = data;
    l->head = tmp;
}