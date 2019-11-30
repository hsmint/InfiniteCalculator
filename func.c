#include "cal_fun.h"

void(*func_p(const char opCode))(NODE*, NODE*){
    if (opCode == '+'){
        return &add;
    } else{
        return &minus;
    }
}

void add(NODE* a, NODE* b){
    NODE* new_num = (NODE*)malloc(sizeof(NODE));

}

void minus(NODE* a, NODE* b){
    NODE* new_num = (NODE*)malloc(sizeof(NODE));

}