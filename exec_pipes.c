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

void	first_command(t_command *command, char *infile, char **envp, t_exec_data *edata)
{
	edata->pid1 = fork();
	if (edata->pid1 == -1)
		fatal("fork function failed!");
	else if (edata->pid1 == 0)
	{
		dup_file(open_file(infile, STDIN), STDIN, &(edata->fd0));
		close(edata->fds[0]);
		dup2(edata->fds[1], STDOUT);
		close(edata->fds[1]);
		command->name = replace_commands(command->name, envp);
		if (execve(command->name, command->args, envp) == -1)
			fatal_execve();
	}
}

void	second_command(t_command *command, char *outfile, char **envp, t_exec_data *edata)
{
	edata->pid2 = fork();
	if (edata->pid2 == -1)
		fatal("fork function failed!");
	else if (edata->pid2 == 0)
	{
		close(edata->fds[1]);
		dup2(edata->fds[0], STDIN);
		close(edata->fds[0]);
		dup_file(open_file(outfile, STDOUT), STDOUT, &(edata->fd1));
		command->next->name = replace_commands(command->next->name, envp);
		if (execve(command->next->name, command->next->args, envp) == -1)
			fatal_execve();
	}
}

void	exec_pipe(t_command *command, char *infile, char *outfile, char **envp)
{
	t_exec_data edata;

	if (pipe(edata.fds) == -1)
		fatal("pipe function failed!");
	first_command(command, infile, envp, &edata);
	second_command(command, outfile, envp, &edata);
	close(edata.fds[0]);
	close(edata.fds[1]);
	waitpid(edata.pid1, &edata.child_state1, 0);
	waitpid(edata.pid2, &edata.child_state2, 0);
	if (WIFEXITED(edata.child_state2))
	{
		ft_free_command(&command);
		reset_files(edata.fd0, edata.fd1);
		exit(WEXITSTATUS(edata.child_state2));
	}
}