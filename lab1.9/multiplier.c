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
#include <sys/time.h>

#define ROW 2000
#define COL 2000
#define SIZE 4000000

long arrA[SIZE];
long arrB[SIZE];

int NUM_BUFFERS;

//Temp buffers
long *buffers;
long result[SIZE];
pthread_mutex_t *mutexes;
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
int saveResultMatrix(long *result);
long *getRow(int row, long *matrix);
long *getCol(int col, long *matrix);
int releaseLock(int lock);

int main(int argc, char *argv[]) {

	//Iteration variables
	long *pt;
	int i;
	int j;
	long dot;

	clock_t begin = clock();

	//Check NUM_BUFFERS
	printf("%s\n", argv[0]);
	NUM_BUFFERS = atoi(argv[1]);
	buffers = malloc(NUM_BUFFERS * sizeof(buffers[0]));
	for (i = 0; i < NUM_BUFFERS; i++) {
		buffers[i] = 0;
	}
	mutexes = malloc(NUM_BUFFERS * sizeof(mutexes[0]));
	for (i = 0; i < NUM_BUFFERS; i++) {
		buffers[i] = 0;
	}

	printf("Number of BUFFERS is %d\n", NUM_BUFFERS);
	mutexes = malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));
	for (i = 0; i < NUM_BUFFERS; i++) {
		pthread_mutex_init(&mutexes[i], NULL);
	}

	//Read file A
	pt = readMatrix("matA.dat");
	for (i = 0; i < SIZE; i++) {
		arrA[i] = *(pt + i);
	}
	//Read file B
	pt = readMatrix("matB.dat");
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
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent: %lf secs\n", time_spent);
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
			//printf("Number is: %ld\n", numberMatrix[i]);
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
		result[join_i] = dotResult;
		printf("thread %d gave %ld\n", join_i, dotResult);
	}
	saveResultMatrix(result);
	return result;
}

void *dotWrap(void *arguments) {
	struct arg_struct *args = arguments;
	//printf("im thread %d\n", args->id);
	int lock;
	lock = getLock();
	while (lock == -1) {
		lock = getLock();
	}
	buffers[lock] = dotProduct(&arrA[args->i * ROW], &arrB[args->j]);
	printf("The result of in [%d][%d] is %ld from thread %d\n", args->i,
			args->j, buffers[lock], args->id);
	result[args->i * ROW + args->j] = buffers[lock];
	releaseLock(lock);
	//printf("thread %d unlocked buffer %d\n", args->id, lock);
	pthread_exit((void*) result[args->i * ROW + args->j]);
}

int getLock(void) {
	int lock;
	int i;
	for (i = 0; i < NUM_BUFFERS; i++) {
		lock = pthread_mutex_trylock(&mutexes[i]);
		if (lock == 0) {
			//printf("free lock\n");
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock) {
	return pthread_mutex_unlock(&mutexes[lock]);
}

long *getRow(int row, long *matrix) {
	long *pt;
	pt = matrix;
	pt = pt + row;
	return pt;
}

long *getCol(int col, long *matrix) {
	long *pt;
	pt = matrix;
	for (int i = 0; i < COL; i++) {
		pt[i] = matrix[i + col];
	}
	return pt;
}

int saveResultMatrix(long *result) {
	printf("saving...");
	int status;
	FILE *f = fopen("result.dat", "w+");
	for (int i = 0; i < SIZE; i++) {
		printf("saving %ld...\n", result[i]);
		fprintf(f, "%ld\n", *(result + i));
	}
	fclose(f);

	return 0;
}

