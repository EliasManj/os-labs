/*
 * memory4.c
 *
 *  Created on: Oct 15, 2018
 *      Author: root
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define ONE_K (1024)

int main4(){
	char *some_memory;
	char *scan_ptr;
	some_memory = (char *)malloc(ONE_K);
	if(some_memory == NULL) exit(EXIT_FAILURE);
	scan_ptr = some_memory;
	while(1){
		*scan_ptr = '\0';
		scan_ptr++;
	}
	exit(EXIT_SUCCESS);
}
