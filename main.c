#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int 	fds[2];
	int 	pid;
	char	**cmd1;
	char	**cmd2;

	pipe(fds);
	cmd1 = ft_split("/bin/ls -la", ' ');
	cmd2 = ft_split("/usr/bin/grep file", ' ');
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execve(cmd1[0], cmd1, envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		execve(cmd2[0], cmd2, envp);
	}
	close(fds[0]);
	close(fds[1]);
}
