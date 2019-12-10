#include "cal_fun.h"

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
    fclose(ifp);

    // Init
    list* link = (list*)malloc(sizeof(list));
    stack* op = (stack*)malloc(sizeof(stack)); 
    init(link);
    s_init(op);

    // Save
    int* check = (int*)malloc(sizeof(int)*3);
    check[0] = check[1] = check[2] = 0;
    while(*buf != '\0'){
        if (*buf == ' '){
            continue;
        }
        else if (*buf == '+' || *buf == '-' || *buf == '(' || *buf == ')') {
            if (*buf == ')') {
                buf++;
                continue;
            } else {
                if (check[0] == 0){
                    s_push(op, *buf);
                    node_add(link);
                    check[0] = 1;
                } else{
                    s_push(op, *buf);
                    check[0] = 0;
                }
            }
            check[1] = 0;
        } else {
            if (*buf == '.') check[1] = 1;
            data_push(link, *buf);
            if (check) link->back->size++;
        }
        buf++;
    }
    free(check);
    
    // Check
    printf("Showing what is inside in link\n");
    node* curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->head;
        printf("NODE: ");
        while(num_curr != NULL){
            printf("%c ", num_curr->data);
            num_curr = num_curr->next;
        }
        printf("\n");
        curr = curr->next_data;
    }
    printf("Finish\n");

    //Finish    
    free(op);
    free(link);
    return 0;
}

