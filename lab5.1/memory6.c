/*
 * memory6.c
 *
 *  Created on: Oct 15, 2018
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main(){
	char *some_memory;
	int exit_code = EXIT_FAILURE;
	some_memory = (char *)malloc(ONE_K);
	if(some_memory != NULL){
		free(some_memory);
		printf("Memory allocaed and freed again\n");
		exit_code = EXIT_SUCCESS;
	}
	exit(exit_code);
}
