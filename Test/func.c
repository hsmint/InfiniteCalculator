#include "cal_fun.h"

void init(list* l){
    l->cnt = 0;
    l->back = NULL;
}

void node_add(list* l){
    node* tmp = (node*)malloc(sizeof(node));
    if (l->back != NULL) l->back->pre_data = tmp;
    tmp->size = 0;
    tmp->tail = NULL;
    tmp->next_data = l->back;
    tmp->pre_data = NULL;
    l->back = tmp;
    l->cnt++;
}

void data_push(list* l, char d){
    num* tmp = (num*)malloc(sizeof(num));
    if (l->back->tail != NULL) l->back->tail->pre = tmp;
    tmp->data = d;
    tmp->pre = NULL;
    tmp->next = l->back->tail;
    l->back->tail = tmp;
    l->back->size++;
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