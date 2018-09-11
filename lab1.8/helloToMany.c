/**
 * A simple pthread program illustrating POSIX scheduling.
 *
 * Figure 6.8
 *
 * To compile:
 *
 *	gcc posix-sched.c -o posix-sched -lpthread
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

/* the thread runs in this function */
void *runner(void *param);

struct thread_struct {
	long id;
	int thread_number;
};

int main(int argc, char *argv[]) {
	int i, scope;
	pthread_t tid[NUM_THREADS]; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	struct thread_struct current_thread_info;

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* first inquire on the current scope */
	if (pthread_attr_getscope(&attr, &scope) != 0)
		fprintf(stderr, "Unable to get scheduling scope.\n");
	else {
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS\n");
		else if (scope == PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD_SCOPE_SYSTEM\n");
		else
			fprintf(stderr, "Illegal scope value.\n");
	}

	/* set the scheduling algorithm to PCS or SCS */
	if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0)
		printf("unable to set scheduling policy.\n");

	/* create the threads */
	for (i = 0; i < NUM_THREADS; i++) {
		current_thread_info.thread_number = i;
		current_thread_info.id = (long) &tid[i];
		printf("I am thread 1, created thread with id (%ld) on iteration %d\n",
				(long) &tid[i], i);
		pthread_create(&tid[i], &attr, runner, (void *) &current_thread_info);
	}

	/**
	 * Now join on each thread
	 */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tid[i], NULL);

	return 0;
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) {
	/* do some work ... */
	struct thread_struct *args = param;
	printf("hello its me, thread %d with id %ld\n", args->thread_number, args->id);
	pthread_exit(0);
}
