/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:08:09 by mlachheb          #+#    #+#             */
/*   Updated: 2021/06/13 17:11:43 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_fork(t_exec_data *e_data, char *out_file, char **envp)
{
	pipe(e_data->fds);
	e_data->pid = fork();
	if (e_data->pid == 0)
	{
		if (e_data->len == 0)
			dup_pipe(0, e_data->fds);
		else
		{
			dup_pipe(0, e_data->fds);
			dup_pipes(e_data->pip_in);
		}
		if (e_data->tmp_cmd->next == NULL)
		{
			dup_pipe(1, e_data->fds);
			open_file(out_file, 1, &(e_data->stdout_fd));
		}
		execve(e_data->tmp_cmd->name, e_data->tmp_cmd->args, envp);
	}
	e_data->pip_in = e_data->fds[0];
	close(e_data->fds[1]);
	e_data->tmp_cmd = e_data->tmp_cmd->next;
	(e_data->len)++;
}

void	exec_pipes(t_command *command, char **envp,
		char *in_file, char *out_file)
{
	t_exec_data	e_data;

	e_data.stdout_fd = 0;
	e_data.pip_in = 0;
	e_data.tmp_cmd = command;
	e_data.len = 0;
	if (open_file(in_file, 0, &(e_data.stdin_fd)) == -1)
		fatal_file(&command, in_file);
	while (e_data.tmp_cmd != NULL)
	{
		pipe_fork(&e_data, out_file, envp);
	}
	reset_files(e_data.stdin_fd, e_data.stdout_fd);
}