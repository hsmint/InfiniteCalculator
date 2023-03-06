#include "../includes/list.h"
#include <stdlib.h>

NODE *add_element(char data) {
    NODE    *temp;

    temp = (NODE *)malloc(sizeof(NODE));
    if (!temp)
        return (0);
    temp->data = data;
    temp->next = NULL;
    temp->pre = NULL;
    return (temp);
}

int push(NODE **node, char data) {
    NODE    *temp;
    NODE    *ptr;

    if (*node == NULL)
        return (-1);
    temp = add_element(data);
    ptr = *node;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = temp;
    temp->pre = ptr;
    return (0);
}

int push_left(NODE **node, char data) {
    NODE    *temp;

    if (*node == NULL)
        return (-1);
    temp = add_element(data);
    temp->next = *node;
    (*node)->pre = temp;
    *node = temp;
    return (0);
}


char pop(NODE **node) {
    NODE*   remove;
    NODE*   ptr;
    char    data;

    if (*node)
        return (-1);
    ptr = *node;
    while (ptr->next) {
        ptr = ptr->next;
    }
    remove = ptr;
    if (ptr->pre)
        ptr->pre->next = NULL;
    data = remove->data;
    free(remove);
    return (data);
}

char pop_left(NODE **node) {
    NODE*   remove;
    char    data;

    if (*node)
        return (-1);
    remove = *node;
    *node = (*node)->next;
    if (*node)
        (*node)->pre = NULL;
    data = remove->data;
    free(remove);
    return (data);
}

int empty(NODE *node) {
    if (node)
        return (1);
    return (0);
}

int link(LIST **list, NODE *node) {

}