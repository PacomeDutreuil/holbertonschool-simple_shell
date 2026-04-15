#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * find_path - find command in PATH
 * @cmd: command
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy, *dir;
	static char full_path[1024];

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		sprintf(full_path, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/*
main - simple shell with PATH 
Return: 0
 */
int main(void)
{
	char *line = NULL, *cmd, *path_cmd;
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

		cmd = line;
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;

		i = strlen(cmd) - 1;
		while (i >= 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
		{
			cmd[i] = '\0';
			i--;
		}

		if (*cmd == '\0')
			continue;

		argv[0] = cmd;
		argv[1] = NULL;

		/* si chemin direct */
		if (strchr(cmd, '/'))
		{
			if (access(cmd, X_OK) != 0)
			{
				perror("./hsh");
				continue;
			}
			path_cmd = cmd;
		}
		else
		{
			path_cmd = find_path(cmd);
			if (path_cmd == NULL)
			{
				perror("./hsh");
				continue;
			}
		}

		pid = fork();

		if (pid == 0)
		{
			execve(path_cmd, argv, NULL);
			perror("./hsh");
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
