#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

int modulus(int numerator, int denominator) {
	return numerator - denominator * (numerator / denominator);
}

int strcmp2(char *array1, char *array2) {
	int i;
	int response = 0;
	i = 0;
	while (array1[i] == array2[i] && response == 0) {
		if (array1[i] == '\0' || array2[i] == '\0') {
			response = 1;
		}
		i++;
	}
	return response;
}

int main(void) {

	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char user_input[MAX_LINE / 2 + 1];
	char history[10][MAX_LINE / 2 + 1];
	int cmd_count = 0;
	int cmd_count_total = 0;

	int should_run = 1;
	pid_t pid;

	while (should_run) {
		printf("osh>");
		fflush(stdout);
		//Get the user input
		fgets(user_input, MAX_LINE, stdin);
		printf("The user typed %s\n", user_input);
		//Check for !!
		if (user_input[0] == '!' && user_input[1] == '!'
				&& user_input[2] == '\n') {
			strcpy(user_input, history[cmd_count - 1]);
		}
		//Check for !N
		else if (isdigit(user_input[1]) && user_input[0] == '!'
				&& user_input[2] == '\n') {
			int n = (int) user_input[1] - '0';
			strcpy(user_input, history[cmd_count - n]);
		} else {
			//Check for history
			if (strcmp2(user_input, "history\n")) {
				if (cmd_count_total >= 10) {
					int index = 10;
					for (int i = cmd_count_total; i > cmd_count_total - 10;
							i--) {
						printf("%d: %s\n", i, history[index-- - 1]);
					}
				} else {
					for (int i = cmd_count_total; i > 0;
							i--) {
						printf("%d: %s\n", i, history[i - 1]);
					}
				}
			}
			strcpy(history[cmd_count++], user_input);
			cmd_count = modulus(cmd_count, 10);
			cmd_count_total++;
		}
		int i = 0;
		//Separate the arguments
		char *token = strtok(user_input, " ");
		while (token != NULL) {
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		//Remove \n char from last argument
		char *ptr;
		ptr = strtok(args[i - 1], " \n");
		while (ptr) {
			ptr = strtok(NULL, " \n");
		}
		//Check for & character
		char last_str[strlen(args[i - 1])];
		strcpy(last_str, args[i - 1]);
		int parent_wait = strcmp(last_str, "&");
		//Fork a child process
		pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
		} else if (pid > 0) {
			//Wait for child to finish
			if (parent_wait) {
				int status = 0;
				wait(&status);
			}
		}

	}

	return 0;
}

