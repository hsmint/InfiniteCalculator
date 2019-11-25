#include "Header/func.h"
#include "Header/node.h"

void(*func_p(const char opCode))(NODE, NODE){
    if (opCode == '+'){
        return &add;
    } else{
        return &minus;
    }
}

void add(NODE a, NODE b){

}

void minus(NODE a, NODE b){

}