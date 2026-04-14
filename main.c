#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

/**
 * main - simple shell
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int status;
	char *argv[2];
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		i = strlen(line) - 1;
		while (i >= 0 && isspace(line[i]))
		{
			line[i] = '\0';
			i--;
		}

		if (line[0] == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();

		if (pid == 0)
		{
			if (execve(line, argv, NULL) == -1)
			{
				perror("./hsh");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
