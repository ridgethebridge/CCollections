
#include"dynamic_array.h"
#include<stdlib.h>

void resize(PDyn_Array array) {
	array->size*=2;
	array->data = realloc(array->data,array->size *sizeof(void*));
}

void add(Dyn_Array *array,void *data) {
	if(array->loc >= array->size) {
		resize(array);
	}
	array->data[array->loc] = data;
	array->loc+=1;
}

Dyn_Array create_array(int size,int data_size) {
	Dyn_Array array = {.size = size,.data = 0,.loc = 0,.data_size=data_size};
	return array;
}
void *remove_index(PDyn_Array array,int index) {
	if(index < 0 || index >= array->size) return 0;
	void *item = *(array->data +(sizeof(void*)*array->loc));
	array->data[index] = 0;
	for(int i = index; i < array->loc; ++i) {
		array->data[i] = array->data[i+1];
	}
	array->loc-=1;
	return item;
}

void *remove_item(PDyn_Array array,void *item,bool (*equals)(void*,void*)) {
	if(item) {
		for(int i = 0; i < array->loc; ++i) {
			if(equals(item,array->data[i])) {
				return remove_index(array,i);
			}
		}
	}
	return 0;
}




