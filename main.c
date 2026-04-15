#include "shell.h"

/**
 * main - simple shell
 * @ac: argument count
 * @av: argument vector
 * @env: environment
 * Return: exit status
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL, *cmd_path;
	size_t len = 0;
	ssize_t read;
	char *args[100];
	int status = 0;
	int i;
	pid_t pid;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(status);
		}

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		i = 0;
		args[i] = strtok(line, " ");
		while (args[i] && i < 99)
			args[++i] = strtok(NULL, " ");
		args[i] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(status);
		}

		cmd_path = find_command(args[0], env);

		if (!cmd_path)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
			status = 127;
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, args, env) == -1)
			{
				perror(av[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}

		free(cmd_path);
	}

	free(line);
	return (status);
}
