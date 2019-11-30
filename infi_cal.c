#include <stdio.h>
#include "cal_fun.h"

//함수 호출
int read(FILE*, char**);

void store(LIST*, char*);

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
    int t_size = read(ifp, &buf) + 1;
    // Init
    LIST* oper = (LIST*)malloc(sizeof(LIST));
    init(oper);
    LIST* link = (LIST*)malloc(sizeof(LIST));
    init(link);

    // Save number
    char* cpy = (char*)malloc(sizeof(char)*t_size);
    strcpy(cpy, buf);
    store(link, cpy);
    free(cpy);

    // Operation
    
    //finish
    free(oper);
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

void store(LIST* link, char* buf){
    char* oper = "+-()";
    char* oper_c = "+-";
    char* seek;
    printf("%s\n", buf);
    char* search = strpbrk(buf, oper_c);
    printf("%s\n", search);
    char* op = (char*)malloc(sizeof(char)*2);
    op[1] = 0;
    for (seek = strtok(buf, oper); seek != NULL; seek = strtok(NULL, oper)){
        push(link, seek);
        if (search != NULL){
            op[0] = search[0];
            push(link, op);
            search = strpbrk(search+1, oper_c);
        }
    }
    printf("Finished\n");
    free(op);
}