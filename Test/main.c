#include "cal_fun.h"

int main(){
    //init
    list* link = (list*)malloc(sizeof(list));
    stack* op = (stack*)malloc(sizeof(stack));
    init(link);
    s_init(op);
    
    //function
    s_push(op, '+');
    s_push(op, '-');
    printf("This is num size: %d\n", op->cnt);
    printf("This is what is in the top: %c\n", op->head->op_data);
    //end
    printf("Success\n");
    free(link);
    free(op);
    return 0;
}