/*
 * memory5b.c
 *
 *  Created on: Oct 15, 2018
 *      Author: root
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main5b(){
	char z = *(const char *)0;
	printf("I read from location zero");
	exit(EXIT_SUCCESS);
}
