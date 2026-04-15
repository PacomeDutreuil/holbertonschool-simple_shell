#include "shell.h"

char **parse_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 100);
	if (!args)
		return (NULL);

	token = strtok(line, " ");
	while (token && i < 99)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	return (args);
}
