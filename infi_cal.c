#include <stdio.h>
#include <string.h>
#include "Header/node.h"
#include "Header/func.h"

//함수 호출
void read(FILE* ifp, char** buf);


//메인
int main(int argc, char* argv[]){
    char* buf;
    FILE *ifp, *ofp;
    if (argc != 2){
        printf("\n%s%s%s\n\n%s\n%s\n\n",
        "Usage: ", argv[0], " infile  outfile",
        "The uppercase letters in infile will be counted.",
        "The results will be written in outfile.");
        exit(1);
    }
    ifp = fopen(argv[1], "r");
    read(ifp, &buf);

    return 0;
}

//함수
void read(FILE* ifp, char** buf){
    fseek(ifp, 0, SEEK_END);
    int size = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    *buf = (char*)malloc((sizeof(char))*size);
    fscanf(ifp, "%s", *buf);
}