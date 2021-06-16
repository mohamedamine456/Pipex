#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ft_split.c"

int main(int argc, char **argv, char **envp)
{
    int     fds[2];
    int     pid;
    int     fd0;
    int     fd1;
    int     child_state;
    char    **cmd1;
    char    **cmd2;

    cmd1 = ft_split("/bin/ls -la", ' ');
    cmd2 = ft_split("/usr/bin/grep file", ' ');
    if (pipe(fds) == -1)
        perror("./main.c");
    pid = fork();
    if (pid == -1)
        perror("./main.c");
    if (pid == 0)
    {
        close(fds[0]);
        dup2(fds[1], 1);
        close(fds[1]);
        execve(cmd1[0], cmd1, envp);
    }
    pid = fork();
    if (pid == -1)
        perror("./main.c");
    if (pid == 0)
    {
        close(fds[1]);
        dup2(fds[0], 0);
        close(fds[0]);
        execve(cmd2[0], cmd2, envp);
    }
    close(fds[0]);
    close(fds[1]);
    waitpid(pid, &child_state, 0);
    if (WIFEXITED(child_state))
	{
		//free_command
		//reset files
		exit(WEXITSTATUS(child_state));
	}
}