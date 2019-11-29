#include <stdio.h>
#include "cal_fun.h"

//함수 호출
void read(FILE*, char**);

void store(LIST*, LIST*, char*);

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
    read(ifp, &buf);

    // Init
    LIST* oper = (LIST*)malloc(sizeof(LIST));
    init(oper);
    LIST* link = (LIST*)malloc(sizeof(LIST));
    init(link);

    //
    

    //finish

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

void store(LIST* link, LIST* oper, char* buf){
    char* find = "()+-";
    char* seek;
    int index = strstr(buf, find);
    push(oper, buf[index]);
    for (seek = strtok(buf, find); seek != NULL; seek = strtok(NULL, find)){
        index = strstr(seek, find);
        push(link, seek);
        push(oper, buf[index]);
        printf("%s", seek);
    }
}