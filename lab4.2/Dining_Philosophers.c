/*
 ============================================================================
 Name        : Dining_Philosophers.c
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

#define N_FORKS 6
#define N_PHILOSOPHERS 6

pthread_t philosophers[N_PHILOSOPHERS];
pthread_mutex_t forks[N_FORKS];

void *thread_fn(void *param);
void pickup_forks(int philosopher_number);
void return_forks(int philosopher_number);

int main(void) {
	int i, k, j;

	//Create mutexes
	printf("Creating mutexes\n");
	for (i = 0; i < N_FORKS; i++) {
		k = pthread_mutex_init(&forks[i], NULL);
		if (k == -1) {
			printf("Mutex init failed...");
			exit(1);
		}
	}

	//Create threads
	printf("Creating threads\n");
	for (i = 0; i < N_PHILOSOPHERS; i++) {
		k = pthread_create(&philosophers[i], NULL, &thread_fn, (void *) i);
		if (k == -1) {
			printf("Pthread create failed...");
			exit(1);
		}
	}

	//Join threads
	printf("Joining threads\n");
	for (j = 0; j < N_PHILOSOPHERS; j++) {
		k = pthread_join(philosophers[j], NULL);
		if (k != 0) {
			printf("Pthread join failed...");
			exit(1);
		}
	}

	//Destroy mutexes
	printf("Destroying mutexes\n");
	for (i = 0; i < N_FORKS; i++) {
		k = pthread_mutex_destroy(&forks[i]);
		if (k != 0) {
			printf("Mutex failed...");
			exit(1);
		}
	}

	return EXIT_SUCCESS;
}

void *thread_fn(void *param) {
	int pn =  (int) param;
	printf("Philosopher %d is thinking...\n", pn);
	sleep(1);
	pickup_forks(pn);
	sleep(1);
	return_forks(pn);
	return 0;
}

void pickup_forks(int philosopher_number) {
	pthread_mutex_lock(&forks[philosopher_number]);
	pthread_mutex_lock(&forks[(philosopher_number + 1) % N_FORKS]);
	printf("Philosopher %d is eating\n", philosopher_number);
}

void return_forks(int philosopher_number) {
	pthread_mutex_unlock(&forks[philosopher_number]);
	pthread_mutex_unlock(&forks[(philosopher_number + 1) % N_FORKS]);
	printf("Philosopher %d finished eating\n", philosopher_number);
}
