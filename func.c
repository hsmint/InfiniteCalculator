#include "cal_fun.h"

void init(list* l){
    l->cnt = 0;
    l->back = NULL;
    node_add(l);
}

void node_add(list* l){
    node* tmp = (node*)malloc(sizeof(node));
    if (l->back != NULL) l->back->pre_data = tmp;
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->next_data = l->back;
    tmp->pre_data = NULL;
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

//Calculate
void num_push(node* n, char d){
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

void equal(node* in, node* out, int size){
    num* cur = in->tail;
    for (int i = 0; i < size; i++){
        num_push(out, cur->data);
        cur = cur->pre;
    }
}

// void add(node* a, node* b){
//     //file here!
//     if (a->head == '-' && b->head == '-'){
        
//         //Make
//         node* new_tmp = (node*)malloc(sizeof(node));
//         node_init(new_tmp);
//     	int cnt = 0;
//     	if((a-> size)>(b->size)){
//     		new_tmp->size = a->size;
//             equal(a, new_tmp, (a->size)-(b->size));
// 		} else{
//             new_tmp->size = b->size;
//             equal(b, new_tmp, (b->size)-(a->size));
//         }

//         //Calculate
//         if ((a->size) == 0 || (b->size) == 0){

//         } else if ((a->size) == 0){

//         } else if ((b->size) == 0){

//         }
//         num* ac = a->tail;
//         num* bc = b->tail;
// 		while(ac->data != '-' && bc->data != '-'){
// 			if (1){
                
//             } else{
// 				int sum, up;
// 				sum = atoi(a -> tail) + atoi(b -> tail) + up;
// 				up = 0;
// 				if(sum > 9){
// 					sum -= 10;
// 					up = 1;
// 				}
// 				num_push(new_tmp, (char)sum);
// 				cnt ++;
// 			}
// 		}
// 		if(a -> tail == '-'){
// 			while(b -> tail == '-'){
// 				num_push(new_tmp, b -> tail);
// 				b -> tail = b -> tail -> pre;
// 			}
// 		}else{
// 			while(a -> tail == '-'){
// 				num_push(new_tmp, a -> tail);
// 				a -> tail = a -> tail -> pre;
// 			}
// 		}
// 		num_push(new_tmp,'-');

//     } else if (a->head == '-' || b->head == '-'){
//         if (a->head == '-'){
//             node* save = a->pre_data;
//             num* del = a->head;
//             a->head = a->head->next;
//             a->head->pre = NULL;
//             free(del);
//             minus(a, b);
//             if (save->next_data->head != '-') num_push(save->next_data, '-');
//             return;
//         } else{
//             num* del = b->head;
//             b->head = b->head->next;
//             b->head->pre = NULL;
//             free(del);
//             minus(a, b);
//             return;
//         }

//     } else{
//         node* new_tmp = (node*)malloc(sizeof(node));
//         node_init(new_tmp);
//     }
// }

// void minus(node* a, node* b){
//     if (a->head == '-' && b->head == '-'){
//         // Make
//         num* ac = a->tail;
//         num* bc = b->tail;
//         node* new_tmp = (node*)malloc(sizeof(node));
//         node_init(new_tmp);

//         // Delete
//         num* del = b->head;
//         b->head = b->head->next;
//         del->next->pre = NULL;
//         free(del);

//         // Equal
//         if ((a->size) > (b->size)){
//             new_tmp->size = a->size;
//             equal(a, new_tmp, (a->size)-(b->size));

//         } else if ((a->size) < (b->size)){
//             for (int i = 0; i < (b->size)-(a->size); i++){
//                 int x = 10 - (int)(bc->data);
//                 num_push(new_tmp, (char)x);
//             }
//         }

//         // Calculate
//         while(1){
//             if (ac->pre == NULL){

//             } else if (bc->pre == NULL){

//             }

//         }

//     } else if (a->head == '-' || b->head == '-'){
//         if (a->head == '-'){
//             node* save = a->pre_data;
//             num* del = a->head;
//             a->head = a->head->next;
//             del->next->pre = NULL;
//             free(del);
//             add(a, b);
//             if (save->next_data->head != '-') num_push(save->next_data, '-');
//         } else{
//             num* del = b->head;
//             b->head = b->head->next;
//             del->next->pre = NULL;
//             free(del);
//             add(a, b);
//         }
//         return;

//     } else{
//         node* new_tmp = (node*)malloc(sizeof(node));
//         node_init(new_tmp);
//         num* ac = a->tail;
//         num* bc = b->tail;
//         if ((a->size) > (b->size)){
//             for (int i = 0; i < (a->size)-(b->size); i++){
//                 num_push(new_tmp, ac->data);
//             }
//         } else if ((a->size) < (b->size)){
//             for (int i = 0; i < (b->size)-(a->size); i++){
//                 int x = 10 - (int)(bc->data);
//                 num_push(new_tmp, (char)x);
//             }
//         }
//         while(1){
//             if (ac->pre == NULL){

//             } else if (bc->pre == NULL){

//             }

//         }
//     }
// }

// void multiply(node* a, node* b){

// }