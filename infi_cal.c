#include <stdio.h>
#include "node.h"
#include "func.h"

void read(FILE* ifp, char* buf){
    fseek(ifp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    int size = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    buf = (char*)malloc(sizeof(char)*size);
    fread(buf, 1, size, ifp);
}

int main(int argc, char* argv[]){
    char* buf;
    FILE *ifp, *ofp;
    int size;
    if (argc != 3){
        printf("\n%s%s%s\n\n%s\n%s\n\n",
        "Usage: ", argv[0], "   infile  outfile",
        "The uppercase letters in infile will be counted.",
        "The results will be written in outfile.");
        exit(1);
    }
    ifp = fopen(argv[1], "r");
    ofp = fopen(argv[2], "w");
    read(ifp, buf);
    
    return 0;
}