#include "shell.h"

int handle_exit(char **args, char *line, int status)
{
    if (strcmp(args[0], "exit") == 0)
    {
        free(line);
        free_args(args);
        exit(status);
    }
    return (0);
}
