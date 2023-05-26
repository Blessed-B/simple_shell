#include "shell.h"

#define MAX_LINE 80

int main(void)
{
	char *args[MAX_LINE / 2 + 1];
	char line[MAX_LINE];
	int should_run = 1;
	pid_t pid;

	while (should_run)
	{
		printf("simple_shell> ");
		fflush(stdout);

		fgets(line, MAX_LINE, stdin);
		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
		{
			should_run = 0;
			continue;
		}

		args[0] = line;
		args[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
