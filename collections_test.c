
#define DYN_ARRAY_IMPLEMENTATION
#include"ccollections.h"
#include<stdio.h>


int main(int argc, char **argv) {
	PDyn_Array int_arr = dyn_array_create_array(5,sizeof(int));
	dyn_array_add(int_arr,objectify((void*)1,sizeof(int)));
	dyn_array_add(int_arr,objectify((void*)2,sizeof(int)));
	dyn_array_add(int_arr,objectify((void*)6,sizeof(int)));
	dyn_array_add(int_arr,objectify((void*)90,sizeof(int)));

	for(int i = 0; i < int_arr->loc; ++i) {
		printf("%d\n",*((int*)int_arr->data[i]));
	}
	printf("done successfully!\n");
return 0;
}
