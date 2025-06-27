#include<stdio.h>
#include<stdlib.h>

typedef struct TWN{
    float data;
    struct TWN *prev;
    struct TWN *next;
}TWN;

typedef struct{
    TWN *cur;
    unsigned int size;
}CTWL;

CTWL *ctwl_create_empty(void){
	CTWL* list = (CTWL*)malloc(sizeof(CTWL));
	list -> cur = NULL;
	list -> size = 0;
}



CTWL *ctwl_sum_demodulation(CTWL *list, unsigned int period){
}

int main() {
    int	val[] = {1 ,2 ,3 ,4 ,5 ,6};
    int val_count = sizeof(val) / sizeof(val[0]);
    CTWL* list = ctwl_create_empty();
    for(int i = 0; i < val_count; i++){
    	
	}
}