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
    printf("Calculating...\n");
    int* chk = (int*)malloc(sizeof(int)*4);
    chk[0] = chk[1] = chk[2] = chk[3] = 0;
    //check[0] = 연산자 수 확인, check[1] = '.' 수 확인, check[2] = '(' 수 확인, check[3] = 전이 '('이였는지
    while(*buf != '\0'){
        if (*buf == ' '){
            continue;
        }
        else if (*buf == '+' || *buf == '-' || *buf == '(' || *buf == ')') {
            if (*buf == ')') { // ')' 이면
                buf++;
                if (chk[2] == 0){
                    printf("Wrong squence found.\nExiting...\n");
                    exit(1);
                }
                chk[2]--;
                continue;
            } else if (*(buf+1) == '\0'){
                printf("Wrong squence found.\nExiting...\n");
                exit(1);
            } else if (*buf == '('){ // '(' 이면
                chk[2]++;
                chk[0]--;
                chk[3] = 1;
                s_push(op, *buf);
            } else if (*buf == '-' && chk[3] == 1){ //'(' 다음 -이면ㅡㅡ
                chk[3] = 0;
                data_push(link, *buf);
            }
            else {
                if (chk[0] == 0){
                    s_push(op, *buf);
                    node_add(link);
                    chk[0] = 1;
                } else{
                    s_push(op, *buf);
                    chk[0] = 0;
                }
            }
            chk[1] = 0;
        } else {
            if (chk[1]) link->back->size++;
            if (*buf == '.' & chk[1] != 0){
                printf("Wrong squence found.\nExiting...\n");
                exit(1);
            } else if (*buf == '.'){
                chk[1] = 1;
            }
            data_push(link, *buf);
            chk[0] = 0;
        }
        buf++;
    }
    free(chk);
    
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
        printf(" Size: %ld\n", curr->size);
        curr = curr->next_data;
    }
    printf("Finish\n");

    //Finish    
    free(op);
    free(link);
    return 0;
}

