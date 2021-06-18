/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:08:09 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/14 17:34:44 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_pipe(t_command *command, char *infile, char *outfile, char **envp)
{
	int 		fds[2];
	int			pid1;
	int			pid2;
	int			fd0;
	int			fd1;
	int			child_state2;

	if (pipe(fds) == -1)
		fatal("pipe function failed!");
	pid1 = fork();
	if (pid1 == -1)
		fatal("fork function failed!");
	else if (pid1 == 0)
	{
		dup_file(open_file(infile, STDIN), STDIN, &fd0);
		close(fds[0]);
		dup2(fds[1], STDOUT);
		close(fds[1]);
		command->name = replace_commands(command->name, envp);
		if (execve(command->name, command->args, envp) == -1)
			fatal_execve();
	}
	pid2 = fork();
	if (pid2 == -1)
		fatal("fork function failed!");
	else if (pid2 == 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN);
		close(fds[0]);
		dup_file(open_file(outfile, STDOUT), STDOUT, &fd1);
		command->next->name = replace_commands(command->next->name, envp);
		if (execve(command->next->name, command->next->args, envp) == -1)
			fatal_execve();
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid2, &child_state2, 0);
	if (WIFEXITED(child_state2))
	{
		ft_free_command(&command);
		reset_files(fd0, fd1);
		exit(WEXITSTATUS(child_state2));
	}
}