#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void) {
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char user_input[MAX_LINE];
	int should_run = 1;
	pid_t pid;

	while (should_run) {
		printf("osh>");
		fgets(user_input, MAX_LINE, stdin);
		//fflush(stdout);
		printf("The user typed %s\n", user_input);

		int i;
		char *token = strtok(user_input, " ");
		while (token != NULL) {
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		char *ptr;
		ptr = strtok(args[i-1], " \n");
		while (ptr) {
			ptr = strtok(NULL, " \n");
		}
		pid = fork();
		if (pid == 0) {
			printf("Excecuting command from child process\n");
			execvp(args[0], args);
		}

		int status = 0;
		wait(&status);

		/**
		 * After reading user input, the steps are:
		 * (1) fork a child process
		 * (2) the child process will invoke execvp()
		 * (3) if command did not include &, parent will invoke wait()
		 */
	}

	return 0;
}

