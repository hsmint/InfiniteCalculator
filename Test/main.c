#include "cal_fun.h"

int main(){
    //init
    list* link = (list*)malloc(sizeof(list));
    stack* op = (stack*)malloc(sizeof(stack));
    init(link);
    s_init(op);
    
    //function
    data_push(link, '1');
    data_push(link, '2');
    data_push(link, '3');
    node_add(link);
    data_push(link, '4');
    data_push(link, '5');
    data_push(link, '6');
    node* curr = link->back;
    while(curr != NULL){
        printf("DATA: ");
        num* cn = curr->head;
        while(cn != NULL){
            printf("%c", cn->data);
            cn = cn->next;
        }
        printf("\n");
        curr = curr->next_data;
    }
    //end
    printf("Success\n");
    free(link);
    free(op);
    return 0;
}