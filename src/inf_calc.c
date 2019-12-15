#include "cal_fun.h"


void see(list*, stack*);

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
    int chk[4] = {0};
    chk[0] = chk[1] = chk[2] = chk[3] = 0;
    // chk[0] = '.', chk[1] = '(' 수 확인, chk[2] = 방금 전이 '(' 이였는지, chk[3] = 연산자 수 확인
    int play = 1;
    while(1){
        if (x == '(' || x == ')'){ // '()'
            if (x == '('){ //'('
                if (play) {
                    chk[1]++;
                    chk[2] = 1;
                    s_push(op, x);
                } else{
                    printf("Wrong input found from back.\nExiting...\n");
                    exit(1);
                }
            } else{
                if (chk[1]){
                    chk[1]--;
                    chk[2] = 0;
                    while(s_top(op) != '('){
                        if (s_top(op) == '+'){
                            see(link, op);
                            add(link);
                            s_pop(op);
                        } 
                        link->cnt--;
                        see(link, op);
                    }
                    s_pop(op);
                } else{
                    printf("Wrong input found: )\nExiting...\n");
                    exit(1);
                }
            }

        } else if (x == '+' || x == '-' || x == '*'){
            if (play == 0){
                printf("Wrong input found from back.\nExiting...\n");
                exit(1);
            } else if (x == '-' && chk[2]){
                data_push(link, x);
            } else if(chk[3]){
                printf("Wrong input found.\nExiting...\n");
                exit(1);
            } else if (x == '-'){
                s_push(op, '+');
                node_add(link);
                data_push(link, x);
                chk[3] = 1;
                chk[0] = 0;
            } else {
                s_push(op, x);
                node_add(link);
                chk[3] = 1;
                chk[0] = 0;
            }

        } else if ('0' <= x && x <= '9'){
            if (chk[0]) link->back->b_size++;
            else link->back->f_size++;
            data_push(link, x);
            chk[3] = 0;
            chk[2] = 0;

            
        } else if (x == '.'){
            if (chk[0]){
                printf("Wrong input found: %c\nExiting...\n", x);
                exit(1);
            } else{
                if (play && '0' <= y && y <= '9'){
                    data_push(link, x);
                    chk[0] = 1;
                }
            }

        } else{
            if (x != ' '){
                printf("Wrong input found: %c\nExiting...\n", x);
                exit(1);
            }
        }
        
        x = y;
        if (play){
            if (fscanf(ifp, "%c", &y) == EOF) play = 0;
        } else{
            break;
        }
    }

    see(link, op);
    // Last Calculate
    while(s_empty(op)){
        if (s_top(op) == '+'){
            add(link);
            s_pop(op);
            see(link, op);
        }
        link->cnt--;
    }
    
    //ERROR?
    if (link->cnt != 1){
        printf("Something gone wrong\nExiting...\n");
        exit(1);
    }

    // Check
    //see(link, op);
    printf("Finished Calculating.\n");
    printf("The result is : ");
    node* curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->head;
        while(num_curr != NULL){
            printf("%c", num_curr->data);
            num_curr = num_curr->next;
        }
        curr = curr->pre_data;
    }
    printf("\n");

    ofp = fopen("output", "w");
    curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->head;
        while(num_curr != NULL){
            fputc(num_curr->data, ofp);
            num_curr = num_curr->next;
        }
        curr = curr->pre_data;
    }
    //Finish    
    free(op);
    free(link);
    fclose(ifp);
    fclose(ofp);
    return 0;
}

void see(list* link, stack* op){
    printf("Showing what is inside in link\n");
    node* curr = link->back;
    while(curr != NULL){
        num* num_curr = curr->head;
        printf("NODE: ");
        while(num_curr != NULL){
            printf("%c", num_curr->data);
            num_curr = num_curr->next;
        }
        printf(" Front Size: %d Back Size: %d\n", curr->f_size ,curr->b_size);
        curr = curr->pre_data;
    }
    printf("\nShowing what is inside in stack\n");
    s_node* sc = op->head;
    while(sc != NULL){
        printf("DATA: %c\n", sc->op_data);
        sc = sc->next_node;
    }
    printf("\n");
}

//Calculate
void num_push(node* n, char d){
    printf("%c\n", d);
    num* tmp = (num*)malloc(sizeof(num));
    tmp->data = d;
    tmp->pre = NULL;
    if (n->tail == NULL) n->tail = tmp;
    else n->head->pre = tmp; 
    tmp->next = n->head;
    n->head = tmp;
}

int add_num(node* new_tmp, int up, int x){
    if (up){
        x++;
        up = 0;
    }
    if (x / 10 != 0){
        up = 1;
        x -= 10;
    }
    num_push(new_tmp, x+'0');
    return up;
}

int minus_num(node* new_tmp, int down, int x){
    if (down){
        x--;
        down = 0;
    }
    if (x < 0){
        x += 10;
        down = 1;
    }
    printf("%d\n", x);
    num_push(new_tmp, x+'0');
    return down;
}

void trash(node* n){
    num* cur = n->head;
    num* del = n->head;
    while(cur != NULL){
        del = cur;
        cur = cur->next;
        free(del);
    }
}

void add(list* link){
    node* a = link->back->pre_data;
    node* b = link->back;
    if(((a->head->data) == '-' && (b->head->data) != '-') || ((a->head->data) != '-' && (b->head->data) == '-')){ // a or b is minus
        if ((a->head->data) == '-') {
            //delete
            link->back->pre_data->head = link->back->pre_data->head->next;
            free(link->back->pre_data->head->pre);
            link->back->pre_data->head->pre = NULL;
            minus(link);

            //after minus
            if (link->back->head->data != '-') data_push(link, '-');
            else{
                link->back->head = link->back->head->next;
                free(link->back->head->pre);
                link->back->head->pre = NULL;
            }

        } else{
            link->back->head = link->back->head->next;
            free(link->back->head->pre);
            link->back->head->pre = NULL;
            minus(link);
        }
        return;

    } else{ // a and b both plus or a and b both minus
        //Setup
        node* new_tmp = (node*)malloc(sizeof(node));
        new_tmp->head = NULL;
        new_tmp->tail = NULL;
        new_tmp->pre_data = a->pre_data;
        new_tmp->next_data = b->next_data;
        link->back = new_tmp;
        num* ac = a->tail;
        num* bc = b->tail;
        int chk = 0, up = 0;

        //Putting who is bigger
        if ((a->f_size) >= (b->f_size)) new_tmp->f_size = a->f_size;
        else new_tmp->f_size = b->f_size;

        //Equal 
    	if((a->b_size)>(b->b_size)){
    		new_tmp->b_size = a->b_size;
            for (int i = 0; i < (a->b_size)-(b->b_size); i++){
                num_push(new_tmp, ac->data);
                ac = ac->pre;
            }
		} else if ((a->b_size)<(b->b_size)){
            new_tmp->b_size = b->b_size;
            for (int i = 0; i < (b->b_size)-(a->b_size); i++){
                num_push(new_tmp, bc->data);
                bc = bc->pre;
            }
        } else{
            new_tmp->b_size = a->b_size;
        }
        
        //'.' Check
        if ((a->b_size == 0 && b->b_size != 0) || (a->b_size != 0 && b->b_size == 0)){
            num_push(new_tmp, '.');
            if (a->b_size == 0) bc = bc->pre;
            else ac = ac->pre;
        }

        // Calculate
        while(1){
            if (ac->pre == NULL && bc->pre == NULL){ // ac bc 위치 일치
                break;
            } else if (ac->pre == NULL){ //a 노드가 짧은 경우
                chk = 1;
                break;
            } else if (bc->pre == NULL){ //b 노드가 짧은 경우
                chk = 2;
                break;
            } else if ((ac->data) == '.') num_push(new_tmp, '.');
            else{
                int x = ((ac->data)-'0')+((bc->data)-'0');
                up = add_num(new_tmp, up, x);
            }
            ac = ac->pre;
            bc = bc->pre;
        }

        // Equal
        if (chk == 1){
            if (ac->data != '-'){
                int x = ((ac->data)-'0')+((bc->data)-'0');
                up = add_num(new_tmp, up, x);
                bc = bc->pre;
                while(bc->pre != NULL){
                    x = (bc->data)-'0';
                    up = add_num(new_tmp, up, x);
                    bc = bc->pre;
                }
                x = (bc->data)-'0';
                up = add_num(new_tmp, up, x);
            } else {
                while(bc->pre != NULL){
                    int x = (bc->data)-'0';
                    up = add_num(new_tmp, up, x);
                    bc = bc->pre;
                }
            }
            if (up) {
                num_push(new_tmp, '1');
                new_tmp->f_size++;
            }
        } else if (chk == 2){
            if (bc->data != '-'){
                int x = ((ac->data)-'0')+((bc->data)-'0');
                up = add_num(new_tmp, up, x);
                ac = ac->pre;
                while(ac->pre != NULL){
                    x = (ac->data)-'0';
                    up = add_num(new_tmp, up, x);
                    ac = ac->pre;
                }
                x = (ac->data)-'0';
                up = add_num(new_tmp, up, x);
            } else{
                while(ac->pre != NULL){
                    int x = (ac->data)-'0';
                    up = add_num(new_tmp, up, x);
                    ac = ac->pre;
                }
            }
            if (up) {
                num_push(new_tmp, '1');
                new_tmp->f_size++;
            }
        } else{
            if (ac->data != '-'){
                int x = ((ac->data)-'0')+((bc->data)-'0');
                up = add_num(new_tmp, up, x);
            }
            if (up) {
                num_push(new_tmp, '1');
                new_tmp->f_size++;
            }
        }

        // Checking if '-' or calulate;
        if (ac->data == '-') num_push(new_tmp, '-');
        
        // freeing a and b;
        trash(a);
        trash(b);
        free(a);
        free(b);
    }
}

void minus(list* link){
    //Init
    node* a = link->back->pre_data;
    node* b = link->back;
    node* new_tmp = (node*)malloc(sizeof(node));
    new_tmp->head = NULL;
    new_tmp->tail = NULL;
    new_tmp->pre_data = a->pre_data;
    new_tmp->next_data = b->next_data;
    link->back = new_tmp;
    int chk = 0, down = 0, re = 0, front, back;
    num* ac;
    num* bc;

    //Size check
    if ((a->f_size) >= (b->f_size)){
        ac = a->tail;
        bc = b->tail;
        front = a->b_size;
        back = b->b_size;
        new_tmp->f_size = a->f_size;
    } else{
        ac = b->tail;
        bc = a->tail;
        front = b->b_size;
        back = a->b_size;
        new_tmp->f_size = b->f_size;
        re = 1;
    }
    int shift = front-back;
    
    //Equal
    if(front > back){
    	new_tmp->b_size = front;
        for (int i = 0; i < front-back; i++){
            num_push(new_tmp, ac->data);
            ac = ac->pre;
        }
	} else if (front < back){
        new_tmp->b_size = back;
        int x = 10 - ((bc->data)-'0');
        num_push(new_tmp, x+'0');
        bc = bc->pre;
        for (int i = 0; i < back-front-1; i++){
            printf("%d\n", ((bc->data)-'0'));
            x = 9 - ((bc->data)-'0');
            num_push(new_tmp, x+'0');
            bc = bc->pre;
        }
        down = 1;
    } else{
        new_tmp->b_size = front;
    }

    //'.' Check
    if ((front == 0 && back != 0) || (front != 0 && back == 0)){
        num_push(new_tmp, '.');
        if (front == 0) bc = bc->pre;
        else ac = ac->pre;
    }

    // Calculate
    while(1){
        if (bc == NULL){
            break;
        } else if ((ac->data) == '.') num_push(new_tmp, '.');
        else{
            int x = ((ac->data)-'0')-((bc->data)-'0');
            down = minus_num(new_tmp, down, x);
        }
        ac = ac->pre;
        bc = bc->pre;
    }


    //Last Calculate
    while(ac != NULL){
        int x = ((ac->data)-'0');
        down = minus_num(new_tmp, down, x);
        ac = ac->pre;
    }


    //Delecting front 0s
    if (new_tmp->head->data == '0'){
        num* curr = new_tmp->head;
        while(curr->data == '0'){
            curr = curr->next;
            free(curr->pre);
            curr->pre = NULL;
        }
        new_tmp->head = curr;
    }

    if ((re && !down) || (!re && down)){
        num_push(new_tmp, '-');
    }

    //freeing a and b;
    trash(a);
    trash(b);
    free(a);
    free(b);
}