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
    int one = 1;
    init(link);
    s_init(op);

    if (fscanf(ifp, "%c", &x) == EOF){
        printf("No input in file.\n");
        exit(1);
    }
    if (fscanf(ifp, "%c", &y) == EOF){
        one = 0;
        data_push(link, x);
    }

    // Save
    printf("Calculating...\n");
    int chk[5] = {0};
    // chk[0] = '.', chk[1] = '(' 수 확인, chk[2] = 방금 전이 '(' 이였는지, chk[3] = 연산자 수 확인, chk[4] = -(-) 확인
    int play = 1;
    while(one){
        if (x == '(' || x == ')'){ // '()'
            if (x == '('){ // x = (
                if (play) {
                    chk[1]++;
                    chk[2] = 1;
                    s_push(op, x);
                } else{
                    printf("Wrong input found from back.\nExiting...\n");
                    exit(1);
                }

            } else{ // x = )
                if (chk[1]){ // ( not 0
                    chk[1]--;
                    chk[2] = 0;
                    while(s_top(op) != '('){
                        if (s_top(op) == '+'){
                            add(link);
                            s_pop(op);
                        } else{
                            multiply(link);
                            s_pop(op);
                        }
                        link->cnt--;
                    }
                    s_pop(op);

                } else{ // There is no (
                    printf("Wrong input found: )\nExiting...\n");
                    exit(1);
                }
            }

        } else if (x == '+' || x == '-' || x == '*'){
            if (play == 0){ //Next is EOF
                printf("Wrong input found from back.\nExiting...\n");
                exit(1);

            } else if (x == '-' && chk[2]){ // ( after - 
                if (!chk[4]) data_push(link, x); // not -(-
                else{ //-(-
                    free(link->back->head);
                    link->back->head = NULL;
                }

            } else if(chk[3]){ //function more than 1
                printf("Wrong input found. Here\nExiting...\n");
                exit(1);

            } else{ // * + -
                if (x == '+' || x == '-'){ // + -
                    if (s_top(op) == '*'){
                        multiply(link);
                        s_pop(op);
                        link->cnt--;
                    }
                    s_push(op, '+');
                } else { // *
                    s_push(op, x);
                }
                node_add(link);
                if (x == '-') {// - to + so push -
                    data_push(link, x);
                    chk[4] = 1;
                }
                chk[3] = 1;
                chk[0] = 0;
            }

        } else if ('0' <= x && x <= '9'){ //Numbers
            if (chk[0]) link->back->b_size++;
            else link->back->f_size++;
            data_push(link, x);
            chk[2] = 0;
            chk[3] = 0;
            chk[4] = 0;

        } else if (x == '.'){ // . in
            if (chk[0]){ // Too many .
                printf("Wrong input found: %c\nExiting...\n", x);
                exit(1);
            } else{
                if (play && '0' <= y && y <= '9'){
                    data_push(link, x);
                    chk[0] = 1;
                }
            }

        } else{ // Some other words or inputs
            if (x != ' ' && x != '\n'){
                printf("Wrong input found. Something gone wrong.\nExiting...\n");
                exit(1);
            }
        }
        
        // Final
        x = y;
        if (play){ // checking if y made to EOF
            if (fscanf(ifp, "%c", &y) == EOF) play = 0;
        } else{
            break;
        }
    }

    // Last Calculate
    while(s_empty(op)){
        if (s_top(op) == '+'){
            add(link);
            s_pop(op);
        } else{
            multiply(link);
            s_pop(op);
        }
        link->cnt--;
    }
    
    //ERROR?
    if (link->cnt != 1){
        printf("Something gone wrong\nExiting...\n");
        exit(1);
    }
    
    printf("Finished Calculating.\n");

    //Putting in to string
    int size = (link->back->f_size)+(link->back->b_size) + 2;
    char ans[size];
    node* curr = link->back;
    int i = 0;
    while(curr != NULL){
        num* num_curr = curr->head;
        while(num_curr != NULL){
          ans[i] = (num_curr->data);
          num_curr = num_curr->next;
          i++;
        }
        ans[i] = '\0';
        curr = curr->next_data;
    }
    
    // Check
    printf("The result is : %s\n", ans);

    ofp = fopen("output", "w");
    fputs(ans, ofp);

    //Finish    
    free(op);
    free(link);
    fclose(ifp);
    fclose(ofp);
    return 0;
}