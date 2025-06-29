#include<stdio.h>
#include<stdlib.h>

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

int ctwl_insert(CTWL* list, int val) {
	if (!list) return 0;
	TWN* node = (TWN*)malloc(sizeof(TWN));
	if (!node) return 0;
	node -> data = val;
	
	if(!list -> cur) {
	   node -> next = node -> prev = node;
	   list -> cur = node;
    } else {
       TWN* last = list -> cur -> prev;
       node -> next = list -> cur;
       node -> prev = last;
       last -> next = node;
       list -> cur -> prev = node;
	}
	list -> size++;
	return 1;
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
      	
      	if (!ctwl_insert(list_2, suma)) {
            while (list_2 -> size > 0) {
                TWN* temp = list_2 -> cur;
                temp -> prev -> next = temp -> next;
                temp -> next -> prev = temp -> prev;
                list_2 -> cur = temp -> next;
                free(temp);
                list_2 -> size--;
            }
            free(list_2);
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
    	ctwl_insert(list, val[i]);
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
	
	return 0;
}