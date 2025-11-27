
#ifndef _CCOLLECTIONS_H
#define _CCOLLECTIONS_H
#include<stdlib.h>
#include<string.h>
/*
 * TODO 
 * maybe get rid of data size for dyn_array 11/27/2025
 * See the efficiency and necessity of error codes
 *
 *
 *
 *
 *
 *
 *
 * */

/* FUNCTION: OBJECTIFY
 * objectifying doesn't work for static arrays, it overflows copying base 
 * address capturing size of array bytes.
 */

// error codes
#define CC_OK 0
#define CC_HEAP_OVERFLOW 1


#define BOX(data) objectify(data,sizeof(data))
void *objectify(void *stack_object,int data_size) {
	void *heap_object = malloc(data_size);
	memcpy(heap_object,&stack_object,data_size);
	return heap_object;
}

#ifdef DYN_ARRAY_IMPLEMENTATION
#include<stdbool.h>
typedef struct _Dyn_Array {
	void **data;
	int loc;
	int size;
	int data_size;
}Dyn_Array, *PDyn_Array;

void resize(PDyn_Array array) {
	array->size*=2;
	array->data = realloc(array->data,array->size *sizeof(void*));
}

void *dyn_array_get(PDyn_Array array,int index) {
	if (index < array->loc) {
		return array->data[index];
	}
	return 0;
}

void dyn_array_add(Dyn_Array *array,void *data) {
	if(array->loc >= array->size) {
		resize(array);
	}
	array->data[array->loc++] = data;
}

PDyn_Array dyn_array_create_array(int size,int data_size) {
	if(size <= 0) return 0;
	PDyn_Array array = malloc(sizeof(Dyn_Array));
	array->size = size;
	array->data = malloc(data_size *size);
	array->loc = 0;
	array->data_size = data_size;
	return array;
}

void *dyn_array_remove_index(PDyn_Array array,int index) {
	if(index < 0 || index >= array->size) return 0;
	void *item = array->data[index];
	array->data[index] = 0;
	for(int i = index; i < array->loc; ++i) {
		array->data[i] = array->data[i+1];
	}
	array->loc-=1;
	return item;
}

void* dyn_array_remove_item(PDyn_Array array,void *item,bool(*equals)(void*,void*)) {
	if(item) {
		for(int i = 0; i < array->loc; ++i) {
			if(equals(item,array->data[i])) {
				return dyn_array_remove_index(array,i);
			}
		}
	}
	return 0;
}

void dyn_array_free(PDyn_Array array) {
	for(int i = 0; i < array->size; ++i){
		free(array->data[i]);
	}
	free(array->data);
}
#endif // DYN_ARRAY_IMPLEMENTATION
 
#ifdef LINKED_LIST_IMPLEMENTATION
typedef struct _Node {
	void *data;
	void *next;
} Node, *PNode;

typedef struct _Linked_List {
	PNode head;
	int size;
	int data_size;
} Linked_List, *PLinked_list;

PLinked_List linked_list_create(int data_size) {
	PLinked_List list = malloc(sizeof(Linked_List));
	list->size = 0;
	list->head = 0;
	list->data_size = data_size;
}

// TODO do the cool linked list trick from csc 329 in the case of the size being 0, I think it is for deletion
void linked_list_add_first(PLinked_List list,void *item) {
	PNode n = malloc(sizeof(Node));
	if(!n) return;
	node->data = item;
	node->next = list->head;
	list->head = node;
}

#endif // LINKED_LIST_IMPLEMENTATION

#ifdef ARRAY_SORTING_IMPLEMENTATION
static void max_heapify_sink(void *arr,int root, int heap_size,int member_size,int (*comparator)(void*,void*));
void build_max_heap(void *arr,int length,int member_size, int (*comparator)(void*,void*));

void heap_sort(void *arr, int length,int member_size,int (*comparator)(void*,void*)) {
	build_max_heap(arr,length,member_size,comparator);
	void *temp = malloc(member_size);
	for(int i = length; i > 1; --i) {
		memcpy(temp,arr,member_size);
		memcpy(arr,arr+(i-1)*member_size,member_size);
		memcpy(arr+(i-1)*member_size,temp,member_size);
		max_heapify_sink(arr,0,i-1,member_size,comparator);
	}
	free(temp);
}

static void max_heapify_sink(void *arr,int root, int heap_size,int member_size, int (*comparator)(void*,void*)) {
	int left = root*2+1;
	int right = root*2+2;
	int greatest = root;
	if(left < heap_size && comparator(arr+left*member_size,arr+root*member_size) >=1) {
		greatest = left;
	}
	if(right < heap_size && comparator(arr+right*member_size,arr+greatest*member_size) >=1) {
		greatest = right;
	}
	if(greatest != root) {
		void *temp = malloc(member_size);
		memcpy(temp,arr+root*member_size,member_size);
		memcpy(arr+root*member_size,arr+greatest*member_size,member_size);
		memcpy(arr+greatest*member_size,temp,member_size);
		free(temp);
		max_heapify_sink(arr,greatest,heap_size,member_size,comparator);
	}
}
void build_max_heap(void *arr,int length,int member_size,int (*comparator)(void*,void*)) {
	for(int i = (length-1)/2; i >= 0; --i) {
		max_heapify_sink(arr,i,length,member_size,comparator);
	}
}
#endif // ARRAY_SORTING_IMPLEMENTATION
#endif // _CCOLECTIONS_H
