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

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	/* ✅ handle direct path ONLY if '/' is present */
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	/* ✅ get PATH */
	path = get_path(env);
	if (!path || path[0] == '\0')
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

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
