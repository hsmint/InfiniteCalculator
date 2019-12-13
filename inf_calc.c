#include "cal_fun.h"

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

    // file read
    ifp = fopen(argv[1], "r");
    
    // Init
    list* link = (list*)malloc(sizeof(list));
    stack* op = (stack*)malloc(sizeof(stack)); 
    char x, y;
    init(link);
    s_init(op);

    if (fscanf(ifp, "%c", &x) == EOF){
        printf("No input in file.\n");
        exit(1);
    }
    
    // Save
    printf("Calculating...\n");
    int* chk = (int*)malloc(sizeof(int)*4);
    chk[0] = chk[1] = chk[2] = chk[3] = 0;
    // chk[0] = '.', chk[1] = '(' 수 확인, chk[2] = 방금 전이 '(' 이였는지, chk[3] = 연산자 수 확인
    while(fscanf(ifp, "%c", &y) != EOF){
        if (x == ' '){
            continue;

        } else if (x == '(' || x == ')'){
            if (x == '('){
                chk[1]++;
                chk[2] = 1;
            } else{
                if (chk[1]){
                    chk[1]--;
                    chk[2] = 0;
                } else{
                    printf("Wrong input found: )\nExiting...\n");
                    exit(1);
                }
            }

        } else if (x == '+' || x == '-' || x == '*'){
            if (x == '-' && chk[2]){
                data_push(link, x);
            } else if(chk[3]){
                printf("Wrong input found.\nExiting...\n");
                exit(1);
            } else{
                s_push(op, x);
                node_add(link);
                chk[3] = 1;
                chk[0] = 0;
            }

        } else if ('0' <= x && x <= '9'){
            if (chk[0]) link->back->size++;
            data_push(link, x);
            chk[3] = 0;
            chk[2] = 0;

            
        } else if (x == '.'){
            if (chk[0]){
                printf("Wrong input found: %c\nExiting...\n", x);
                exit(1);
            } else{
                data_push(link, x);
                chk[0] = 1;
            }

        } else{
            printf("Wrong input found: %c\nExiting...\n", x);
            exit(1);
        }
        x = y;
    }
    
    // Check
    printf("Showing what is inside in link\n");
    node* curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->head;
        printf("NODE: ");
        while(num_curr != NULL){
            printf("%c", num_curr->data);
            num_curr = num_curr->next;
        }
        printf(" Size: %d\n", curr->size);
        curr = curr->next_data;
    }
    printf("Finish\n");

    //Finish    
    free(op);
    free(link);
    return 0;
}

//e.set_image(url="attachment://image.png")
//await messagable.send(file=f, embed=e)