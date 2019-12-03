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
    int check = 0;
    while(*buf != '\0'){
        if (*buf == ' ') continue;
        elif (*buf == '+' || *buf == '-' || *buf == '(' || *buf == ')'){
            if (check){
                data_push(link, *buf);
            } else{
                node_add(link);
                data_push(link, *buf);
            }
            if (*(buf+1) != '\0') node_add(link);
            s_push(op, *buf);
            check = 1;
        } else {
            data_push(link, *buf);
            check = 0;
        }
        buf++;
    }
    
    // Check
    printf("Showing what is inside in link\n");
    node* curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->tail;
        printf("Data: ");
        while(num_curr != NULL){
            printf("%c", num_curr->data);
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

