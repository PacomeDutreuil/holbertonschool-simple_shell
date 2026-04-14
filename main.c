#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - simple shell
 *
 * Return: 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    pid_t pid;
    int status;
    char *argv[2];

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("($) ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        /* remove newline */
        line[strcspn(line, "\n")] = '\0';

        argv[0] = line;
        argv[1] = NULL;

        pid = fork();

        if (pid == 0)
        {
            if (execve(line, argv, NULL) == -1)
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
