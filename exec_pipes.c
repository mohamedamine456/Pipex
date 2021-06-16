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

void	exec_pipe(t_command *command, int in_file, int out_file, char **envp)
{
	t_exec_data e_data;

	e_data.stdout_fd = 0;
	e_data.pip_in = 0;
	e_data.tmp_cmd = 0;
	e_data.len = 0;
	e_data.child_state = 0;
	e_data.tmp_cmd = command;
	while (e_data.tmp_cmd != NULL)
	{
		fork_pipe(&e_data, in_file, out_file, envp);
		// waitpid(e_data.pid, &e_data.child_state, 0);
		// if (WIFEXITED(e_data.child_state))
		// {
		// 	//free_command
		// 	//reset files
		// 	exit(WEXITSTATUS(e_data.child_state));
		// }
		e_data.tmp_cmd = e_data.tmp_cmd->next;
		(e_data.len)++;
	}
	reset_files(e_data.stdin_fd, e_data.stdout_fd);
}

void	fork_pipe(t_exec_data *e_data, int in_file, int out_file, char **envp)
{
	pipe(e_data->fds);
	e_data->pid = fork();
	if (e_data->pid == 0)
	{
		if (e_data->len == 0)
		{
			dup_file(in_file, 0, &(e_data->stdin_fd));
			dup_pipe(0, e_data->fds);
		}
		else
		{
			dup_pipe(0, e_data->fds);
			dup_pipes(e_data->pip_in);
		}
		if (e_data->tmp_cmd->next == NULL)
		{
			dup_pipe(1, e_data->fds);
			dup_file(out_file, 1, &(e_data->stdout_fd));
		}
		e_data->tmp_cmd->name = replace_commands(e_data->tmp_cmd->name, envp);
		if (execve(e_data->tmp_cmd->name, e_data->tmp_cmd->args, envp) != 0)
			fatal_execve();
	}
	e_data->pip_in = e_data->fds[0];
	close(e_data->fds[1]);
}