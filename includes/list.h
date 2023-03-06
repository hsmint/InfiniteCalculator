#ifndef LIST_H
#define LIST_H

typedef struct node {
    char data;
    struct node *pre;
    struct node *next;
} NODE;

typedef struct list {
    int decimal_size;
    int float_size;
    NODE *head;
    NODE *tail;
} LIST;

NODE *add_element(char data);

int push_left(NODE **node, char data);

int push(NODE **node, char data);

char pop(NODE **node);

char pop_left(NODE **node);

int empty(NODE *node);

int link(LIST **list, NODE *node);

#endif