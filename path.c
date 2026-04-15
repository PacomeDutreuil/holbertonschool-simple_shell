#include "shell.h"

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
