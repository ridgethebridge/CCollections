
#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H
#include<stdbool.h>

typedef struct _Dyn_Array {
	void **data;
	int loc;
	int size;
	int data_size;
}Dyn_Array, *PDyn_Array;
void add(PDyn_Array array,void* data);
void resize(PDyn_Array array);
Dyn_Array create_array(int length,int data_size);
void *remove_index(PDyn_Array array,int index);
void *remove_item(PDyn_Array array,void *item,bool (*equals)(void*,void*));


#endif
