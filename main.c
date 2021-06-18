#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int     fds[2];
    int     pid1;
    int     pid2;
    int     fd0;
    int     fd1;
    int     state_child1;
    int     state_child2;
    char    **cmd1;
    char    **cmd2;

    cmd1 = ft_split("/bin/ls", ' ');
    cmd2 = ft_split("/bin/echo hello", ' ');
    if (pipe(fds) == -1)
        perror("./main.c");
    pid1 = fork();
    if (pid1 == -1)
        perror("./main.c");
    if (pid1 == 0)
    {
        dup_file(open_file(argv[1], 0), 0, &fd0);
        close(fds[0]);
        dup2(fds[1], 1);
        close(fds[1]);
        if (execve(cmd1[0], cmd1, envp) == -1)
            fatal_execve();
    }
    pid2 = fork();
    if (pid2 == -1)
        perror("./main.c");
    if (pid2 == 0)
    {
        close(fds[1]);
        dup2(fds[0], 0);
        close(fds[0]);
        dup_file(open_file(argv[argc - 1], 1), 1, &fd1);
        if (strcmp(cmd2[0], "/bin/echo"))
            exit(127);
        if (execve(cmd2[0], cmd2, envp) == -1)
            fatal_execve();
    }
    close(fds[0]);
    close(fds[1]);
    waitpid(pid2, &state_child2, 0);
    if (WIFEXITED(state_child2))
	{
		//free_command
		//reset files
		exit(WEXITSTATUS(state_child2));
	}
}