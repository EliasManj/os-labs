/*
 ============================================================================
 Name        : 9.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ROW 4
#define COL 4
#define SIZE 16

long arrA[SIZE];
long arrB[SIZE];
long arrA[SIZE];
long arrB[SIZE];

int NUM_BUFFERS;

//Temp buffers
long *buffers;
long result[SIZE];
pthread_mutex_t mutexes[6];
pthread_t threads[SIZE];

//Args
struct arg_struct {
	int i;
	int j;
	int id;
	long result;
};

long *readMatrix(char *filename);
long dotProduct(long *vec1, long *vec2);
long* multiply(long *matA, long *matB);
int getLock(void);
void *dotWrap(void *arguments);

int main(int argc, char *argv[]) {

	//Iteration variables
	long *pt;
	int i;
	int j;
	long dot;

	//Check NUM_BUFFERS
	printf("%s\n", argv[0]);
	NUM_BUFFERS = atoi(argv[1]);
	buffers = malloc(NUM_BUFFERS * sizeof(buffers[0]));
	for (i = 0; i < NUM_BUFFERS; i++) {
		buffers[i] = 0;
	}
	printf("Number of BUFFERS is %d\n", NUM_BUFFERS);

	//mutexes = malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));
	for (i = 0; i < NUM_BUFFERS; i++) {
		pthread_mutex_init(&mutexes[i], NULL);
	}

	//Read file A
	pt = readMatrix("matA16.dat");
	for (i = 0; i < SIZE; i++) {
		arrA[i] = *(pt + i);
	}
	//Read file B
	pt = readMatrix("matB16.dat");
	for (i = 0; i < SIZE; i++) {
		arrB[i] = *(pt + i);
	}
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			dot = dotProduct(&arrA[i * ROW], &arrB[j]);
			printf("The result of in [%d][%d] is %ld\n", i, j, dot);
		}
	}
	long *result_p;
	printf("Start multiplication\n");
	result_p = multiply(arrA, arrB);
	printf("Result");
	return 0;
}

long *readMatrix(char *filename) {
	FILE *file;
	static long numberMatrix[SIZE] = { 0 };
	int i;
	file = fopen(filename, "r");
	if (file) {
		for (i = 0; i < SIZE; i++) {
			fscanf(file, "%ld\n", &numberMatrix[i]);
		}
		for (i = 0; i < SIZE; i++) {
			printf("Number is: %ld\n", numberMatrix[i]);
		}
		fclose(file);
	} else {
		return 0;
	}
	return numberMatrix;
}

long dotProduct(long *vec1, long *vec2) {
	long sum = 0;
	int i;
	for (i = 0; i < ROW; i++) {
		sum += vec2[i * ROW] * vec1[i];
		printf("we multiply %ld times %ld\n", vec1[i], vec2[i * ROW]);
	}
	return sum;
}

long* multiply(long *matA, long *matB) {
	struct arg_struct args;
	long dotResult;
	int i;
	int j;
	int join_i;
	int index;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			index = ROW * i + j;
			args.i = i;
			args.j = j;
			args.id = index;
			pthread_create(&threads[index], NULL, &dotWrap, (void *) &args);
		}
	}
	for (join_i = 0; join_i < SIZE; join_i++) {
		pthread_join(threads[join_i], (void**) &(dotResult));
		printf("thread %d gave %ld\n",join_i, dotResult);
	}
	return result;
}

void *dotWrap(void *arguments) {
	struct arg_struct *args = arguments;
	printf("im thread %d\n", args->id);
	int lock;
	lock = getLock();
	if (lock == -1) {
		lock = 1;
	}
	buffers[lock] = dotProduct(&arrA[args->i * ROW], &arrB[args->j]);
	result[args->i*ROW+args->j] = buffers[lock];
	pthread_mutex_unlock(&mutexes[lock]);
	printf("thread %d unlocked a buffer\n", args->id);
	pthread_exit((void*) buffers[lock]);
}

int getLock(void) {
	int lock;
	int i;
	for (i = 0; i < NUM_BUFFERS; i++) {
		lock = pthread_mutex_trylock(&mutexes[i]);
		if (lock == 0) {
			printf("free lock\n");
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock){
	return pthread_mutex_unlock(&mutexes[lock]);
}


