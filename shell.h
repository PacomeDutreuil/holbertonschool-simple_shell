#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* PATH */
char *get_path(char **env);
char *find_command(char *cmd, char **env);

/* EXEC */
int execute_command(char *cmd_path, char **args, char **env, char *prog);

/* PARSE */
char **parse_line(char *line);

/* UTILS */
void free_args(char **args);

#endif
