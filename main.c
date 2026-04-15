#include "shell.h"

/**
 * get_path - extract PATH from env
 * @env: environment variables
 * Return: PATH string or NULL
 */
char *get_path(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

/**
 * find_command - find executable in PATH
 * @cmd: command
 * @env: environment
 * Return: full path or NULL
 */
char *find_command(char *cmd, char **env)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;

	if (!cmd)
		return (NULL);

	if (stat(cmd, &st) == 0)
		return (strdup(cmd));

	path = get_path(env);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(cmd) + 2);
		if (!full_path)
			return (free(path_copy), NULL);

		sprintf(full_path, "%s/%s", token, cmd);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

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
