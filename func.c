#include "cal_fun.h"

void(*func_p(const char opCode))(NODE*, NODE*){
    if (opCode == '+'){
        return &add;
    } else{
        return &minus;
    }
}

NODE* add(NODE* a, NODE* b){
    NODE* new_num = (NODE*)malloc(sizeof(NODE));

    return new_num;
}

NODE* minus(NODE* a, NODE* b){
    NODE* new_num = (NODE*)malloc(sizeof(NODE));

    return new_num;
}