#include "cal_fun.h"

//Calculate
void num_push(node* n, char d){
    num* tmp = (num*)malloc(sizeof(num));
    tmp->data = d;
    tmp->pre = NULL;
    if (n->tail == NULL) n->tail = tmp;
    else n->head->pre = tmp; 
    tmp->next = n->head;
    n->head = tmp;
}

int add_num(node* new_tmp, int up, int x){
    x += up;
    up = 0;
    if (x/10 != 0){
        up = x / 10;
        x %= 10;
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
    if (new_tmp->head->data == '0' && new_tmp->f_size != 1){
        num* curr = new_tmp->head;
        while(curr->data == '0' && new_tmp->f_size != 1){
            curr = curr->next;
            free(curr->pre);
            curr->pre = NULL;
            new_tmp->f_size--;
        }
        new_tmp->head = curr;
    }

    if ((re && !down) || (!re && down)){
        if (new_tmp->f_size == 1){
            new_tmp->head->data = '0';
            num* curr = new_tmp->tail;
            int x = 10 - ((curr->data)-'0');
            curr->data = (x+'0');
            curr = curr->pre;
            for (int i = 0; i < (new_tmp->b_size)-1; i++){
                x = 9 - ((curr->data)-'0');
                curr->data = (x+'0');
                curr = curr->pre;
            }
        }
        num_push(new_tmp, '-');
    }

    //freeing a and b;
    trash(a);
    trash(b);
    free(a);
    free(b);
}

void multiply(list* link){
    node* a = link->back->pre_data;
    node* b = link->back;
    //init
    node* new_tmp = (node*)malloc(sizeof(node));
    new_tmp->head = NULL;
    new_tmp->tail = NULL;
    new_tmp->f_size = 0;
    new_tmp->pre_data = a->pre_data;
    new_tmp->next_data = b->next_data;
    new_tmp->b_size = (a->b_size) + (b->b_size);
    link->back = new_tmp;
    num* ac = a->tail;
    num* bc = b->tail;
    int chk = 0, multi = 0, count = 0, x, sign = 0;

    //Minus out
    if (a->head->data == '-' && b->head->data == '-'){
        a->head = a->head->next;
        b->head = b->head->next;
        free(a->head->pre);
        free(b->head->pre);
        a->head->pre = NULL;
        b->head->pre = NULL;
    } else if (a->head->data == '-'){
        a->head = a->head->next;
        free(a->head->pre);
        a->head->pre = NULL;
        chk = 1;
    } else if (b->head->data == '-'){
        b->head = b->head->next;
        free(b->head->pre);
        b->head->pre = NULL;
        chk = 1;
    }

    // Multiply once
    while(ac != NULL){
        if (ac->data != '.' && bc->data != '.'){
            x = ((ac->data)-'0')*((bc->data)-'0');
            multi = add_num(new_tmp, multi, x);
            new_tmp->f_size++;
        }
        ac = ac->pre;
    }
    if (multi){
        num_push(new_tmp, multi+'0');
        multi = 0;
        new_tmp->f_size++;
    }

    ac = a->tail;
    bc = bc->pre;
    num* tc = new_tmp->tail;

    // Multiply Calculate
    while(bc != NULL){
        for (int i = 0; i < count; i++){
            tc = tc->pre;
        }
        while(ac != NULL){
            if (ac->data != '.' && bc->data != '.'){
                x = ((ac->data)-'0')*((bc->data)-'0') + multi;
                multi = 0;
                if (x /10 != 0){
                    multi = x / 10;
                    x %= 10;
                }
                if (tc->pre == NULL){
                    new_tmp->f_size++;
                    num_push(new_tmp, x+'0');
                } else {
                    tc = tc->pre;
                    x += ((tc->data)-'0');
                    if (x / 10 != 0){
                        multi += x / 10;
                        x %= 10;
                    }
                    tc->data = (x+'0');
                }
                
            }else if (bc->data == '.') {
                sign = 1;
                break;
            }
            ac = ac->pre;
        }
        if (sign == 0) count++;

        if (multi){
            num_push(new_tmp, multi+'0');
            new_tmp->f_size++;
        }
        bc = bc->pre;
        ac = a->tail;
        tc = new_tmp->tail;
        multi = 0;
        sign = 0;
    }

    // Putting '.'
    if(new_tmp->b_size != 0){
        tc = new_tmp->tail;
        for (int i = 0; i < (new_tmp->b_size)-1; i++){
            tc = tc->pre;
        }
        num* tmp = (num*)malloc(sizeof(num));
        tmp->data = '.';
        tmp->pre = tc->pre;
        tmp->next = tc;
        tc->pre->next = tmp;
        tc->pre = tmp;
    }
    
    if (chk){
        num_push(new_tmp, '-');
    }
    new_tmp->f_size -= (new_tmp->b_size);
    //freeing a and b;
    trash(a);
    trash(b);
    free(a);
    free(b);
}