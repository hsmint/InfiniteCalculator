#include "cal_fun.h"

void init(list* l){
    l->cnt = 0;
    l->back = NULL;
    node_add(l);
}

void node_add(list* l){
    node* tmp = (node*)malloc(sizeof(node));
    if (l->back != NULL) l->back->next_data = tmp;
    tmp->f_size = 0;
    tmp->b_size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->pre_data = l->back;
    tmp->next_data = NULL;
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

// Stack function
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

char s_top(stack* s){
    if (s->cnt == 0) return '\0';
    return s->head->op_data;
}

int s_empty(stack* s){
    if (s->cnt == 0) return 0;
    return 1;
}

int s_pop(stack* s){
    if (s->cnt == 0) return 0;
    s_node* del = s->head;
    s->head = s->head->next_node;
    free(del);
    s->cnt--;
    return 1;
}