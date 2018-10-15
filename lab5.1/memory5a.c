/*
 * memory5a.c
 *
 *  Created on: Oct 15, 2018
 *      Author: root
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main5a(){
	char *some_memory = (char *)0;
	printf("A read from null %s\n", some_memory);
	sprintf(some_memory, "A write to null\n");
	exit(EXIT_SUCCESS);
}
