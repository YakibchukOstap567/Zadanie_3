#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define CTWL_OK 1
#define CTWL_FAIL 0

typedef struct TWN{
    int data;
    struct TWN *prev;
    struct TWN *next;
} TWN;

typedef struct CTWL{
    TWN *cur;
    unsigned int size;
} CTWL;

CTWL *ctwl_create_empty(void) {
	CTWL* list = (CTWL*)malloc(sizeof(CTWL));
	if (!list) return NULL;
	list -> cur = NULL;
	list -> size = 0;
	return list;
}

void ctwl_destroy(CTWL* list) {
    if (!list || !list->cur) {
        free(list);
        return;
    }
    TWN* current = list->cur;
    for (unsigned int i = 0; i < list->size; i++) {
        TWN* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

TWN* ctwl_insert_left(CTWL* list, int val) {
	if (!list) return 0;
	TWN* node = (TWN*)malloc(sizeof(TWN));
	if (!node) return 0;
	node -> data = val;
	
	if(!list -> cur) {
	   node -> next = node -> prev = node;
	   list -> cur = node;
    } else {
       TWN* left = list -> cur -> prev;
       node -> next = list -> cur;
       node -> prev = left;
       left -> next = node;
       list -> cur -> prev = node;
	}
	list -> size++;
	return node;
}

TWN* ctwl_insert_right(CTWL* list, int val) {
	if (!list) return 0;
	TWN* node = (TWN*)malloc(sizeof(TWN));
	if (!node) return 0;
	node -> data = val;
	
	if(!list -> cur) {
	   node -> next = node -> prev = node;
	   list -> cur = node;
    } else {
       TWN* right = list -> cur -> next;
       node -> prev = list -> cur;
       node -> next = right;
       right -> prev = node;
       list -> cur -> next = node;
	}
	list -> size++;
	return node;
}

CTWL* ctwl_create_random(unsigned int size) {
    CTWL* list = ctwl_create_empty();
    if (!list) return NULL;
    srand((unsigned int)time(NULL));

    for (unsigned int i = 0; i < size; i++) {
        int val = rand() % 100;
        if (!ctwl_insert_right(list, val)) {
            ctwl_destroy(list);
            return NULL;
        }
    }
    return list;
}


void ctwl_print(CTWL *list) {
	if (!list || !list->cur) return;
    TWN *current = list->cur;
	for(unsigned int i = 0; i < list -> size; i++){
		printf("%d ", current -> data);
		current = current -> next;
	}
	printf("\n");
}

char ctwl_delete(CTWL* list) {
    if (!list || !list->cur) return CTWL_FAIL;
    TWN* targ = list->cur;

    if (list->size == 1) {
        free(targ);
        list->cur = NULL;
    } else {
        TWN* prev = targ->prev;
        TWN* next = targ->next;
        prev->next = next;
        next->prev = prev;
        list->cur = next;
        free(targ);
    }
    list->size--;
    return CTWL_OK;
}

void ctwl_cur_step_right(CTWL *list) {
    if (list && list->cur) {
        list->cur = list->cur->next;
    }
}

void ctwl_cur_step_left(CTWL *list) {
    if (list && list->cur) {
        list->cur = list->cur->prev;
    }
}

CTWL *ctwl_sum_demodulation(CTWL *list, unsigned int period) {
		
	if (!list || !list->cur || period == 0 || list->size % period != 0)
        return NULL;
	
	unsigned int n = list -> size;
	unsigned int result_size = n / period;
	
	CTWL* list_2 = ctwl_create_empty();
	if (!list_2) return NULL;
	
	TWN* current = list ->cur;
	
	for(unsigned int i = 0; i < result_size; i++){
	    int suma = 0;
		for(unsigned int j = 0; j < period; j++){
			suma += current -> data;
			current = current -> next;
      	}
      	
      	if (!ctwl_insert_left(list_2, suma)) {
            ctwl_destroy(list_2);
            return NULL;
        }
	}
	
	return list_2;
}

int main() {
    int	val[] = {1 ,2 ,3 ,4 ,5 ,6};
    int val_count = sizeof(val) / sizeof(val[0]);
    CTWL* list = ctwl_create_empty();
    for(int i = 0; i < val_count; i++){
    	ctwl_insert_left(list, val[i]);
	}
		
	puts("Povodny zoznam:\n");
	
	ctwl_print(list);
	
	CTWL* list_2 = ctwl_sum_demodulation(list, 2);
	
	if (list_2) {
		puts("Demodulovany zoznam (period = 2):\n");
		ctwl_print(list_2);
	} else {
		puts("Chyba: demodulacia zlyhala.\n");
	}
	
	ctwl_destroy(list);
    ctwl_destroy(list_2);
	
	return 0;
}