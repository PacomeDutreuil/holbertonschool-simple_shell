#include "shell.h"

int execute_command(char *cmd_path, char **args, char **env, char *prog)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, env) == -1)
		{
			perror(prog);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}

	return (status);
}
