#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

void parse_input(char *args[], char user_input[]) {
	int i;
	char *token = strtok(user_input, " ");
	while (token != NULL) {
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	printf("the first arg is %s\n", args[0]);
}

int main(void) {
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char user_input[MAX_LINE];
	int should_run = 1;

	while (should_run) {
		printf("osh>");
		fgets(user_input, MAX_LINE, stdin);
		fflush(stdout);
		printf("The user typed %s\n", user_input);
		parse_input(args, user_input);
		/**
		 * After reading user input, the steps are:
		 * (1) fork a child process
		 * (2) the child process will invoke execvp()
		 * (3) if command did not include &, parent will invoke wait()
		 */
	}

	return 0;
}
