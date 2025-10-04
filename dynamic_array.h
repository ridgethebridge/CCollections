
#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

int add(Dyn_Array* array,void* data, int size);
void resize(PDyn_array array);
Dyn_Array create_array(int length, int data_size);
void *remove_index(PDyn_array array,int index);
void *remove_item(PDyn_array array,void *item);
typedef struct _Dyn_Array {
	void **data;
	int loc;
	int data_size;
	int size;
}Dyn_Array, *PDyn_array;





#endif
