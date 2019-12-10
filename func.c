#include "cal_fun.h"

void init(list* l){
    l->cnt = 0;
    l->back = NULL;
    node_add(l);
}

void node_add(list* l){
    node* tmp = (node*)malloc(sizeof(node));
    if (l->back != NULL) l->back->pre_data = tmp;
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->next_data = l->back;
    tmp->pre_data = NULL;
    l->back = tmp;
    l->cnt++;
}

void data_push(list* l, char d){
    num* tmp = (num*)malloc(sizeof(num));
    tmp->data = d;
    tmp->next = NULL;
    if (l->back->head == NULL){
        l->back->head = tmp;
        l->back->tail = tmp;
        tmp->pre = NULL;
    } else{
        tmp->pre = l->back->tail;
        l->back->tail->next = tmp;
        l->back->tail = tmp;
    }
}

void s_init(stack* s){
    s->cnt = 0;
    s->head = NULL;
}

void s_push(stack* s, char d){
    s_node* tmp = (s_node*)malloc(sizeof(s_node));
    tmp->op_data = d;
    tmp->next_node = s->head;
    s->head = tmp;
    s->cnt++;
}

void read(FILE* ifp, char** buf){
    fseek(ifp, 0, SEEK_END);
    unsigned long size = ftell(ifp) + 1;
    fseek(ifp, 0, SEEK_SET);
    *buf = (char*)malloc((sizeof(char))*size);
    fscanf(ifp, "%s", *buf);
}