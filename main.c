#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - simple shell
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL, *cmd;
	size_t len = 0;
	pid_t pid;
	int status;
	char *argv[2];

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

		/* remove newline */
		line[strcspn(line, "\n")] = '\0';

		/* skip leading spaces */
		cmd = line;
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;

		/* remove trailing spaces */
		int i = strlen(cmd) - 1;
		while (i >= 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
		{
			cmd[i] = '\0';
			i--;
		}

		/* ignore empty line */
		if (*cmd == '\0')
			continue;

		argv[0] = cmd;
		argv[1] = NULL;

		pid = fork();

		if (pid == 0)
		{
			if (execve(cmd, argv, NULL) == -1)
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
