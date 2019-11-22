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

void s_push(STACK* s, DATA data){
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->next = s->head;
    tmp->d = data;
    s->head = tmp;
    s->num += 1;
}

char s_pop(STACK* s){
    NODE* new_head = s->head->next;
    DATA pop_d = s->head->d;
    free(s->head);
    s->num -= 1;
    s->head = new_head;
    return pop_d;
}

int s_size(STACK* s){
    return s->num;
}

int s_empty(STACK* s){
    if (s->num == 0) return 0;
    else return -1;
}

char s_top(STACK* s){
    if (s->num == 0) return '\0';
    else return s->head->d;
}

//QUEUE METHOD

void q_push(QUEUE* q, DATA data){
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->d = data;
    tmp->next = NULL;
    if ((q->head) == NULL){
        q->head = tmp;
        q->tail = tmp;
    } else {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->num += 1;
}

char q_pop(QUEUE* q){
    NODE* new_head = q->head->next;
    DATA pop_d = q->head->d;
    free(q->head);
    q->num -= 1;
    q->head = new_head;
    return pop_d; 
}

int q_size(QUEUE* q){
    return q->num;
}

char q_front(QUEUE* q){
    if (q->num == 0) return '\0';
    return q->head->d;
}

char q_back(QUEUE* q){
    if (q->num == 0) return '\0';
    return q->tail->d;
}

int q_empty(QUEUE* q){
    if (q->num == 0) return 0;
    else return -1;
}