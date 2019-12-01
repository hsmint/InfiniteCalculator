#include <stdio.h>
#include "cal_fun.h"

//함수 호출
int read(FILE*, char**);


//메인
int main(int argc, char* argv[]){
    char* buf;
    FILE *ifp, *ofp;

    // argument check
    if (argc != 2){
        printf("\n%s%s%s\n\n%s\n%s\n\n",
        "Usage: ", argv[0], " infile  outfile",
        "The uppercase letters in infile will be counted.",
        "The results will be written in outfile.");
        exit(1);
    }
    
    // Read from File
    ifp = fopen(argv[1], "r");
    long long t_size = read(ifp, &buf) + 1;

    // Init
    STACK* op = (STACK*)malloc(sizeof(STACK));
    LIST* link = (LIST*)malloc(sizeof(LIST));
    s_init(op);
    init(link);
    
    // Operation
    char* cpy;
    strcpy(cpy, buf);
    printf("Finished\n");
    //finish
    free(op);
    free(link);
    return 0;
}

//함수
int read(FILE* ifp, char** buf){
    fseek(ifp, 0, SEEK_END);
    int size = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    *buf = (char*)malloc((sizeof(char))*size);
    fscanf(ifp, "%s", *buf);
    return size;
}

