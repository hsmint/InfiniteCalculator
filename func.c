#include "cal_fun.h"

void init(list* l){
    l->cnt = 0;
    l->back = NULL;
    node_add(l);
}

void node_add(list* l){
    node* tmp = (node*)malloc(sizeof(node));
    if (l->back != NULL) l->back->next_data = tmp;
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->pre_data = l->back;
    tmp->next_data = NULL;
    l->back = tmp;
    l->cnt++;
}

void data_push(list* l, char d){
    num* tmp = (num*)malloc(sizeof(num));
    tmp->data = d;
    tmp->next = NULL;
    if (l->back->head == NULL){
        l->back->head = tmp;
        l->back->tail = tmp;
        tmp->pre = NULL;
    } else{
        tmp->pre = l->back->tail;
        l->back->tail->next = tmp;
        l->back->tail = tmp;
    }
}

// Stack function
void s_init(stack* s){
    s->cnt = 0;
    s->head = NULL;
}

void s_push(stack* s, char d){
    s_node* tmp = (s_node*)malloc(sizeof(s_node));
    tmp->op_data = d;
    tmp->next_node = s->head;
    s->head = tmp;
    s->cnt++;
}

char s_top(stack* s){
    if (s->cnt == 0) return '\0';
    return s->head->op_data;
}

int s_empty(stack* s){
    if (s->cnt == 0) return 0;
    return 1;
}

int s_pop(stack* s){
    if (s->cnt == 0) return 0;
    s_node* del = s->head;
    s->head = s->head->next_node;
    free(del);
    s->cnt--;
    return 1;
}

//Calculate
void num_push(node* n, char d){
    printf("Pushing : %c\n", d);
    num* tmp = (num*)malloc(sizeof(num));
    tmp->data = d;
    tmp->pre = NULL;
    if (n->tail == NULL) n->tail = tmp; 
    tmp->next = n->head;
    n->head = tmp;
}

void node_init(node* n){
    n->size = 0;
    n->tail = NULL;
    n->head = NULL;
    n->next_data = NULL;
    n->pre_data = NULL;
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
            node* save = a->pre_data;
            num* del = a->head;
            a->head = a->head->next;
            a->head->pre = NULL;
            free(del);
            minus(a, b);
            if (save->next_data->head->data != '-') num_push(save->next_data, '-');
            return;
        } else{
            num* del = b->head;
            b->head = b->head->next;
            b->head->pre = NULL;
            free(del);
            minus(a, b);
            return;
        }

    } else{ // a and b both plus or a and b both minus
        node* new_tmp = (node*)malloc(sizeof(node));
        node_init(new_tmp);
        num* ac = a->tail;
        num* bc = b->tail;

        //Equal
    	if((a->size)>(b->size)){
    		new_tmp->size = a->size;
            for (int i = 0; i < (a->size)-(b->size); i++){
                num_push(new_tmp, ac->data);
                ac = ac->pre;
            }
		} else if ((a->size)<(b->size)){
            new_tmp->size = b->size;
            for (int i = 0; i < (b->size)-(a->size); i++){
                num_push(new_tmp, bc->data);
                bc = bc->pre;
            }
        } else{
            new_tmp->size = a->size;
        }
        
        //'.' Check
        if ((a->size == 0 && b->size != 0) || (a->size != 0 && b->size == 0)){
            num_push(new_tmp, '.');
            if (a->size == 0) bc = bc->pre;
            else ac = ac->pre;
        }

        // Calculate
        int chk = 0, up = 0;
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
                if (up) {
                    x++;
                    up = 0;
                }
                if (x / 10 != 0){
                    up = 1;
                    x -= 10;
                }
                num_push(new_tmp, x+'0');
            }
            ac = ac->pre;
            bc = bc->pre;
        }

        // Equal
        if (chk == 1){
            while(bc->pre != NULL){
                num_push(new_tmp, bc->data);
                bc = bc->pre;
            }
        } else if (chk == 2){
            while(ac->pre != NULL){
                num_push(new_tmp, ac->data);
                ac = ac->pre;
            }
        }

        // Checking if '-' or calulate;
        if (ac->data == '-') num_push(new_tmp, '-');
        else{
            int x = (ac->data - '0') + (bc->data - '0');
            printf("The last input: %d\n", x);
            if (x / 10 == 0){
                num_push(new_tmp, x+'0');
            } else{
                x -= 10;
                num_push(new_tmp, x+'0');
                num_push(new_tmp, '1');
            }
        }

        // Putting into node list;
        new_tmp->pre_data = a->pre_data;
        new_tmp->next_data = b->next_data;
        link->back = new_tmp;

        // freeing a and b;
        trash(a);
        trash(b);
        free(a);
        free(b);
    }
}

void minus(node* a, node* b){
    if (a->head->data == '-' && b->head->data == '-'){
        // Make
        num* ac = a->tail;
        num* bc = b->tail;
        node* new_tmp = (node*)malloc(sizeof(node));
        node_init(new_tmp);

        // Delete
        num* del = b->head;
        b->head = b->head->next;
        del->next->pre = NULL;
        free(del);

        // Equal
        if ((a->size) > (b->size)){
            new_tmp->size = a->size;

        } else if ((a->size) < (b->size)){
            for (int i = 0; i < (b->size)-(a->size); i++){
                int x = 10 - (int)(bc->data);
                num_push(new_tmp, (char)x);
            }
        }

        // Calculate
        while(1){
            if (ac->pre == NULL){

            } else if (bc->pre == NULL){

            }

        }

    } else if (a->head->data == '-' || b->head->data == '-'){
        if (a->head->data == '-'){
            node* save = a->pre_data;
            num* del = a->head;
            a->head = a->head->next;
            del->next->pre = NULL;
            free(del);
            if (save->next_data->head->data != '-') num_push(save->next_data, '-');
        } else{
            num* del = b->head;
            b->head = b->head->next;
            del->next->pre = NULL;
            free(del);
        }
        return;

    } else{
        node* new_tmp = (node*)malloc(sizeof(node));
        node_init(new_tmp);
        num* ac = a->tail;
        num* bc = b->tail;
        if ((a->size) > (b->size)){
            for (int i = 0; i < (a->size)-(b->size); i++){
                num_push(new_tmp, ac->data);
            }
        } else if ((a->size) < (b->size)){
            for (int i = 0; i < (b->size)-(a->size); i++){
                int x = 10 - (int)(bc->data);
                num_push(new_tmp, (char)x);
            }
        }
        while(1){
            if (ac->pre == NULL){

            } else if (bc->pre == NULL){

            }

        }
    }
}

// void multiply(node* a, node* b){

// }