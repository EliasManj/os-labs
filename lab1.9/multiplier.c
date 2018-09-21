#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ROW 2000
#define COL 2000
#define SIZE 4000000
#define NUM_BUFFERS 40

long **buffers[NUM_BUFFERS];
pthread_mutex_t mutexes[NUM_BUFFERS];
pthread_t threads[ROW];
long *result;
long *matA;
long *matB;

struct MatStruct {
	long row;
	long *matA_pt;
	long *matB_pt;
	long *result;
};

long *readMatrix(char *filename);
void printMatrix(long *mat_pt);
long *getColumn(int col, long *matrix);
void printColumn(long *col);
void printRow(long *row);
long *getRow(int row, long *matrix);
int getLock(void);
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2);
int saveResultMatrix(long *result);
long *multiply(long* matA, long* matB);
void *row_mul(void *args);
long *test(void);

int main(void) {
	printf("Reading file A\n");
	matA = readMatrix("matA.dat");
	printf("Reading file B\n");
	matB = readMatrix("matB.dat");
	printf("begin multiplication");
	clock_t begin = clock();
	/*
	 printMatrix(matA);
	 printMatrix(matB);
	 //Testing
	 long *col0;
	 col0 = getColumn(0, matA);
	 printColumn(col0);
	 long *row0;
	 row0 = getRow(0, matA);
	 printRow(row0);
	 long result0;
	 result0 = dotProduct(row0, col0);

	 long *col1;
	 long *row1;
	 long result1;
	 row1 = getRow(1, matA);
	 col1 = getColumn(1, matA);
	 result1 = dotProduct(row1, col1);
	 */
	long *result;

	result = multiply(matA, matB);
	saveResultMatrix(result);

	clock_t end = clock();
	double time_spent = (double)(end- begin)/CLOCKS_PER_SEC;
	printf("time spent: %lf\n", time_spent);
	return EXIT_SUCCESS;
}

long *multiply(long *matA, long *matB) {
	int i;
	int j;
	int index;
	int rv;
	static long *result;
	long *row_result_pt;
	result = malloc(SIZE * sizeof(long));
	for (i = 0; i < ROW; i++) {
		rv = pthread_create(&threads[i], NULL, &row_mul, (void *) i);
		if (rv != 0) {
			perror("failed to create child thread");
			return 0;
		}
	}
	for (j = 0; j < ROW; j++) {
		pthread_join(threads[j], (long *) &row_result_pt);
		for (index = 0; index < COL; index++) {
			*(result + ((j * COL) + index)) = *(row_result_pt + index);
		}

	}
	return result;
}

void *row_mul(void *args) {
	long *row;
	long *col;
	long *result_vec;
	int row_n = (int) args;
	int lock;
	int i;
	printf("calculating row %d\n", row_n);
	result_vec = malloc(ROW * sizeof(long));
	row = getRow(row_n, matA);
	lock = getLock();
	while (lock == -1) {
		lock = getLock();
	}
	buffers[lock] = &result_vec;
	for (i = 0; i < ROW; i++) {
		col = getColumn(i, matB);
		*(*buffers[lock] + i) = dotProduct(row, col);
	}
	buffers[lock] = 0;
	releaseLock(lock);
	return (void *) result_vec;
}

long *test(void) {
	long *row;
	long *col;
	int i;
	long *pt;
	pt = malloc(ROW * sizeof(long));
	buffers[0] = &pt;
	row = getRow(0, matA);
	for (i = 0; i < ROW; i++) {
		col = getColumn(i, matB);
		*(*buffers[0] + i) = dotProduct(row, col);
	}
	return pt;
}

void printMatrix(long *mat_pt) {
	int i;
	int j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf("[%d][%d] = %ld\n", i, j, *(mat_pt + (i * ROW) + j));
		}
	}
}

void printColumn(long *col) {
	int j;
	printf("[");
	for (j = 0; j < COL; j++) {
		printf("%d:%ld, ", j, *(col + j));
	}
	printf("]\n");
}

void printRow(long *row) {
	int j;
	printf("[");
	for (j = 0; j < ROW; j++) {
		printf("%d:%ld, ", j, *(row + j));
	}
	printf("]\n");
}

long *readMatrix(char *filename) {
	FILE *file;
	int i;
	long *matrix;
	matrix = malloc(SIZE * sizeof(long));
	file = fopen(filename, "r");
	if (file) {
		for (i = 0; i < SIZE; i++) {
			fscanf(file, "%ld\n", &matrix[i]);
		}
		fclose(file);
	} else {
		return 0;
	}
	return matrix;
}

long *getColumn(int col, long *matrix) {
	static long *column;
	column = malloc(COL * sizeof(long));
	int j;
	for (j = 0; j < COL; j++) {
		column[j] = matrix[(j * ROW) + col];
	}
	return column;
}

long *getRow(int row, long *matrix) {
	long *row_list;
	row_list = malloc(ROW * sizeof(long));
	int i;
	for (i = 0; i < ROW; i++) {
		row_list[i] = matrix[(row * ROW) + i];
	}
	return row_list;
}

int getLock(void) {
	int lock;
	int i;
	for (i = 0; i < NUM_BUFFERS; i++) {
		lock = pthread_mutex_trylock(&mutexes[i]);
		if (lock == 0) {
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock) {
	return pthread_mutex_unlock(&mutexes[lock]);
}

long dotProduct(long *vec1, long *vec2) {
	int i;
	int result;
	result = 0;
	for (i = 0; i < ROW; i++) {
		result += vec1[i] * vec2[i];
	}
	return result;
}

int saveResultMatrix(long *result) {
	printf("saving...\n");
	FILE *f = fopen("result.dat", "w+");
	for (int i = 0; i < SIZE; i++) {
		//printf("saving %ld...\n", result[i]);
		fprintf(f, "%ld\n", *(result + i));
	}
	fclose(f);

	return 0;
}



